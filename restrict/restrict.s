	.file	"restrict.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4,,15
	.globl	incrementAndAdd
	.type	incrementAndAdd, @function
incrementAndAdd:
.LFB23:
	.cfi_startproc
	movl	4(%rsi), %eax
	addl	4(%rdi), %eax
	ret
	.cfi_endproc
.LFE23:
	.size	incrementAndAdd, .-incrementAndAdd
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.section	.text.unlikely
.LCOLDB1:
	.text
.LHOTB1:
	.p2align 4,,15
	.globl	incrementAndAddRestrict
	.type	incrementAndAddRestrict, @function
incrementAndAddRestrict:
.LFB24:
	.cfi_startproc
	movl	4(%rsi), %eax
	addl	4(%rdi), %eax
	ret
	.cfi_endproc
.LFE24:
	.size	incrementAndAddRestrict, .-incrementAndAddRestrict
	.section	.text.unlikely
.LCOLDE1:
	.text
.LHOTE1:
	.section	.text.unlikely
.LCOLDB2:
	.text
.LHOTB2:
	.p2align 4,,15
	.globl	add5AndAdd
	.type	add5AndAdd, @function
add5AndAdd:
.LFB25:
	.cfi_startproc
	addl	$5, (%rdi)
	movl	(%rsi), %eax
	addl	$5, %eax
	movl	%eax, (%rsi)
	addl	(%rdi), %eax
	ret
	.cfi_endproc
.LFE25:
	.size	add5AndAdd, .-add5AndAdd
	.section	.text.unlikely
.LCOLDE2:
	.text
.LHOTE2:
	.section	.text.unlikely
.LCOLDB3:
	.text
.LHOTB3:
	.p2align 4,,15
	.globl	add5AndAddRestrict
	.type	add5AndAddRestrict, @function
add5AndAddRestrict:
.LFB26:
	.cfi_startproc
	movl	(%rdi), %eax
	leal	5(%rax), %edx
	movl	(%rsi), %eax
	movl	%edx, (%rdi)
	addl	$5, %eax
	movl	%eax, (%rsi)
	addl	%edx, %eax
	ret
	.cfi_endproc
.LFE26:
	.size	add5AndAddRestrict, .-add5AndAddRestrict
	.section	.text.unlikely
.LCOLDE3:
	.text
.LHOTE3:
	.section	.text.unlikely
.LCOLDB4:
	.text
.LHOTB4:
	.p2align 4,,15
	.globl	overwrite
	.type	overwrite, @function
overwrite:
.LFB27:
	.cfi_startproc
	movl	$5, (%rdi)
	movl	$6, (%rsi)
	movl	(%rdi), %eax
	addl	$6, %eax
	ret
	.cfi_endproc
.LFE27:
	.size	overwrite, .-overwrite
	.section	.text.unlikely
.LCOLDE4:
	.text
.LHOTE4:
	.section	.text.unlikely
.LCOLDB5:
	.text
.LHOTB5:
	.p2align 4,,15
	.globl	overwriteRestrict
	.type	overwriteRestrict, @function
overwriteRestrict:
.LFB28:
	.cfi_startproc
	movl	$5, (%rdi)
	movl	$6, (%rsi)
	movl	$11, %eax
	ret
	.cfi_endproc
.LFE28:
	.size	overwriteRestrict, .-overwriteRestrict
	.section	.text.unlikely
.LCOLDE5:
	.text
.LHOTE5:
	.section	.text.unlikely
.LCOLDB6:
	.text
.LHOTB6:
	.p2align 4,,15
	.globl	overwriteTheSame
	.type	overwriteTheSame, @function
overwriteTheSame:
.LFB29:
	.cfi_startproc
	movl	$5, (%rdi)
	movl	$5, (%rsi)
	movl	(%rdi), %eax
	addl	$5, %eax
	ret
	.cfi_endproc
.LFE29:
	.size	overwriteTheSame, .-overwriteTheSame
	.section	.text.unlikely
.LCOLDE6:
	.text
.LHOTE6:
	.section	.text.unlikely
.LCOLDB7:
	.text
.LHOTB7:
	.p2align 4,,15
	.globl	multiplyArrays
	.type	multiplyArrays, @function
