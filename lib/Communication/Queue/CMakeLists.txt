add_library(
    Queue
    QueConnector.cpp
    QueConnector.hpp
    QueReceiver.hpp
    QueReceiver.cpp
    QueSender.cpp
    QueSender.hpp
)

find_library(LIBRT rt)
if(LIBRT)
    target_link_libraries(Queue ${LIBRT})
endif()