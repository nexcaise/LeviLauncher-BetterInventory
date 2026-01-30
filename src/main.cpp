#include <jni.h>
#include <android/log.h>
#include <dlfcn.h>
#include <cstdint>
#include <sys/mman.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <thread>

#include "util/ItemStackBase.h"
#include "pl/Gloss.h"

#define LOG_TAG "HmmAja"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,  LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

class ShulkerBoxBlockItem;

using Fn =
    void (*)(void*, ItemStackBase*, void*, std::string&, bool);

static Fn g_orig = nullptr;
static int g_index = -1;

static void hookFn(
    ShulkerBoxBlockItem* self,
    ItemStackBase* stack,
    void* level,
    std::string& out,
    bool flag
) {
    LOGI("VALID HIT index=%d self=%p", g_index, self);
    out.append("\n§7[Hooked]");
    g_orig(self, stack, level, out, flag);
}

static bool hookOnce() {
    void* h = dlopen("libminecraftpe.so", RTLD_NOLOAD);
    if (!h) h = dlopen("libminecraftpe.so", RTLD_LAZY);
    if (!h) return false;

    uintptr_t libStart = 0, libEnd = 0;
    std::ifstream maps("/proc/self/maps");
    std::string line;

    while (std::getline(maps, line)) {
        if (line.find("libminecraftpe.so") != std::string::npos &&
            line.find("r-xp") != std::string::npos) {
            sscanf(line.c_str(), "%lx-%lx", &libStart, &libEnd);
            break;
        }
    }

    if (!libStart || !libEnd) return false;

    const char* name = "19ShulkerBoxBlockItem";
    uintptr_t zts = 0;
    size_t len = strlen(name);

    std::ifstream maps2("/proc/self/maps");
    while (std::getline(maps2, line)) {
        if (line.find("libminecraftpe.so") == std::string::npos) continue;
        if (line.find("r--p") == std::string::npos) continue;

        uintptr_t s, e;
        if (sscanf(line.c_str(), "%lx-%lx", &s, &e) != 2) continue;

        for (uintptr_t p = s; p < e - len; p++) {
            if (memcmp((void*)p, name, len) == 0) {
                zts = p;
                break;
            }
        }
        if (zts) break;
    }

    if (!zts) return false;

    uintptr_t zti = 0;
    std::ifstream maps3("/proc/self/maps");
    while (std::getline(maps3, line)) {
        if (line.find("libminecraftpe.so") == std::string::npos) continue;
        if (line.find("r--p") == std::string::npos) continue;

        uintptr_t s, e;
        if (sscanf(line.c_str(), "%lx-%lx", &s, &e) != 2) continue;

        for (uintptr_t p = s; p < e; p += sizeof(void*)) {
            if (*(uintptr_t*)p == zts) {
                zti = p - sizeof(void*);
                break;
            }
        }
        if (zti) break;
    }

    if (!zti) return false;

    uintptr_t vtable = 0;
    std::ifstream maps4("/proc/self/maps");
    while (std::getline(maps4, line)) {
        if (line.find("libminecraftpe.so") == std::string::npos) continue;
        if (line.find("r--p") == std::string::npos) continue;

        uintptr_t s, e;
        if (sscanf(line.c_str(), "%lx-%lx", &s, &e) != 2) continue;

        for (uintptr_t p = s; p < e; p += sizeof(void*)) {
            if (*(uintptr_t*)p == zti) {
                vtable = p + sizeof(void*);
                break;
            }
        }
        if (vtable) break;
    }

    if (!vtable) return false;

    uintptr_t* vt = (uintptr_t*)vtable;

    for (int i = 0; i < 120; i++) {
        uintptr_t fn = vt[i];
        if (!fn) break;
        if (fn < libStart || fn > libEnd) continue;

        g_orig = (Fn)fn;
        g_index = i;

        uintptr_t page = ((uintptr_t)&vt[i]) & ~(4095UL);
        mprotect((void*)page, 4096, PROT_READ | PROT_WRITE);
        vt[i] = (uintptr_t)&hookFn;
        mprotect((void*)page, 4096, PROT_READ);

        LOGI("HOOK TRY index=%d fn=%p", i, (void*)fn);
        return true;
    }

    return false;
}

static void hookLoop() {
    for (int i = 0; i < 10; i++) {
        if (hookOnce()) {
            LOGI("HOOK INSTALLED, open inventory now");
            return;
        }
        sleep(1);
    }
    LOGE("HOOK FAILED");
}

__attribute__((constructor))
void Init() {
    LOGI("Init");
    GlossInit(true);
    std::thread(hookLoop).detach();
}