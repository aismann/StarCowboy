
#ifndef __MemPool_h__
#define __MemPool_h__

#include <cstdlib>

namespace memory {
    
    class Bucket
    {
    public:
        
        void init(size_t blockSiz, unsigned char blockNum);
        void release();
        
        void *alloc(size_t blockSiz);
        void dealloc(void* p, size_t blockSiz);
        
        bool contain(void *p, size_t length) const {
            return _data <= p && p < _data + length;
        }
        
        unsigned char getAvailableBlockNum() const {
            return _availableBlockNum;
        }
        
    protected:
        
        unsigned char *_data = nullptr;
        unsigned char _availableBlockNum;
        unsigned char _availableBlock;
    };
}

#endif
