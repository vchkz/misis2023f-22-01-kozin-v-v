cmake_minimum_required (VERSION 3.8)

find_package(OpenCV REQUIRED)
find_package(imgui REQUIRED)
find_package(unofficial-nativefiledialog CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(ImGui-SFML CONFIG REQUIRED)


add_executable(imageWarping
        "main.cpp"
        "image.cpp"
        "image.h"
        "imageEval.h"
        "imageEval.cpp"
        "asterisms.h"
        "asterisms.cpp")

target_link_libraries(imageWarping
        ${OpenCV_LIBS}
        imgui::imgui
        unofficial::nativefiledialog::nfd
        sfml-system sfml-network sfml-graphics sfml-window
        ImGui-SFML::ImGui-SFML
        )