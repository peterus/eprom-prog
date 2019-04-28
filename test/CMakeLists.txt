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

SET(EXECUTABLE_NAME "EPROM-Test")

FILE(GLOB_RECURSE _SOURCES *.c)
FILE(GLOB_RECURSE _HEADERS *.h)
SOURCE_GROUP("Header Files" FILES ${_HEADERS})

add_avr_executable(${EXECUTABLE_NAME} ${_SOURCES} ${_HEADERS})

avr_target_link_libraries(${EXECUTABLE_NAME} HAL)

