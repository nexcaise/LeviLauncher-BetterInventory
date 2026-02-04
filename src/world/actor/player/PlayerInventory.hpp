#pragma once
#include <cstdint>
#include <unordered_set>
#include <deque>
#include <string>
#include <functional>
#include "world/item/ItemStack.hpp"
#include "world/actor/player/Inventory.hpp"

enum class ContainerID : unsigned char {
    CONTAINER_ID_NONE = 0xFF,
    CONTAINER_ID_INVENTORY = 0x0,
    CONTAINER_ID_FIRST = 0x1,
    CONTAINER_ID_LAST = 0x64,
    CONTAINER_ID_OFFHAND = 0x77,
    CONTAINER_ID_ARMOR = 0x78,
    CONTAINER_ID_SELECTION_SLOTS = 0x7A,
    CONTAINER_ID_PLAYER_ONLY_UI = 0x7C,
};

class PlayerInventory {
public:
    std::unique_ptr<Inventory> mInventory;

    const ItemStack& getSelectedItem() const;
};