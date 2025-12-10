cmake_minimum_required(VERSION 3.10)
project(sysy_compiler)

# 查找 Flex 和 Bison
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)

# 1. 生成词法分析器
flex_target(MyLexer sysy.l ${CMAKE_BINARY_DIR}/sysy.lex.cpp)

# 2. 生成语法分析器
bison_target(MyParser sysy.y ${CMAKE_BINARY_DIR}/sysy.tab.cpp
    DEFINES_FILE ${CMAKE_BINARY_DIR}/sysy.tab.hpp)

# 3. 获取生成的文件
set(GENERATED_SOURCES 
    ${FLEX_MyLexer_OUTPUTS}
    ${BISON_MyParser_OUTPUTS}
)

# 4. 创建可执行文件
add_executable(sysy_compiler
    main.cpp
    ${GENERATED_SOURCES}
)

# 5. 包含目录（关键！）
target_include_directories(sysy_compiler PRIVATE
    ${CMAKE_BINARY_DIR}           # 包含build目录，为了sysy.tab.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}   # 包含源代码目录，为了ast.hpp
)