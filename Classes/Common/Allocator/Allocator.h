
#ifndef __Allocator_h__
#define __Allocator_h__

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

#define New(class, args...) new(memory::Allocator::getInstance()->alloc(sizeof(class))) class(args)

#define Delete(p) \
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
