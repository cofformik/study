counter0 equ 0600h
counter1 equ 0602h
counter2 equ 0604h
con8254  equ 0606h

a8255 equ 0640h
b8255 equ 0642h
c8255 equ 0644h
con8255 equ 0646h

code segment
 assume cs:code 
start:
 mov  dx,con8255
 mov al,80h
 out dx,al
 
 mov ax,offset mir6
 mov si,38h
 mov [si],ax
 mov ax,cs
 mov si,3ah
 mov [si],ax
 cli
 mov al,11h
 out 20h,al
 mov al,08h
 out 21h,al
 mov al,04h
 out 21h,al
 mov al,07h
 out 21h,al
 mov al,2fh
 out 21h,al
 sti
 mov dx,con8254
 mov al,76h
 out dx,al
 mov dx,counter1
 mov al,00h
 out dx,al
 mov al,48h
 out dx,al
 mov al,00h
 mov dx,b8255
main :
    out dx,al
    jmp main
mir6:
    cmp al,0ffh
    jz i1
    rol al,1
    inc al
    jmp i2
 i1:
   mov al,00h
 i2:
   iret
    
    code ends
    end start    