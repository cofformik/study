P8255A EQU 0640H
P8255B EQU 0642H
P8255C EQU 0646H
P8255MODE EQU 0646H
SSTACK	SEGMENT STACK
		DW 32 DUP(0)
SSTACK	ENDS
DATA 	SEGMENT
VALUE	DB	00H					;标志
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
		CLI						;初始化前关中断
		POP DS
		;初始化主片8259
		MOV AL, 11H				;级联，边沿触发，要ICW4
		OUT 20H, AL				;ICW1
		MOV AL, 08H				;中断类型号从8开始
		OUT 21H, AL				;ICW2
		MOV AL, 04H				; 
		OUT 21H, AL				;ICW3
		MOV AL, 01H				;非缓冲方式，8086/8088配置
		OUT 21H, AL				;ICW4
 
		;初始化从片8259
		MOV AL, 11H				;级联，边沿触发，要ICW4
		OUT 0A0H, AL			;ICW1
		MOV AL, 30H				;终端类型号从30H开始
		OUT 0A1H, AL			;ICW2
		MOV AL, 02H				;通过IR1引脚连接主片
		OUT 0A1H, AL			;ICW3
		MOV AL, 01H				;非缓冲方式，8086/8088配置
		OUT 0A1H, AL			;ICW4
		MOV AL, 0FDH
		OUT 0A1H,AL				;从8259 OCW1 = 1111 1101	允许IR1中断请求	
		MOV AL, 2BH       		;0010 1011
		OUT 21H, AL				;主8259 OCW1	允许IR2 IR4 IR6 IR7
		STI
 		
AA2:	NOP
AA24:	CMP VALUE,0C0H			;阶梯波
		JZ	AA6
AA23:	CMP VALUE,80H			;三角波
		JZ  AA5
AA22:	CMP VALUE,40H			;矩形波
		JZ	AA4
AA21:	CMP VALUE,00H			;锯齿波
		JZ	AA3
		JMP AA2		
		
AA3:	
		MOV DX, 0600H     		;DAC0832接IOY0,0600H为控制端口地址
		MOV AL, 00H       		;AL为数字量
JC1: 
		OUT DX, AL        		;转换为模拟量
		CALL DELAY1       		;延时，此为短延时
		CMP AL ,0FFH
		JE JC2
		INC AL            		;AL步加1，直到等于0FFH
		JMP JC1
JC2:
		JMP	AA21
    	
AA4:
		MOV DX, 0600H
		MOV AL, 00H       		;先输出00H的波形
		OUT DX, AL
		CALL DELAY2       		;长延时
		MOV AL, 0FFH      		;再输出0FFH的波形
		OUT DX, AL
		CALL DELAY2       		;长延时  
		JMP	AA22
   
AA5:
		MOV AL,00H
SJ1:
		MOV DX, 0600H
		OUT DX, AL
		CALL DELAY1       		;短延时
		CMP AL, 0FFH
		JE SJ2           
		INC AL            		;将AL从00H步加0FFH
		JMP SJ1
SJ2:
		MOV DX, 0600H
		OUT DX, AL
		CALL DELAY1       		;短延时
		CMP AL, 00H
		JE SJ3
		DEC AL            		;将AL从0FFH步减至00H
		JMP SJ2
SJ3:
		JMP	AA23

AA6:
		MOV AX, 0FEH       
		;波形振幅最大值为0FFH
		;考虑到8086的DIV除法可能会出现余数为负导致加起来之后的最大值大于0FFH，故使用0FEH作最大值
		MOV BL,05H         		;阶梯波中的阶梯数，如果想改变阶梯波中的阶梯数请修改这里
		DIV BL             		;用最大振幅除以阶梯数，得到每个台阶的高度
		MOV BL, AL         		;将上述除法的商保存在BL中
		MOV BH, 00H        		;BH置0
JIETI:
		MOV AX,0000H       		;AX初始化0000H
JT1:
		MOV DX, 0600H
		OUT DX, AL
		CMP AX, 00FFH      		;判断AX是否达到幅度上线
		JAE JT2            		;达到上限，表示一次阶梯波完整生成，开始新一次生成
		CALL DELAY2       	 	;长延时
		ADD AX, BX         		;用当前解体高度加上每个阶梯的高度得到下一阶梯的高度
		JMP JT1
JT2:
		JMP AA24

MIR6:	
		ADD VALUE,64			;循环增量
		PUSH AX					;保护AX
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
DELAY1:                			;短延时
		PUSH CX
		MOV CX, 01FFH
D1: 
		PUSH AX
		POP AX
		LOOP D1
		POP CX
		RET
 
DELAY2:               			;长延时
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