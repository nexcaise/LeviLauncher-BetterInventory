/// @symbolgeneration
#pragma once

#include <memory>
#include "world/level/ILevel.hpp"

class Level : public ILevel/*, public BlockSourceListener, public IWorldRegistriesProvider*/ {
public:
    bool isClientSide;
};

// 1.21.0.3
/*
static_assert(offsetof(Level, mPacketSender) == 2864);
static_assert(offsetof(Level, isClientSide) == 5520);
static_assert(offsetof(Level, mTrimPatternRegistry) == 2680);
static_assert(offsetof(Level, mTrimMaterialRegistry) == 2696);*/