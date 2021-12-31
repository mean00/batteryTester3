
SET(SRCS assets.cpp fonts.cpp )

ADD_LIBRARY(backgrounds 
                             ${SRCS}
                            
                        )
include_directories(.)
target_include_directories(backgrounds  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})                        
