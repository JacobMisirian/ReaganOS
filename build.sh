#!/bin/bash

rm src/*.o > /dev/null
rm src/*/*.o > /dev/null
rm src/*/*/*.o > /dev/null
make
