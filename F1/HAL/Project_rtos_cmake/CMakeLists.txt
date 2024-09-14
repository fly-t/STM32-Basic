cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME Project)

# Include toolchain file
include("cmake/gcc-arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# 定义一个函数，用于处理模块的源文件和头文件路径
function(add_module module_name module_dir)
    # 递归查找 module_dir 中的所有 .c 文件
    file(GLOB_RECURSE ALL_C_FILES "${module_dir}/*.c")

    # 设置头文件包含路径为 module_dir 目录
    set(MODULE_INCLUDE_DIR "${module_dir}")

    # 添加源文件到可执行文件
    target_sources(${CMAKE_PROJECT_NAME} PRIVATE
        ${ALL_C_FILES}  # 添加 module_dir/src 中的 .c 文件
    )

    # 添加包含路径
    target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        ${MODULE_INCLUDE_DIR}  # 添加 module_dir/inc 目录为包含路径
    )
endfunction()


# 添加 App 模块
add_module(App "${CMAKE_SOURCE_DIR}/App")
# 添加 Device 模块
add_module(Device "${CMAKE_SOURCE_DIR}/Device")
# 添加 bsp_uart 模块
add_module(BSP::uart "${CMAKE_SOURCE_DIR}/Bsp/uart")



# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)
