#pragma once
#include <memory>

#include "world/level/BlockSource.hpp"

#include "world/entity/EntityContext.hpp"
#include "world/level/ILevel.hpp"
#include "world/actor/player/PlayerInventory.hpp"

#include "world/level/dimension/Dimension.hpp"
#include "world/entity/components/StateVectorComponent.hpp"

struct BuiltInActorComponents {
    gsl::not_null<StateVectorComponent*> mStateVectorComponent;
};

class Player {
public:
    InventoryTransactionManager mTransactionManager;
    PlayerInventory* playerInventory;
    ILevel* mLevel;
    EntityContext mEntityContext;
    std::weak_ptr<Dimension> mDimension
    BuiltInActorComponents mBuiltInComponents;
    std::unique_ptr<ItemStackNetManagerBase> mItemStackNetManager;
    
    bool isClientSide() const;
    const LayeredAbilities& getAbilities() const;
    bool canUseOperatorBlocks() const;
    Vec3* getPosition() const;
    bool isCreative() const;
    virtual void swing();
    const BlockSource& getDimensionBlockSourceConst() const;
    BlockSource& getDimensionBlockSource() const;
    
    template <typename T>
    const T* tryGetComponent() const
    {
        const auto& registry = mEntityContext.getRegistry();
        return registry.try_get<T>(mEntityContext.mEntity);
    }

    template <typename T>
    T* tryGetComponent()
    {
        auto& registry = mEntityContext.getRegistry();
        return registry.try_get<T>(mEntityContext.mEntity);
    }
    
     template <typename T>
    bool hasComponent() const
    {
        const auto& registry = mEntityContext.getRegistry();
        return registry.all_of<T>(mEntityContext.mEntity);
    }

    template <typename T, typename... Args>
    T& addComponent(Args&&... args)
    {
        auto& registry = mEntityContext.getRegistry();
        //Assert(!registry.all_of<T>(mEntityContext.mEntity), "Entity already has component");
        return registry.emplace<T>(mEntityContext.mEntity, std::forward<Args>(args)...);
    }
};