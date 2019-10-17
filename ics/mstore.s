	.file	"mstore.c"
	.intel_syntax noprefix
	.text
	.globl	mulstore
	.type	mulstore, @function
mulstore:
	push	rbx
	mov	rbx, rdx
	call	mul2@PLT
	mov	QWORD PTR [rbx], rax
	pop	rbx
	ret
	.size	mulstore, .-mulstore
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
