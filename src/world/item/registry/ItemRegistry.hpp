/// @symbolgeneration
#pragma once
//#include <amethyst/Imports.hpp>
#include <unordered_map>
#include "util/SharedPtr.hpp"
#include "world/item/Item.hpp"

class ItemRegistry : public std::enable_shared_from_this<ItemRegistry> {
public:
    std::unordered_map<int, WeakPtr<Item>> mIdToItemMap;
};