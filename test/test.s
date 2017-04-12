	.text
	.file	"test.cpp"
	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp0:
	.cfi_def_cfa_offset 16
.Ltmp1:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp2:
	.cfi_def_cfa_register %rbp
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	movl	$1, -12(%rbp)
.LBB0_1:                                # =>This Inner Loop Header: Depth=1
	cmpl	$100000000, -12(%rbp)   # imm = 0x5F5E100
	jg	.LBB0_4
# BB#2:                                 #   in Loop: Header=BB0_1 Depth=1
	movl	-12(%rbp), %eax
	shll	$1, %eax
	orl	$1, %eax
	addl	-8(%rbp), %eax
	movl	%eax, -8(%rbp)
# BB#3:                                 #   in Loop: Header=BB0_1 Depth=1
	movl	-12(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -12(%rbp)
	jmp	.LBB0_1
.LBB0_4:
	xorl	%eax, %eax
	popq	%rbp
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc


	.ident	"clang version 3.8.0-2ubuntu4 (tags/RELEASE_380/final)"
	.section	".note.GNU-stack","",@progbits
