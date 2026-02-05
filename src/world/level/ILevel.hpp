/// @symbolgeneration
#pragma once
#include "world/level/GameType.hpp"

class ILevel {
public:
    virtual GameType getDefaultGameType() const;
};