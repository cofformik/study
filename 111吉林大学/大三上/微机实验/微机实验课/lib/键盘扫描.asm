SCANF:      ; ����ɨ�뺯�������ú� key_inputΪ��ֵ key_input_flag Ϊ1��Ч Ϊ0��Ч
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
        jz monitor_the_keys	;����ȫ��Ϊ�ߵ�ƽ��û�м�����
        
    reconfirm:
        call delay	;����ǰ�ض���
        
        mov dx,C8255_A
        mov al,00h
        out dx,al
        
        mov dx,C8255_C
        in al,dx
        
        and al,0fh
        cmp al,0fh
        jz monitor_the_keys	;����ǰ�İ��������ڸ���
    
    find_the_key:	; ����˵���а�������
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
        or al,ah 	;��ʱal�ĸ���λΪ����������λΪ����

        lea si, KTable
        mov bl,00h 
        mov bh,00h
    translate_key_code: 
        cmp al,[si+bx]
        jz save_the_key		;ȷ����al��������ĸ����룬ֵ��bl�У������������ʾ
        inc bl
        cmp bl,10h
        jnz translate_key_code
        jmp monitor_the_keys	;����ֵ�Ѿ�����16���ˣ�������û�ҵ�������������ʾ�����°�������
        
    ;��ʱ�����ƫ�����Ѿ���bl����
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