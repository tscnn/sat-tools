	.file	"testarray.cpp"
	.section	.text._ZNSt6vectorIiSaIiEED2Ev,"axG",@progbits,_ZNSt6vectorIiSaIiEED5Ev,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZNSt6vectorIiSaIiEED2Ev
	.type	_ZNSt6vectorIiSaIiEED2Ev, @function
_ZNSt6vectorIiSaIiEED2Ev:
.LFB591:
	.cfi_startproc
	movq	(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L1
	jmp	_ZdlPv
	.p2align 4,,10
	.p2align 3
.L1:
	rep ret
	.cfi_endproc
.LFE591:
	.size	_ZNSt6vectorIiSaIiEED2Ev, .-_ZNSt6vectorIiSaIiEED2Ev
	.weak	_ZNSt6vectorIiSaIiEED1Ev
	.set	_ZNSt6vectorIiSaIiEED1Ev,_ZNSt6vectorIiSaIiEED2Ev
	.text
	.p2align 4,,15
	.globl	_Z4getai
	.type	_Z4getai, @function
_Z4getai:
.LFB486:
	.cfi_startproc
	movq	a(%rip), %rax
	movslq	%edi, %rdi
	movl	(%rax,%rdi,4), %eax
	ret
	.cfi_endproc
.LFE486:
	.size	_Z4getai, .-_Z4getai
	.p2align 4,,15
	.globl	_Z4getbi
	.type	_Z4getbi, @function
_Z4getbi:
.LFB487:
	.cfi_startproc
	movslq	%edi, %rdi
	movl	b(,%rdi,4), %eax
	ret
	.cfi_endproc
.LFE487:
	.size	_Z4getbi, .-_Z4getbi
	.p2align 4,,15
	.globl	_Z4getvi
	.type	_Z4getvi, @function
_Z4getvi:
.LFB488:
	.cfi_startproc
	movq	v(%rip), %rax
	movslq	%edi, %rdi
	movl	(%rax,%rdi,4), %eax
	ret
	.cfi_endproc
.LFE488:
	.size	_Z4getvi, .-_Z4getvi
	.p2align 4,,15
	.globl	_Z4getwi
	.type	_Z4getwi, @function
_Z4getwi:
.LFB489:
	.cfi_startproc
	movq	w(%rip), %rax
	movslq	%edi, %rdi
	movl	(%rax,%rdi,4), %eax
	ret
	.cfi_endproc
.LFE489:
	.size	_Z4getwi, .-_Z4getwi
	.section	.text._ZNSt6vectorIiSaIiEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPiS1_EERKi,"axG",@progbits,_ZNSt6vectorIiSaIiEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPiS1_EERKi,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZNSt6vectorIiSaIiEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPiS1_EERKi
	.type	_ZNSt6vectorIiSaIiEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPiS1_EERKi, @function
_ZNSt6vectorIiSaIiEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPiS1_EERKi:
.LFB528:
	.cfi_startproc
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
	movq	%rsi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movq	%rdi, %rbx
	subq	$16, %rsp
	.cfi_def_cfa_offset 64
	movq	8(%rdi), %rax
	cmpq	16(%rdi), %rax
	je	.L9
	testq	%rax, %rax
	je	.L10
	movl	-4(%rax), %ecx
	movl	%ecx, (%rax)
.L10:
	leaq	4(%rax), %rcx
	movq	%rcx, 8(%rbx)
	movl	(%rdx), %ebx
	leaq	-4(%rax), %rdx
	subq	%rbp, %rdx
	sarq	$2, %rdx
	testq	%rdx, %rdx
	je	.L11
	salq	$2, %rdx
	movq	%rbp, %rsi
	subq	%rdx, %rax
	movq	%rax, %rdi
	call	memmove
.L11:
	movl	%ebx, 0(%rbp)
.L8:
	addq	$16, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	popq	%rbx
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
.L9:
	.cfi_restore_state
	movq	(%rdi), %rcx
	subq	%rcx, %rax
	sarq	$2, %rax
	testq	%rax, %rax
	je	.L13
	leaq	(%rax,%rax), %rsi
	cmpq	%rsi, %rax
	jbe	.L38
.L14:
	movq	%rbp, %r12
	movq	$-4, %r13
	subq	%rcx, %r12
	sarq	$2, %r12
.L21:
	movq	%r13, %rdi
	movq	%rdx, 8(%rsp)
	call	_Znwm
	movq	(%rbx), %rsi
	movq	%rbp, %rdi
	movq	8(%rsp), %rdx
	movq	%rax, %r14
	subq	%rsi, %rdi
	sarq	$2, %rdi
	movq	%rdi, %r8
.L15:
	leaq	(%r14,%r12,4), %rax
	testq	%rax, %rax
	je	.L16
	movl	(%rdx), %edx
	movl	%edx, (%rax)
.L16:
	testq	%rdi, %rdi
	leaq	0(,%r8,4), %r12
	je	.L18
	movq	%r12, %rdx
	movq	%r14, %rdi
	call	memmove
.L18:
	movq	8(%rbx), %rcx
	leaq	4(%r14,%r12), %r8
	xorl	%r12d, %r12d
	subq	%rbp, %rcx
	sarq	$2, %rcx
	testq	%rcx, %rcx
	je	.L19
	leaq	0(,%rcx,4), %r12
	movq	%r8, %rdi
	movq	%rbp, %rsi
	movq	%r12, %rdx
	call	memmove
	movq	%rax, %r8
.L19:
	movq	(%rbx), %rdi
	addq	%r8, %r12
	testq	%rdi, %rdi
	je	.L20
	call	_ZdlPv
.L20:
	addq	%r14, %r13
	movq	%r14, (%rbx)
	movq	%r12, 8(%rbx)
	movq	%r13, 16(%rbx)
	jmp	.L8
	.p2align 4,,10
	.p2align 3
.L13:
	movq	%rsi, %r12
	movl	$4, %r13d
	subq	%rcx, %r12
	sarq	$2, %r12
	jmp	.L21
.L38:
	movabsq	$4611686018427387903, %rdi
	cmpq	%rdi, %rsi
	ja	.L14
	movq	%rbp, %r12
	leaq	0(,%rax,8), %r13
	subq	%rcx, %r12
	sarq	$2, %r12
	testq	%rsi, %rsi
	jne	.L21
	movq	%r12, %r8
	movq	%r12, %rdi
	movq	%rcx, %rsi
	xorl	%r14d, %r14d
	jmp	.L15
	.cfi_endproc
.LFE528:
	.size	_ZNSt6vectorIiSaIiEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPiS1_EERKi, .-_ZNSt6vectorIiSaIiEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPiS1_EERKi
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB490:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movl	$4000, %edi
	call	_Znam
	movl	$0, (%rsp)
	movq	%rax, a(%rip)
	xorl	%edx, %edx
	jmp	.L44
	.p2align 4,,10
	.p2align 3
.L47:
	movq	a(%rip), %rax
.L44:
	movslq	%edx, %rcx
	movq	v+8(%rip), %rsi
	cmpq	v+16(%rip), %rsi
	movl	%edx, (%rax,%rcx,4)
	movl	(%rsp), %eax
	movslq	%eax, %rdx
	movl	%eax, b(,%rdx,4)
	je	.L40
	testq	%rsi, %rsi
	je	.L41
	movl	%eax, (%rsi)
	movl	(%rsp), %eax
.L41:
	addq	$4, %rsi
	movq	%rsi, v+8(%rip)
.L42:
	movq	w(%rip), %rdx
	movslq	%eax, %rcx
	movl	%eax, (%rdx,%rcx,4)
	movl	(%rsp), %eax
	leal	1(%rax), %edx
	cmpl	$999, %edx
	movl	%edx, (%rsp)
	jle	.L47
	movl	b+400(%rip), %eax
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L40:
	.cfi_restore_state
	movq	%rsp, %rdx
	movl	$v, %edi
	call	_ZNSt6vectorIiSaIiEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPiS1_EERKi
	movl	(%rsp), %eax
	jmp	.L42
	.cfi_endproc
.LFE490:
	.size	main, .-main
	.p2align 4,,15
	.type	_GLOBAL__sub_I_a, @function
_GLOBAL__sub_I_a:
.LFB593:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$__dso_handle, %edx
	movl	$v, %esi
	movl	$_ZNSt6vectorIiSaIiEED1Ev, %edi
	movq	$0, v(%rip)
	movq	$0, v+8(%rip)
	movq	$0, v+16(%rip)
	call	__cxa_atexit
	movl	$4000, %edi
	movq	$0, w(%rip)
	movq	$0, w+8(%rip)
	movq	$0, w+16(%rip)
	call	_Znwm
	leaq	4000(%rax), %rsi
	testb	$1, %al
	movq	%rax, w(%rip)
	movq	%rax, %rdi
	movl	$4000, %edx
	movq	%rsi, w+16(%rip)
	jne	.L74
.L49:
	testb	$2, %dil
	jne	.L75
.L50:
	testb	$4, %dil
	jne	.L76
.L51:
	movl	%edx, %ecx
	xorl	%eax, %eax
	shrl	$3, %ecx
	testb	$4, %dl
	rep stosq
	je	.L52
	movl	$0, (%rdi)
	addq	$4, %rdi
.L52:
	testb	$2, %dl
	je	.L53
	movw	$0, (%rdi)
	addq	$2, %rdi
.L53:
	andl	$1, %edx
	je	.L54
	movb	$0, (%rdi)
.L54:
	movq	%rsi, w+8(%rip)
	movl	$__dso_handle, %edx
	movl	$w, %esi
	movl	$_ZNSt6vectorIiSaIiEED1Ev, %edi
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	jmp	__cxa_atexit
.L74:
	.cfi_restore_state
	movb	$0, (%rax)
	addq	$1, %rdi
	movb	$-97, %dl
	jmp	.L49
.L75:
	movw	$0, (%rdi)
	subl	$2, %edx
	addq	$2, %rdi
	jmp	.L50
.L76:
	movl	$0, (%rdi)
	subl	$4, %edx
	addq	$4, %rdi
	jmp	.L51
	.cfi_endproc
.LFE593:
	.size	_GLOBAL__sub_I_a, .-_GLOBAL__sub_I_a
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I_a
	.globl	w
	.bss
	.align 16
	.type	w, @object
	.size	w, 24
w:
	.zero	24
	.globl	v
	.align 16
	.type	v, @object
	.size	v, 24
v:
	.zero	24
	.globl	b
	.align 32
	.type	b, @object
	.size	b, 4000
b:
	.zero	4000
	.globl	a
	.align 16
	.type	a, @object
	.size	a, 8
a:
	.zero	8
	.hidden	__dso_handle
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
