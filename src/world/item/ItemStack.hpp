#pragma once
#include "world/item/Item.hpp"
#include "world/item/ItemStackBase.hpp"

class ItemStackNetIdVariant;
class BlockPalette;
class NetworkItemStackDescriptor;

class ItemStack : public ItemStackBase {
public:
    static ItemStack fromDescriptor(const NetworkItemStackDescriptor& descriptor, BlockPalette& palette, bool isClientSide );

    ItemStackNetIdVariant* mNetIdVariant;
    
    InteractionResult useOn(Actor&, int, int, int, FacingID, const Vec3&);
};