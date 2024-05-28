; Name: cdecl.s
	.file	"cdecl.c"
	.intel_syntax noprefix
	.text
	.globl	callee
	.type	callee, @function
callee:
	nop
	ret	; 스택을 정리하지 않고 리턴한다.
	.size	callee, .-callee
	.globl	caller
	.type	caller, @function
caller:
	push	2	;2를 스택에 저장하여 callee의 인자로 전달한다.
	push	1	;1을 스택에 저장하여 callee의 인자로 전달한다.
	call	callee
	add	esp, 8	; 스택을 정리한다.(push를 2번하였기 때문에 8byte만큼 esp가 증가되어 있다.)
	nop
	ret
	.size	caller, .-caller
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
