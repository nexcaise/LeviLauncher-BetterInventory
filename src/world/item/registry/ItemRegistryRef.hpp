#pragma once
#include <memory>
class ItemRegistry;

class ItemRegistryRef {
public:
    std::weak_ptr<ItemRegistry> mItemRegistry;
    
    std::weak_ptr<ItemRegistry> mWeakRegistry;

    std::shared_ptr<ItemRegistry> _lockRegistry() const;
};
