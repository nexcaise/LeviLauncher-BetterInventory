/// @symbolgeneration
#pragma once
#include <unordered_map>
#include "SharedPtr.hpp"
#include "Item.hpp"
#include <vector>

class ItemRegistry {
public:
    std::vector<SharedPtr<Item>> mItemRegistry;
    std::unordered_map<int, WeakPtr<Item>> mIdToItemMap;
};