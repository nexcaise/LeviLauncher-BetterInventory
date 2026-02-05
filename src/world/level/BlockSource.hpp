/// @symbols
#pragma once
#include <functional>
#include <optional>
#include <vector>
#include <thread>
/* 
#include <amethyst/Memory.hpp>
#include <mc/src-deps/core/headerIncludes/gsl_includes.hpp>
#include <mc/src-deps/core/utility/optional_ref.hpp>*/
#include "world/level/BlockPos.hpp"
/*#include <mc/src/common/world/phys/AABB.hpp>
#include <mc/src/common/CommonTypes.hpp>
#include <mc/src/common/world/level/material/MaterialType.hpp>
#include <mc/src/common/world/level/block/GetCollisionShapeInterface.hpp>
#include <mc/src/common/world/phys/HitResult.hpp>
#include <mc/src/common/world/entity/EntityContext.hpp>
#include <mc/src/common/world/level/Level.hpp>
#include <mc/src/common/world/phys/ShapeType.hpp>
#include <mc/src-deps/core/utility/AutomaticID.hpp>
#include <mc/src/common/world/level/chunk/ChunkSource.hpp>
#include <mc/src/common/world/actor/ActorType.hpp>

namespace BlockSourceVisitor { struct CollisionShape {}; }

// Auto-generated: Forward declarations
*/
class Block;
/*class BlockActor;
class Vec3;
class Material;
class LevelChunk;
struct Bounds;
class Actor;
class GameEvent;
class BlockSourceListener;
struct ActorBlockSyncMessage;
class ChunkPos;
class ItemStackBase; 
class Dimension;

class IConstBlockSource {
};
*/
#pragma pack(push, 8)
class BlockSource /*: public IConstBlockSource */{
public:
/*    std::byte padding8_enableSharedPadding[16]; // std::bit_cast not working with inheriting from std::enable_shared_from_this
    const std::thread::id mOwnerThreadID;
    const bool mAllowUnpopulatedChunks;
    const bool mPublicSource;
    bool mCheckValidity;
    Level* mLevel;
    ChunkSource* mChunkSource;
    Dimension* mDimension;
    const Height mMaxHeight;
    const Height mMinHeight;
    std::byte padding60[272 - 60];
*/
public:
    //virtual ~BlockSource();
    
    virtual const Block& getLiquidBlock(const BlockPos& p) const;
    virtual const Block& getBlock(int x, int y, int z) const;
    virtual const Block& getBlock(const BlockPos& pos) const; // 16
    virtual const Block& getBlock(const BlockPos& pos, unsigned int layer) const;
};
#pragma pack(pop)

//static_assert(sizeof(BlockSource) == 272);