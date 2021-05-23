add_executable(pathCreator main.cpp)
target_link_libraries(pathCreator FileLib Socket Communication ${OpenCV_LIBS})
