P8255A EQU 0640H
P8255B EQU 0642H
P8255C EQU 0646H
P8255MODE EQU 0646H				;8255片选CS接IOY1
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
		MOV BL,00H				;初始时，数据灯全部熄灭
		MOV DX,P8255MODE
		MOV AL,10010000B
		OUT DX,AL				;送方式控制字

		MOV AL,BL
		MOV DX,P8255B
		OUT DX,AL				;送b口
	  
		MOV AX,0000H
		MOV DS,AX
		MOV AX, OFFSET MIR6 	;8254单元OUT1连接MIR6
		MOV SI, 0038H
		MOV [SI], AX
		MOV AX,CS
		MOV SI,003AH
		MOV [SI], AX
 
		CLI
		MOV AL, 11H				;上升边沿触发
		OUT 20H, AL
		MOV AL, 08H
		OUT 21H, AL
		MOV AL,04H
		OUT 21H, AL
		MOV AL, 07H
		OUT 21H, AL
		MOV AL, 10101111B		;开放了IR4 IR6 IR4必须开放 否则会造成不可预料的情况
		OUT 21H, AL
		STI
    

		MOV DX, CON8254
		MOV AL, 76H            	;8254计数器1工作在方式3，产生方波。 
		OUT DX, AL 
		MOV DX, B8254 
		MOV AL, 00H
		OUT DX, AL 
		MOV AL, 048H            ;写入计数初值04800H
		OUT DX, AL 
AA1: 
		JMP AA1 
;将GATE1置为高电平，运行程序，在示波器中可以看到OUT1规律输出方波。
;CLK1输入为18.432kHz 用计时器1计数18432次 得到周期为1s的方波。
;想要得到周期1s的方波 计数初值为18432 即04800H
;
MIR6:
		CMP BL,0FFH
		JZ  M
		SHL BL,1				;数据灯逐渐点亮的控制
		ADD BL,01H				;同上
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