	.file	"loop.c"            ;以下的内容都属于逻辑文件loop.c
	.text
	.section	.rodata
.LC0:
	.string	"count %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp           ;SP - 16，栈向下扩展
	movw	$0, -2(%rbp)        ;栈底第一个字为0，把这两个字节用作循环计数
	jmp	.L2
.L3:
	movzwl	-2(%rbp), %eax      ;为什么esi不能直接等于-2(%rbp)
	movl	%eax, %esi          ;SI存储循环计数的值
	leaq	.LC0(%rip), %rdi    ;DI指向字符串
	movl	$0, %eax            ;AX = 0，为什么？
	call	printf@PLT
	movzwl	-2(%rbp), %eax      ;为什么-2(%rbp)不能直接加1
	addl	$1, %eax
	movw	%ax, -2(%rbp)
.L2:
	cmpw	$4, -2(%rbp)
	jbe	.L3                     ;如果小于等于，就继续循环
	movl	$1, %eax            ;EAX = 1，准备返回值
	leave                       ;move %rbp %rsp; pop %rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 8.2.1 20180831"
	.section	.note.GNU-stack,"",@progbits
