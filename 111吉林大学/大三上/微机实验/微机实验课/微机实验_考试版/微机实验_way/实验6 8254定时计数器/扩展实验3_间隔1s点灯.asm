P8255A EQU 0640H
P8255B EQU 0642H
P8255C EQU 0646H
P8255MODE EQU 0646H				;8255ƬѡCS��IOY1
A8254 EQU 0600H
B8254 EQU 0602H 
C8254 EQU 0604H 
CON8254 EQU 0606H
SSTACK 	SEGMENT STACK 
		DW 32 DUP(?) 
SSTACK 	ENDS 
CODE 	SEGMENT 
		ASSUME CS:CODE
START:
		MOV BL,00H				;��ʼʱ�����ݵ�ȫ��Ϩ��
		MOV DX,P8255MODE
		MOV AL,10010000B
		OUT DX,AL				;�ͷ�ʽ������

		MOV AL,BL
		MOV DX,P8255B
		OUT DX,AL				;��b��
	  
		MOV AX,0000H
		MOV DS,AX
		MOV AX, OFFSET MIR6 	;8254��ԪOUT1����MIR6
		MOV SI, 0038H
		MOV [SI], AX
		MOV AX,CS
		MOV SI,003AH
		MOV [SI], AX
 
		CLI
		MOV AL, 11H				;�������ش���
		OUT 20H, AL
		MOV AL, 08H
		OUT 21H, AL
		MOV AL,04H
		OUT 21H, AL
		MOV AL, 07H
		OUT 21H, AL
		MOV AL, 10101111B		;������IR4 IR6 IR4���뿪�� �������ɲ���Ԥ�ϵ����
		OUT 21H, AL
		STI
    

		MOV DX, CON8254
		MOV AL, 76H            	;8254������1�����ڷ�ʽ3������������ 
		OUT DX, AL 
		MOV DX, B8254 
		MOV AL, 00H
		OUT DX, AL 
		MOV AL, 048H            ;д�������ֵ04800H
		OUT DX, AL 
AA1: 
		JMP AA1 
;��GATE1��Ϊ�ߵ�ƽ�����г�����ʾ�����п��Կ���OUT1�������������
;CLK1����Ϊ18.432kHz �ü�ʱ��1����18432�� �õ�����Ϊ1s�ķ�����
;��Ҫ�õ�����1s�ķ��� ������ֵΪ18432 ��04800H
;
MIR6:
		CMP BL,0FFH
		JZ  M
		SHL BL,1				;���ݵ��𽥵����Ŀ���
		ADD BL,01H				;ͬ��
M:		MOV DX,0642H
		MOV AL,BL
		OUT DX,AL
		IRET
    
DELAY:
		PUSH CX
		PUSH AX
		MOV CX,0FFFFH
L1:
		LOOP L1
		POP AX
		POP CX
		RET

CODE 	ENDS 
		END START