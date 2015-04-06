
#include "MemoryAllocator.h"
#include "FixedAllocator.h"
#include "MathUtils.h"

using namespace memory;

inline size_t __n_bace(size_t size, size_t bace) {
    return size % bace == 0 ? size / bace : (size + bace - 1) / bace;
}

size_t __index(size_t size, size_t bace) {
    size_t n = __n_bace(size, bace);
    size_t n_ = 1;
    size_t index = 0;
    while (n_ < n) {
        n_ *= 2;
        ++index;
    }
    return index;
}

Allocator::Allocator() {
    _poolSize = __index(kMaxAllocSize, kBlockBace) + 1;
    _pool = new FixedAllocator[_poolSize];
    for (int i = 0; i < _poolSize; ++i) {
        _pool[i].init(math::power(2, i) * kBlockBace, kPageSize);
    }
}

void* Allocator::alloc(size_t size)
{
    if (size <= 0) {
        return nullptr;
    }
    if (size > kMaxAllocSize) {
        return malloc(size);
    }
    return _pool[__index(size, kBlockBace)].alloc();
}

void Allocator::dealloc(void* p)
{
    size_t index = __index(READ_COOKIE(p) - COOKIE_SIZE, kBlockBace);
    if (index >= _poolSize || !_pool[index].dealloc(p)) {
        free(p);
    }
}

void Allocator::dealloc(void* p, size_t size)
{
    if (size > kMaxAllocSize) {
        free(p);
        return;
    }
    _pool[__index(size, kBlockBace)].dealloc(p);
}

