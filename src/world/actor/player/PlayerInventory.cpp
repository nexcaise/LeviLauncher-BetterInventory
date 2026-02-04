#include "world/actor/player/PlayerInventory.hpp"

const ItemStack& PlayerInventory::getSelectedItem() const
{
    if (mSelectedContainerId != ContainerID::CONTAINER_ID_INVENTORY) {
        return ItemStack::EMPTY_ITEM;
    }

    return mInventory->getItem(mSelected);
}