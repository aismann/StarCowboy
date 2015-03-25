
#include "Bucket.h"

#include <stdlib.h>

using namespace memory;

void Bucket::init(size_t blockSiz, unsigned char blockNum)
{
    release();
    _data = (unsigned char*)calloc(blockSiz, blockNum);
    _availableBlock = 0;
    _availableBlockNum = blockNum;
    unsigned char* p = _data;
    for (unsigned char i = 0; i < blockNum; p += blockSiz) {
        *p = ++i;
    }
}

void Bucket::release()
{
    if (_data) {
        free(_data);
        _data = nullptr;
    }
}

void* Bucket::alloc(size_t blockSiz)
{
    assert(_data);
    if (_availableBlockNum > 0) {
        unsigned char* p = _data + (_availableBlock * blockSiz);
        _availableBlock = *p;
        --_availableBlockNum;
        return p;
    }
    return nullptr;
}

void Bucket::dealloc(void* p, size_t blockSiz)
{
    assert(_data);
    unsigned char* pd = (unsigned char*)p;
    assert((pd - _data) % blockSiz == 0);
    *pd = _availableBlock;
    _availableBlock = ((pd - _data) / blockSiz);
    ++_availableBlockNum;
}
