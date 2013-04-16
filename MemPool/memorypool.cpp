#include "memorypool.h"
#include "constant.h"
MemoryPool::MemoryPool(long tSize)
{
    this->pageNum = tSize/PGSIZE;
    this->ptr = (void *)calloc(tSize, sizeof(char));
}

MemoryPool::~MemoryPool()
{
    //dtor
}
