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

WeakPtr<BlockLegacy> ItemStackBase::getLegacyBlock() const
{
    if (mItem && mItem->mLegacyBlock) {
        return mItem->mLegacyBlock;
    }

    return WeakPtr<BlockLegacy>();
}

bool ItemStackBase::isNull() const {
    if (!mValid) 
        return true;
    Item* item = mItem.get();

    if (!item || item->mFullName != HashedString("minecraft:air")) {
        if (mCount != 0 || mBlock != nullptr || mAuxValue != 0) 
            return false;
        if (item || mUserData != 0 || mCanDestroyHash != 0 || mCanPlaceOnHash != 0) 
            return false;
    }

    return true;
}