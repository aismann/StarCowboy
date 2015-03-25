//
//  CustomAllocateObject.h
//  StarCowboy
//
//  Created by match5 on 15/3/24.
//
//

#ifndef __CustomAllocate_h__
#define __CustomAllocate_h__

#include "MemoryAllocator.h"

class CustomAllocate
{
public:
    virtual ~CustomAllocate() = default;
    
    void* operator new(size_t size) {
        return memory::Allocator::getInstance()->alloc(size);
    }
    
    void* operator new [](size_t size) {
        return memory::Allocator::getInstance()->alloc(size);
    }
    
    void operator delete(void* p, size_t size) {
        memory::Allocator::getInstance()->dealloc(p, size);
    }
    
    void operator delete [](void* p, size_t size) {
        memory::Allocator::getInstance()->dealloc(p, size);
    }
};

#endif