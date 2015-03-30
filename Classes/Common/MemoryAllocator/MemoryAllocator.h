
#ifndef __MemoryAllocator_h__
#define __MemoryAllocator_h__

#include "Singleton.h"

#include <vector>
#include <map>

namespace memory {
    
    class FixedAllocator;
    
    class Allocator : public Singleton<Allocator>
    {
        
    public:
        
        Allocator();
        
        void *alloc(size_t size);
        
        void dealloc(void* p);
        void dealloc(void* p, size_t size);
        
    protected:
        
        const size_t                        _align = 32;
        const size_t                        _maxAllocSize = 256;
        const size_t                        _pageSize = 16;
        
        size_t                              _maxBlockSize = 0;
        FixedAllocator*                     _pool;
    };
    
}

#define NewEx(class, args...) new(memory::Allocator::getInstance()->alloc(sizeof(class))) class(args)


template <class T>
void __destruct(T* p) {
    p->~T();
}

#define DelEx(p) \
if (p) {\
    __destruct(p);\
    memory::Allocator::getInstance()->dealloc(p);\
    p = nullptr;\
}

#endif
