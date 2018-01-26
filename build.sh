#!/bin/bash

VENV="${VENV:-mbed}"

if [ -z "$VIRTUAL_ENV" ]; then
    VIRTUAL_ENV="${WORKON_HOME:-$HOME/.virtualenvs}/$VENV"
    if [ -d "${WORKON_HOME:-$HOME/.virtualenvs}/$VENV" ]; then
        export PATH="$VIRTUAL_ENV/bin:$PATH"
    fi
fi

TOOLCHAIN="${TOOLCHAIN:-$(mbed toolchain | cut -d ' ' -f 2)}"
TARGET="${TARGET:-$(mbed target | cut -d ' ' -f 2)}"

if [ "x$1" = "x-f" ]; then
    FLASH=yes
    shift
fi

mbed compile -t $TOOLCHAIN -m $TARGET "$@"

if [ -n "$FLASH" ]; then
    st-flash --reset write ./BUILD/$TARGET/$TOOLCHAIN/*.bin 0x8000000
fi
