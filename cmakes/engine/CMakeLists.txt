project(engine)

set(SOURCES_DIR ${SOLUTION_DIR}/src/engine/)

set(SOURCES
${SOURCES_DIR}config.cpp
${SOURCES_DIR}config.h
${SOURCES_DIR}compile_route.cpp
${SOURCES_DIR}compile_route.h
${SOURCES_DIR}compile_args.cpp
${SOURCES_DIR}compile_args.h
${SOURCES_DIR}define.h
${SOURCES_DIR}dependon.h
${SOURCES_DIR}dllmain.cpp
${SOURCES_DIR}engine.cpp
${SOURCES_DIR}engine.h
${SOURCES_DIR}engine.def
${SOURCES_DIR}engine.rc
${SOURCES_DIR}exports.cpp
${SOURCES_DIR}exports.h
${SOURCES_DIR}global.cpp
${SOURCES_DIR}global.h
${SOURCES_DIR}manager.cpp
${SOURCES_DIR}manager.h
${SOURCES_DIR}resource.h
${SOURCES_DIR}scriptobj.cpp
${SOURCES_DIR}scriptobj.h
${SOURCES_DIR}stdafx.cpp
${SOURCES_DIR}stdafx.h
)

add_definitions(-DSHARED_API)
add_library(${PROJECT_NAME} SHARED ${SOURCES})
#[[
# 设置编译选项
target_compile_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:Release>:/GL>")
# 设置链接选项
target_link_options(${PROJECT_NAME} PRIVATE "$<$<CONFIG:Release>:/LTCG>")
]]
# 指定专用库头文件目录
target_include_directories(${PROJECT_NAME} 
PRIVATE 
${SOLUTION_ROOT_DIR}/3rdparty/spdlog/include/
${SOLUTION_ROOT_DIR}/include/openssl/3.0.5/
${SOLUTION_ROOT_DIR}/projects/$(projectname)/
${SOLUTION_ROOT_DIR}/projects/$(projectname)/
${LLVM_PROJECT_DIR}/build/tools/clang/tools/driver/
${LLVM_PROJECT_DIR}/tools/clang/tools/driver/
${LLVM_PROJECT_DIR}/tools/clang/include/
${LLVM_PROJECT_DIR}/build/tools/clang/include/
${LLVM_PROJECT_DIR}/build/include/
${LLVM_PROJECT_DIR}/include/
)

# 依赖库目录
target_link_directories(${PROJECT_NAME} 
PRIVATE 
${SOLUTION_ROOT_DIR}/librarys/$(Platform)/
${SOLUTION_ROOT_DIR}/librarys/openssl/3.0.5/$(Platform)/
${SOLUTION_ROOT_DIR}/projects/MT5Projects/lib/$(Platform)/
${LLVM_PROJECT_DIR}/build/$(Configuration)/lib/
${LLVM_PROJECT_DIR}/build/tools/clang/lib/
)

# MSVC 预编译头设置
if (MSVC)
set(MSVCCMAKE_PCH ${SOLUTION_DIR}/cmakes/)
set(STDAFX_PCH_H ${SOURCES_DIR}stdafx.h)
set(STDAFX_PCH_C ${SOURCES_DIR}stdafx.cpp)	
LIST(APPEND CMAKE_MODULE_PATH ${MSVCCMAKE_PCH})
INCLUDE(msvcpch)
USE_MSVC_PCH(${PROJECT_NAME} stdafx.h ${STDAFX_PCH_C})
endif()

#[[
#/$(Platform)/$(Configuration)
# 设置生成目录
set_target_properties(${PROJECT_NAME}
 PROPERTIES
 LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PUBLISH_LIB_DEBUG}
 LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PUBLISH_LIB_RELEASE}
 RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PUBLISH_BIN_DEBUG}
 RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PUBLISH_BIN_RELEASE}
)
]]




