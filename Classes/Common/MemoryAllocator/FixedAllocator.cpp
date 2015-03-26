
#include "FixedAllocator.h"

using namespace memory;

FixedAllocator::~FixedAllocator()
{
    auto it = _buckets.begin();
    for (; it != _buckets.end(); ++it) {
        it->release();
    }
    _buckets.clear();
}


void FixedAllocator::init(size_t blockSiz, unsigned char bucketSiz)
{
    _blockSiz = blockSiz;
    _bucketSiz = bucketSiz;
}

void* FixedAllocator::alloc()
{
    if (_lastAllocBucket >= 0) {
        Bucket& b = _buckets.at(_lastAllocBucket);
        if (b.getAvailableBlockNum() > 0) {
            return b.alloc(_blockSiz);
        }
    }
    //find a available bucket
    auto it = _buckets.begin();
    for (; it != _buckets.end(); ++it) {
        if (it->getAvailableBlockNum() > 0) {
            _lastAllocBucket = it - _buckets.begin();
            return it->alloc(_blockSiz);
        }
    }
    //add bucket
    _lastAllocBucket = _buckets.size();
    _buckets.push_back(Bucket());
    Bucket& b = _buckets.back();
    b.init(_blockSiz, _bucketSiz);
    return b.alloc(_blockSiz);
}

bool FixedAllocator::dealloc(void* p)
{
    size_t length = _blockSiz * _bucketSiz;
    if (_lastDeallocBucket >= 0) {
        Bucket& b = _buckets.at(_lastDeallocBucket);
        if (b.contain(p, length)) {
            b.dealloc(p, _blockSiz);
            return true;
        }
    }
    //find bucket
    auto it = _buckets.begin();
    for (; it != _buckets.end(); ++it) {
        if (it->contain(p, length)) {
            _lastDeallocBucket = it - _buckets.begin();
            it->dealloc(p, _blockSiz);
            return true;
        }
    }
    return false;
}
