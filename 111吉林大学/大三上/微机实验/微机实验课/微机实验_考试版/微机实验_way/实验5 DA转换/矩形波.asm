STACK 	SEGMENT STACK
		DW 32 DUP(?)
STACK 	ENDS
 
CODE 	SEGMENT
		ASSUME  CS:CODE, SS:STACK
 
START: 
		;产生矩形波
		MOV CX, 05H       	;产生矩形波的周期数为5次，如果想改变三角波产生周期请修改这里
JUXING:
		MOV DX, 0600H
		MOV AL, 00H       	;先输出00H的波形
		OUT DX, AL
		CALL DELAY2       	;长延时
		MOV AL, 0FFH      	;再输出0FFH的波形
		OUT DX, AL
		CALL DELAY2       	;长延时
		LOOP JUXING
 
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