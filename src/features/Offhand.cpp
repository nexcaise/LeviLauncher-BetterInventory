#include "features/Offhand.hpp"
//#include "util/Logger.hpp"

pl::log::Logger log("OffhandMod");
//Example: log.info("JNI call {}", 42);

//class GameMode
/*
using useItemOnFn = InteractionResult(*)(
        VanillaItems*,
        ItemStack&,
        BlockPos const&,
        uchar,
        Vec3 const&,
        Block const*,
        bool
);*/

using useItemOnFn = InteractionResult(*)(
        void*,
        ItemStack&,
        void*,
        void*,
        void*,
        void*,
        bool
);

static useItemOnFn useItemOn_orig = nullptr;

InteractionResult* useItemOn_hook(
        void* self,
        ItemStack& stack,
        void* at,
        void* face,
        void* hit,
        void* tb,
        bool isFirstEvent
) {
    const Item *item = stack.getItem();
    bool realMayUse = stack.mItem == nullptr;//!stack.mValid || stack.mItem == nullptr || stack.isNull() ||/* stack.mCount == 0 || !isSimTick ||*/ !item/* || item->canUseOnSimTick()*/;

    if (!realMayUse)
    {
        log.info("May not use item: {}", stack);
        return orig(self,stack,at,face,hit,tb,isFirstEvent);
    }
    
    log.info("item.setAllowOffhand(true);");
    item->setAllowOffhand(true);

    return orig(self,stack,at,face,hit,tb,isFirstEvent);

}

void OffhandHooks()
{
    uintptr_t useItemOn_addr = pl::signature::pl_resolve_signature(
        "EC 13 40 F9 E8 03 16 AA",
        "libminecraftpe.so"
    );
    if (!addr) {
        log.error("Signature not found");
        return;
    }
    log.info("Signature found at: {}", (void*)addr);
    int useItemOn_ret = DobbyHook(
        (void*)useItemOn_addr,
        (void*)useItemOn_hook,
        (void**)&useItemOn_orig
    );
    if (useItemOn_ret == 0) {
        log.info("DobbyHook success");
    } else {
        log.error("DobbyHook failed: {}", useItemOn_ret);
    }
}