cmake_minimum_required(VERSION 3.5.1)

# project name
project(Random)

# set the C11 Standard
set(CMAKE_C_STANDARD 11)

# Source file
set(LIB_SOURCES random.c)
set(EXEC_SOURCES main.c random.c)


# create shared library
add_library(random SHARED ${LIB_SOURCES})

# create terminal app
add_executable(app ${EXEC_SOURCES})


