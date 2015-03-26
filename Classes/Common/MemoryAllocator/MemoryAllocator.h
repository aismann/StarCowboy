
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
        
        Allocator();
        
        void *alloc(size_t size);
        
        void dealloc(void* p);
        void dealloc(void* p, size_t size);
        
    protected:
        
        const size_t                        _align = 16;
        const size_t                        _maxAllocSize = 128;
        const size_t                        _pageSize = 32;
        
        size_t                              _maxBlockSize = 0;
        FixedAllocator*                     _pool;
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
