P8255A EQU 0640H
P8255B EQU 0642H
P8255C EQU 0646H
P8255MODE EQU 0646H
CODE SEGMENT
		ASSUME CS:CODE
START:
		MOV DX,P8255MODE
		MOV AL,10010000B
		OUT DX,AL				;送方式控制字
		
NEXT:
		MOV DX,P8255A
		IN  AL,DX				;读a口
		AND AL,03H
		JZ  A1					;K1K0=00
		SUB AL,1
		JZ  A2					;K1K0=01
		SUB AL,1
		JZ  A3					;K1K0=10
		SUB AL,1
		JZ  A4					;K1K0=11
A1:		MOV AL,00H				;数据灯全部熄灭
		JMP OUT
A2:		MOV AL,0FH				;数据灯低四位亮
		JMP OUT
A3:		MOV AL,0F0H				;数据灯高四位亮
		JMP OUT
A4:		MOV AL,0FFH				;数据灯全亮
		
OUT:	MOV DX,P8255B
		OUT DX,AL				;送b口
		JMP NEXT


		
OVER:	MOV AH,4CH
		INT 21H
CODE ENDS
		END START