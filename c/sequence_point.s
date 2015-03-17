	.file	"sequence_point.c"
	.section	.rodata
.LC0:
	.string	"%d\n"
.LC1:
	.string	"ans:%d; i:%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$32, %esp
	movl	$5, 28(%esp)
	movl	28(%esp), %eax
	leal	1(%eax), %edx
	movl	%edx, 28(%esp)
	cmpl	$5, %eax
	jg	.L2
	movl	28(%esp), %eax
	jmp	.L3
.L2:
	movl	$0, %eax
.L3:
	movl	%eax, 24(%esp)
	movl	24(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC0, (%esp)
	call	printf
	movl	$3, 20(%esp)
	movl	20(%esp), %edx
	leal	1(%edx), %eax
	movl	%eax, 20(%esp)
	movl	20(%esp), %eax
	leal	1(%eax), %ecx
	movl	%ecx, 20(%esp)
	leal	(%edx,%eax), %ecx
	movl	20(%esp), %eax
	leal	1(%eax), %edx
	movl	%edx, 20(%esp)
	addl	%ecx, %eax
	movl	%eax, 16(%esp)
	movl	20(%esp), %eax
	movl	%eax, 8(%esp)
	movl	16(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$.LC1, (%esp)
	call	printf
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.0 20130502 (prerelease)"
	.section	.note.GNU-stack,"",@progbits
