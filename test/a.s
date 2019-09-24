	.file	"a.cpp"
	.text
	.globl	_Z13asbdasfasdsafii
	.type	_Z13asbdasfasdsafii, @function
_Z13asbdasfasdsafii:
.LFB46:
	.cfi_startproc
	leal	(%rdi,%rsi), %eax
	ret
	.cfi_endproc
.LFE46:
	.size	_Z13asbdasfasdsafii, .-_Z13asbdasfasdsafii
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d%d"
.LC1:
	.string	"%d + %d = %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB47:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	leaq	4(%rsp), %rdx
	movq	%rsp, %rsi
	leaq	.LC0(%rip), %rdi
	call	scanf@PLT
	movl	4(%rsp), %ebp
	movl	(%rsp), %ebx
	movl	%ebp, %esi
	movl	%ebx, %edi
	call	_Z13asbdasfasdsafii
	movl	%eax, %r8d
	movl	%ebp, %ecx
	movl	%ebx, %edx
	leaq	.LC1(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movq	8(%rsp), %rcx
	xorq	%fs:40, %rcx
	jne	.L5
	movl	$0, %eax
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L5:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE47:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
