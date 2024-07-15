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
		MOV DX, CON8254
		MOV AL, 36H
		OUT DX, AL
		MOV DX, A8254
		MOV AL, 0E8H
		OUT DX, AL
		MOV AL, 03H
		OUT DX, AL
		;8254计数器0工作在方式3，产生方波，相当于CLK
		MOV DX, CON8254
		MOV AL, 76H             ;8254计数器0工作在方式3，产生方波。 
		OUT DX, AL 
		MOV DX, B8254 
		MOV AL, 0E8H
		OUT DX, AL 
		MOV AL, 03H             ;写入计数初值0E8H
		OUT DX, AL 
AA1: 
		JMP AA1 
;将GATE1置为高电平，运行程序，在示波器中可以看到OUT1规律输出方波。
;CLK0输入为1MHz的计数脉冲，周期为1μs，产生1s周期的方波需要1s/1μs=1000000个计数
;由于单个计数器的上限为2的16次方为65536远小于所需计数值
;因此将1000000拆分成1000*1000，计数器0的计数初值为1000，产生1ms的计数脉冲输入到CLK1
;计数器1的计数初值为1000，最终计数器1产生1s的方波。
CODE 	ENDS 
		END START