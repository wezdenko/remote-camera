add_executable(ProducerApp main.cpp)
target_link_libraries(ProducerApp ${OpenCV_LIBS} Camera Communication)
