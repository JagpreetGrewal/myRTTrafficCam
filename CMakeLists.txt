cmake_minimum_required(VERSION 3.16.0)
project (myRTTrafficCame)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)
set(PKG_CONFIG_EXECUTABLE "/usr/bin/pkg-config")
# pkg_check_modules(GST REQUIRED gstreamer-1.0)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
  message("-- No build mode chosen - using Release by default")
endif(NOT CMAKE_BUILD_TYPE)

find_package (OpenCV 4.5.1 REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} ${GST_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR})


set (CMAKE_CXX_FLAGS "-g -D _POSIX_C_SOURCE=200809L -Wno-unused-function -Werror") 
# no need to include 'pkg-config --cflags --libs opencv4' with correct cmake configuration

set (OUTDIR ../bin)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTDIR})

add_executable(processVideo src/processVideo.cc)
target_link_libraries(processVideo ${OpenCV_LIBS} ${GST_LIBRARIES})

foreach(flag ${GST_CFLAGS_OTHER})
  set_property(TARGET processVideo APPEND_STRING PROPERTY COMPILE_FLAGS " ${flag}")
endforeach()

foreach(flag ${GST_LDFLAGS_OTHER})
  set_property(TARGET processVideo APPEND_STRING PROPERTY LINK_FLAGS " ${flag}")
endforeach()

