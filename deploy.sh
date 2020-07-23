#!/bin/bash

ARDUINO_HOME="$HOME/.local/opt/arduino"

$ARDUINO_HOME/hardware/tools/avr/bin/avrdude             \
    -v -D                                                \
    -C $ARDUINO_HOME/hardware/tools/avr/etc/avrdude.conf \
    -P /dev/ttyUSB2                                      \
    -b 57600                                             \
    -c arduino                                           \
    -p m328p                                             \
    -U flash:w:build/"$1".hex:i                          \
    -U eeprom:w:build/"$1".eep:i
