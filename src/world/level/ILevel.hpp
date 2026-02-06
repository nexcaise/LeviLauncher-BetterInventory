/// @symbolgeneration
#pragma once
#include "world/level/GameType.hpp"
#include "world/phys/HitResult.hpp"

class ILevel {
public:
    virtual GameType getDefaultGameType() const;
    virtual BlockPalette& getBlockPalette() const;
    virtual bool isClientSide() const;
    virtual HitResult& getHitResult();
    virtual HitResult& getLiquidHitResult();
};