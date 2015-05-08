	.file	"testcnf.cpp"
	.text
	.align 2
	.p2align 4,,15
	.globl	_ZN3CNFC2Ev
	.type	_ZN3CNFC2Ev, @function
_ZN3CNFC2Ev:
.LFB693:
	.cfi_startproc
	movq	$0, (%rdi)
	movq	$0, 8(%rdi)
	movq	$0, 16(%rdi)
	movq	$0, 24(%rdi)
	movq	$0, 32(%rdi)
	movq	$0, 40(%rdi)
	movq	$0, 48(%rdi)
	movq	$0, 56(%rdi)
	movq	$0, 64(%rdi)
	movl	$0, 72(%rdi)
	movl	$0, 76(%rdi)
	ret
	.cfi_endproc
.LFE693:
	.size	_ZN3CNFC2Ev, .-_ZN3CNFC2Ev
	.globl	_ZN3CNFC1Ev
	.set	_ZN3CNFC1Ev,_ZN3CNFC2Ev
	.align 2
	.p2align 4,,15
	.globl	_ZN3CNF5clearEv
	.type	_ZN3CNF5clearEv, @function
_ZN3CNF5clearEv:
.LFB698:
	.cfi_startproc
	movq	(%rdi), %rax
	movl	$0, 72(%rdi)
	movl	$0, 76(%rdi)
	movq	%rax, 8(%rdi)
	movq	24(%rdi), %rax
	movq	%rax, 32(%rdi)
	movq	48(%rdi), %rax
	movq	%rax, 56(%rdi)
	ret
	.cfi_endproc
.LFE698:
	.size	_ZN3CNF5clearEv, .-_ZN3CNF5clearEv
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"p cnf %d %d\n"
.LC1:
	.string	"%d"
	.text
	.align 2
	.p2align 4,,15
	.globl	_ZN3CNF5writeEP8_IO_FILE
	.type	_ZN3CNF5writeEP8_IO_FILE, @function
_ZN3CNF5writeEP8_IO_FILE:
.LFB700:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	movl	$.LC0, %edx
	xorl	%eax, %eax
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movq	%rsi, %r14
	movl	$1, %esi
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$8, %rsp
	.cfi_def_cfa_offset 64
	movl	72(%rdi), %ecx
	movl	76(%rdi), %r8d
	movq	%r14, %rdi
	call	__fprintf_chk
	movl	76(%rbp), %edx
	testl	%edx, %edx
	jle	.L3
	xorl	%r15d, %r15d
	.p2align 4,,10
	.p2align 3
.L5:
	movq	48(%rbp), %rax
	leaq	0(,%r15,4), %r12
	movl	(%rax,%r15,4), %eax
	testl	%eax, %eax
	je	.L7
	xorl	%r13d, %r13d
	xorl	%ebx, %ebx
	.p2align 4,,10
	.p2align 3
.L8:
	movq	24(%rbp), %rax
	movl	$.LC1, %edx
	movl	$1, %esi
	movq	%r14, %rdi
	addl	$1, %ebx
	addl	(%rax,%r12), %r13d
	movq	0(%rbp), %rax
	movl	(%rax,%r13,4), %ecx
	xorl	%eax, %eax
	movl	%ebx, %r13d
	call	__fprintf_chk
	movq	48(%rbp), %rax
	cmpl	(%rax,%r12), %ebx
	jae	.L7
	movq	%r14, %rsi
	movl	$32, %edi
	call	fputc
	jmp	.L8
	.p2align 4,,10
	.p2align 3
.L7:
	movq	%r14, %rsi
	movl	$10, %edi
	call	fputc
	leal	1(%r15), %eax
	addq	$1, %r15
	cmpl	%eax, 76(%rbp)
	jg	.L5
.L3:
	addq	$8, %rsp
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE700:
	.size	_ZN3CNF5writeEP8_IO_FILE, .-_ZN3CNF5writeEP8_IO_FILE
	.align 2
	.p2align 4,,15
	.globl	_ZN3CNF4minkEv
	.type	_ZN3CNF4minkEv, @function
_ZN3CNF4minkEv:
.LFB701:
	.cfi_startproc
	movq	56(%rdi), %rsi
	movq	48(%rdi), %rdx
	cmpq	%rdx, %rsi
	je	.L12
	movl	(%rdx), %eax
	addq	$4, %rdx
	jmp	.L13
	.p2align 4,,10
	.p2align 3
.L15:
	movl	(%rdx), %ecx
	cmpl	%ecx, %eax
	cmova	%ecx, %eax
	addq	$4, %rdx
