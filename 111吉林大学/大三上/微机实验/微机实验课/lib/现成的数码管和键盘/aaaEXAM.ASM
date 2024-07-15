; 8255CS -> IOY0
C8255_A equ 0600h
C8255_B equ 0602h
C8255_C equ 0604h
C8255_CON  equ 0606h

; 8254CS -> IOY1
C8254_A equ 0640h
C8254_B equ 0642h 
C8254_C equ 0644h 
C8254_CON equ 0646h

data segment
        
    DTable db 3fh ,06h, 5bh, 4fh, 66h ,6dh, 7dh, 07h, 7fh, 6fh,77h,7ch,39h,5eh,79h,71h,00h
    
    KTable :
    	db  0eeh,0deh,0beh,7eh
        db  0edh,0ddh,0bdh,7dh
        db  0ebh,0dbh,0bbh,7bh
        db  0e7h,0d7h,0b7h,77h
    
    key_input: db 00h
    key_input_flag: db 00h
    
    numbers : db 01h, 02h, 03h, 04h, 05h, 06h, 00h
    
data ends

sstack  segment stack
		dw 32 dup(?)
sstack  ends

code segment
    assume cs:code,ds:data
;-------------------------------
;---------------| 鍦ㄦ澶勫啓浠ｇ爜 |-------------------------------
;-------------------------------
start:
	
INIT8255:
    mov dx, C8255_CON
    mov al, 10001001b ;AB出 C入
    ;mov al, 10001011b ;A出 BC入
    out dx, al

INIT8254:
		mov dx, C8254_CON
		mov al, 01110110b   ;8254计数器1工作在方式3，产生方波。 
		out dx, al 
		mov dx, C8254_B
		mov al, 00h
		out dx, al 
		mov al, 048h        ;写入计数初值04800h 
		out dx, al 
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
	
	
mainloop:	
	call display_nums

	;call SCANF
	
	;lea si, key_input_flag
	;mov ax, [si]
	;jz mainloop
	
	;lea si, numbers ; si?????????,al????洢????,bx????洢?±?
	;mov al, 00h
	;mov [si], al
	
    jmp mainloop



; 涓柇鍑芥暟-----------------------------------------------------------

mir6:
	iret
	
mir7:
	lea si, numbers ; si?????????,al????洢????,bx????洢?±?
	
	;mov al, 00h
	;mov [si], al
	
	;mov bx, 05h
	;mov al, 00h
	;mov [si+bx], al
	
	mov al, [si]
	mov bx, 06h
	mov [si+bx], al
	
	mov bx, 01h
	mov al, [si+bx]
	mov bx, 00h
	mov [si+bx], al
	
	mov bx, 02h
	mov al, [si+bx]
	mov bx, 01h
	mov [si+bx], al
	
	mov bx, 03h
	mov al, [si+bx]
	mov bx, 02h
	mov [si+bx], al
	
	mov bx, 04h
	mov al, [si+bx]
	mov bx, 03h
	mov [si+bx], al
	
	mov bx, 05h
	mov al, [si+bx]
	mov bx, 04h
	mov [si+bx], al
	
	mov bx, 06h
	mov al, [si+bx]
	mov bx, 05h
	mov [si+bx], al
	iret
	
; 浠ヤ笅涓哄瓙鍑芥暟-------------------------------------------------------

display_nums:
    PUSH AX
    PUSH DX

        mov bx,00h

        mov cx,06h
        mov al,11011111b
    xx:
        mov dx,c8255_a
        out dx,al
        ror al,1
        
        push ax ;use to out data
        lea si,numbers
        mov dx, 00h
        mov dl,[bx+si] ;get data
        
        push bx
        mov bx, dx
        lea si, DTable
        mov al,[bx+si] ; trans to code
        pop bx
        inc bx
        
        mov dx,c8255_b
        out dx,al
        pop ax
        
        call delay
        loop xx

    POP DX
    POP AX
    ret


delay:
    push cx
    mov cx,00ffh
	d1:
    loop d1
    pop cx
    ret 

SCANF:      ; 键盘扫秒函数，调用后 key_input为键值 key_input_flag 为1有效 为0无效
	PUSH AX
	PUSH DX
    PUSH BX
    monitor_the_keys:
        call delay
        
        mov dx,C8255_A
        mov al,00h
        out dx,al  	; set the input of the keys with 0000
        
        mov dx,C8255_C
        in al,dx

        and al,0fh
        cmp al,0fh
        jz monitor_the_keys	;按键全部为高电平，没有键按下
        
    reconfirm:
        call delay	;消除前沿抖动
        
        mov dx,C8255_A
        mov al,00h
        out dx,al
        
        mov dx,C8255_C
        in al,dx
        
        and al,0fh
        cmp al,0fh
        jz monitor_the_keys	;消抖前的按键是由于干扰
    
    find_the_key:	; 到此说明有按键输入
        mov ah,11111110b
        mov dx,C8255_A
        
        mov cx,04h
    scanf_keys: 
        mov al,ah
        mov dx,C8255_A
        out dx,al	; set the input of the keys with 1110
        
        mov dx,C8255_C
        in al,dx
        and al,0fh
        cmp al,0fh
        
        jnz confirm_the_key
        rol ah,1
        loop scanf_keys
        jmp monitor_the_keys ; find nothing
        
    confirm_the_key:
        mov cl,4
        shl ah,cl
        or al,ah 	;此时al的高四位为列数，低四位为行数

        lea si, KTable
        mov bl,00h 
        mov bh,00h
    translate_key_code: 
        cmp al,[si+bx]
        jz save_the_key		;确定了al代表的是哪个键码，值在bl中，进行数码管显示
        inc bl
        cmp bl,10h
        jnz translate_key_code
        jmp monitor_the_keys	;键码值已经大于16个了，但还是没找到，放弃本次显示，重新按键输入
        
    ;此时键码的偏移量已经在bl中了
        lea si, key_input
        cmp [si], bl
        jz concel_the_key
    save_the_key:
        mov [si], bl
        lea si, key_input_flag
        mov bl, 01h
        mov [si], bl
        ret
    concel_the_key:
        lea si, key_input_flag
        mov bl, 00h
        mov [si], bl
        ret

    POP BX
    POP DX
    POP AX
    RET


code 	ends
		end start