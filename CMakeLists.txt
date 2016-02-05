cmake_minimum_required(VERSION 2.8.12)
project(monoRenderer)

#--------------------------------------------------------------------
# Set version
#--------------------------------------------------------------------
set(MONORENDERER_VERSION_MAJOR "0")
set(MONORENDERER_VERSION_MINOR "0")
set(MONORENDERER_VERSION_PATCH "0")
set(MONORENDERER_VERSION_EXTRA "-alpha")
set(MONORENDERER_VERSION "${MONORENDERER_VERSION_MAJOR}.${MONORENDERER_VERSION_MINOR}")
set(MONORENDERER_VERSION_FULL "${MONORENDERER_VERSION}.${MONORENDERER_VERSION_PATCH}${MONORENDERER_VERSION_EXTRA}")

#--------------------------------------------------------------------
# Check OS
#--------------------------------------------------------------------
if (NOT UNIX)
	message(FATAL_ERROR "Only UNIX is supported so far!")
endif ()

#--------------------------------------------------------------------
# Check if static lib
#--------------------------------------------------------------------
option(STATIC_LIB "builds static library" OFF)
if (NOT STATIC_LIB)
	set(CMAKE_BUILD_TYPE Release)
endif ()

#--------------------------------------------------------------------
# Set compiler specific flags
#--------------------------------------------------------------------
if (UNIX)
	set(MY_WARNING_FLAGS " -Wall -pedantic -Wextra -Werror -Wcast-align -Wconversion -Wfloat-equal -Wformat=2 -Wmissing-declarations -Woverlength-strings -Wshadow -Wunreachable-code")
	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		set(MY_WARNING_FLAGS "${MY_WARNING_FLAGS} -Wimplicit-atomic-properties -Wstrict-selector-match -Wundeclared-selector")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
	elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
	endif ()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -msse2 -msse3 ${MY_WARNING_FLAGS}")
endif ()

