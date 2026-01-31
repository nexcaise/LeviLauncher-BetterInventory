#pragma once
#include <memory>
#include <unordered_map>
#include "SharedPtr.hpp"
#include "Item.hpp"

class ItemRegistry;

class StringHash {
public:
    int mHash;
    bool operator==(StringHash const& o) const { return mHash == o.mHash; }
};

namespace std {
template<>
struct hash<StringHash> {
    size_t operator()(StringHash const& s) const noexcept {
        return std::hash<int>()(s.mHash);
    }
};
}

class ItemRegistryRef {
public:
    std::weak_ptr<ItemRegistry> mWeakRegistry;
    std::weak_ptr<ItemRegistry> mItemRegistry;

    inline std::unordered_map<StringHash, WeakPtr<Item>> const& getNameToItemMap() const {
        return _lockRegistry()->mNameToItemMap;
    }

    inline std::shared_ptr<ItemRegistry> _lockRegistry() const {
        auto sp = mWeakRegistry.lock();
        if (!sp) sp = mItemRegistry.lock();
        return sp;
    }
};