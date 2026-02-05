#pragma once

#include "util/gamerefs/GameRefs.hpp"

template <typename T>
class StackRefResult : public GameRefs<T>::StackResultStorage {
public:
    using Base = GameRefs<T>::StackResultStorage;
    using Base::Base;

    constexpr StackRefResult(Base const& ptr) : Base(ptr) {}
    constexpr StackRefResult(Base&& ptr) : Base(std::move(ptr)) {}
};