multiplyArrays:
.LFB30:
	.cfi_startproc
	testq	%rcx, %rcx
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	je	.L8
	movq	%rsi, %rax
	andl	$15, %eax
	shrq	$2, %rax
	negq	%rax
	andl	$3, %eax
	cmpq	%rcx, %rax
	cmova	%rcx, %rax
	cmpq	$4, %rcx
	ja	.L30
	movq	%rcx, %rax
.L10:
	movl	(%rsi), %r8d
	imull	(%rdx), %r8d
	cmpq	$1, %rax
	movl	%r8d, (%rdi)
	je	.L22
	movl	4(%rsi), %r8d
	imull	4(%rdx), %r8d
	cmpq	$2, %rax
	movl	%r8d, 4(%rdi)
	je	.L23
	movl	8(%rsi), %r8d
	imull	8(%rdx), %r8d
	cmpq	$4, %rax
	movl	%r8d, 8(%rdi)
	jne	.L24
	movl	12(%rdx), %r8d
	movl	$4, %r11d
	imull	12(%rsi), %r8d
	movl	%r8d, 12(%rdi)
	movl	$4, %r8d
.L12:
	cmpq	%rax, %rcx
	je	.L8
.L11:
	movq	%rcx, %r12
	leaq	-1(%rcx), %r9
	subq	%rax, %r12
	leaq	-4(%r12), %r10
	subq	%rax, %r9
	shrq	$2, %r10
	addq	$1, %r10
	cmpq	$2, %r9
	leaq	0(,%r10,4), %rbp
	jbe	.L14
	salq	$2, %rax
	xorl	%r9d, %r9d
	xorl	%ebx, %ebx
	leaq	(%rsi,%rax), %r13
	leaq	(%rdx,%rax), %r14
	addq	%rdi, %rax
.L15:
	movdqu	(%r14,%r9), %xmm0
	addq	$1, %rbx
	movdqa	%xmm0, %xmm1
	movdqa	%xmm0, %xmm2
	movdqa	0(%r13,%r9), %xmm0
	pmuludq	0(%r13,%r9), %xmm1
	pshufd	$8, %xmm1, %xmm1
	psrlq	$32, %xmm2
	psrlq	$32, %xmm0
	pmuludq	%xmm2, %xmm0
	pshufd	$8, %xmm0, %xmm0
	punpckldq	%xmm0, %xmm1
	movups	%xmm1, (%rax,%r9)
	addq	$16, %r9
	cmpq	%rbx, %r10
	ja	.L15
	addl	%ebp, %r8d
	addq	%rbp, %r11
	cmpq	%rbp, %r12
	je	.L8
.L14:
	movl	(%rdx,%r11,4), %eax
	imull	(%rsi,%r11,4), %eax
	movl	%eax, (%rdi,%r11,4)
	leal	1(%r8), %eax
	cltq
	cmpq	%rax, %rcx
	jbe	.L8
	movl	(%rsi,%rax,4), %r9d
	addl	$2, %r8d
	imull	(%rdx,%rax,4), %r9d
	movslq	%r8d, %r8
	cmpq	%r8, %rcx
	movl	%r9d, (%rdi,%rax,4)
	jbe	.L8
	movl	(%rsi,%r8,4), %eax
	imull	(%rdx,%r8,4), %eax
	movl	%eax, (%rdi,%r8,4)
.L8:
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L30:
	.cfi_restore_state
	testq	%rax, %rax
	jne	.L10
	xorl	%r11d, %r11d
	xorl	%r8d, %r8d
	jmp	.L11
	.p2align 4,,10
	.p2align 3
.L24:
	movl	$3, %r11d
	movl	$3, %r8d
	jmp	.L12
	.p2align 4,,10
	.p2align 3
.L22:
	movl	$1, %r11d
	movl	$1, %r8d
	jmp	.L12
	.p2align 4,,10
	.p2align 3
.L23:
	movl	$2, %r11d
	movl	$2, %r8d
	jmp	.L12
	.cfi_endproc
.LFE30:
	.size	multiplyArrays, .-multiplyArrays
	.section	.text.unlikely
.LCOLDE7:
	.text
.LHOTE7:
	.section	.text.unlikely
.LCOLDB8:
	.section	.text.startup,"ax",@progbits
.LHOTB8:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB31:
	.cfi_startproc
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE31:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE8:
	.section	.text.startup
.LHOTE8:
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
