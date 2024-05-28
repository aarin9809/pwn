; mac OS 에서는 구동이 안된다는 것을 확인하고 Linux 환경에서 작업했습니다. 파일 실행 시 명령어는 다음과 같이 했을때 작동을 확인했습니다.

; nasm -f elf64 -o hello.s hello.asm
; ld -o hello hello.s

; 파일 실행에 있어 편의를 위해 hello.asm으로 이름 바꿔서 실행하시는것을 추천드립니다.


section .data   ; 데이터 섹션은 프로그램에서 사용하는 정적 데이터를 저장함.
	msg db "Hello World!"       ; msg에 Hello world를 저장함. db는 database가 아니라 define byte를 의미함. 각문자를 1바이르토 정의

section .text           ; 실질적인 코드가 시작되는 부분임.
	global _start       ; start라는 라벨을 전역으로 선언. 프로그램의 실행 시작점을 가리킴.
    
 _start:                 ; 프로그램 시작.
    mov rax, 1      ; syscall number 1을 rax 레지에 저장. 1은 write를 의미함.
    mov rdi, 1      ; stdout number 1을 rdi에 저장함. 파일 디스크립터임.
    mov rsi, msg    ; 출력할 문자열이 담긴 msg의 주소를 rsi 레지에 저장함.
    mov rdx, 12     ; rdx에 12 저장. 문자열 길이를 의미함.
    syscall         ; rax 값에 따라 시스템 콜을 호출.
    
    mov rax, 60     ; syscall number 60을 rax에 저장. 60은 exit을 의미함.
    mov rdi, 0      ; 0을 rdi에 저장. 프로그램 정상종료.
    syscall         ; rax에 저장된 syscall 호출. 정상 종료하는 시스템콜임.