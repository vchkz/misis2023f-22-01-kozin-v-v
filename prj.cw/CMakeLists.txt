add_executable(imageGenTest
        "main.cpp")


find_package(OpenCV REQUIRED)


target_link_libraries(imageGenTest
        ${OpenCV_LIBS})