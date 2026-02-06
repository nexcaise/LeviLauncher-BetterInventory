#pragma once

#include <string>
#include "world/item/ItemStackBase.hpp"
#include "util/StringHash.hpp"

class Actor;
class FacingID;
class ItemTag : public HashedString {

};

class Item {
public:
    WeakPtr<BlockLegacy> mLegacyBlock;
    bool mAllowOffhand;
	Item& setAllowOffhand(bool allowOffhand);
	std::string mNamespace;
	HashedString mFullName;
	std::vector<ItemTag> mTags;
	
	bool hasTag(const HashedString& tag) const;
	virtual bool canUseOnSimTick() const;
	virtual bool calculatePlacePos(ItemStackBase& stack, Actor& actor, FacingID& face, BlockPos& pos) const;
};