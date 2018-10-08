	.file	"hello.c"           #指定逻辑文件名，hello.c没有双引号也可以
	.text                       #告诉as把后面的语句汇编到text 0的末尾
	.section	.rodata         #把后面的代码汇编到.rodata section
.LC0:
	.string	"hello, world!"
	.text                       #把后面的代码汇编到text 0的末尾
	.globl	hello               #让hello对ld可见，.globl和.xdef和.global一样的意思
	.type	hello, @function    #hello的类型是函数，用在符号表中
hello:
.LFB0:
	.cfi_startproc              #CFI 调用框架指令, cfi_startproc标志函数开始
	pushq	%rbp                #保存栈基地址
	.cfi_def_cfa_offset 16      #cfi use offset 16
	.cfi_offset 6, -16          #cfi register 6 save at offset -16
	movq	%rsp, %rbp          #BP = SP
	.cfi_def_cfa_register 6     #cfi use register 6
	leaq	.LC0(%rip), %rdi    #lea = load effective adrress, 让DI指向字符串
	call	puts@PLT            #call puts function. PLT = Procedure Linkage Table.
	movl	$0, %eax            #AX = 0 函数返回值
	popq	%rbp                #恢复BP
	.cfi_def_cfa 7, 8           #cfi add 8 to register 7
	ret                         #return
	.cfi_endproc                #cfi 标志函数结束
.LFE0:
	.size	hello, .-hello      #计算hello占用的地址空间
	.ident	"GCC: (GNU) 8.2.1 20180831" #do nothing
	.section	.note.GNU-stack,"",@progbits
