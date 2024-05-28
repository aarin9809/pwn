#!/usr/bin/env python3
# Name : shellcraft.py

from pwn import *
context.arch = 'amd64'

code = shellcraft.sh()  # 대상 아키텍처 x86_64

code = shellcraft.sh()  # 셸을 실행하는 셸 코드
print(code)
