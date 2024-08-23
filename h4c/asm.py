#!/usr/bin/env python3
# Name : asm.py

from pwn import *
context.arch = 'amd64'  #익스 대상 아키텍처 x86-64

code = shellcraft.sh()
code = asm(code)

print(code)
