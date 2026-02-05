
class BlockItem;
class BlockPos;
class BlockSource;

class BlockLegacy {
public:
	virtual bool canBeBuiltOver(BlockSource& unk0, const BlockPos& unk1, const BlockItem& unk2) const;
	virtual bool canBeBuiltOver(BlockSource& unk0, const BlockPos& unk1) const;
};