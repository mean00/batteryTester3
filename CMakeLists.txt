# Select platform and installation for extra arduino files AND toolchain (compiler...)
SET(PLATFORM_ARCHITECTURE "STM32F1")
# Do we have patch around ?
#
include(./platformConfig.cmake)

cmake_minimum_required(VERSION 3.0)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(cmake_tools)
SET(CMAKE_TOOLCHAIN_FILE cmake/ArduinoToolchain.cmake)
Project("BatteryTester" C CXX ASM)
include(cmake_tools)
SET(EXTENSION             "_STM32F103")
set(ARDUINO_LD_FILE      jtag)      # Use that instead of default jtag-c8 to get the full 128 kB
set(ARDUINO_DEFAULT_BOARD genericSTM32F103C)        # Default Board ID, when not specified
set(ARDUINO_CPU           STM32F103C8)
SET(ARDUINO_UPLOAD_METHOD BMP) # Use blackmagic link, if you comment it out you'll use DFU => 8kB flash

#
#print_board_list()
set(ARDUINO_DEFAULT_PORT ttyACM0) # Default Port, when not specified
set(ARDUINO_CPUMENU .menu.cpu.${ARDUINO_CPU})
SET(libPrefix ${ARDUINO_DEFAULT_BOARD}_)
#
MESSAGE(STATUS "**** Configuration is ** ${CONFIGURATION} **")
SET(SUB_COMPONENTS FreeRTOS RotaryEncoder backgrounds )
SET(SUB_LIBRARIES xpt2046 TFT_eSPI )


include_directories(${CMAKE_SOURCE_DIR}/stubs)
include_directories(${CMAKE_SOURCE_DIR})
include_directories(FreeRTOS/Source/include)
include_directories(FreeRTOS/)
include_directories(FreeRTOS/Source/portable/Stm32duino/)
include_directories(RotaryEncoder/)


include_directories(simplerMCP4725)
include_directories(simpler_INA219)

# Build 
add_subdirectory(XPT2046) # Physical folder name
add_subdirectory(TFT_eSPI)
FOREACH(comp ${SUB_LIBRARIES} ) # Logical name    
    IMPORT_LIBRARY(${comp})
ENDFOREACH(comp ${SUB_LIBRARIES} )
FOREACH(comp ${SUB_COMPONENTS} )
    add_subdirectory(${comp})
ENDFOREACH(comp ${SUB_COMPONENTS} )



#
# Our code
#
SET(UTILS utils/fancyLock.cpp    utils/cycleClock.cpp utils/myPwm.cpp utils/i2c_stubs.c)
add_compile_options("-O0")
generate_arduino_firmware(componentTester${EXTENSION}
                SKETCH batteryTester2.ino
                SRCS screenCalibration.cpp 
                            mainCode.cpp push_button.cpp 
                            screenIdle.cpp screenBase.cpp screenError.cpp screenSetup.cpp items.cpp screenDischarging.cpp screenFinished.cpp   
                            dso_eeprom.cpp
                            dso_logger.cpp
                            calibration.cpp
                PORT ${ARDUINO_DEFAULT_PORT}
                BOARD_CPU ${ARDUINO_CPU}
                )
FOREACH(comp ${SUB_COMPONENTS})
    target_link_libraries(componentTester${EXTENSION} ${libPrefix}${comp})
ENDFOREACH(comp ${SUB_COMPONENTS})

FOREACH(comp ${SUB_LIBRARIES} )
    LINK_TO_LIBRARIES(componentTester${EXTENSION} ${comp})
ENDFOREACH(comp ${SUB_LIBRARIES} )




# EOF
