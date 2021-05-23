add_executable(movementDetector main.cpp)
target_link_libraries(movementDetector ${OpenCV_LIBS} Camera Communication)
