STACK 	SEGMENT STACK
		DW 32 DUP(?)
STACK 	ENDS
 
CODE 	SEGMENT
		ASSUME  CS:CODE, SS:STACK
 
START: 
		;�������β�
		MOV CX, 05H       	;�������β���������Ϊ5�Σ������ı����ǲ������������޸�����
JUXING:
		MOV DX, 0600H
		MOV AL, 00H       	;�����00H�Ĳ���
		OUT DX, AL
		CALL DELAY2       	;����ʱ
		MOV AL, 0FFH      	;�����0FFH�Ĳ���
		OUT DX, AL
		CALL DELAY2       	;����ʱ
		LOOP JUXING
 
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