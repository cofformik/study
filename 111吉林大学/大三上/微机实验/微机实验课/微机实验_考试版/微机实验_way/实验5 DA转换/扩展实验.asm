P8255A EQU 0640H
P8255B EQU 0642H
P8255C EQU 0646H
P8255MODE EQU 0646H
SSTACK	SEGMENT STACK
		DW 32 DUP(0)
SSTACK	ENDS
DATA 	SEGMENT
VALUE	DB	00H					;��־
DATA 	ENDS 
CODE   	SEGMENT
	   	ASSUME CS:CODE,DS:DATA
 
START: 	
NEXT:
		PUSH DS
		MOV AX, 0000H
		MOV DS, AX		
		MOV AX, OFFSET MIR6		;
		MOV SI, 0038H
		MOV [SI], AX
		MOV AX, CS
		MOV SI, 003AH
		MOV [SI], AX
		CLI						;��ʼ��ǰ���ж�
		POP DS
		;��ʼ����Ƭ8259
		MOV AL, 11H				;���������ش�����ҪICW4
		OUT 20H, AL				;ICW1
		MOV AL, 08H				;�ж����ͺŴ�8��ʼ
		OUT 21H, AL				;ICW2
		MOV AL, 04H				; 
		OUT 21H, AL				;ICW3
		MOV AL, 01H				;�ǻ��巽ʽ��8086/8088����
		OUT 21H, AL				;ICW4
 
		;��ʼ����Ƭ8259
		MOV AL, 11H				;���������ش�����ҪICW4
		OUT 0A0H, AL			;ICW1
		MOV AL, 30H				;�ն����ͺŴ�30H��ʼ
		OUT 0A1H, AL			;ICW2
		MOV AL, 02H				;ͨ��IR1����������Ƭ
		OUT 0A1H, AL			;ICW3
		MOV AL, 01H				;�ǻ��巽ʽ��8086/8088����
		OUT 0A1H, AL			;ICW4
		MOV AL, 0FDH
		OUT 0A1H,AL				;��8259 OCW1 = 1111 1101	����IR1�ж�����	
		MOV AL, 2BH       		;0010 1011
		OUT 21H, AL				;��8259 OCW1	����IR2 IR4 IR6 IR7
		STI
 		
AA2:	NOP
AA24:	CMP VALUE,0C0H			;���ݲ�
		JZ	AA6
AA23:	CMP VALUE,80H			;���ǲ�
		JZ  AA5
AA22:	CMP VALUE,40H			;���β�
		JZ	AA4
AA21:	CMP VALUE,00H			;��ݲ�
		JZ	AA3
		JMP AA2		
		
AA3:	
		MOV DX, 0600H     		;DAC0832��IOY0,0600HΪ���ƶ˿ڵ�ַ
		MOV AL, 00H       		;ALΪ������
JC1: 
		OUT DX, AL        		;ת��Ϊģ����
		CALL DELAY1       		;��ʱ����Ϊ����ʱ
		CMP AL ,0FFH
		JE JC2
		INC AL            		;AL����1��ֱ������0FFH
		JMP JC1
JC2:
		JMP	AA21
    	
AA4:
		MOV DX, 0600H
		MOV AL, 00H       		;�����00H�Ĳ���
		OUT DX, AL
		CALL DELAY2       		;����ʱ
		MOV AL, 0FFH      		;�����0FFH�Ĳ���
		OUT DX, AL
		CALL DELAY2       		;����ʱ  
		JMP	AA22
   
AA5:
		MOV AL,00H
SJ1:
		MOV DX, 0600H
		OUT DX, AL
		CALL DELAY1       		;����ʱ
		CMP AL, 0FFH
		JE SJ2           
		INC AL            		;��AL��00H����0FFH
		JMP SJ1
SJ2:
		MOV DX, 0600H
		OUT DX, AL
		CALL DELAY1       		;����ʱ
		CMP AL, 00H
		JE SJ3
		DEC AL            		;��AL��0FFH������00H
		JMP SJ2
SJ3:
		JMP	AA23

AA6:
		MOV AX, 0FEH       
		;����������ֵΪ0FFH
		;���ǵ�8086��DIV�������ܻ��������Ϊ�����¼�����֮������ֵ����0FFH����ʹ��0FEH�����ֵ
		MOV BL,05H         		;���ݲ��еĽ������������ı���ݲ��еĽ��������޸�����
		DIV BL             		;�����������Խ��������õ�ÿ��̨�׵ĸ߶�
		MOV BL, AL         		;�������������̱�����BL��
		MOV BH, 00H        		;BH��0
JIETI:
		MOV AX,0000H       		;AX��ʼ��0000H
JT1:
		MOV DX, 0600H
		OUT DX, AL
		CMP AX, 00FFH      		;�ж�AX�Ƿ�ﵽ��������
		JAE JT2            		;�ﵽ���ޣ���ʾһ�ν��ݲ��������ɣ���ʼ��һ������
		CALL DELAY2       	 	;����ʱ
		ADD AX, BX         		;�õ�ǰ����߶ȼ���ÿ�����ݵĸ߶ȵõ���һ���ݵĸ߶�
		JMP JT1
JT2:
		JMP AA24

MIR6:	
		ADD VALUE,64			;ѭ������
		PUSH AX					;����AX
		MOV AL, 20H
		OUT 20H, AL
		POP AX
		IRET
		
DELAY:	PUSH CX
		MOV AL, 05H
AA1:	MOV CX, 0FFFFH 
AA0:	PUSH AX
		POP  AX
		LOOP AA0
		SUB AL,1
		JNZ AA1
		POP CX
		RET
DELAY1:                			;����ʱ
		PUSH CX
		MOV CX, 01FFH
D1: 
		PUSH AX
		POP AX
		LOOP D1
		POP CX
		RET
 
DELAY2:               			;����ʱ
		PUSH CX
		MOV CX, 0FFFFH
D2: 
		PUSH AX
		POP AX
		LOOP D2
		POP CX
		RET
		
CODE	ENDS
		END  START