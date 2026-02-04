#pragma once
#include "world/item/ItemStack.hpp"

class Inventory {
public:
    virtual const ItemStack& getItem(int slot) const;
};