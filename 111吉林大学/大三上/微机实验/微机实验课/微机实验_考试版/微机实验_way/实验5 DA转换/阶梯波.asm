STACK 	SEGMENT STACK
		DW 32 DUP(?)
STACK 	ENDS
 
CODE 	SEGMENT
		ASSUME  CS:CODE, SS:STACK
 
START:
		;产生阶梯波
		MOV CX, 0FFFFH     	;产生阶梯波的周期数为0FFFF次，如果想改变阶梯波产生周期请修改这里
		MOV AX, 0FEH       
		;波形振幅最大值为0FFH
		;考虑到8086的DIV除法可能会出现余数为负导致加起来之后的最大值大于0FFH，故使用0FEH作最大值
		MOV BL,05H         	;阶梯波中的阶梯数，如果想改变阶梯波中的阶梯数请修改这里
		DIV BL             	;用最大振幅除以阶梯数，得到每个台阶的高度
		MOV BL, AL         	;将上述除法的商保存在BL中
		MOV BH, 00H        	;BH置0
JIETI:
		MOV AX,0000H       	;AX初始化0000H
JT1:
		MOV DX, 0600H
		OUT DX, AL
		CMP AX, 00FFH      	;判断AX是否达到幅度上线
		JAE JT2            	;达到上限，表示一次阶梯波完整生成，开始新一次生成
		CALL DELAY2        	;长延时
		ADD AX, BX         	;用当前解体高度加上每个阶梯的高度得到下一阶梯的高度
		JMP JT1
JT2:    
		LOOP JIETI
 
 
DELAY1:                		;短延时
		PUSH CX
		MOV CX, 01FFH
D1: 
		PUSH AX
		POP AX
		LOOP D1
		POP CX
		RET
 
DELAY2:               		;长延时
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