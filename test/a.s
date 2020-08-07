	.file	"a.c"
	.text
	.p2align 4
	.globl	tmult_ok
	.type	tmult_ok, @function
tmult_ok:
.LFB0:
	.cfi_startproc
	imulq	%rsi, %rdi
#APP
# 4 "a.c" 1
	setae %al
# 0 "" 2
#NO_APP
	movzbl	%al, %eax
	movq	%rdi, (%rdx)
	ret
	.cfi_endproc
.LFE0:
	.size	tmult_ok, .-tmult_ok
	.p2align 4
	.globl	tmult_ok0
	.type	tmult_ok0, @function
tmult_ok0:
.LFB1:
	.cfi_startproc
	imulq	%rsi, %rdi
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
#APP
# 13 "a.c" 1
	setae %bl;movzbl %bl, %eax
# 0 "" 2
#NO_APP
	popq	%rbx
	.cfi_def_cfa_offset 8
	movq	%rdi, (%rdx)
	ret
	.cfi_endproc
.LFE1:
	.size	tmult_ok0, .-tmult_ok0
	.p2align 4
	.globl	umult_ok
	.type	umult_ok, @function
umult_ok:
.LFB2:
	.cfi_startproc
	movq	%rdx, %r8
#APP
# 25 "a.c" 1
	movq %rdi, %rax;mulq %rsi;movq %rax, (%r8);setae %dil
# 0 "" 2
#NO_APP
	movzbl	%dil, %eax
	ret
	.cfi_endproc
.LFE2:
	.size	umult_ok, .-umult_ok
	.ident	"GCC: (GNU) 10.1.0"
	.section	.note.GNU-stack,"",@progbits
