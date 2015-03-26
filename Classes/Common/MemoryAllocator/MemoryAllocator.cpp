
#include "MemoryAllocator.h"

using namespace memory;

#define ALIGNED_SIZE(size, align) (size % align == 0 ? size : size + align - size % align)
#define ALIGNED_OFFSET(size, align) ((size + align - 1) / align)
#define ALIGNED_INDEX(size, align) (ALIGNED_OFFSET(size, align) - 1)

Allocator::Allocator() {
    size_t n = ALIGNED_OFFSET(_maxAllocSize, _align);
    _maxBlockSize = n * _align;
    _pool = new FixedAllocator[n];
    for (int i = 0; i < n; ++i) {
        _pool[i].init((i + 1) * _align, _pageSize);
    }
}

void* Allocator::alloc(size_t size)
{
    if (size > _maxBlockSize) {
        return malloc(size);
    }
    return _pool[ALIGNED_INDEX(size, _align)].alloc();
}

void Allocator::dealloc(void* p)
{
    size_t n = ALIGNED_OFFSET(_maxAllocSize, _align);
    for (int i = 0; i < n; ++i) {
        if (_pool[i].dealloc(p)) {
            return;
        }
    }
    free(p);
}

void Allocator::dealloc(void* p, size_t size)
{
    if (size > _maxBlockSize) {
        free(p);
        return;
    }
    _pool[ALIGNED_INDEX(size, _align)].dealloc(p);
}

