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

		MOV DX, CON8254
		MOV AL, 76H             	;8254������1�����ڷ�ʽ3������������ 
		OUT DX, AL 
		MOV DX, B8254 
		MOV AL, 00H
		OUT DX, AL 
		MOV AL, 048H             	;д�������ֵ04800H ������ֵȡ����CLK1������
		OUT DX, AL 
AA1: 
		JMP AA1 
;��GATE1��Ϊ�ߵ�ƽ�����г�����ʾ�����п��Կ���OUT1�������������
;CLK1����Ϊ18.432kHz �ü�ʱ��1����18432�� �õ�����Ϊ1s�ķ�����
;������ʵ�����ϻ���184.32kHz��1.8432MHz��ʱ��Ƶ��
;
CODE 	ENDS 
		END START