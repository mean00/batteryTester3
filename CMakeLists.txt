# Select platform and installation for extra arduino files AND toolchain (compiler...)
SET(PLATFORM_ARCHITECTURE "STM32F1")
# Do we have patch around ?
#
include(./platformConfig.cmake)

cmake_minimum_required(VERSION 3.0)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
SET(CMAKE_TOOLCHAIN_FILE cmake/ArduinoToolchain.cmake)
Project("BatteryTester" C CXX ASM)

    SET(EXTENSION             "_STM32F103")
    set(ARDUINO_LD_FILE      jtag)      # Use that instead of default jtag-c8 to get the full 128 kB
    set(ARDUINO_DEFAULT_BOARD genericSTM32F103C)        # Default Board ID, when not specified
    set(ARDUINO_CPU           STM32F103C8)
    SET(ARDUINO_UPLOAD_METHOD BMP) # Use blackmagic link, if you comment it out you'll use DFU => 8kB flash

ADD_DEFINITIONS("-g3")

#print_board_list()
set(ARDUINO_DEFAULT_PORT ttyACM0) # Default Port, when not specified
set(ARDUINO_CPUMENU .menu.cpu.${ARDUINO_CPU})
SET(libPrefix ${ARDUINO_DEFAULT_BOARD}_)
#
MESSAGE(STATUS "**** Configuration is ** ${CONFIGURATION} **")
SET(SUB_COMPONENTS FreeRTOS )


include_directories(${CMAKE_SOURCE_DIR})
include_directories(FreeRTOS/Source/include)
include_directories(FreeRTOS/)

# Build 
FOREACH(comp ${SUB_COMPONENTS} )
    add_subdirectory(${comp})
ENDFOREACH(comp ${SUB_COMPONENTS} )

include_directories(Arduino_STM32/STM32F1/libraries/Adafruit_GFX_AS/)


SET(ILI ${CMAKE_CURRENT_SOURCE_DIR}/extendedIli9341)

#
# Our code
#
SET(UTILS utils/fancyLock.cpp    utils/cycleClock.cpp utils/myPwm.cpp utils/i2c_stubs.c)

generate_arduino_firmware(componentTester${EXTENSION}
                SKETCH batteryTester2.ino
                SRCS screenCalibration.cpp wav_irotary.cpp mainCode.cpp push_button.cpp screenIdle.cpp screenBase.cpp screenError.cpp screenSetup.cpp items.cpp screenDischarging.cpp screenFinished.cpp   ${ILI}/ILI9341_extended.cpp ${ILI}/ILI9341_extended_glyph.cpp
                PORT ${ARDUINO_DEFAULT_PORT}
                BOARD_CPU ${ARDUINO_CPU}
                )
FOREACH(comp ${SUB_COMPONENTS})
    target_link_libraries(componentTester${EXTENSION} ${libPrefix}${comp})
ENDFOREACH(comp ${SUB_COMPONENTS})



# EOF
