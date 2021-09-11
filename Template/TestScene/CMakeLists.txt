cmake_minimum_required( VERSION 3.9 )
project( TestScene )

include( ../Common/build_files/Common_packages.cmake )

set( TARGET_NAME TestScene_CS300 )

add_executable( ${TARGET_NAME}
        main.cpp )

# Set target properties
include( ../Common/build_files/Common_target.cmake )