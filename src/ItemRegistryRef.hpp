#pragma once
#include <memory>
#include <unordered_map>
#include "SharedPtr.hpp"
#include "Item.hpp"
//#include "StringHash.hpp"

class ItemRegistry;

class StringHash {
public:
    int mHash;

    StringHash(const char* str) : 
        mHash(StringToNameId(str)) 
    {
    }

    StringHash(const std::string& str) :
        mHash(StringToNameId(str)) 
    {
    }
};

class ItemRegistryRef {
public:
    std::weak_ptr<ItemRegistry> mWeakRegistry;
    std::weak_ptr<ItemRegistry> mItemRegistry;
    
    std::unordered_map<StringHash, WeakPtr<Item>> const& getNameToItemMap() const;

    std::shared_ptr<ItemRegistry> _lockRegistry() const;
};
