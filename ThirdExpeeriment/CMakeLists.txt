# cmake最低版本号要求
cmake_minimum_required (VERSION 3.1)
# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
# 设置PROJECT_NAME变量
set(PROJECT_NAME main)

# 设置工程名
project (${PROJECT_NAME})

# 查找当前目录下的所有源文件并存入DIR_SRCS变量
aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SRCS)

# 修改可执行程序输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# 递归列出所有源文件
#file (GLOB_RECURSE SOURCE_FILES *.cc)

#指定头文件目录位置
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

# 添加一个可编译的目标到工程
add_executable (${PROJECT_NAME} ${DIR_SRCS})