
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
        
        // 1-16 17-32 33-64 65-128 129-256
        enum {
            kMaxAllocSize   = 256,
            kBlockBace      = 16,
            kPageSize       = 16
        };
        
        FixedAllocator*     _pool;
        size_t              _poolSize;
    };
    
}

#define NewEx(class, args...) new(memory::Allocator::getInstance()->alloc(sizeof(class))) class(args)

#define DelEx(p) \
if (p) {\
    __destruct(p);\
    memory::Allocator::getInstance()->dealloc(p);\
    p = nullptr;\
}

template <class T>
void __destruct(T* p) {
    p->~T();
}

#endif
