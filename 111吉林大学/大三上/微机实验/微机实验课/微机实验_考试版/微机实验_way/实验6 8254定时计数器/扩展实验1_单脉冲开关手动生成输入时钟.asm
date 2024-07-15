A8254 EQU 0600H
B8254 EQU 0602H 
C8254 EQU 0604H 
CON8254 EQU 0606H
;8254计数器012以及控制端口的地址，由IOY决定， 此处用的IOY0
SSTACK 	SEGMENT STACK 
		DW 32 DUP(?) 
SSTACK 	ENDS 
CODE 	SEGMENT 
		ASSUME CS:CODE
START: 
		;CLK1连接一个单脉冲开关
 
		MOV DX, CON8254
		MOV AL, 70H             ;8254计数器1工作在方式0，计数时输出低电平，到0时输出高电平 
		OUT DX, AL 
		MOV DX, B8254 
		MOV AL, 05H 
		OUT DX, AL 
		MOV AL, 00H             ;写入计数初值0005H
		OUT DX, AL 
AA1: 
		JMP AA1 
;将GATE1置为低电平，运行程序。
;将GATE1置为高电平，在示波器中可以观察到OUT1输出低电平，待过一段时间后（计数器减至0）输出高电平。
;当方式0控制字写进某计数器的控制寄存器后，计数器的输出OUT立即变低（与GATE的状态无关）。
;在GATE为高电平的情况下，减1计数器开始计数。
;每来一个计数脉冲CLK，减1计数器的值减1，当减1计数器的变成0时，OUT变成高电平。
;此高电平一直保持到CPU又写入一个方式0控制字，OUT又立即变低，
;再写入计数初值，减1计数器按照新的计数初值开始计数;
;或者CPU重新写一个计数初值，OUT也立即变低，计数器按新的计数初值计数，
;并计数到0时，OUT又变成高电平为止。
;
;备注：工作方式重要性排序
;3,0＞2＞1,4,5
;
CODE 	ENDS 
		END START