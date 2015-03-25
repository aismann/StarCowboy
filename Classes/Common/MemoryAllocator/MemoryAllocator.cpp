
#include "MemoryAllocator.h"

using namespace memory;

#define ALIGNED_SIZE(size, align) (size % align == 0 ? size : size + align - size % align)

void* Allocator::alloc(size_t size)
{
    if (size > _maxAllocSize) {
        return malloc(size);
    }
    
    size_t alignedSize = ALIGNED_SIZE(size, _align);
    
    if (_lastAlloc >= 0) {
        FixedAllocator &a = _pool.at(_lastAlloc);
        if (a.getBlockSize() == alignedSize) {
            return a.alloc();
        }
    }
    
    auto it = _sizeIndex.find(alignedSize);
    if (it != _sizeIndex.end()) {
        _lastAlloc = it->second;
        return _pool.at(_lastAlloc).alloc();
    }
    _lastAlloc = _pool.size();
    _sizeIndex[alignedSize] = _lastAlloc;
    _pool.push_back(FixedAllocator(alignedSize, _poolIncrease));
    FixedAllocator& fa = _pool.back();
    return fa.alloc();
}

void Allocator::dealloc(void* p)
{
    auto it = _pool.begin();
    for (; it != _pool.end(); ++it) {
        if (it->dealloc(p)) {
            return;
        }
    }
    free(p);
}

void Allocator::dealloc(void* p, size_t size)
{
    if (size > _maxAllocSize) {
        free(p);
        return;
    }
    
    size_t alignedSize = ALIGNED_SIZE(size, _align);
    if (_lastDealloc >= 0) {
        FixedAllocator &a = _pool.at(_lastDealloc);
        if (a.getBlockSize() == alignedSize) {
            a.dealloc(p);
            return;
        }
    }
    
    auto it = _sizeIndex.find(alignedSize);
    if (it != _sizeIndex.end()) {
        _lastDealloc = it->second;
        _pool[_lastDealloc].dealloc(p);
        return;
    }
    assert(!"dealloc error!");
}

