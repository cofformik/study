;8255�ӿڳ�ʼ������CS���ӵ�IOY�˿ھ����������õ���IOY0��
MY8255_A EQU 0600H
MY8255_B EQU 0602H
MY8255_C EQU 0604H
MY8255_CON  EQU 0606H
SSTACK  SEGMENT STACK
		DW 16 DUP(?)
SSTACK  ENDS
 
DATA 	SEGMENT
		DTABLE  DB 3FH,06H,5BH,4FH,66H,6DH,7DH,07H,7FH,6FH,77H,7CH,39H,5EH,79H,71H	;0~9 A~F
DATA 	ENDS
;
;�˳���ʵ�ֵĹ�������
;��ʼʱ����ܾ���ʾ��0��
;��һ�ΰ��¼���ʱ����������������ʾ��Ӧ��ʮ����������
;�ڶ��ΰ��¼���ʱ���������ڶ����������ʾ��Ӧ��ʮ����������
;...
;�����ΰ��¼���ʱ�������Ҳ��������ʾ��Ӧ��ʮ����������
;���ߴΰ��¼���ʱ����������������ʾ��Ӧ��ʮ����������
;�ڰ˴ΰ��¼���ʱ���������ڶ����������ʾ��Ӧ��ʮ����������
;...
;���ѭ��
;

;
;������
;�����¼�������һ������ʱ�����ð�����Ӧ�ı����һ�����������ʾ������
;���ٰ���һ������ʱ���㽫��������ı������һ�����������ʾ������
;������Ͽ�����ʾ��� 6 �ΰ��µİ�����š�
;

;
;�Ķ�����ǰ �����Ķ���⡶΢�ͼ����ԭ����ӿڼ��������ڶ��棩 p296-300 ��ɨ�跨
;
CODE 	SEGMENT
		ASSUME CS:CODE,DS:DATA
START:  
		MOV AX,DATA				;װ�����ݶ�
		MOV DS,AX
		MOV SI,3000H			;���������������Ҫ��ʾ�ļ�ֵ
		MOV AL,00H
		MOV [SI],AL        		;��6 ����ʾ����
		MOV [SI+1],AL			;��5
		MOV [SI+2],AL			;��4
		MOV [SI+3],AL			;��3
		MOV [SI+4],AL			;��2
		MOV [SI+5],AL			;��1
		MOV DI,3005H
		MOV DX,MY8255_CON  		;д 8255 ������
		MOV AL,81H				;81H=10000001 A�ڷ�ʽ0 ��� B�ڷ�ʽ0 ��� C�ڵ���λ ����
		OUT DX,AL
BEGIN:  
		CALL DIS                ;������ʾ�ӳ���
		CALL CLEAR              ;����
		CALL CCSCAN             ;ɨ�谴��
		JNZ INK1				
		JMP BEGIN
 
INK1:  
		CALL DIS
		CALL DALLY				;����ǰ�ض���
		CALL DALLY
		CALL CLEAR
		CALL CCSCAN				;�ٴ�ɨ�谴��
		JNZ INK2                ;�м����£�ת�� INK2
		JMP BEGIN
	
;ȷ�����¼���λ��
INK2:  
		MOV CH,0FEH				;11111110B �տ�ʼѡȡ��һ��
		MOV CL,00H				;���õ�ǰ�����ǵڼ���
 
COLUM:  
		MOV AL,CH				;ѡȡһ�У���X1~X4��һ����0
		MOV DX,MY8255_A
		OUT DX,AL
		MOV DX,MY8255_C			;��Y1~Y4�������ж�����һ�а����պ�
		IN 	AL,DX
L1: 
		TEST AL,01H             ;�Ƿ�Ϊ��1��
		JNZ L2					;����������ж�
		MOV AL,00H              ;���õ�1�е�1�ж�Ӧ�ļ�ֵ
		JMP KCODE
