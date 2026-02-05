#include "world/item/ItemStackBase.hpp"

Item* ItemStackBase::getItem() const {
    return mItem.get();
}

bool ItemStackBase::isInstance(const HashedString& itemName, bool useItemLookup) const
{
    if (!mItem) return false;
    return mItem->mFullName == itemName;
}

bool ItemStackBase::hasTag(const HashedString& tag) const
{
    return mItem && mItem->hasTag(tag);
}