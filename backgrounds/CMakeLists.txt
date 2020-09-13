
SET(SRCS assets.cpp fonts.cpp )

generate_arduino_library(${libPrefix}backgrounds 
                            SRCS ${SRCS}
                            BOARD ${ARDUINO_DEFAULT_BOARD}
                        )

target_include_directories(${libPrefix}backgrounds  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})                        
