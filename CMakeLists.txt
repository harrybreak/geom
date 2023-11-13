cmake_minimum_required(VERSION 3.21)
project(CollisionDetection)

set(BUILD_SHARED_LIBS OFF)
add_subdirectory("thirdparty/SDL")
#add_subdirectory("thirdparty/SDL_ttf")
#add_subdirectory("thirdparty/SDL_image")
add_subdirectory("thirdparty/GLM")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Og -ggdb3")

#file(COPY "${CMAKE_CURRENT_LIST_DIR}/data/JetBrainsMono-Regular.ttf" DESTINATION "${CMAKE_BINARY_DIR}/")

file(GLOB sources src/*.cpp src/*.inl src/*.hpp)

add_executable(Simulator ${sources})
#target_link_libraries(Simulator PUBLIC SDL2-static SDL2_ttf SDL2_image glm)
target_link_libraries(Simulator PUBLIC SDL2-static glm)
#target_include_directories(SchedulerSimulator PRIVATE ${SDL2_INCLUDE_DIRS})
