M8251_DATA EQU 0600H             	;8251数据端口地址
M8251_CON EQU 0602H              	;8251控制端口地址
M8254_2 EQU 06C4H                	;8254计数器2端口地址
M8254_CON EQU 06C6H              	;8254控制寄存器端口地址
M8255_CON EQU 0646H              	;8255控制寄存器端口地址
M8255_B EQU 0642H                	;8255B口地址
;关于接线 RxCLK TxCLK OUT2 CLK2 GATE2 已在机箱内部接好
SSTACK  SEGMENT STACK
		DW 64 DUP(?)
SSTACK  ENDS
 
CODE 	SEGMENT
		ASSUME CS:CODE
START:  
		MOV AX, 0000H
		MOV DS, AX
 
		MOV DX, M8255_CON
		MOV AL, 90H
		OUT DX, AL
		MOV DX, M8255_B
		MOV AL, 11000111B			;开始时数据灯状态 如果传输无错误保持此状态
		OUT DX, AL
		;初始化8255，B口输出
 
AA0: 
		MOV SI, 3000H               ;数据首写入首地址
		MOV CX, 001AH				;循环26次
		MOV AX, 61H					;“a”的ASCII码为61H
AA1: 
		MOV [SI], AX
		INC AX
		INC SI
		LOOP AA1
 
		;初始化 8254，得到收发时钟
		MOV AL, 0B6H				;计数器2 先读/写低8位再读/写高8位 方式3 二进制数
		MOV DX, M8254_CON
		OUT DX, AL
		MOV AL, 0CH
		MOV DX, M8254_2
		OUT DX, AL
		MOV AL, 00					;写入计数初值000CH=12 为确保波特率为9600
		OUT DX, AL
;
;备注：CLK2接的是1.8432MHz的时钟
;波特率9600 波特率因子16（由方式控制字决定） OUT2接RxCLK和TxCLK RxCLK=TxCLK=9600x16=153600Hz
;CLK2=1.8432MHz OUT2=153600Hz 可得到计数器2的计数初值 即CLK2/OUT2=12=000CH 
;
		MOV DX, M8251_CON
		MOV AL, 00H
		OUT DX, AL
		CALL DELAY
		;复位 8251
 
		MOV AL, 40H
		OUT DX, AL
		CALL DELAY
 
		;8251 方式字
		MOV AL,7EH
		OUT DX, AL					;写入8251方式字7EH=01111110B，详见实验讲义P59
		CALL DELAY					;1位停止位 偶校验 字符长度8位 波特率系数16
 
		;8251 控制字
		MOV AL, 34H
		OUT DX, AL					;写入8251控制字34H=00110100B，详见实验讲义P60
		CALL DELAY					;
 
		MOV DI, 4000H				;写入地址
		MOV SI, 3000H				;读入地址
		MOV CX, 001AH				;循环26次
A1: 
		MOV AL, [SI]
		PUSH AX
		MOV AL, 37H					;数据终端准备好了
		MOV DX, M8251_CON
		OUT DX, AL
		POP AX
		MOV DX, M8251_DATA
		OUT DX, AL  
		;发送数据
		MOV DX, M8251_CON
A2: 
		IN AL, DX
		AND AL, 01H
		;判断发送缓冲是否为空
		JZ A2
		CALL DELAY
A3: 
		IN AL, DX 
		;MOV DX, M8255_B
		;OUT DX, AL
		TEST AL, 02H
		;判断是否接收到数据
		JZ A3
		TEST AL, 38H
		;判断是否有错误，如果出现错误则显示在D7-D0上
		JZ CONTINUE
		MOV DX, M8255_B
		OUT DX, AL					;显示错误
		JMP EXIT
CONTINUE:
		MOV DX, M8251_DATA
		IN AL, DX 
		;读取接收到的数据
		MOV [DI], AL
		INC DI
		INC SI
		LOOP A1						;循环26次
EXIT:    
		MOV AH,4CH
		INT 21H 
		;程序终止
 
DELAY:
		PUSH CX
		MOV CX,3000H
A5: 
		PUSH AX
		POP AX
		LOOP A5
		POP CX
		RET
CODE 	ENDS
		END START