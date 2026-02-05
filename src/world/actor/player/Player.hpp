#pragma once
#include <memory>

#include "world/level/BlockSource.hpp"

#include "world/entity/EntityContext.hpp"
#include "world/level/ILevel.hpp"
#include "world/actor/player/PlayerInventory.hpp"

#include "world/level/dimension/Dimension.hpp"

class Player {
public:
    PlayerInventory* playerInventory;
    ILevel* mLevel;
    EntityContext mEntityContext;
    std::weak_ptr<Dimension> mDimension
    
    const LayeredAbilities& getAbilities() const;
    bool canUseOperatorBlocks() const;
    bool isCreative() const;
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
};