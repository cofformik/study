;8255初始化，地址由8254 cs连接的IOY端口决定, 0600为IOY0, 0640为IOY1

C8255_CON equ 0606h
C8255_A equ 0600h
C8255_B equ 0602h
C8255_C equ 0604h

INIT8255:
    mov dx, C8255_CON
    ;mov al, 10001001b ;AB出 C入
    ;mov al, 10001011b ;A出 BC入
    out dx, al

