STACK 	SEGMENT STACK
		DW 32 DUP(?)
STACK 	ENDS
 
CODE 	SEGMENT
		ASSUME  CS:CODE, SS:STACK
 
START:  
		MOV AL,00H
		;产生三角波
		MOV CX, 05H     	;产生三角波的周期数为5次，如果想改变三角波产生周期请修改这里
SANJIAO:
SJ1:
		MOV DX, 0600H
		OUT DX, AL
		CALL DELAY1       	;短延时
		CMP AL,0FFH
		JE SJ2           
		INC AL            	;将AL从00H步加0FFH
		JMP SJ1
SJ2:
		MOV DX, 0600H
		OUT DX, AL
		CALL DELAY1       	;短延时
		CMP AL, 00H
		JE SJ3
		DEC AL            	;将AL从0FFH步减至00H
		JMP SJ2
SJ3:
		LOOP SANJIAO
 
    
DELAY1:                		;短延时
		PUSH CX
		MOV CX, 01FFH
D1: 
		PUSH AX
		POP AX
		LOOP D1
		POP CX
		RET
 
DELAY2:               		;长延时
		PUSH CX
		MOV CX, 0FFFFH
D2: 
		PUSH AX
		POP AX
		LOOP D2
		POP CX
		RET
 
CODE 	ENDS
		END START