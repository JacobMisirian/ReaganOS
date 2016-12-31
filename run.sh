#!/bin/bash

make
make iso
qemu-system-i386 bin/ReaganOS.iso
