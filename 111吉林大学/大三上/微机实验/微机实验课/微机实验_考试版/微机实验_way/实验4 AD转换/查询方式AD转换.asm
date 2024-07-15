CODE 	SEGMENT
		ASSUME CS:CODE
START:
		MOV DX, 0686H  	;8255初始化，同上
		MOV AL, 90H
		OUT DX, AL
 
X3: 
		MOV DX, 0640H  	;启动AD采样
		OUT DX, AL
 
X1: 
		MOV DX,0680H	;ADC0809的EOC引脚连接转换单元 将圆锥孔转接排线 排线连接到8255A口
		IN AL,DX       	;从8255A口读入EOC状态
		TEST AL,80H    	;检测EOC是否为高电平
		JNZ X1         	;如果不是低电平，表示未开始转换，跳转继续查询
 
X2:
		MOV DX,0680H
		IN AL,DX       	;从8255A口读入EOC状态   
		TEST AL,80H    	;检测EOC是否为高电平
		JZ X2          	;如果是高电平，表示装换完成
 
		MOV DX,0640H
		IN AL,DX       	;从ADC0809读入转换完成的数据
		MOV DX, 0682H
		OUT DX,AL      	;从8255B口输出转换完成的数据
		JMP X3         	;循环转换
		;此处对EOC状态的判断详见《微型计算机原理与接口技术》P274图7.4.8
CODE 	ENDS 
		END START