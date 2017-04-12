	.text
	.file	"test.cpp"
	.globl	_Z4rsoni
	.align	16, 0x90
	.type	_Z4rsoni,@function
_Z4rsoni:                               # @_Z4rsoni
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
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %edi
	shll	$1, %edi
	orl	$1, %edi
	movl	%edi, %eax
	popq	%rbp
	retq
.Lfunc_end0:
	.size	_Z4rsoni, .Lfunc_end0-_Z4rsoni
	.cfi_endproc

	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:
	pushq	%rbp
.Ltmp3:
	.cfi_def_cfa_offset 16
.Ltmp4:
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
.Ltmp5:
	.cfi_def_cfa_register %rbp
	subq	$16, %rsp
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	movl	$1, -12(%rbp)
.LBB1_1:                                # =>This Inner Loop Header: Depth=1
	cmpl	$100000000, -12(%rbp)   # imm = 0x5F5E100
	jg	.LBB1_4
# BB#2:                                 #   in Loop: Header=BB1_1 Depth=1
	movl	-12(%rbp), %edi
	callq	_Z4rsoni
	addl	-8(%rbp), %eax
	movl	%eax, -8(%rbp)
# BB#3:                                 #   in Loop: Header=BB1_1 Depth=1
	movl	-12(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -12(%rbp)
	jmp	.LBB1_1
.LBB1_4:
	xorl	%eax, %eax
	addq	$16, %rsp
	popq	%rbp
	retq
.Lfunc_end1:
	.size	main, .Lfunc_end1-main
	.cfi_endproc


	.ident	"clang version 3.8.0-2ubuntu4 (tags/RELEASE_380/final)"
	.section	".note.GNU-stack","",@progbits
