	.file	"a.cpp"
	.text
	.p2align 4,,15
	.globl	_Z1fii
	.type	_Z1fii, @function
_Z1fii:
.LFB57:
	.cfi_startproc
	leal	(%rdi,%rsi), %eax
	ret
	.cfi_endproc
.LFE57:
	.size	_Z1fii, .-_Z1fii
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d%d"
.LC1:
	.string	"%d + %d = %d\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB58:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	leaq	.LC0(%rip), %rdi
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	leaq	4(%rsp), %rdx
	movq	%rsp, %rsi
	call	scanf@PLT
	movl	4(%rsp), %ecx
	movl	(%rsp), %edx
	leaq	.LC1(%rip), %rsi
	movl	$1, %edi
	xorl	%eax, %eax
	leal	(%rcx,%rdx), %r8d
	call	__printf_chk@PLT
	movq	8(%rsp), %rdi
	xorq	%fs:40, %rdi
	jne	.L6
	xorl	%eax, %eax
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L6:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE58:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
