
#ifndef __PoolAllocator_h__
#define __PoolAllocator_h__

#include "Bucket.h"

#include <vector>

#define COOKIE_TYPE             unsigned short
#define COOKIE_SIZE             sizeof(COOKIE_TYPE)

#define SKIP_COOKIE(p)          ((unsigned char*)p + COOKIE_SIZE)
#define BACKTO_COOKIE(p)        ((unsigned char*)p - COOKIE_SIZE)

#define WRITE_COOKIE(p, size)   *(COOKIE_TYPE*)p = (COOKIE_TYPE)size
#define READ_COOKIE(p)          *((COOKIE_TYPE*)p - 1)

namespace memory {
    
    class FixedAllocator
    {
    public:
        FixedAllocator() = default;
        ~FixedAllocator();
        
        void init(size_t blockSiz, unsigned char bucketSiz);
        
        void* alloc();
        bool dealloc(void* p);
        
        size_t getBlockSize() const {
            return _blockSiz;
        }
        
    protected:
        
        bool isBucketEmpty(const Bucket& b) {
            return b.getAvailableBlockNum() == _bucketSiz;
        }
        
        std::vector<Bucket> _buckets;
        
        long          _lastAllocBucket = -1;
        long          _lastDeallocBucket = -1;
        
        size_t          _blockSiz = 0;
        unsigned char   _bucketSiz = 0;
    };
    
}

#endif
