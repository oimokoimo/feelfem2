#!/bin/bash
for f in $(find . -name Makefile); do
    sed -i 's/^CFLAGS[[:space:]]*=.*/& -g -O0 -fno-omit-frame-pointer -fsanitize=address/' "$f"
done
