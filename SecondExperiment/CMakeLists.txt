# cmake最低版本号要求
cmake_minimum_required (VERSION 3.21)
# 设置PROJECT_NAME变量
set(PROJECT_NAME test)
# 设置工程名
project (${PROJECT_NAME})
# 查找当前目录下的所有源文件并存入DIR_SRCS变量
aux_source_directory(src DIR_SRCS)

# 递归列出所有源文件
#file (GLOB_RECURSE SOURCE_FILES *.cpp)
# 添加一个可编译的目标到工程
#add_executable (${PROJECT_NAME} ${SOURCE_FILES})

# 添加头文件搜索路径
include_directories (include)
# 添加链接库

# 添加一个可编译的目标到工程
add_executable (${PROJECT_NAME} ${DIR_SRCS})