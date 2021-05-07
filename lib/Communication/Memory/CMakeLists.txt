add_library(
    Memory
    MemoryAllocator.cpp
    MemoryAllocator.hpp
    MemoryConsumer.cpp
    MemoryConsumer.hpp
    MemoryProducer.cpp
    MemoryProducer.hpp
)

find_library(LIBRT rt)
if(LIBRT)
    target_link_libraries(Memory ${LIBRT})
endif()