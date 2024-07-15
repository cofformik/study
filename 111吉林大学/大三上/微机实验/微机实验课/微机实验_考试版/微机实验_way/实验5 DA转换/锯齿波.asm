STACK 	SEGMENT STACK
		DW 32 DUP(?)
STACK 	ENDS
 
CODE 	SEGMENT
		ASSUME  CS:CODE, SS:STACK
 
START:
		;产生锯齿波
		MOV CX, 07H       	;产生锯齿波的周期数为7次，如果想改变锯齿波产生周期请修改这里
JUCHI:
		MOV DX, 0600H     	;DAC0832接IOY0,0600H为控制端口地址
		MOV AL, 00H       	;AL为数字量
JC1: 
		OUT DX, AL        	;转换为模拟量
		CALL DELAY1       	;延时，此为短延时
		CMP AL ,0FFH
		JE JC2
		INC AL           	;AL步加1，直到等于0FFH
		JMP JC1
JC2:
		LOOP JUCHI
 
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