
SET(SUB ${CMAKE_CURRENT_SOURCE_DIR}/tft)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

SET(SRCS
        ${SUB}/TFT_eSPI.cpp
        ${SUB}/TFT_eSPI_draw.cpp
      #  ${SUB}/TFT_eSPI_font.cpp
        TFT_eSPI_extended.cpp
        TFT_eSPI_extended_glyph.cpp
        TFT_eSPI_extended_glyph_hl.cpp
)
generate_arduino_library(${libPrefix}TFT_eSPI 
                            SRCS ${SRCS}
                            BOARD ${ARDUINO_DEFAULT_BOARD}
                        )
target_include_directories(${libPrefix}TFT_eSPI PRIVATE ${SUB} ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(${libPrefix}TFT_eSPI PRIVATE SPI_HAS_TRANSACTION ltoa=itoa CUSTOM_DRIVER=1)

EXPORT_LIBRARY(TFT_eSPI FLAGS "" INCLUDE_PATHS "${CMAKE_CURRENT_SOURCE_DIR};${CMAKE_CURRENT_SOURCE_DIR}/tft;${CMAKE_CURRENT_SOURCE_DIR}/tft/Fonts/GFXFF/" NAME ${libPrefix}TFT_eSPI)
