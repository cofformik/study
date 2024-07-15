; 设置中断向量，其中中断向量程序的标号为MIR6和MIR7
; 一个地址占两字节，中断向量格式为 段地址:偏移地址

; MIR6中断向量的存放地址 003AH:0038H
    MOV AX,OFFSET MIR6
    MOV SI,0038H
    MOV [SI],AX ; 设置偏移地址
    MOV AX,CS
    MOV SI,003AH
    MOV [SI],AX ; 设置段地址

; MIR7中断向量的存放地址 003EH:003CH
    MOV AX,OFFSET MIR7
    MOV SI,003CH
    MOV [SI],AX ; 设置偏移地址
    MOV AX,CS
    MOV SI,003EH
    MOV [SI],AX ; 设置段地址


；-------------------------------------需要中断时复制下面程序
setIR:
   
	PUSH DS;数据段寄存器
		mov ax,offset mir7	;取中断入口地址
	   	mov si,003ch	;中断矢量地址
	   	mov [si],ax	;填irq7的偏移矢量
	   	mov ax,cs	;段地址
	   	mov si,003eh
	   	mov [si],ax	;填irq7的段地址矢量

	    mov ax,offset mir6
       	mov si,0038h
	   	mov [si],ax
	   	mov ax,cs
	   	mov si,003ah
	   	mov [si],ax	   
	POP DS
	 
	cli ;关中断
	   ;初始化主片8259
	   mov al,11h;级联，边沿触发，要icw4
	   out 20h,al;icw1，端口地址查表可知
	   mov al,08h;中断类型号从8开始
	   out 21h,al ;icw2
	   mov al,04h
	   out 21h,al;icw3
	   mov al,03h;非缓冲方式，8086/8088配置
	   out 21h,al;icw4
	   mov al,2fh;
	   out 21h,al;主8259 ocw1
	   mov al,10000000b
	sti;允许中断发生
	
