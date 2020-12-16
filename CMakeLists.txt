 cmake_minimum_required(VERSION 3.0)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(select_mcu_stm32)
include(cmake_tools)
include(applyPatch)
# Patch
include(./platformConfig.cmake)


APPLY_PATCH_IF_NEEDED(patched gd32_patch.diff              "add gd32f303 support") 
APPLY_PATCH_IF_NEEDED(patched2 spi_dma_async_patch2.diff   "add cookie to spi callback ") 
APPLY_PATCH_IF_NEEDED(patched3 weak_i2c.diff               "weaken i2c symbols") 


SET(CMAKE_TOOLCHAIN_FILE cmake/ArduinoToolchain.cmake)
Project("BatteryTester" C CXX ASM)

# Board setup
# Set config depending on the MCU selected

set(ARDUINO_DEFAULT_BOARD ${X_ARDUINO_DEFAULT_BOARD})        # Default Board ID, when not specified
set(ARDUINO_CPU           ${X_ARDUINO_CPU})
SET(ARDUINO_UPLOAD_METHOD ${X_ARDUINO_UPLOAD_METHOD}) # Use blackmagic link, if you comment it out you'll use DFU => 8kB flash
set(ARDUINO_DEFAULT_PORT ttyACM0) # Default Port, when not specified

#
#print_board_list()
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

set(ARDUINO_DEFAULT_PORT ttyACM0) # Default Port, when not specified
MESSAGE(STATUS "\tUsing ${EXTENSION} MCU ")


# EOF
