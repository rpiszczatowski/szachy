#pragma once

#include "HashContainer.h"
#include "AlphaBetaGenericHashElement.h"

template <uint64_t hashSizeInBits>
struct AlphaBetaHashContainer : HashContainer<AlphaBetaGenericHashElement, hashSizeInBits> {
    using UnderlyingContainer = HashContainer<AlphaBetaGenericHashElement, hashSizeInBits>;
    inline void insert(uint64_t hash, const AlphaBetaGenericHashElement &value) {
        UnderlyingContainer::insert(hash, value);
    }
};