#--------------------------------------------------------------------
# Glob files
#--------------------------------------------------------------------
file(GLOB_RECURSE CXX_SRCS src/*.cpp)
file(GLOB_RECURSE C_SRCS src/*.c)
file(GLOB_RECURSE HPP_HDRS src/*.hpp)
file(GLOB_RECURSE H_HDRS src/*.h)
set(SRCS "${C_SRCS};${CXX_SRCS}")
set(HDRS "${H_HDRS};${HPP_HDRS}")

#--------------------------------------------------------------------
# Find packages
#--------------------------------------------------------------------
find_package(OpenGL REQUIRED)
find_package(Threads)

#--------------------------------------------------------------------
# MonoEngine
#--------------------------------------------------------------------
set(CONTRIB_DIR "${PROJECT_SOURCE_DIR}/contrib")

set(MONOENGINE_BUILD_DIR "${PROJECT_SOURCE_DIR}/build/monoengine")
set(MONOENGINE_DOWNLOAD_FILE "master.zip")
set(MONOENGINE_DIR "${PROJECT_SOURCE_DIR}/contrib/monoengine")

set(MONOENGINE_LIB_NAME "libmonoEngine.a")

set(MONOENGINE_STAMP_DIR 		"${MONOENGINE_BUILD_DIR}/stamp")
set(MONOENGINE_TMP_DIR 			"${MONOENGINE_BUILD_DIR}/tmp")
set(MONOENGINE_DOWNLOAD_DIR 	"${PROJECT_SOURCE_DIR}/dl")
set(MONOENGINE_LIB_INSTALL_DIR 	"${MONOENGINE_BUILD_DIR}/libinstall")
set(MONOENGINE_LIB_DIR 			"${MONOENGINE_DIR}/lib")
set(MONOENGINE_SOURCE_DIR 		"${MONOENGINE_BUILD_DIR}/source")
set(MONOENGINE_INCLUDE_DIR 		"${MONOENGINE_DIR}/include")

set(MONOENGINE_CMAKE_ARGS -DSTATIC_LIB=1 -DGLFW_DOWNLOAD_DIR:STRING=${MONOENGINE_DOWNLOAD_DIR} -DCMAKE_INSTALL_PREFIX=${MONOENGINE_INSTALL_DIR})

if (EXISTS ${MONOENGINE_DOWNLOAD_DIR}/${MONOENGINE_DOWNLOAD_FILE})
	set(MONOENGINE_URL "${MONOENGINE_DOWNLOAD_DIR}/${MONOENGINE_DOWNLOAD_FILE}")
else ()
	set(MONOENGINE_URL "https://github.com/gartenriese2/monoengine/archive/${MONOENGINE_DOWNLOAD_FILE}")
endif ()

include(ExternalProject)
ExternalProject_Add(
	MonoEngine
	URL ${MONOENGINE_URL}
	TMP_DIR ${MONOENGINE_TMP_DIR}
	DOWNLOAD_DIR ${MONOENGINE_DOWNLOAD_DIR}
	STAMP_DIR ${MONOENGINE_STAMP_DIR}
	SOURCE_DIR ${MONOENGINE_SOURCE_DIR}
	BINARY_DIR ${MONOENGINE_LIB_INSTALL_DIR}
	INSTALL_DIR ${MONOENGINE_DIR}
	CMAKE_ARGS ${MONOENGINE_CMAKE_ARGS}
	INSTALL_COMMAND make
)
ExternalProject_Add_Step(
	MonoEngine
	createFolders
	WORKING_DIRECTORY ${MONOENGINE_DIR}
	DEPENDEES install
	COMMAND mkdir -p lib include/MonoEngine
	COMMENT "Creating MonoEngine folders"
)
ExternalProject_Add_Step(
	MonoEngine
	copySource
	WORKING_DIRECTORY ${MONOENGINE_DIR}
	DEPENDEES createFolders
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${MONOENGINE_SOURCE_DIR}/src/engine ${MONOENGINE_INCLUDE_DIR}/MonoEngine
	COMMENT "Moving MonoEngine includes"
)
ExternalProject_Add_Step(
	MonoEngine
	copyContrib
	WORKING_DIRECTORY ${MONOENGINE_DIR}
	DEPENDEES createFolders
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${MONOENGINE_SOURCE_DIR}/contrib ${CONTRIB_DIR}
	COMMENT "Moving MonoEngine contribs"
)
ExternalProject_Add_Step(
	MonoEngine
	copyLib
	WORKING_DIRECTORY ${MONOENGINE_DIR}
	DEPENDEES createFolders
	COMMAND mv ${MONOENGINE_LIB_INSTALL_DIR}/${MONOENGINE_LIB_NAME} ${MONOENGINE_LIB_DIR}
	COMMENT "Moving MonoEngine lib"
)

set(MONOENGINE_STATIC_LIB "${MONOENGINE_LIB_DIR}/${MONOENGINE_LIB_NAME}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem ${MONOENGINE_INCLUDE_DIR}")

#--------------------------------------------------------------------
# GLFW
#--------------------------------------------------------------------
set(GLFW_STATIC_LIB "${CONTRIB_DIR}/glfw/lib/libglfw3.a")
set(GLFW_LIBRARIES "-lX11 -lXrandr -lXi -lXxf86vm")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem ${CONTRIB_DIR}/glfw/include")

#--------------------------------------------------------------------
# GLM
#--------------------------------------------------------------------
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem ${CONTRIB_DIR}/glm")
add_definitions( -DGLM_FORCE_RADIANS )

#--------------------------------------------------------------------
# ASSIMP
#--------------------------------------------------------------------
set(ASSIMP_DOWNLOAD_DIR "${PROJECT_SOURCE_DIR}/dl" CACHE STRING "specifies the ASSIMP download directory")
set(ASSIMP_DOWNLOAD_FILE "v3.2.zip")
if (EXISTS ${ASSIMP_DOWNLOAD_DIR}/${ASSIMP_DOWNLOAD_FILE})
	set(ASSIMP_URL "${ASSIMP_DOWNLOAD_DIR}/${ASSIMP_DOWNLOAD_FILE}")
else ()
	set(ASSIMP_URL "https://github.com/assimp/assimp/archive/${ASSIMP_DOWNLOAD_FILE}")
endif ()

set(ASSIMP_LIB_NAME "libassimp.a")

set(ASSIMP_BUILD_DIR "${PROJECT_SOURCE_DIR}/build/assimp")
set(ASSIMP_DIR "${PROJECT_SOURCE_DIR}/contrib/assimp")
set(ASSIMP_SOURCE_DIR 		"${ASSIMP_BUILD_DIR}/source")
set(ASSIMP_INCLUDE_DIR 		"${ASSIMP_DIR}/include")
set(ASSIMP_CODE_DIR 		"${ASSIMP_DIR}/code")
set(ASSIMP_LIB_INSTALL_DIR 	"${ASSIMP_BUILD_DIR}/libinstall")
set(ASSIMP_LIB_DIR 			"${ASSIMP_DIR}/lib")

ExternalProject_Add(
	assimp
	PREFIX "contrib"
	DOWNLOAD_DIR ${ASSIMP_DOWNLOAD_DIR}
	URL ${ASSIMP_URL}
	SOURCE_DIR ${ASSIMP_SOURCE_DIR}
	BINARY_DIR ${ASSIMP_LIB_INSTALL_DIR}
	INSTALL_DIR ${ASSIMP_DIR}
	CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF -DASSIMP_NO_EXPORT=ON -DASSIMP_BUILD_ASSIMP_TOOLS=OFF -DASSIMP_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=/assimp
	INSTALL_COMMAND make
)
ExternalProject_Add_Step(
	assimp
	createFolders
	WORKING_DIRECTORY ${ASSIMP_DIR}
	DEPENDEES install
	COMMAND mkdir -p lib include/assimp code
	COMMENT "Creating Assimp folders"
)
ExternalProject_Add_Step(
	assimp
	copySource
	WORKING_DIRECTORY ${ASSIMP_DIR}
	DEPENDEES createFolders
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSIMP_SOURCE_DIR}/include ${ASSIMP_INCLUDE_DIR}
	COMMENT "Moving Assimp includes"
)
ExternalProject_Add_Step(
	assimp
	copyLib
	WORKING_DIRECTORY ${ASSIMP_DIR}
	DEPENDEES createFolders
	COMMAND mv ${ASSIMP_LIB_INSTALL_DIR}/code/${ASSIMP_LIB_NAME} ${ASSIMP_LIB_DIR}
	COMMENT "Moving Assimp lib"
)
ExternalProject_Add_Step(
	assimp
	copyCode
	WORKING_DIRECTORY ${ASSIMP_DIR}
	DEPENDEES createFolders
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSIMP_SOURCE_DIR}/code ${ASSIMP_CODE_DIR}
	COMMENT "Moving Assimp code"
)
set(ASSIMP_STATIC_LIB "${ASSIMP_LIB_DIR}/${ASSIMP_LIB_NAME}")
include_directories(${ASSIMP_INCLUDE_DIR})
set(ASSIMP_LIBRARIES "-lz")

#--------------------------------------------------------------------
# Building
#--------------------------------------------------------------------
if (STATIC_LIB)
	add_library(monoRenderer STATIC ${SRCS} ${HDRS})
else ()
	add_executable(monoRenderer ${SRCS} ${HDRS})
	target_link_libraries(monoRenderer ${MONOENGINE_STATIC_LIB} ${GLFW_STATIC_LIB} ${ASSIMP_STATIC_LIB} ${ASSIMP_LIBRARIES} ${OPENGL_gl_LIBRARY} ${GLFW_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
endif ()
add_dependencies(monoRenderer MonoEngine assimp)