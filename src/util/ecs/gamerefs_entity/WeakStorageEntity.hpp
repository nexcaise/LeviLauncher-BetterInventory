#pragma once
#include "util/gamerefs/WeakRef.hpp"
#include "world/entity/EntityId.hpp"

class EntityRegistry;

class WeakStorageEntity {
public:
	WeakRef<EntityRegistry> mRegistry;
	EntityId mEntity;
};