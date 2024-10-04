cmake_minimum_required (VERSION 2.8)

project(Logger)

# find all source files in current directory
# store source files' name into DIR_SRCS 
aux_source_directory(. DIR_SRCS)

# add subdir and put executable file into utility/bin
add_subdirectory(utility bin)

add_executable(main ${DIR_SRCS})

# add linking library
target_link_libraries(main Logger)
