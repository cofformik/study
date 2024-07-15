;8254初始化，地址由8254 cs连接的IOY端口决定, 0600为IOY0, 0640为IOY1

C8254_A equ 0600h
C8254_B equ 0602h 
C8254_C equ 0604h 
C8254_CON equ 0606h

INIT8254:
		mov dx, C8254_CON
		mov al, 01110110b   ;8254计数器1工作在方式3，产生方波。 
		out dx, al 
		mov dx, C8254_B
		mov al, 00h
		out dx, al 
		mov al, 048h        ;写入计数初值04800h 
		out dx, al 