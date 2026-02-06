#pragma once
#include "util/NonOwnerPointer.hpp"
#include "util/gamerefs/StackRefResult.hpp"

class EntityRegistry;

class IEntityRegistryOwner : public Bedrock::EnableNonOwnerReferences {
protected:
    virtual ~IEntityRegistryOwner();
public:
    virtual StackRefResult<const EntityRegistry> getEntityRegistry() const;
    virtual StackRefResult<EntityRegistry> getEntityRegistry();
};