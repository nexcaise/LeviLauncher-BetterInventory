#pragma once
#include "world/inventory/transaction/InventorySource.hpp"
#include "world/item/ItemStack.hpp"
#include "world/inventory/network/NetworkItemStackDescriptor.hpp"

class InventoryAction {
public:
    InventorySource mSource;
    unsigned int mSlot;
    NetworkItemStackDescriptor mFromItemDescriptor;
    NetworkItemStackDescriptor mToItemDescriptor;
    ItemStack mFromItem;
    ItemStack mToItem;

    InventoryAction(InventorySource source, unsigned int slot, const ItemStack& fromItem, const ItemStack& toItem)
        : mSource(source), mSlot(slot), mFromItemDescriptor(fromItem), mToItemDescriptor(toItem), mFromItem(fromItem), mToItem(toItem) {}
};