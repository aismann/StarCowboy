
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
    _blockSiz = blockSiz + COOKIE_SIZE;
    _bucketSiz = bucketSiz;
}

void* FixedAllocator::alloc()
{
    void *result = nullptr;
    if (_lastAllocBucket >= 0) {
        Bucket& b = _buckets.at(_lastAllocBucket);
        if (b.getAvailableBlockNum() > 0) {
            result = b.alloc(_blockSiz);
            WRITE_COOKIE(result, _blockSiz);
            return SKIP_COOKIE(result);
        }
    }
    //find a available bucket
    auto it = _buckets.begin();
    for (; it != _buckets.end(); ++it) {
        if (it->getAvailableBlockNum() > 0) {
            _lastAllocBucket = it - _buckets.begin();
            result = it->alloc(_blockSiz);
            WRITE_COOKIE(result, _blockSiz);
            return SKIP_COOKIE(result);
        }
    }
    //add bucket
    _lastAllocBucket = _buckets.size();
    _buckets.push_back(Bucket());
    Bucket& b = _buckets.back();
    b.init(_blockSiz, _bucketSiz);
    result = b.alloc(_blockSiz);
    WRITE_COOKIE(result, _blockSiz);
    return SKIP_COOKIE(result);
}

bool FixedAllocator::dealloc(void* p)
{
    size_t length = _blockSiz * _bucketSiz;
    if (_lastDeallocBucket >= 0) {
        Bucket& b = _buckets.at(_lastDeallocBucket);
        if (b.contain(p, length)) {
            b.dealloc(BACKTO_COOKIE(p), _blockSiz);
            return true;
        }
    }
    //find bucket
    auto it = _buckets.begin();
    for (; it != _buckets.end(); ++it) {
        if (it->contain(p, length)) {
            _lastDeallocBucket = it - _buckets.begin();
            it->dealloc(BACKTO_COOKIE(p), _blockSiz);
            return true;
        }
    }
    return false;
}
