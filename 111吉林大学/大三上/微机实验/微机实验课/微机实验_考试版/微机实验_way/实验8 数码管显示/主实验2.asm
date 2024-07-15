;8255接口初始化，由CS连接的IOY端口决定。这里用的是IOY0。
A8255_CON EQU 0606H
A8255_A EQU 0600H
A8255_B EQU 0602H
A8255_C EQU 0604H
;数码管的数据表，分别表示6-1 从右向左点亮 从左往右看就是数字“123456”了
DATA 	SEGMENT
TABLE1:
		DB 7DH
		DB 6DH
		DB 66H
		DB 4FH
		DB 5BH
		DB 06H
DATA 	ENDS
CODE 	SEGMENT
		ASSUME CS:CODE,DS:DATA
START:
		MOV AX,DATA
		MOV DS,AX
		LEA SI,TABLE1
		MOV DX,A8255_CON
		MOV AL,81H					;81H=10000001B A口方式0 输出 B口方式0 输出 C口低四位 输入
		OUT DX,AL
		;当初测试用的遗留代码
		MOV DX,A8255_B
		MOV AL,3FH					;“0"的编码
		OUT DX,AL
		MOV DX,A8255_A
		MOV AL,00H
		OUT DX,AL
		;位选信号置0 相应数码管点亮
X2:    
		MOV CX,06H					;循环6次
		MOV BX,0000H
		MOV AL,11011111B			;数码管6将要点亮
;数码管1-6的位选信号为X1-X6
;备注：机箱上从左往右为数码管1-6
;实验中X1接了PA0 X2--PA1 X3--PA2 X4--PA3 X5--PA4 X6--PA5
;数码管1 数码管2 数码管3 数码管4 数码管5 数码管6
;  X1      X2      X3      X4      X5      X6
;  PA0     PA1     PA2     PA3     PA4     PA5
X1: 
		MOV DX,A8255_A
		OUT DX,AL		
		ROR AL,1					;将要点亮下一个数码管
		PUSH AX						;保护位选信号
		MOV AL,[BX+SI]
		MOV DX,A8255_B
		OUT DX,AL
		POP AX						;在相应数码管上显示当前的数字
		CALL DELAY
		INC BX						;选定下一个数码管要显示的数字
		LOOP X1
		JMP X2    
DELAY:
		PUSH CX
		MOV CX,0FFH					;由于要显示稳定的数字“123456” 延时要短
X4:
		LOOP X4
		POP CX
		RET
CODE 	ENDS
		END START