#pragma once
#include <world/level/BlockPos.hpp>

class NetworkBlockPosition : public BlockPos {
public:
	NetworkBlockPosition() : BlockPos() {}
    NetworkBlockPosition(const BlockPos& other) : BlockPos(other) {}
};