CODE SEGMENT
	ASSUME CS:CODE
START:
 	MOV AX, 8000H
	MOV DS, AX
	MOV DX, 0646H
	MOV AL, 90H
	OUT DX, AL			
		
MAIN:
	MOV DX, 0640H
	IN AL, DX			
	AND AL, 03H			;K1K0=00
	JZ  A1
	SUB AL, 1				;K1K0=01
	JZ  A2
	SUB AL, 1				;K1K0=10
	JZ A3
	SUB AL, 1				;K1K0=11 退出程序
	JZ  OVER
	
	;规则字	
A1:		
	MOV BX, 0000H
	MOV CX, 16
	MOV DX, 0000H
AA1:	
	MOV [BX], DX
       	ADD BX, 2
      	INC DX
	LOOP AA1
	JMP MAIN
		

	;非规则字

A2:		
	 MOV BX, 00H	;8000:0000写入
       	MOV [BX], 00H
       	ADD BX, 1		;8000:0001
       	MOV DX, 0100H 
       	MOV CX, 15

AA2:	
	MOV [BX], DX
       	ADD BX, 2
       	INC DH
       	LOOP AA2
	MOV [BX], 00H	;最后写入8000:0020
	JMP MAIN
		


A3:		
       	MOV BX, 00H   
       	MOV DX, 00H   
      	MOV CX, 16
AA3:	
       	MOV [BX], DL
       	MOV [BX+1], DH
       	ADD BX, 2
       	INC DX
       	LOOP AA3
	JMP MAIN
	
QUIT:
	MOV AH, 4CH
	INT 21H

CODE ENDS
	END START