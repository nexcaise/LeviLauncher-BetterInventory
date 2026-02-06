/// @symbolgeneration
#pragma once
//#include "amethyst/Imports.hpp"
#include "world/Container.hpp"

class ListTag;
class SemVersion;
class Level;

/// @vptr {0x4DE56F8}
class FillingContainer : public Container {
public:
	/** @sig {48 8D 15 ? ? ? ? 48 8B CF E8 ? ? ? ? 48 8B 5C 24 ? B0} */
	static SemVersion PLAYER_UI_CONTAINER_UNVERSIONED;

    std::vector<ItemStack> mItems;
    Player* mPlayer;

public:
    FillingContainer(Player* player, int size, ContainerType type);

public:
    /// @vidx {inherit}
    virtual ~FillingContainer();
    /// @vidx {inherit}
    virtual void serverInitItemStackIds(int, int, std::function<void(int, const ItemStack&)>) override;
    /// @vidx {inherit}
    virtual const ItemStack& getItem(int slot) const override;
    /// @vidx {inherit}
    virtual void setItem(int slot, const ItemStack& item) override;
    /// @vidx {inherit}
    virtual void setItemWithForceBalance(int, const ItemStack&, bool) override;
    /// @vidx {inherit}
    virtual void removeItem(int, int) override;
    /// @vidx {inherit}
    virtual int getContainerSize() const override;
    /// @vidx {inherit}
    virtual int getMaxStackSize() const override;
    /// @vidx {inherit}
    virtual void startOpen(Player&) override;
    /// @vidx {41}
    virtual void add(ItemStack& item);
    /// @vidx {42}
    virtual bool canAdd(const ItemStack& item);
    /// @vidx {43}
    virtual void clearSlot(int slot);
    /// @vidx {44}
    virtual void clearInventory(int size);
    /// @vidx {45}
    virtual void load(const ListTag& tag, const SemVersion& version, Level& level);

	/** @sig {E8 ? ? ? ? 90 48 8B 45 ? 4C 89 7D ? 48 89 45} */
	std::unique_ptr<ListTag> save();
};

// 1.21.0.3
//static_assert(sizeof(FillingContainer) - sizeof(Container) == 32);