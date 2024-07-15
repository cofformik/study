;8255接口初始化，由CS连接的IOY端口决定。这里用的是IOY0。
A8255_CON EQU 0606H
A8255_A EQU 0600H
A8255_B EQU 0602H
A8255_C EQU 0604H
;8254接口初始化，由CS连接的IOY端口决定。这里用的是IOY1。
A8254 EQU 0640H
B8254 EQU 0642H 
C8254 EQU 0644H 
CON8254 EQU 0646H
SSTACK 	SEGMENT STACK 
		DW 32 DUP(?) 
SSTACK 	ENDS
;数码管的数据表，分别表示123 从左向右点亮 从左往右看就是数字“123”
DATA	SEGMENT
TABLE1:
		DB 06H					;"1"
		DB 5BH					;"2"
		DB 4FH					;"3"
VALUE	DB 00H					;用于状态控制
DATA 	ENDS 
CODE 	SEGMENT 
		ASSUME CS:CODE,DS:DATA
START:	
		MOV DX,A8255_CON
		MOV AL,80H				;80H=10000000B A口方式0 输出 B口方式0 输出
		OUT DX,AL
	  
	  
		MOV AX,0000H
		MOV DS,AX
		MOV AX, OFFSET MIR6 	;8254单元OUT1连接MIR6 CLK1接时钟源18.432Hz GATE1接K0 
		MOV SI, 0038H			;K0可控制方波是否发生（K0高电平有方波 低电平没有） 进而控制是否有中断（中断在上升边沿触发）
		MOV [SI], AX			;从而可以控制123是否向右循环移动
		MOV AX,CS				;K0高电平循环右移 K0低电平停止移动
		MOV SI,003AH
		MOV [SI], AX
 
		CLI
		MOV AL, 11H				;上升边沿触发
		OUT 20H, AL
		MOV AL, 08H
		OUT 21H, AL
		MOV AL, 04H
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
		
		MOV AX,DATA				;装入数据段
		MOV DS,AX
		LEA SI,TABLE1
FOREVER: 
AA1:	CMP VALUE,00H			;状态1 数字1位于数码管1（最左侧）
		JZ	A1
AA2:	CMP VALUE,01H			;状态2 数字1位于数码管2
		JZ  A2
AA3:	CMP VALUE,02H			;状态3 数字1位于数码管3
		JZ 	A3
AA4:	CMP VALUE,03H			;状态4 数字1位于数码管4
		JZ	A4
AA5:	CMP VALUE,04H			;状态5 数字1位于数码管5
		JZ 	A5
AA6:	CMP	VALUE,05H			;状态6 数字1位于数码管6（最右侧）
		JZ	A6
		JMP FOREVER 
;将GATE1置为高电平，运行程序，在示波器中可以看到OUT1规律输出方波。
;CLK1输入为18.432kHz 用计时器1计数18432次 得到周期为1s的方波。
;想要得到周期1s的方波 计数初值为18432 即04800H
;

A1:		   
		MOV CX,03H					;循环3次
		MOV BX,0000H
		MOV AL,01111111B			;数码管1将要点亮
;数码管1-6的位选信号为X1-X6
;备注：机箱上从左往右为数码管1-6
;实验中X1接了PA0 X2--PA1 X3--PA2 X4--PA3 X5--PA4 X6--PA5
;数码管1 数码管2 数码管3 数码管4 数码管5 数码管6
;  X1      X2      X3      X4      X5      X6
;  PA0     PA1     PA2     PA3     PA4     PA5
X1: ;与后面的子程序XX1相同 将代码放在这里 仅是为了分析逻辑	
		CMP AL,0DFH
		JNZ X2 
		ROL AL,2					;AL有8位 而位选信号只有6位 故在AL=DFH=11011111B时 需要多左移两位
X2:		
		ROL AL,1					;点亮目标数码管
		MOV DX,A8255_A
		OUT DX,AL		
		PUSH AX						;保护位选信号
		MOV AL,[BX+SI]
		MOV DX,A8255_B
		OUT DX,AL					;在相应数码管上显示当前的数字
		POP AX						
		CALL DELAY
		INC BX						;选定下一个数码管要显示的数字
		LOOP X1
		JMP AA1

A2:		   
		MOV CX,03H					;循环3次
		MOV BX,0000H
		MOV AL,11111110B			;数码管2将要点亮
		CALL XX1
		JMP AA2
		
A3:		   
		MOV CX,03H					;循环3次
		MOV BX,0000H
		MOV AL,11111101B			;数码管3将要点亮
		CALL XX1
		JMP AA3
		
A4:		   
		MOV CX,03H					;循环3次
		MOV BX,0000H
		MOV AL,11111011B			;数码管4将要点亮
		CALL XX1
		JMP AA4
		
A5:		   
		MOV CX,03H					;循环3次
		MOV BX,0000H
		MOV AL,11110111B			;数码管5将要点亮
		CALL XX1
		JMP AA5
		
A6:		   
		MOV CX,03H					;循环3次
		MOV BX,0000H
		MOV AL,11101111B			;数码管6将要点亮
		CALL XX1
		JMP AA6

MIR6:
		CMP VALUE,05H			;若当前状态是状态6 回溯到状态1 以达到循环的目的
		JZ  M
		ADD VALUE,01H
		JMP N
M:		MOV VALUE,00H			;回到状态1
N:		NOP
		IRET

XX1: 								;点亮数码管子程序
		CMP AL,0DFH
		JNZ XX2 
		ROL AL,2					;AL有8位 而位选信号只有6位 故在AL=DFH=11011111B时 需要多左移两位
XX2:		
		ROL AL,1					;点亮目标数码管
		MOV DX,A8255_A
		OUT DX,AL		
		PUSH AX						;保护位选信号
		MOV AL,[BX+SI]
		MOV DX,A8255_B
		OUT DX,AL					;在相应数码管上显示当前的数字
		POP AX						
		CALL DELAY
		INC BX						;选定下一个数码管要显示的数字
		LOOP XX1
		RET
 
DELAY:							;延时子程序
		PUSH CX
		PUSH AX
		MOV CX,0FFH				;由于要显示稳定的数字“123” 延时要短
L1:
		LOOP L1
		POP AX
		POP CX
		RET

CODE 	ENDS 
		END START