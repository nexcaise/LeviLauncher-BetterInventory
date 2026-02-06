#pragma once
#include <memory>
class ItemRegistry;

class ItemRegistryRef {
public:
    virtual std::shared_ptr<ItemRegistry> _lockRegistry() const;
};
