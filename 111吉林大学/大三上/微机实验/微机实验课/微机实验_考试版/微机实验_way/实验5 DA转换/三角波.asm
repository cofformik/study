STACK 	SEGMENT STACK
		DW 32 DUP(?)
STACK 	ENDS
 
CODE 	SEGMENT
		ASSUME  CS:CODE, SS:STACK
 
START:  
		MOV AL,00H
		;�������ǲ�
		MOV CX, 05H     	;�������ǲ���������Ϊ5�Σ������ı����ǲ������������޸�����
SANJIAO:
SJ1:
		MOV DX, 0600H
		OUT DX, AL
		CALL DELAY1       	;����ʱ
		CMP AL,0FFH
		JE SJ2           
		INC AL            	;��AL��00H����0FFH
		JMP SJ1
SJ2:
		MOV DX, 0600H
		OUT DX, AL
		CALL DELAY1       	;����ʱ
		CMP AL, 00H
		JE SJ3
		DEC AL            	;��AL��0FFH������00H
		JMP SJ2
SJ3:
		LOOP SANJIAO
 
    
DELAY1:                		;����ʱ
		PUSH CX
		MOV CX, 01FFH
D1: 
		PUSH AX
		POP AX
		LOOP D1
		POP CX
		RET
 
DELAY2:               		;����ʱ
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