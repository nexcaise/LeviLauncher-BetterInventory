#pragma once
#include "world/phys/Vec3.hpp"

class AABB {
public:
    Vec3 min;
    Vec3 max;

public:
    AABB();
    AABB(Vec3 min, Vec3 max);
    AABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);

    static AABB BLOCK_SHAPE;
};