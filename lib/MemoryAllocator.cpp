#include "MemoryAllocator.hpp"

MemoryAllocator::MemoryAllocator(std::string memoryName=MEMORY_NAME){
    sharedMemmory = shm_open(MEMORY_NAME, O_CREAT|O_RDWR, S_IRUSR | S_IWUSR);
    ftruncate(sharedMemmory, sizeof(buffer));
    auto shmp = mmap(NULL, sizeof(buffer), PROT_READ | PROT_WRITE, MAP_SHARED, sharedMemmory, 0);
    buffer = static_cast<Shmbuf*>(shmp);
}
Shmbuf* MemoryAllocator::getBuffer(){
    return buffer;
}
MemoryAllocator::~MemoryAllocator(){
    close(sharedMemmory);
    munmap(buffer, sizeof(buffer));
    shm_unlink(MEMORY_NAME);
}