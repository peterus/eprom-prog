##########################################################################
# "THE ANY BEVERAGE-WARE LICENSE" (Revision 42 - based on beer-ware
# license):
# <dev@layer128.net> wrote this file. As long as you retain this notice
# you can do whatever you want with this stuff. If we meet some day, and
# you think this stuff is worth it, you can buy me a be(ve)er(age) in
# return. (I don't like beer much.)
#
# Matthias Kleemann
##########################################################################

cmake_minimum_required(VERSION 2.8)

### TOOLCHAIN SETUP AREA #################################################
# Set any variables used in the toolchain prior project() call. In that
# case they are already set and used.
##########################################################################

##########################################################################
# tools to beused for programming the AVR
##########################################################################
set(AVR_UPLOADTOOL avrdude)
#set(AVR_PROGRAMMER avrispmkII)
#set(AVR_UPLOADTOOL_PORT usb)
set(AVR_PROGRAMMER stk500v2)
set(AVR_UPLOADTOOL_PORT /dev/ttyACM0)

##########################################################################
# AVR and fuses needs to be set
##########################################################################
set(AVR_MCU atmega2560)
set(AVR_H_FUSE 0xd9)
set(AVR_L_FUSE 0xc3)
set(MCU_SPEED "16000000UL")

### END TOOLCHAIN SETUP AREA #############################################

# Intentionally left blank, due to a different approach of using the
# toolchain file via -DCMAKE_TOOLCHAIN_FILE=path/to/generic-gcc-avr.cmake
# at the cmake command line call
#
include(AVRhal/generic-gcc-avr.cmake)

##########################################################################
# name your project
##########################################################################
project(EPROM)

##########################################################################
# status messages
##########################################################################
message(STATUS "Current uploadtool is: ${AVR_UPLOADTOOL}")
message(STATUS "Current programmer is: ${AVR_PROGRAMMER}")
message(STATUS "Current upload port is: ${AVR_UPLOADTOOL_PORT}")
message(STATUS "Current uploadtool options are: ${AVR_UPLOADTOOL_OPTIONS}")
message(STATUS "Current MCU is set to: ${AVR_MCU}")
message(STATUS "Current H_FUSE is set to: ${AVR_H_FUSE}")
message(STATUS "Current L_FUSE is set to: ${AVR_L_FUSE}")

##########################################################################
# set build type
##########################################################################
if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

##########################################################################
# include search paths
##########################################################################
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/AVRhal/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/AVRhal/driver)

##########################################################################
# building library and application in their subdirectories
##########################################################################

add_subdirectory(AVRhal)
add_subdirectory(src)

