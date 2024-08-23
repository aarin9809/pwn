* Stack Canary

rsp - 0x10 만큼의 buf 크기 생성
fs:[0x28]를 rax에 저장
rax값을 rbp - 8 위치에 저장

eax 값 0으로 초기화

rbp - 10 값을 rax에 저장

edx에 0x20 값 저장

rsi에 rax 값을 저장

edi 0으로 초기화

read() 호출

eax 0으로 초기화

rbp - 8 값을 rdx에 저장


현재 스택 상황

BUF - Canary - SFP - RET

BUF = 0x10

canary = rbp - 0x8

SFP = 0x8 byte

