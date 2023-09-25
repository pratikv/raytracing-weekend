# set the minimum cmake version required
cmake_minimum_required(VERSION 3.20.0)

#set the name of the project. Remember to use this everywhere
project (rt1 VERSION 1.0 DESCRIPTION "Temp project" LANGUAGES CXX)

set( CMAKE_CXX_STANDARD 11 )

# set the include directories. This is relative to the local folder
include_directories(src)

#set the third party include directories
# include_directories(/opt/homebrew/include)

# set the third party link directories
# link_directories(/opt/homebrew/lib)

# add the files that needs to be compiled
file(GLOB SOURCES "src/*.cpp")

# just printing the messages
message("SOURCES = ${SOURCES}")

# set files required for executable.
add_executable(${PROJECT_NAME} ${SOURCES} main.cpp)

# add the third party link libraries
# target_link_libraries(${PROJECT_NAME} 
# PUBLIC
# glad
# glfw
# glm
# 
# PRIVATE
# ${PROJECT_LINK_LIBS}
# )
