STACK 	SEGMENT STACK
		DW 32 DUP(?)
STACK 	ENDS
 
CODE 	SEGMENT
		ASSUME  CS:CODE, SS:STACK
 
START:
		;������ݲ�
		MOV CX, 07H       	;������ݲ���������Ϊ7�Σ������ı��ݲ������������޸�����
JUCHI:
		MOV DX, 0600H     	;DAC0832��IOY0,0600HΪ���ƶ˿ڵ�ַ
		MOV AL, 00H       	;ALΪ������
JC1: 
		OUT DX, AL        	;ת��Ϊģ����
		CALL DELAY1       	;��ʱ����Ϊ����ʱ
		CMP AL ,0FFH
		JE JC2
		INC AL           	;AL����1��ֱ������0FFH
		JMP JC1
JC2:
		LOOP JUCHI
 
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