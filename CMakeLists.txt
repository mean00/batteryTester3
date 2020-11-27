OPTION(USE_GD30F103   "Use GD32F103 MCU" FALSE) 
OPTION(USE_GD30F303   "Use GD32F303 MCU" FALSE) 
# Select platform and installation for extra arduino files AND toolchain (compiler...)
SET(PLATFORM_ARCHITECTURE "STM32F1")
# Do we have patch around ?
#
include(cmake_utils/FindPatch.cmake)
include(./platformConfig.cmake)
cmake_minimum_required(VERSION 3.0)

IF(USE_GD32F103 OR USE_GD32F303)
    SET(MCU_SPEED             96000000)                 # Max speed, above 96M USB will not work (?)
ENDIF(USE_GD32F103 OR USE_GD32F303)
include(./platformConfig.cmake)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(cmake_tools)
include(FindPatch)
SET(CMAKE_TOOLCHAIN_FILE cmake/ArduinoToolchain.cmake)
Project("BatteryTester" C CXX ASM)

#
# Patch Arduino_stm32 if needed to add gd32f303 support
#
IF(NOT EXISTS "${PLATFORM_PATH}/patched")
    MESSAGE(STATUS "Patching file in ${PLATFORM_PATH} to fix spi dma in async mode")
    patch_file_p(2 "${PLATFORM_PATH}" "${CMAKE_SOURCE_DIR}/patches/spi_dma_async_patch2.diff")
    file(WRITE "${PLATFORM_PATH}/patched" "patched")
ENDIF(NOT EXISTS "${PLATFORM_PATH}/patched")

IF(NOT EXISTS "${PLATFORM_PATH}/patched2")
    MESSAGE(STATUS "Patching file in ${PLATFORM_PATH} to add gd32f303/103 support")
    patch_file_p(2 "${PLATFORM_PATH}" "${CMAKE_SOURCE_DIR}/patches/gd32_patch.diff")
    file(WRITE "${PLATFORM_PATH}/patched2" "patched2")
ENDIF(NOT EXISTS "${PLATFORM_PATH}/patched2")

include(cmake_tools)

Project("BatteryTester" C CXX ASM)
# Board setup
IF(USE_GD32F103)
    SET(EXTENSION             "_GD32F103")
    set(ARDUINO_DEFAULT_BOARD genericGD32F103C)        # Default Board ID, when not specified
    set(ARDUINO_CPU           GD32F103C8)
ELSEIF(USE_GD32F303)
    SET(EXTENSION             "_GD32F303")
    set(ARDUINO_DEFAULT_BOARD genericGD32F303C)        # Default Board ID, when not specified
    set(ARDUINO_CPU           GD32F303C8)
ELSE()
    SET(EXTENSION             "_STM32F103")
    set(ARDUINO_LD_FILE      jtag)      # Use that instead of default jtag-c8 to get the full 128 kB
    set(ARDUINO_DEFAULT_BOARD genericSTM32F103C)        # Default Board ID, when not specified
    set(ARDUINO_CPU           STM32F103C8)
ENDIF(USE_GD32F103)
SET(ARDUINO_UPLOAD_METHOD BMP) # Use blackmagic link, if you comment it out you'll use DFU => 8kB flash

#
#print_board_list()
set(ARDUINO_DEFAULT_PORT ttyACM0) # Default Port, when not specified
set(ARDUINO_CPUMENU .menu.cpu.${ARDUINO_CPU})
SET(libPrefix ${ARDUINO_DEFAULT_BOARD}_)
#
MESSAGE(STATUS "**** Configuration is ** ${CONFIGURATION} **")
SET(SUB_COMPONENTS FreeRTOS RotaryEncoder adc )
SET(SUB_LIBRARIES xpt2046  TFT_eSPI )

add_subdirectory(assets)

include_directories(${CMAKE_SOURCE_DIR}/stubs)
include_directories(${CMAKE_SOURCE_DIR})
include_directories(FreeRTOS/Source/include)
include_directories(FreeRTOS/)
include_directories(FreeRTOS/Source/portable/Stm32duino/)
include_directories(RotaryEncoder/)
include_directories(assets/backgrounds/generated)
include_directories(utils)


# Build 
add_subdirectory(XPT2046) # Physical folder name
FOREACH(comp ${SUB_LIBRARIES} ) # Logical name    
    IMPORT_LIBRARY(${comp})
ENDFOREACH(comp ${SUB_LIBRARIES} )
FOREACH(comp ${SUB_COMPONENTS} )
    add_subdirectory(${comp})
ENDFOREACH(comp ${SUB_COMPONENTS} )

add_definitions("-DPRINTF_DISABLE_SUPPORT_EXPONENTIAL -DPRINTF_DISABLE_SUPPORT_LONG_LONG -DPRINTF_DISABLE_SUPPORT_PTRDIFF_T ")


#
# Our code
#
SET(UTILS utils/fancyLock.cpp    utils/cycleClock.cpp  utils/i2c_stubs.c)
generate_arduino_firmware(batTester${EXTENSION}
                SKETCH batteryTester2.ino
                SRCS screenCalibration.cpp 
                            mainCode.cpp push_button.cpp 
                            screenIdle.cpp screenBase.cpp screenError.cpp screenSetup.cpp items.cpp screenDischarging.cpp screenFinished.cpp embedded_printf/printf.c    settings.cpp
                            dso_eeprom.cpp
                            dso_logger.cpp
                            calibration.cpp
                            heap.cpp
                PORT ${ARDUINO_DEFAULT_PORT}
                BOARD_CPU ${ARDUINO_CPU}
                )
FOREACH(comp ${SUB_COMPONENTS})
    target_link_libraries(batTester${EXTENSION} ${libPrefix}${comp})
ENDFOREACH(comp ${SUB_COMPONENTS})

FOREACH(comp ${SUB_LIBRARIES} )
    LINK_TO_LIBRARIES(batTester${EXTENSION} ${comp})
ENDFOREACH(comp ${SUB_LIBRARIES} )

target_link_libraries(batTester${EXTENSION}  ${libPrefix}backgrounds)


# EOF
