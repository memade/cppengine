project(test_engine)

# set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")

set(SOURCES_DIR ${SOLUTION_DIR}/tests/test_engine/)

set(SOURCES
${SOURCES_DIR}main.cpp
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})
# 设置编译选项
target_compile_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:Release>:/GL>")
# 设置链接选项
target_link_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:Release>:/LTCG>")
# 指定专用库头文件目录
target_include_directories(${PROJECT_NAME} 
PRIVATE 
${SOLUTION_ROOT_DIR}/3rdparty/spdlog/include/)
# 依赖库目录
target_link_directories(${PROJECT_NAME} 
PRIVATE 
${SOLUTION_ROOT_DIR}/librarys/$(Platform)/
${SOLUTION_ROOT_DIR}/projects/MT5Projects/lib/$(Platform)/
)

#/$(Platform)/$(Configuration)
# 设置生成目录
set_target_properties(${PROJECT_NAME}
 PROPERTIES
 LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PUBLISH_LIB_DEBUG}
 LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PUBLISH_LIB_RELEASE}
 RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PUBLISH_BIN_DEBUG}
 RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PUBLISH_BIN_RELEASE}
)

# 设置编译中间目录

#[[
# MSVC 预编译头设置
if (MSVC)
set(MSVCCMAKE_PCH ${SOLUTION_DIR}/cmakes/)
set(STDAFX_PCH_H ${SOURCES_DIR}stdafx.h)
set(STDAFX_PCH_C ${SOURCES_DIR}stdafx.cpp)	
LIST(APPEND CMAKE_MODULE_PATH ${MSVCCMAKE_PCH})
INCLUDE(msvcpch)
USE_MSVC_PCH(${PROJECT_NAME} stdafx.h ${STDAFX_PCH_C})
endif()
]]