.L13:
	cmpq	%rdx, %rsi
	jne	.L15
	rep ret
	.p2align 4,,10
	.p2align 3
.L12:
	movl	(%rsi), %eax
	ret
	.cfi_endproc
.LFE701:
	.size	_ZN3CNF4minkEv, .-_ZN3CNF4minkEv
	.align 2
	.p2align 4,,15
	.globl	_ZN3CNF4maxkEv
	.type	_ZN3CNF4maxkEv, @function
_ZN3CNF4maxkEv:
.LFB702:
	.cfi_startproc
	movq	56(%rdi), %rsi
	movq	48(%rdi), %rdx
	cmpq	%rdx, %rsi
	je	.L17
	movl	(%rdx), %eax
	addq	$4, %rdx
	jmp	.L18
	.p2align 4,,10
	.p2align 3
.L20:
	movl	(%rdx), %ecx
	cmpl	%ecx, %eax
	cmovb	%ecx, %eax
	addq	$4, %rdx
.L18:
	cmpq	%rdx, %rsi
	jne	.L20
	rep ret
	.p2align 4,,10
	.p2align 3
.L17:
	movl	(%rsi), %eax
	ret
	.cfi_endproc
.LFE702:
	.size	_ZN3CNF4maxkEv, .-_ZN3CNF4maxkEv
	.align 2
	.p2align 4,,15
	.globl	_ZN3CNF3litEii
	.type	_ZN3CNF3litEii, @function
_ZN3CNF3litEii:
.LFB703:
	.cfi_startproc
	movq	24(%rdi), %rax
	movslq	%esi, %rsi
	addl	(%rax,%rsi,4), %edx
	movq	(%rdi), %rax
	movl	(%rax,%rdx,4), %eax
	ret
	.cfi_endproc
.LFE703:
	.size	_ZN3CNF3litEii, .-_ZN3CNF3litEii
	.align 2
	.p2align 4,,15
	.globl	_ZN3CNF3varEii
	.type	_ZN3CNF3varEii, @function
_ZN3CNF3varEii:
.LFB704:
	.cfi_startproc
	movq	24(%rdi), %rax
	movslq	%esi, %rsi
	addl	(%rax,%rsi,4), %edx
	movq	(%rdi), %rax
	movl	(%rax,%rdx,4), %ecx
	movl	(%rax,%rdx,4), %edi
	sarl	$31, %ecx
	xorl	%ecx, %edi
	movl	%edi, %eax
	subl	%ecx, %eax
	ret
	.cfi_endproc
.LFE704:
	.size	_ZN3CNF3varEii, .-_ZN3CNF3varEii
	.section	.text._ZN3CNFD2Ev,"axG",@progbits,_ZN3CNFD5Ev,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZN3CNFD2Ev
	.type	_ZN3CNFD2Ev, @function
_ZN3CNFD2Ev:
.LFB707:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	movq	48(%rdi), %rdi
	testq	%rdi, %rdi
	je	.L24
	call	_ZdlPv
.L24:
	movq	24(%rbx), %rdi
	testq	%rdi, %rdi
	je	.L25
	call	_ZdlPv
.L25:
	movq	(%rbx), %rdi
	testq	%rdi, %rdi
	je	.L23
	popq	%rbx
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	jmp	_ZdlPv
	.p2align 4,,10
	.p2align 3
.L23:
	.cfi_restore_state
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE707:
	.size	_ZN3CNFD2Ev, .-_ZN3CNFD2Ev
	.weak	_ZN3CNFD1Ev
	.set	_ZN3CNFD1Ev,_ZN3CNFD2Ev
	.section	.text._ZNSt6vectorIiSaIiEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPiS1_EERKi,"axG",@progbits,_ZNSt6vectorIiSaIiEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPiS1_EERKi,comdat
	.align 2
	.p2align 4,,15
	.weak	_ZNSt6vectorIiSaIiEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPiS1_EERKi
	.type	_ZNSt6vectorIiSaIiEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPiS1_EERKi, @function
_ZNSt6vectorIiSaIiEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPiS1_EERKi:
.LFB766:
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
	je	.L35
	testq	%rax, %rax
	je	.L36
	movl	-4(%rax), %ecx
	movl	%ecx, (%rax)
.L36:
	leaq	4(%rax), %rcx
	movq	%rcx, 8(%rbx)
	movl	(%rdx), %ebx
	leaq	-4(%rax), %rdx
	subq	%rbp, %rdx
	sarq	$2, %rdx
	testq	%rdx, %rdx
	je	.L37
	salq	$2, %rdx
	movq	%rbp, %rsi
	subq	%rdx, %rax
	movq	%rax, %rdi
	call	memmove
