cmake_minimum_required (VERSION 3.8)


find_package(OpenCV REQUIRED)
find_package(imgui REQUIRED)
find_package(unofficial-nativefiledialog CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)


add_executable(evalWarpImg
        "main.cpp"
        "image.cpp"
        "image.h"
        "imageEval.h"
        "imageEval.cpp"
        "asterisms.h"
        "asterisms.cpp")

target_link_libraries(evalWarpImg
        ${OpenCV_LIBS}
        imgui::imgui
        unofficial::nativefiledialog::nfd
        sfml-system sfml-network sfml-graphics sfml-window
        ImGui-SFML::ImGui-SFML
        )


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET evalWarpImg PROPERTY CXX_STANDARD 20)
endif()

