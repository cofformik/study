;8255接口初始化，由CS连接的IOY端口决定。这里用的是IOY0。
A8255_CON EQU 0606H
A8255_A EQU 0600H
A8255_B EQU 0602H
A8255_C EQU 0604H

;数码管1	数码管2		数码管3		数码管4		数码管5		数码管6
;									  灯3		  灯2 		  灯1	
 
PUBLIC LED1			;灯1为数码管6 最右侧数码管
PUBLIC LED2			;灯2为数码管5 右侧倒数第二个数码管
PUBLIC LED3			;灯3为数码管4 右侧倒数第三个数码管
DATA SEGMENT
LED1 DB ?
LED2 DB ?
LED3 DB ?
TABLE1:
    DB 3FH			;0的编码
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
    	MOV AL,89H				;89H=10001001B A口输出 B口输出 C口输入
    	OUT DX,AL
    	MOV DX,A8255_B
    	MOV AL,3FH				;3FH=00111111B 0的编码
    	OUT DX,AL
    	MOV DX,A8255_A
    	MOV AL,00H				;00H=00000000B
    	OUT DX,AL
X2:    
    	MOV DX,A8255_C
    	IN AL,DX				;读入开关状态
    	MOV AH,00H
    	MOV BL,0AH
   	 	DIV BL
    	MOV LED1, AH			;个位
    	MOV AH,00H
    	DIV BL
    	MOV LED2, AH			;十位
    	MOV AH,00H
    	DIV BL
    	MOV LED3, AH			;百位
    	
    	MOV CX,03H					
    	MOV BX,0000H
    	MOV AL,11011111B		;选中数码管6
    	MOV DX,A8255_A
    	OUT DX,AL
    	MOV BX,OFFSET LED1
    	MOV BX,[BX]
    	MOV BH,00H
    	MOV AL,[BX+SI]
    	MOV DX,A8255_B
    	OUT DX,AL				;显示个位
    	CALL DELAY
    	MOV AL,00H
    	OUT DX,AL
    	
    	MOV AL,11101111B		;选中数码管5
    	MOV DX,A8255_A
    	OUT DX,AL
    	MOV BX,OFFSET LED2
    	MOV BX,[BX]
    	MOV BH,00H
    	MOV AL,[BX+SI]
    	MOV DX,A8255_B
    	OUT DX,AL				;显示十位
    	CALL DELAY
   		MOV AL,00H
    	OUT DX,AL
    	
    	MOV AL,11110111B		;选中数码管4
    	MOV DX,A8255_A
    	OUT DX,AL
    	MOV BX,OFFSET LED3
    	MOV BX,[BX]
    	MOV BH,00H
    	MOV AL,[BX+SI]
    	MOV DX,A8255_B
    	OUT DX,AL				;显示百位
    	CALL DELAY
    	MOV AL,00H
    	OUT DX,AL
    	JMP X2    				;跳到X2 再次读取开关状态
DELAY:
    	PUSH CX
    	MOV CX,0FFH
X4:
    	LOOP X4
    	POP CX
    	RET
CODE 	ENDS
     	END START