.L37:
	movl	%ebx, 0(%rbp)
.L34:
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
.L35:
	.cfi_restore_state
	movq	(%rdi), %rcx
	subq	%rcx, %rax
	sarq	$2, %rax
	testq	%rax, %rax
	je	.L39
	leaq	(%rax,%rax), %rsi
	cmpq	%rsi, %rax
	jbe	.L64
.L40:
	movq	%rbp, %r12
	movq	$-4, %r13
	subq	%rcx, %r12
	sarq	$2, %r12
.L47:
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
.L41:
	leaq	(%r14,%r12,4), %rax
	testq	%rax, %rax
	je	.L42
	movl	(%rdx), %edx
	movl	%edx, (%rax)
.L42:
	testq	%rdi, %rdi
	leaq	0(,%r8,4), %r12
	je	.L44
	movq	%r12, %rdx
	movq	%r14, %rdi
	call	memmove
.L44:
	movq	8(%rbx), %rcx
	leaq	4(%r14,%r12), %r8
	xorl	%r12d, %r12d
	subq	%rbp, %rcx
	sarq	$2, %rcx
	testq	%rcx, %rcx
	je	.L45
	leaq	0(,%rcx,4), %r12
	movq	%r8, %rdi
	movq	%rbp, %rsi
	movq	%r12, %rdx
	call	memmove
	movq	%rax, %r8
.L45:
	movq	(%rbx), %rdi
	addq	%r8, %r12
	testq	%rdi, %rdi
	je	.L46
	call	_ZdlPv
.L46:
	addq	%r14, %r13
	movq	%r14, (%rbx)
	movq	%r12, 8(%rbx)
	movq	%r13, 16(%rbx)
	jmp	.L34
	.p2align 4,,10
	.p2align 3
.L39:
	movq	%rsi, %r12
	movl	$4, %r13d
	subq	%rcx, %r12
	sarq	$2, %r12
	jmp	.L47
.L64:
	movabsq	$4611686018427387903, %rdi
	cmpq	%rdi, %rsi
	ja	.L40
	movq	%rbp, %r12
	leaq	0(,%rax,8), %r13
	subq	%rcx, %r12
	sarq	$2, %r12
	testq	%rsi, %rsi
	jne	.L47
	movq	%r12, %r8
	movq	%r12, %rdi
	movq	%rcx, %rsi
	xorl	%r14d, %r14d
	jmp	.L41
	.cfi_endproc
.LFE766:
	.size	_ZNSt6vectorIiSaIiEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPiS1_EERKi, .-_ZNSt6vectorIiSaIiEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPiS1_EERKi
	.section	.rodata.str1.1
.LC2:
	.string	" cnf %d %d\n"
.LC3:
	.string	"vector::reserve"
	.text
	.align 2
	.p2align 4,,15
	.globl	_ZN3CNF4readEP8_IO_FILE
	.type	_ZN3CNF4readEP8_IO_FILE, @function
_ZN3CNF4readEP8_IO_FILE:
.LFB699:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	movq	%rdi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rsi, %rbx
	subq	$24, %rsp
	.cfi_def_cfa_offset 80
	movq	(%rdi), %rax
	movl	$0, 72(%rdi)
	movl	$0, 76(%rdi)
	movq	%rax, 8(%rdi)
	movq	24(%rdi), %rax
	movq	%rax, 32(%rdi)
	movq	48(%rdi), %rax
	movq	%rax, 56(%rdi)
	movq	%rbx, %rdi
	call	fgetc
	cmpl	$112, %eax
	je	.L107
	.p2align 4,,10
	.p2align 3
.L69:
	movq	%rbx, %rdi
	call	fgetc
	cmpl	$10, %eax
	jne	.L69
	movq	%rbx, %rdi
	call	fgetc
	cmpl	$112, %eax
	jne	.L69
.L107:
	leaq	76(%rbp), %rcx
	leaq	72(%rbp), %rdx
	xorl	%eax, %eax
	movl	$.LC2, %esi
	movq	%rbx, %rdi
	call	fscanf
	cmpl	$2, %eax
	je	.L108
.L65:
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L108:
	.cfi_restore_state
	movslq	76(%rbp), %r12
	movabsq	$4611686018427387903, %rax
	cmpq	%rax, %r12
	ja	.L77
	movq	24(%rbp), %r15
	movq	40(%rbp), %rax
	subq	%r15, %rax
	movq	%r15, %r13
	sarq	$2, %rax
	cmpq	%rax, %r12
	ja	.L109
