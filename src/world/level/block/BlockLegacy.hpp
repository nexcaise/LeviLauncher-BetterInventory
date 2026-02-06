#include <string>
#include "util/StringHash.hpp"

#include "world/level/block/GetCollisionShapeInterface.hpp"
#include "util/optional_ref.hpp"
#include "world/level/block/BlockProperty.hpp"

class BlockItem;
class BlockPos;
class BlockSource;
class Block;

class BlockLegacy {

    struct NameInfo {
        HashedString mRawName;
        std::string mNamespaceName;
        HashedString mFullName;
        HashedString mPreFlatteningName;
    };

public:
    BlockLegacy::NameInfo mNameInfo;
    uint64_t mProperties;

    bool isSnappableBlock() const;
    bool isAir() const;

    virtual const Block& getRenderBlock() const;
    virtual AABB getCollisionShape(const Block& unk0, const BlockSource& unk1, const BlockPos& unk2, optional_ref<const GetCollisionShapeInterface> unk3) const;
    virtual bool canContainLiquid() const;
    virtual bool isFenceBlock() const;
	virtual bool isFenceGateBlock() const;
	virtual bool isWallBlock() const;
	virtual bool canBeBuiltOver(BlockSource& unk0, const BlockPos& unk1, const BlockItem& unk2) const;
	virtual bool canBeBuiltOver(BlockSource& unk0, const BlockPos& unk1) const;
};