#include "world/item/Item.hpp"

Item& Item::setAllowOffhand(bool allowOffhand) {
    mAllowOffhand = allowOffhand;
    return *this;
}
/*
bool Item::hasTag(const HashedString& tag) const {
    for (const auto& t : mTags) {
        if (t.getHash() == tag.getHash()) return true; // Assuming ItemTag can provide HashedString hash
    }
    return false;
}*/