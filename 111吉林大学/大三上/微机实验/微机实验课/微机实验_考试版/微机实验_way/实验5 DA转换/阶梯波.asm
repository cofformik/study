STACK 	SEGMENT STACK
		DW 32 DUP(?)
STACK 	ENDS
 
CODE 	SEGMENT
		ASSUME  CS:CODE, SS:STACK
 
START:
		;�������ݲ�
		MOV CX, 0FFFFH     	;�������ݲ���������Ϊ0FFFF�Σ������ı���ݲ������������޸�����
		MOV AX, 0FEH       
		;����������ֵΪ0FFH
		;���ǵ�8086��DIV�������ܻ��������Ϊ�����¼�����֮������ֵ����0FFH����ʹ��0FEH�����ֵ
		MOV BL,05H         	;���ݲ��еĽ������������ı���ݲ��еĽ��������޸�����
		DIV BL             	;�����������Խ��������õ�ÿ��̨�׵ĸ߶�
		MOV BL, AL         	;�������������̱�����BL��
		MOV BH, 00H        	;BH��0
JIETI:
		MOV AX,0000H       	;AX��ʼ��0000H
JT1:
		MOV DX, 0600H
		OUT DX, AL
		CMP AX, 00FFH      	;�ж�AX�Ƿ�ﵽ��������
		JAE JT2            	;�ﵽ���ޣ���ʾһ�ν��ݲ��������ɣ���ʼ��һ������
		CALL DELAY2        	;����ʱ
		ADD AX, BX         	;�õ�ǰ����߶ȼ���ÿ�����ݵĸ߶ȵõ���һ���ݵĸ߶�
		JMP JT1
JT2:    
		LOOP JIETI
 
 
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