.L72:
	movl	$0, 0(%r13)
	movl	76(%rbp), %edx
	movabsq	$4611686018427387903, %rax
	movslq	%edx, %r12
	cmpq	%rax, %r12
	ja	.L77
	movq	48(%rbp), %r15
	movq	64(%rbp), %rax
	subq	%r15, %rax
	sarq	$2, %rax
	cmpq	%rax, %r12
	ja	.L110
.L78:
	xorl	%r12d, %r12d
	.p2align 4,,10
	.p2align 3
.L83:
	cmpl	%r12d, %edx
	jle	.L65
	xorl	%eax, %eax
	movq	%rsp, %rdx
	movl	$.LC1, %esi
	movq	%rbx, %rdi
	call	fscanf
	cmpl	$1, %eax
	jne	.L65
	movl	(%rsp), %eax
	testl	%eax, %eax
	jne	.L111
	movq	8(%rbp), %rax
	subq	0(%rbp), %rax
	movslq	%r12d, %rdx
	movq	24(%rbp), %rcx
	movq	48(%rbp), %rsi
	leaq	0(,%rdx,4), %r8
	addl	$1, %r12d
	sarq	$2, %rax
	movl	%eax, %edi
	subl	(%rcx,%rdx,4), %edi
	movl	%edi, (%rsi,%rdx,4)
	movl	76(%rbp), %edx
	cmpl	%edx, %r12d
	jge	.L83
	movl	%eax, 4(%rcx,%r8)
	movl	76(%rbp), %edx
	jmp	.L83
.L110:
	movq	56(%rbp), %r13
	xorl	%r14d, %r14d
	subq	%r15, %r13
	sarq	$2, %r13
	testq	%r12, %r12
	je	.L79
	salq	$2, %r12
	movq	%r12, %rdi
	call	_Znwm
	movq	%rax, %r14
.L79:
	testq	%r13, %r13
	je	.L81
	salq	$2, %r13
	movq	%r15, %rsi
	movq	%r14, %rdi
	movq	%r13, %rdx
	call	memmove
.L81:
	movq	48(%rbp), %rdi
	testq	%rdi, %rdi
	je	.L82
	call	_ZdlPv
.L82:
	addq	%r14, %r13
	addq	%r14, %r12
	movq	%r14, 48(%rbp)
	movq	%r13, 56(%rbp)
	movq	%r12, 64(%rbp)
	movl	76(%rbp), %edx
	jmp	.L78
.L109:
	movq	32(%rbp), %r14
	xorl	%r13d, %r13d
	subq	%r15, %r14
	sarq	$2, %r14
	testq	%r12, %r12
	je	.L73
	salq	$2, %r12
	movq	%r12, %rdi
	call	_Znwm
	movq	%rax, %r13
.L73:
	testq	%r14, %r14
	je	.L75
	salq	$2, %r14
	movq	%r15, %rsi
	movq	%r13, %rdi
	movq	%r14, %rdx
	call	memmove
.L75:
	movq	24(%rbp), %rdi
	testq	%rdi, %rdi
	je	.L76
	call	_ZdlPv
.L76:
	addq	%r13, %r14
	addq	%r13, %r12
	movq	%r13, 24(%rbp)
	movq	%r14, 32(%rbp)
	movq	%r12, 40(%rbp)
	jmp	.L72
.L111:
	movq	8(%rbp), %rsi
	cmpq	16(%rbp), %rsi
	je	.L85
	testq	%rsi, %rsi
	je	.L86
	movl	%eax, (%rsi)
.L86:
	addq	$4, %rsi
	movl	76(%rbp), %edx
	movq	%rsi, 8(%rbp)
	jmp	.L83
.L85:
	movq	%rsp, %rdx
	movq	%rbp, %rdi
	call	_ZNSt6vectorIiSaIiEE13_M_insert_auxEN9__gnu_cxx17__normal_iteratorIPiS1_EERKi
	movl	76(%rbp), %edx
	jmp	.L83
.L77:
	movl	$.LC3, %edi
	call	_ZSt20__throw_length_errorPKc
	.cfi_endproc
.LFE699:
	.size	_ZN3CNF4readEP8_IO_FILE, .-_ZN3CNF4readEP8_IO_FILE
	.align 2
	.p2align 4,,15
	.globl	_ZN3CNFC2EP8_IO_FILE
	.type	_ZN3CNFC2EP8_IO_FILE, @function
_ZN3CNFC2EP8_IO_FILE:
.LFB696:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA696
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rdi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	$0, (%rdi)
	movq	$0, 8(%rdi)
	movq	$0, 16(%rdi)
	movq	$0, 24(%rdi)
	movq	$0, 32(%rdi)
	movq	$0, 40(%rdi)
	movq	$0, 48(%rdi)
	movq	$0, 56(%rdi)
	movq	$0, 64(%rdi)
