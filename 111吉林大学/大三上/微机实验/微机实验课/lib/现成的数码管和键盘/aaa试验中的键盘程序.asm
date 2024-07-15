;8255接口初始化，由cs连接的ioy端口决定。这里用的是ioy0。
my8255_a equ 0600h
my8255_b equ 0602h
my8255_c equ 0604h
my8255_con  equ 0606h
sstack  segment stack
		dw 16 dup(?)
sstack  ends
 
data 	segment
		dtable  db 00h,3fh,06h,5bh,4fh,66h,6dh,7dh,07h,7fh,6fh,77h,7ch,39h,5eh,79h,71h		;熄灭 0~9 a~f
data 	ends


code 	segment
		assume cs:code,ds:data
start:  
		mov ax,data				;装载数据段
		mov ds,ax
		mov si,3000h			;建立缓冲区，存放要显示的键值
		mov al,00h
		mov [si],al        		;管6 清显示缓冲
		mov [si+1],al			;管5
		mov [si+2],al			;管4
		mov [si+3],al			;管3
		mov [si+4],al			;管2
		mov [si+5],al			;管1
		mov di,3000h
		
		mov dx,my8255_con  		;写 8255 控制字
		mov al,81h				;81h=10000001 a口方式0 输出 b口方式0 输出 c口低四位 输入
		out dx,al
begin:  
		call dis                ;调用显示子程序
		call clear              ;清屏
		call ccscan             ;扫描按键
		jnz ink1				
		jmp begin
 
ink1:  
		call dis
		call delay				;消除前沿抖动
		call delay
		call clear
		call ccscan				;再次扫描按键
		jnz ink2                ;有键按下，转到 ink2
		jmp begin
	
;确定按下键的位置
ink2:  
		mov ch,0feh				;11111110b 刚开始选取第一列
		mov cl,00h				;设置当前检测的是第几列
 
colum:  
		mov al,ch				;选取一列，将x1~x4中一个置0
		mov dx,my8255_a
		out dx,al
		mov dx,my8255_c			;读y1~y4，用于判断是哪一行按键闭合
		in 	al,dx
l1: 
		test al,01h             ;是否为第1行
		jnz l2					;不是则继续判断
		mov al,01h              ;设置第1行第1列对应的键值
		jmp kcode
l2: 
		test al,02h             ;是否为第2行
		jnz l3					;不是则继续判断
		mov al,05h              ;设置第2行第1列对应的键值
		jmp kcode
l3: 
		test al,04h             ;是否是第3行
		jnz l4					;不是则继续判断
		mov al,09h              ;设置第3行第1列对应的键值
		jmp kcode
l4: 
		test al,08h             ;是否是第4行
		jnz next				;不是则继续判断
		mov al,0dh              ;设置第4行第1列对应的键值
kcode:  
		add al,cl				;将第1列的值加上当前列数，确定按键值,al就是从键盘中读出来的键值
		call putbuf				;保存按键值
		push ax
kon: 
		call dis				;显示刷新
		call clear				;清屏
		call ccscan				;扫描按键，判断按键是否弹起
		jnz kon					;未弹起则继续循环等待弹起
		pop ax
next:  
		inc cl					;当前检测的列数递增
		mov al,ch				
		test al,08h				;检测是否扫描到第4列
		jz kerr					;是则跳回到开始处
		rol al,1				;没检测到第4列则准备检测下一列
		mov ch,al				
		jmp colum
kerr:  
		jmp begin

;
;	数码管1		数码管2		数码管3		数码管4		数码管5		数码管6
;	  左<---------------------------------------------------------右
;

putbuf: 
		push ax
		mov di,3006h			;数码管1显示的数字移出数码管（即最左侧的数字移出数码管）
		mov si,3005h;si,di作为两个中间的值用来实现数值的交换
		mov al,[si]
		mov [di],al;数码管1显示之前数码管2显示的数字
		mov di,3005h			
		mov si,3004h
		mov al,[si]
		mov [di],al;数码管2显示之前数码管3显示的数字
		mov di,3004h			
		mov si,3003h
		mov al,[si]
		mov [di],al;数码管3显示之前数码管4显示的数字
		mov di,3003h			
		mov si,3002h
		mov al,[si]
		mov [di],al;数码管4显示之前数码管5显示的数字
		mov di,3002h			
		mov si,3001h
		mov al,[si]
		mov [di],al;数码管5显示之前数码管6显示的数字
		mov di,3001h			
		mov si,3000h
        mov al,[si]
		mov [di],al
        pop ax 	
		mov [si],al				;存键盘值到相应位的缓冲中（数码管6显示新键入的数字）
goback: 
		ret
		
ccscan: 						;扫描是否有按键闭合
		mov al,00h             
		mov dx,my8255_a			;将4列全选通，x1~x4置0
		out dx,al
		mov dx,my8255_c
		in 	al,dx				;读y1~y4
		not al						
		and al,0fh				;取出y1~y4的反值
		ret
	
clear:  						;清屏子程序
		mov dx,my8255_b         ;段位置0即可清除数码管显示
		mov al,00h
		out dx,al
		ret
	
dis: 							;显示键值子程序
		push ax    				;以缓冲区存放的键值为键值表偏移找到键值并显示             
		mov si,3000h			
		mov dl,0dfh				;dfh=11011111b
		mov al,dl
again:  
		push dx
		mov dx,my8255_a
		out dx,al				;设置x1~x6，选通一个数码管
    
		mov al,[si]				;取出缓冲区中存放键值
		mov bx,offset dtable	
		and ax,00ffh
		add bx,ax				
		mov al,[bx]				;将键值作为偏移和键值基地址相加得到相应的共阴极数码管编码
		mov dx,my8255_b
		out dx,al				;写入数码管a~dp
    
		call delay
		inc si					;取下一个键值
		pop dx
		mov al,dl
		test al,01h				;判断是否显示完，因为每次显示之后都是右移，所以判断最后是不是0就知道显示完成没有
		jz out1					;显示完，返回
		ror al,1
		mov dl,al
		jmp again				;未显示完，跳回继续
out1:  
		pop ax				
		ret


delay:  
		push cx                	;延时子程序
		mov cx,0006h
t1: 	
		mov ax,009fh
t2: 
		dec ax
		jnz t2
		loop t1
		pop cx
		ret
		
		
code 	ends
		end start
