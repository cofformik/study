;8255�ӿڳ�ʼ������CS���ӵ�IOY�˿ھ����������õ���IOY0��
A8255_CON EQU 0606H
A8255_A EQU 0600H
A8255_B EQU 0602H
A8255_C EQU 0604H

;�����1	�����2		�����3		�����4		�����5		�����6
;									  ��3		  ��2 		  ��1	
 
PUBLIC LED1			;��1Ϊ�����6 ���Ҳ������
PUBLIC LED2			;��2Ϊ�����5 �Ҳ൹���ڶ��������
PUBLIC LED3			;��3Ϊ�����4 �Ҳ൹�������������
DATA SEGMENT
LED1 DB ?
LED2 DB ?
LED3 DB ?
TABLE1:
    DB 3FH			;0�ı���
    DB 06H			;1
    DB 5BH			;2
    DB 4FH			;3
    DB 66H			;4
    DB 6DH			;5
    DB 7DH			;6
    DB 07H			;7
    DB 7FH			;8
    DB 6FH			;9
DATA ENDS
 
CODE 	SEGMENT
    	ASSUME CS:CODE,DS:DATA
START:
    	MOV AX,DATA
    	MOV DS,AX
    	LEA SI,TABLE1
    	MOV DX,A8255_CON
    	MOV AL,89H				;89H=10001001B A����� B����� C������
    	OUT DX,AL
    	MOV DX,A8255_B
    	MOV AL,3FH				;3FH=00111111B 0�ı���
    	OUT DX,AL
    	MOV DX,A8255_A
    	MOV AL,00H				;00H=00000000B
    	OUT DX,AL
X2:    
    	MOV DX,A8255_C
    	IN AL,DX				;���뿪��״̬
    	MOV AH,00H
    	MOV BL,0AH
   	 	DIV BL
    	MOV LED1, AH			;��λ
    	MOV AH,00H
    	DIV BL
    	MOV LED2, AH			;ʮλ
    	MOV AH,00H
    	DIV BL
    	MOV LED3, AH			;��λ
    	
    	MOV CX,03H					
    	MOV BX,0000H
    	MOV AL,11011111B		;ѡ�������6
    	MOV DX,A8255_A
    	OUT DX,AL
    	MOV BX,OFFSET LED1
    	MOV BX,[BX]
    	MOV BH,00H
    	MOV AL,[BX+SI]
    	MOV DX,A8255_B
    	OUT DX,AL				;��ʾ��λ
    	CALL DELAY
    	MOV AL,00H
    	OUT DX,AL
    	
    	MOV AL,11101111B		;ѡ�������5
    	MOV DX,A8255_A
    	OUT DX,AL
    	MOV BX,OFFSET LED2
    	MOV BX,[BX]
    	MOV BH,00H
    	MOV AL,[BX+SI]
    	MOV DX,A8255_B
    	OUT DX,AL				;��ʾʮλ
    	CALL DELAY
   		MOV AL,00H
    	OUT DX,AL
    	
    	MOV AL,11110111B		;ѡ�������4
    	MOV DX,A8255_A
    	OUT DX,AL
    	MOV BX,OFFSET LED3
    	MOV BX,[BX]
    	MOV BH,00H
    	MOV AL,[BX+SI]
    	MOV DX,A8255_B
    	OUT DX,AL				;��ʾ��λ
    	CALL DELAY
    	MOV AL,00H
    	OUT DX,AL
    	JMP X2    				;����X2 �ٴζ�ȡ����״̬
DELAY:
    	PUSH CX
    	MOV CX,0FFH
X4:
    	LOOP X4
    	POP CX
    	RET
CODE 	ENDS
     	END START