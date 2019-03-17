	.text
	.file	"a.c"
	.globl	f                       # -- Begin function f
	.p2align	4, 0x90
	.type	f,@function
f:                                      # @f
	.cfi_startproc
# %bb.0:
	xorl	%eax, %eax
	retq
.Lfunc_end0:
	.size	f, .Lfunc_end0-f
	.cfi_endproc
                                        # -- End function
	.globl	g                       # -- Begin function g
	.p2align	4, 0x90
	.type	g,@function
g:                                      # @g
	.cfi_startproc
# %bb.0:
	xorl	%eax, %eax
	retq
.Lfunc_end1:
	.size	g, .Lfunc_end1-g
	.cfi_endproc
                                        # -- End function
	.globl	h                       # -- Begin function h
	.p2align	4, 0x90
	.type	h,@function
h:                                      # @h
	.cfi_startproc
# %bb.0:
	xorl	%eax, %eax
	retq
.Lfunc_end2:
	.size	h, .Lfunc_end2-h
	.cfi_endproc
                                        # -- End function
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	$.L.str, %edi
	xorl	%esi, %esi
	xorl	%eax, %eax
	callq	printf
	movl	$.L.str, %edi
	xorl	%esi, %esi
	xorl	%eax, %eax
	callq	printf
	movl	$.L.str, %edi
	xorl	%esi, %esi
	xorl	%eax, %eax
	callq	printf
	xorl	%eax, %eax
	popq	%rcx
	retq
.Lfunc_end3:
	.size	main, .Lfunc_end3-main
	.cfi_endproc
                                        # -- End function
	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"%lld\n"
	.size	.L.str, 6


	.ident	"clang version 6.0.0-1ubuntu2 (tags/RELEASE_600/final)"
	.section	".note.GNU-stack","",@progbits
