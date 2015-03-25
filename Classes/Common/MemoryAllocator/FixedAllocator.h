
#ifndef __PoolAllocator_h__
#define __PoolAllocator_h__

#include "Bucket.h"

#include <vector>

namespace memory {
    
    class FixedAllocator
    {
    public:
        FixedAllocator() = default;
        FixedAllocator(size_t blockSiz, unsigned char bucketSiz)
        :_blockSiz(blockSiz)
        ,_bucketSiz(bucketSiz)
        {
        }
        ~FixedAllocator();
        
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
