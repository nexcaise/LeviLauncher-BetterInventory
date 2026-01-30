#include <jni.h>
#include <android/log.h>
#include <dlfcn.h>
#include <cstring>
#include <cstdint>
#include <sys/mman.h>
#include <unistd.h>
#include <fstream>
#include <string>

#include "util/ItemStackBase.h"
#include "pl/Gloss.h"

#define LOG_TAG "HmmAja"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,  LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

class ShulkerBoxBlockItem;

using Shulker_appendHover_t =
    void (*)(void*, ItemStackBase*, void*, std::string&, bool);

static Shulker_appendHover_t g_ShulkerBoxBlockItem_appendFormattedHovertext_orig = nullptr;

static void ShulkerBoxBlockItem_appendFormattedHovertext_hook(
    ShulkerBoxBlockItem* self,
    ItemStackBase* stack,
    void* level,
    std::string& out,
    bool flag
) {
    LOGI("HOOK CALLED self=%p stack=%p", self, stack);
    out.append("\n§7[Hooked appendFormattedHovertext]");
    g_ShulkerBoxBlockItem_appendFormattedHovertext_orig(
        self, stack, level, out, flag
    );
}

static bool findAndHookShulkerBoxBlockItem() {
    LOGI("Start hook");

    void* mcLib = dlopen("libminecraftpe.so", RTLD_NOLOAD);
    if (!mcLib) mcLib = dlopen("libminecraftpe.so", RTLD_LAZY);
    if (!mcLib) {
        LOGE("dlopen failed");
        return false;
    }

    uintptr_t libBase = 0;
    std::ifstream maps("/proc/self/maps");
    std::string line;

    while (std::getline(maps, line)) {
        if (line.find("libminecraftpe.so") != std::string::npos &&
            line.find("r-xp") != std::string::npos) {
            sscanf(line.c_str(), "%lx-%*lx", &libBase);
            break;
        }
    }

    if (!libBase) {
        LOGE("lib base not found");
        return false;
    }

    LOGI("lib base = 0x%lx", libBase);

    const char* typeName = "19ShulkerBoxBlockItem";
    size_t nameLen = strlen(typeName);
    uintptr_t typeNameAddr = 0;

    std::ifstream maps2("/proc/self/maps");
    while (std::getline(maps2, line)) {
        if (line.find("libminecraftpe.so") == std::string::npos) continue;
        if (line.find("r--p") == std::string::npos &&
            line.find("r-xp") == std::string::npos) continue;

        uintptr_t start, end;
        if (sscanf(line.c_str(), "%lx-%lx", &start, &end) != 2) continue;

        for (uintptr_t addr = start; addr < end - nameLen; addr++) {
            if (memcmp((void*)addr, typeName, nameLen) == 0) {
                typeNameAddr = addr;
                break;
            }
        }
        if (typeNameAddr) break;
    }

    if (!typeNameAddr) {
        LOGE("ZTS not found");
        return false;
    }

    LOGI("ZTS = 0x%lx", typeNameAddr);

    uintptr_t typeInfoAddr = 0;
    std::ifstream maps3("/proc/self/maps");

    while (std::getline(maps3, line)) {
        if (line.find("libminecraftpe.so") == std::string::npos) continue;
        if (line.find("r--p") == std::string::npos) continue;

        uintptr_t start, end;
        if (sscanf(line.c_str(), "%lx-%lx", &start, &end) != 2) continue;

        for (uintptr_t addr = start; addr < end - sizeof(void*); addr += sizeof(void*)) {
            if (*(uintptr_t*)addr == typeNameAddr) {
                typeInfoAddr = addr - sizeof(void*);
                break;
            }
        }
        if (typeInfoAddr) break;
    }

    if (!typeInfoAddr) {
        LOGE("ZTI not found");
        return false;
    }

    LOGI("ZTI = 0x%lx", typeInfoAddr);

    uintptr_t vtableAddr = 0;
    std::ifstream maps4("/proc/self/maps");

    while (std::getline(maps4, line)) {
        if (line.find("libminecraftpe.so") == std::string::npos) continue;
        if (line.find("r--p") == std::string::npos) continue;

        uintptr_t start, end;
        if (sscanf(line.c_str(), "%lx-%lx", &start, &end) != 2) continue;

        for (uintptr_t addr = start; addr < end - sizeof(void*); addr += sizeof(void*)) {
            if (*(uintptr_t*)addr == typeInfoAddr) {
                vtableAddr = addr + sizeof(void*);
                break;
            }
        }
        if (vtableAddr) break;
    }

    if (!vtableAddr) {
        LOGE("vtable not found");
        return false;
    }

    LOGI("VTABLE = 0x%lx", vtableAddr);

    uintptr_t* slot53 = (uintptr_t*)(vtableAddr + 53 * sizeof(void*));
    LOGI("vtable[53] before = %p", (void*)(*slot53));

    g_ShulkerBoxBlockItem_appendFormattedHovertext_orig =
        (Shulker_appendHover_t)(*slot53);

    uintptr_t page = ((uintptr_t)slot53) & ~(4095UL);
    if (mprotect((void*)page, 4096, PROT_READ | PROT_WRITE) != 0) {
        LOGE("mprotect RW failed");
        return false;
    }

    *slot53 = (uintptr_t)&ShulkerBoxBlockItem_appendFormattedHovertext_hook;

    mprotect((void*)page, 4096, PROT_READ);

    LOGI("vtable[53] after = %p", (void*)(*slot53));
    LOGI("HOOK SUCCESS");
    return true;
}

__attribute__((constructor))
void Init() {
    LOGI("Init called");
    GlossInit(true);
    if (!findAndHookShulkerBoxBlockItem())
        LOGE("Hook FAILED");
}