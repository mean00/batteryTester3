#-----------------------------------------------------------------------------
#
# CMakeLists for lnBatteryTester
#
#-----------------------------------------------------------------------------
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

cmake_minimum_required(VERSION 3.0)
MESSAGE(STATUS "======================")
MESSAGE(STATUS "Starting BatteryTester")
MESSAGE(STATUS "======================")
SET(AF_FOLDER  ${CMAKE_SOURCE_DIR}/lnArduino/)
include(./mcuSelect.cmake)
SET(CMAKE_TOOLCHAIN_FILE ${AF_FOLDER}/lnArduino.cmake)

PROJECT(lnBatteryTester NONE) # the NONE is very important !

enable_language(C CXX ASM) # this is important too!

SET(SIMPLER_ILI9341_FONT_COMPRESSION ON CACHE INTERNAL "")
SET(SIMPLER_ILI9341_2BPP_SUPPORT  ON CACHE INTERNAL "")
#

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)

SET(LN_ENABLE_RUST ON CACHED "")

add_subdirectory(${AF_FOLDER})

include(${AF_FOLDER}/setup.cmake)


SET(EXTENSION "_${LN_MCU}")



math(EXPR MCU_SPEED_M "${LN_MCU_SPEED}/1000000")
SET(EXTENSION "${EXTENSION}_${MCU_SPEED_M}M")

 
include_directories(include)

#_______________________
#  Display
#_______________________
include_directories(externals/simplerILI9341/platformExample/longanNano)
SET(ILI9341_DRIVER  platformExample/longanNano/gd32_spi.cpp)
ADD_SUBDIRECTORY(externals/simplerILI9341) 
include_directories(externals/simplerILI9341)
#
USE_LIBRARY(NeVerMind)
USE_LIBRARY(RotaryEncoder)

ADD_SUBDIRECTORY(assets) 
ADD_SUBDIRECTORY(src)
#
#____________________
# Build
#____________________
GENERATE_GD32_FIRMWARE(lnBatteryTester${EXTENSION})
TARGET_LINK_LIBRARIES( lnBatteryTester${EXTENSION}  sourceLib backgrounds)
TARGET_LINK_LIBRARIES( lnBatteryTester${EXTENSION}  simplerILI9341  simplerILI9341HS) #assets)
TARGET_LINK_LIBRARIES( lnBatteryTester${EXTENSION}  rnArduino)
# Summary
MESSAGE(STATUS "Configuration:")
MESSAGE(STATUS "\tBuild folder ${CMAKE_BINARY_DIR}")
MESSAGE(STATUS "\tUsing ${LN_MCU} based MCU")
MESSAGE(STATUS "\tUsing ${LN_MCU} MCU at ${LN_MCU_SPEED} Hz")
MESSAGE(STATUS "\tFinal name is ${EXTENSION}")
