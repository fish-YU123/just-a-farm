cmake_minimum_required(VERSION 3.15)  # 匹配CLion 2025的最低要求
project(just-a-farm)  # 项目名称，可自定义

# 1. 设置C++标准（匹配你的代码，用C++17足够）
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # 强制启用指定的C++标准

# 2. 设置SDL2和SDL2_image的路径（务必替换为你的实际路径！）
# 注意：路径中的“./”表示项目根目录，确保SDL文件夹确实在根目录下
set(SDL2_ROOT ./SDL2-2.32.10/x86_64-w64-mingw32)
set(SDL2_IMAGE_ROOT ./SDL2_image-2.6.3/x86_64-w64-mingw32)

# 3. 告诉CMake去哪里找SDL的头文件（避免“找不到SDL2/SDL.h”错误）
include_directories(
        ${SDL2_ROOT}/include          # SDL2的头文件目录
        ${SDL2_IMAGE_ROOT}/include    # SDL2_image的头文件目录
        ./public/renderer             # 你的renderer.h所在目录
)

# 4. 告诉CMake去哪里找SDL的库文件（避免“cannot find -lSDL2_image”错误）
link_directories(
        ${SDL2_ROOT}/lib              # SDL2的库文件目录
        ${SDL2_IMAGE_ROOT}/lib        # SDL2_image的库文件目录
)

# 5. 列出所有需要编译的源文件（如果有renderer.cpp，也要加进来）
add_executable(just-a-farm  # 生成的可执行文件名称，可自定义
        main.cpp                  # 你的主程序文件
        ./public/renderer/renderer.h  # 自定义头文件（确保路径正确）
)

# 6. 链接SDL库（顺序不能乱：SDL2main在前，SDL2和SDL2_image在后）
target_link_libraries(just-a-farm
        PRIVATE  # 私有链接，避免影响其他模块
        SDL2main  # SDL的入口函数库
        SDL2      # SDL核心库
        SDL2_image  # SDL图片加载库
)

# 7. 可选：自动复制SDL的动态库到可执行文件目录（避免“缺少DLL”错误）
# （替换路径为你的SDL bin目录，确保SDL2.dll和SDL2_image.dll存在）
add_custom_command(TARGET just-a-farm POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_ROOT}/bin/SDL2.dll"
        "${CMAKE_BINARY_DIR}/SDL2.dll"  # CMAKE_BINARY_DIR是编译后的目录（如cmake-build-debug）

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_IMAGE_ROOT}/bin/SDL2_image.dll"
        "${CMAKE_BINARY_DIR}/SDL2_image.dll"
)