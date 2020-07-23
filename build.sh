#!/bin/bash

ARDUINO_HOME="$HOME/.local/opt/arduino"

PATH="$ARDUINO_HOME:$PATH"

mkdir -p build

arduino-builder                                                                \
    -hardware "$ARDUINO_HOME/hardware"                                         \
    -tools "$ARDUINO_HOME/tools"                                               \
    -fqbn "arduino:avr:nano"                                                   \
    -libraries "$ARDUINO_HOME/libraries"                                       \
    -prefs "compiler.path=$ARDUINO_HOME/hardware/tools/avr/bin/"               \
    -prefs "tools.ctags.path=$ARDUINO_HOME/tools-builder/ctags/5.8-arduino11/" \
    -verbose                                                                   \
    -build-path build                                                          \
    "$1"
