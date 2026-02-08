#include <pl/Gloss.h>
#include "world/item/registry/ItemRegistryRef.hpp"
#include "world/item/Item.hpp"
#include "world/item/registry/ItemRegistry.hpp"
#include "util/Hooks.hpp"
#include "util/Logger.hpp"

#include <string>

class BaseGameVersion;
class Experiments;
namespace cereal { struct ReflectionCtx; }
class VanillaItems;

using TargetFn = void(*)(
        VanillaItems*,
        const cereal::ReflectionCtx&,
        const ItemRegistryRef,
        const BaseGameVersion&,
        const Experiments&
);

static TargetFn orig = nullptr;

void hook(
        VanillaItems* self,
        const cereal::ReflectionCtx& uk,
        const ItemRegistryRef itemRegistry,
        const BaseGameVersion& baseGameVersion,
        const Experiments& experiments
) {
    getLogger().info("Hook Function Called");
    getLogger().info("Calling Original Function...");
    orig(self, uk, itemRegistry, baseGameVersion, experiments);
    
    getLogger().info("trying patch item...");
    ItemRegistry* registry = itemRegistry._lockRegistry().get();
    for (auto& pair : registry->mIdToItemMap)
    {
        pair.second.get()->setAllowOffhand(true);
    }
    getLogger().info("Success!");
}

class ShulkerBoxBlockItem;
class ItemStackBase;

using Shulker_appendHover_t = void (*)(void*, ItemStackBase*, void*, std::string&, bool);

inline Shulker_appendHover_t ShulkerBoxBlockItem_appendFormattedHovertext_orig = nullptr;

inline void ShulkerBoxBlockItem_appendFormattedHovertext_hook(
    ShulkerBoxBlockItem* self,
    ItemStackBase* stack,
    void* level,
    std::string& out,
    bool flag)
{
    out += "\n Hooked!!!!!!";
    if (ShulkerBoxBlockItem_appendFormattedHovertext_orig) ShulkerBoxBlockItem_appendFormattedHovertext_orig(self, stack, level, out, flag);
}

class ItemStack;

using FoodItemFn = int(*)(
        void*,
        ItemStack*
);

static FoodItemFn FoodItem_getUseDuration_orig = nullptr;

int FoodItem_getUseDuration_hook(
        void* self,
        ItemStack* stack
) {
    int original_d = FoodItem_getUseDuration_orig(self, stack);
    return original_d * 10;
}

void RegisterHooks() {
    HOOK(
        "FD 7B BA A9 FC 6F 01 A9 FA 67 02 A9 F8 5F 03 A9 F6 57 04 A9 F4 4F 05 A9 FD 03 00 91 FF 07 40 D1 FF 83 00 D1 48 D0 3B D5 EA 83 00 B2",
        (void*)hook,
        (void**)&orig
    );
    VHOOK(
        "19ShulkerBoxBlockItem",
        55,
        (void*)ShulkerBoxBlockItem_appendFormattedHovertext_hook,
        (void**)&ShulkerBoxBlockItem_appendFormattedHovertext_orig
    );
    HOOK(
        "_ZNK8FoodItem14getUseDurationERK9ItemStack",
        (void*)FoodItem_getUseDuration_hook,
        (void**)&FoodItem_getUseDuration_orig
    );
};

__attribute__((constructor))
void Init() {
    GlossInit(true);
    RegisterHooks();
}