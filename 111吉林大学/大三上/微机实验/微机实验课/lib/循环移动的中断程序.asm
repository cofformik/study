	lea si, numbers ; siָ��������,al���ڴ洢����,bx���ڴ洢�±�
	
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