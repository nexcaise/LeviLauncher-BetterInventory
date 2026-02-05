#include "world/level/block/BlockLegacy.hpp"

bool BlockLegacy::hasProperty(BlockProperty prop) const
{
    return (mProperties & (uint64_t)prop) != 0;
}

bool BlockLegacy::isSnappableBlock() const
{
    if (hasProperty(BlockProperty::CubeShaped)) return true;
    if (hasProperty(BlockProperty::Stair)) return true;
    if (hasProperty(BlockProperty::HalfSlab)) return true;
    if (isFenceBlock()) return true;
    if (isFenceGateBlock()) return true;
    if (isWallBlock()) return true;

    return false;
}

bool BlockLegacy::isAir() const
{
    return mNameInfo.mFullName == HashedString("minecraft:air");
}