L2: 
		TEST AL,02H             ;�Ƿ�Ϊ��2��
		JNZ L3					;����������ж�
		MOV AL,04H              ;���õ�2�е�1�ж�Ӧ�ļ�ֵ
		JMP KCODE
L3: 
		TEST AL,04H             ;�Ƿ��ǵ�3��
		JNZ L4					;����������ж�
		MOV AL,08H              ;���õ�3�е�1�ж�Ӧ�ļ�ֵ
		JMP KCODE
L4: 
		TEST AL,08H             ;�Ƿ��ǵ�4��
		JNZ NEXT				;����������ж�
		MOV AL,0CH              ;���õ�4�е�1�ж�Ӧ�ļ�ֵ
KCODE:  
		ADD AL,CL				;����1�е�ֵ���ϵ�ǰ������ȷ������ֵ
		CALL PUTBUF				;���水��ֵ
		PUSH AX
KON: 
		CALL DIS				;��ʾˢ��
		CALL CLEAR				;����
		CALL CCSCAN				;ɨ�谴�����жϰ����Ƿ���
		JNZ KON					;δ���������ѭ���ȴ�����
		POP AX
NEXT:  
		INC CL					;��ǰ������������
		MOV AL,CH				
		TEST AL,08H				;����Ƿ�ɨ�赽��4��
		JZ KERR					;�������ص���ʼ��
		ROL AL,1				;û��⵽��4����׼�������һ��
		MOV CH,AL				
		JMP COLUM
KERR:  
		JMP BEGIN

PUTBUF: 
		MOV SI,DI              	
		MOV [SI],AL				;�����ֵ����Ӧλ�Ļ�����
		DEC DI
		CMP DI,2FFFH			;��ǰ�����Ϊ�������7����ʵ�ʲ����ڣ�
		JNZ GOBACK
		MOV DI,3005H			;�ص������1
GOBACK: 
		RET
		
CCSCAN: 						;ɨ���Ƿ��а����պ�
		MOV AL,00H             
		MOV DX,MY8255_A			;��4��ȫѡͨ��X1~X4��0
		OUT DX,AL
		MOV DX,MY8255_C
		IN 	AL,DX				;��Y1~Y4
		NOT AL						
		AND AL,0FH				;ȡ��Y1~Y4�ķ�ֵ
		RET
	
CLEAR:  						;�����ӳ���
		MOV DX,MY8255_B         ;��λ��0��������������ʾ
		MOV AL,00H
		OUT DX,AL
		RET
	
DIS: 							;��ʾ��ֵ�ӳ���
		PUSH AX    				;�Ի�������ŵļ�ֵΪ��ֵ��ƫ���ҵ���ֵ����ʾ             
		MOV SI,3000H			
		MOV DL,0DFH
		MOV AL,DL
AGAIN:  
		PUSH DX
		MOV DX,MY8255_A
		OUT DX,AL				;����X1~X6��ѡͨһ�������
    
		MOV AL,[SI]				;ȡ���������д�ż�ֵ
		MOV BX,OFFSET DTABLE	
		AND AX,00FFH
		ADD BX,AX				
		MOV AL,[BX]				;����ֵ��Ϊƫ�ƺͼ�ֵ����ַ��ӵõ���Ӧ�Ĺ���������ܱ���
		MOV DX,MY8255_B
		OUT DX,AL				;д�������A~Dp
    
		CALL DALLY
		INC SI					;ȡ��һ����ֵ
		POP DX
		MOV AL,DL
		TEST AL,01H				;�ж��Ƿ���ʾ��
		JZ OUT1					;��ʾ�꣬����
		ROR AL,1
		MOV DL,AL
		JMP AGAIN				;δ��ʾ�꣬���ؼ���
OUT1:  
		POP AX				
		RET


DALLY:  
		PUSH CX                	;��ʱ�ӳ���
		MOV CX,0006H
T1: 	
		MOV AX,009FH
T2: 
		DEC AX
		JNZ T2
		LOOP T1
		POP CX
		RET
CODE 	ENDS
		END START