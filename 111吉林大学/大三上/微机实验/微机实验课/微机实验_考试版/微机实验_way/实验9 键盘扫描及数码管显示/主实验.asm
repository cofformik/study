;8255接口初始化，由CS连接的IOY端口决定。这里用的是IOY0。
MY8255_A EQU 0600H
MY8255_B EQU 0602H
MY8255_C EQU 0604H
MY8255_CON  EQU 0606H
SSTACK  SEGMENT STACK
		DW 16 DUP(?)
SSTACK  ENDS
 
DATA 	SEGMENT
		DTABLE  DB 3FH,06H,5BH,4FH,66H,6DH,7DH,07H,7FH,6FH,77H,7CH,39H,5EH,79H,71H	;0~9 A~F
DATA 	ENDS
;
;此程序实现的功能如下
;初始时数码管均显示“0”
;第一次按下键盘时，在最左侧数码管显示对应的十六进制数字
;第二次按下键盘时，在左数第二个数码管显示对应的十六进制数字
;...
;第六次按下键盘时，在最右侧数码管显示对应的十六进制数字
;第七次按下键盘时，在最左侧数码管显示对应的十六进制数字
;第八次按下键盘时，在左数第二个数码管显示相应的十六进制数字
;...
;如此循环
;

;
;简单来讲
;当按下键盘其中一个按键时，将该按键对应的编号在一个数码管上显示出来，
;当再按下一个按键时，便将这个按键的编号在下一个数码管上显示出来，
;数码管上可以显示最近 6 次按下的按键编号。
;

;
;阅读程序前 请先阅读理解《微型计算机原理与接口技术》（第二版） p296-300 行扫描法
;
CODE 	SEGMENT
		ASSUME CS:CODE,DS:DATA
START:  
		MOV AX,DATA				;装载数据段
		MOV DS,AX
		MOV SI,3000H			;建立缓冲区，存放要显示的键值
		MOV AL,00H
		MOV [SI],AL        		;管6 清显示缓冲
		MOV [SI+1],AL			;管5
		MOV [SI+2],AL			;管4
		MOV [SI+3],AL			;管3
		MOV [SI+4],AL			;管2
		MOV [SI+5],AL			;管1
		MOV DI,3005H
		MOV DX,MY8255_CON  		;写 8255 控制字
		MOV AL,81H				;81H=10000001 A口方式0 输出 B口方式0 输出 C口低四位 输入
		OUT DX,AL
BEGIN:  
		CALL DIS                ;调用显示子程序
		CALL CLEAR              ;清屏
		CALL CCSCAN             ;扫描按键
		JNZ INK1				
		JMP BEGIN
 
INK1:  
		CALL DIS
		CALL DALLY				;消除前沿抖动
		CALL DALLY
		CALL CLEAR
		CALL CCSCAN				;再次扫描按键
		JNZ INK2                ;有键按下，转到 INK2
		JMP BEGIN
	
;确定按下键的位置
INK2:  
		MOV CH,0FEH				;11111110B 刚开始选取第一列
		MOV CL,00H				;设置当前检测的是第几列
 
COLUM:  
		MOV AL,CH				;选取一列，将X1~X4中一个置0
		MOV DX,MY8255_A
		OUT DX,AL
		MOV DX,MY8255_C			;读Y1~Y4，用于判断是哪一行按键闭合
		IN 	AL,DX
L1: 
		TEST AL,01H             ;是否为第1行
		JNZ L2					;不是则继续判断
		MOV AL,00H              ;设置第1行第1列对应的键值
		JMP KCODE
L2: 
		TEST AL,02H             ;是否为第2行
		JNZ L3					;不是则继续判断
		MOV AL,04H              ;设置第2行第1列对应的键值
		JMP KCODE
L3: 
		TEST AL,04H             ;是否是第3行
		JNZ L4					;不是则继续判断
		MOV AL,08H              ;设置第3行第1列对应的键值
		JMP KCODE
L4: 
		TEST AL,08H             ;是否是第4行
		JNZ NEXT				;不是则继续判断
		MOV AL,0CH              ;设置第4行第1列对应的键值
KCODE:  
		ADD AL,CL				;将第1列的值加上当前列数，确定按键值
		CALL PUTBUF				;保存按键值
		PUSH AX
KON: 
		CALL DIS				;显示刷新
		CALL CLEAR				;清屏
		CALL CCSCAN				;扫描按键，判断按键是否弹起
		JNZ KON					;未弹起则继续循环等待弹起
		POP AX
NEXT:  
		INC CL					;当前检测的列数递增
		MOV AL,CH				
		TEST AL,08H				;检测是否扫描到第4列
		JZ KERR					;是则跳回到开始处
		ROL AL,1				;没检测到第4列则准备检测下一列
		MOV CH,AL				
		JMP COLUM
KERR:  
		JMP BEGIN

PUTBUF: 
		MOV SI,DI              	
		MOV [SI],AL				;存键盘值到相应位的缓冲中
		DEC DI
		CMP DI,2FFFH			;当前数码管为“数码管7”（实际不存在）
		JNZ GOBACK
		MOV DI,3005H			;回到数码管1
GOBACK: 
		RET
		
CCSCAN: 						;扫描是否有按键闭合
		MOV AL,00H             
		MOV DX,MY8255_A			;将4列全选通，X1~X4置0
		OUT DX,AL
		MOV DX,MY8255_C
		IN 	AL,DX				;读Y1~Y4
		NOT AL						
		AND AL,0FH				;取出Y1~Y4的反值
		RET
	
CLEAR:  						;清屏子程序
		MOV DX,MY8255_B         ;段位置0即可清除数码管显示
		MOV AL,00H
		OUT DX,AL
		RET
	
DIS: 							;显示键值子程序
		PUSH AX    				;以缓冲区存放的键值为键值表偏移找到键值并显示             
		MOV SI,3000H			
		MOV DL,0DFH
		MOV AL,DL
AGAIN:  
		PUSH DX
		MOV DX,MY8255_A
		OUT DX,AL				;设置X1~X6，选通一个数码管
    
		MOV AL,[SI]				;取出缓冲区中存放键值
		MOV BX,OFFSET DTABLE	
		AND AX,00FFH
		ADD BX,AX				
		MOV AL,[BX]				;将键值作为偏移和键值基地址相加得到相应的共阴极数码管编码
		MOV DX,MY8255_B
		OUT DX,AL				;写入数码管A~Dp
    
		CALL DALLY
		INC SI					;取下一个键值
		POP DX
		MOV AL,DL
		TEST AL,01H				;判断是否显示完
		JZ OUT1					;显示完，返回
		ROR AL,1
		MOV DL,AL
		JMP AGAIN				;未显示完，跳回继续
OUT1:  
		POP AX				
		RET


DALLY:  
		PUSH CX                	;延时子程序
		MOV CX,0006H
T1: 	
		MOV AX,009FH
T2: 
		DEC AX
		JNZ T2
		LOOP T1
		POP CX
		RET
CODE 	ENDS
		END START