#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H
#include <stdlib.h>

class MemoryPool
{
    public:
        MemoryPool(long tSize);
        virtual ~MemoryPool();
        void alloc(long size);
    protected:
    private:
        void *ptr;
        unsigned int pageNum;
};

#endif // MEMORYPOOL_H
