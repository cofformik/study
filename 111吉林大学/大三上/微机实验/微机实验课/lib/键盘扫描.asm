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