.LEHB0:
	call	_ZN3CNF4readEP8_IO_FILE
.LEHE0:
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L117:
	.cfi_restore_state
	movq	48(%rbx), %rdi
	movq	%rax, %rbp
	testq	%rdi, %rdi
	je	.L114
	call	_ZdlPv
.L114:
	movq	24(%rbx), %rdi
	testq	%rdi, %rdi
	je	.L115
	call	_ZdlPv
.L115:
	movq	(%rbx), %rdi
	testq	%rdi, %rdi
	je	.L116
	call	_ZdlPv
.L116:
	movq	%rbp, %rdi
.LEHB1:
	call	_Unwind_Resume
.LEHE1:
	.cfi_endproc
.LFE696:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA696:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE696-.LLSDACSB696
.LLSDACSB696:
	.uleb128 .LEHB0-.LFB696
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L117-.LFB696
	.uleb128 0
	.uleb128 .LEHB1-.LFB696
	.uleb128 .LEHE1-.LEHB1
	.uleb128 0
	.uleb128 0
.LLSDACSE696:
	.text
	.size	_ZN3CNFC2EP8_IO_FILE, .-_ZN3CNFC2EP8_IO_FILE
	.globl	_ZN3CNFC1EP8_IO_FILE
	.set	_ZN3CNFC1EP8_IO_FILE,_ZN3CNFC2EP8_IO_FILE
	.section	.rodata.str1.1
.LC4:
	.string	"mink=%d\n"
.LC5:
	.string	"maxk=%d\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB705:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA705
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subq	$80, %rsp
	.cfi_def_cfa_offset 96
	movq	stdin(%rip), %rsi
	movq	%rsp, %rdi
	movq	$0, (%rsp)
	movq	$0, 8(%rsp)
	movq	$0, 16(%rsp)
	movq	$0, 24(%rsp)
	movq	$0, 32(%rsp)
	movq	$0, 40(%rsp)
	movq	$0, 48(%rsp)
	movq	$0, 56(%rsp)
	movq	$0, 64(%rsp)
	movl	$0, 72(%rsp)
	movl	$0, 76(%rsp)
.LEHB2:
	call	_ZN3CNF4readEP8_IO_FILE
	movq	56(%rsp), %rsi
	movq	48(%rsp), %rax
	cmpq	%rax, %rsi
	je	.L130
	movl	(%rax), %edx
	jmp	.L131
	.p2align 4,,10
	.p2align 3
.L133:
	movl	(%rax), %ecx
	cmpl	%ecx, %edx
	cmova	%ecx, %edx
.L131:
	addq	$4, %rax
	cmpq	%rax, %rsi
	jne	.L133
.L132:
	movl	$.LC4, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk
	movq	56(%rsp), %rsi
	movq	48(%rsp), %rax
	cmpq	%rax, %rsi
	je	.L134
	movl	(%rax), %edx
	jmp	.L135
	.p2align 4,,10
	.p2align 3
.L137:
	movl	(%rax), %ecx
	cmpl	%ecx, %edx
	cmovb	%ecx, %edx
.L135:
	addq	$4, %rax
	cmpq	%rax, %rsi
	jne	.L137
.L136:
	movl	$.LC5, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	__printf_chk
.LEHE2:
	movq	%rsp, %rdi
	call	_ZN3CNFD1Ev
	addq	$80, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
.L130:
	.cfi_restore_state
	movl	(%rsi), %edx
	jmp	.L132
.L134:
	movl	(%rsi), %edx
	jmp	.L136
.L139:
	movq	%rax, %rbx
	movq	%rsp, %rdi
	call	_ZN3CNFD1Ev
	movq	%rbx, %rdi
.LEHB3:
	call	_Unwind_Resume
.LEHE3:
	.cfi_endproc
.LFE705:
	.section	.gcc_except_table
.LLSDA705:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE705-.LLSDACSB705
.LLSDACSB705:
	.uleb128 .LEHB2-.LFB705
	.uleb128 .LEHE2-.LEHB2
	.uleb128 .L139-.LFB705
	.uleb128 0
	.uleb128 .LEHB3-.LFB705
	.uleb128 .LEHE3-.LEHB3
	.uleb128 0
	.uleb128 0
.LLSDACSE705:
	.section	.text.startup
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.8.2-19ubuntu1) 4.8.2"
	.section	.note.GNU-stack,"",@progbits
