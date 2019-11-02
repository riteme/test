	.file	"a.c"
	.text
	.p2align 4,,15
	.globl	imul
	.type	imul, @function
imul:
.LFB0:
	.cfi_startproc
	leal	(%rdi,%rdi,4), %eax
	sall	$2, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	imul, .-imul
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
