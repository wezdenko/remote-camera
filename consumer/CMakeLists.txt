add_executable(ConsumerApp main.cpp)
target_link_libraries(ConsumerApp FileLib Socket Communication ${OpenCV_LIBS})
