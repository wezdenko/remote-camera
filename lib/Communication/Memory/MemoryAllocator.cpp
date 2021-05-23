#include "MemoryAllocator.hpp"

MemoryAllocator::MemoryAllocator(std::string mName): memoryName(mName){
    sharedMemmory = shm_open(memoryName.c_str(), O_CREAT|O_RDWR, S_IRUSR | S_IWUSR);
    ftruncate(sharedMemmory, sizeof(Shmbuf));
    auto shmp = mmap(NULL, sizeof(Shmbuf), PROT_READ | PROT_WRITE, MAP_SHARED, sharedMemmory, 0);
    buffer = static_cast<Shmbuf*>(shmp);
}
Shmbuf* MemoryAllocator::getBuffer(){
    return buffer;
}
MemoryAllocator::~MemoryAllocator(){
    close(sharedMemmory);
    munmap(buffer, sizeof(buffer));
    shm_unlink(memoryName.c_str());
}