add_subdirectory(Queue)
add_subdirectory(Memory)

add_library(Communication CommunicationStructs.hpp)
target_link_libraries(Communication Queue Memory)
