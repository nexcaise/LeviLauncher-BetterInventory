#pragma once
#include "util/gamerefs/gamerefs_shareptr/OwnerStorageSharePtr.hpp"

template <typename T>
struct SharePtrRefTraits {
    typedef T StackRef;
    typedef OwnerStorageSharePtr<T> OwnerStorage;
    typedef SharePtrRefTraits<T>::StackRef OwnerStackRef;
};