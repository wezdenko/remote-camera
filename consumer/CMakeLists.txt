add_executable(ConsumerApp main.cpp)
target_link_libraries(ConsumerApp CommunicationLib)

find_library(LIBRT rt)
if(LIBRT)
    target_link_libraries(ConsumerApp ${LIBRT} ${OpenCV_LIBS})
endif()