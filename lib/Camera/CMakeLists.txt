add_library(
    Camera
    Camera.hpp
    Camera.cpp
    MovementDetection.hpp
    MovementDetection.cpp
    ObjectDetection.hpp
    ObjectDetection.cpp
)

target_link_libraries(Camera ${OpenCV_LIBS})