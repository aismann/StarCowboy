
#ifndef __MemoryAllocator_h__
#define __MemoryAllocator_h__

#include "Singleton.h"
#include "FixedAllocator.h"

#include <vector>
#include <map>

namespace memory {
    
    class Allocator : public Singleton<Allocator>
    {
        
    public:
        
        Allocator() {
            _pool.reserve((_maxAllocSize + _align - 1) / _align);
        }
        
        void *alloc(size_t size);
        
        void dealloc(void* p);
        void dealloc(void* p, size_t size);
        
    protected:
        
        std::vector<FixedAllocator>         _pool;
        std::map<size_t, size_t>            _sizeIndex;
        size_t                              _align = 16;
        
        long                                _lastAlloc = -1;
        long                                _lastDealloc = -1;
        
        const size_t                        _maxAllocSize = 128;
        const size_t                        _poolIncrease = 32;
    };
    
}

#define NewEx(class, args...) new(memory::Allocator::getInstance()->alloc(sizeof(class))) class(args)

#define DelEx(class, p) \
if (p) {\
    p->~class();\
    memory::Allocator::getInstance()->dealloc(p, sizeof(class));\
    p = nullptr;\
}

#endif
