#pragma once
#include "util/ecs/WeakEntityRef.hpp"
#include "world/Facing.hpp"
#include "world/level/BlockPos.hpp"
#include "world/phys/Vec3.hpp"

enum class HitResultType : int {
    TILE = 0x0,
    ENTITY = 0x1,
    ENTITY_OUT_OF_RANGE = 0x2,
    NO_HIT = 0x3,
};

class HitResult {
public:
    Vec3 mStartPos;
    Vec3 mRayDir;
    HitResultType mType;
    FacingID mFacing;
    BlockPos mBlock;
    Vec3 mPos;
    WeakEntityRef mEntity;
    bool mIsHitLiquid;
    FacingID mLiquidFacing;
    BlockPos mLiquid;
    Vec3 mLiquidPos;
    bool mIndirectHit;
};