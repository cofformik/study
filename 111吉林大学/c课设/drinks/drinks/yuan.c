#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define MAX_NAME_LENGTH 20
#define MAX_ORIGIN_LENGTH 20
#define MAX_BRAND_LENGTH 20
void save_accounts();//保存到文件
void load_accounts();//读取文件
void register_account();//注册
void login_account();//登录
void logout_account();//注销账户
void change_password();//修改密码
void menu1();//登录菜单
void register_account1();
void recover_password();//找回密码
void menu();//主菜单
void delete();//删除酒水
void hotdrinks();//热销酒水
void discount();//折扣
void individual1();//管理员中心
void individual2();//用户中心
void Add();//添加
void addfile();//将链表写入文件
void scanffile();// 从文件中读取酒水信息到链表中
void T_scanffile();//获取商品折扣价
int check(char a[]);//检查是否重复
struct Node* search(char a[]);//查找商品
void shop_2();//用户购买
void order2();//用户订单
void modify();//修改商品信息
void modifystock(int n);//修改库存
void alldrinks();//查看所有酒水库存
void inventory();//库存菜单
void Searchproduct();//寻找商品
void init();          //初始化
void print();//显示
struct VIP gete();//添加
void add1();//添加新的会员信息 
void findbyno();//根据账号查找会员信息 
void findbyname();//根据姓名查找会员信息 
void findbyIDcard();//根据身份证号查找会员信息 
void findbyphone();//根据手机号查找会员信息 
void mod();////修改已有的会员信息 
void del();//删除已有会员信息 
void sort();//根据会员账号从小到大排序 
void save_vip();//将信息存入文件
void scanf_vip();//把文件中信息读入数组
void customer();//客户信息
struct VIP             //定义结构体，存储会员账号、姓名、身份证号、联系方式、状态
{
	long no;
	char name[20];    //姓名、身份证号含有字符，使用char定义 
	char IDcard[19];
	char phone[12];   //联系电话有11位，超出了int的范围，使用字符串定义 
	int zhuangtai;      //如果状态为1，则正常，若为0，则状态为挂失 
	//int yue;
};
struct VIP s[50];     //定义结构体数组 
int n = 0;              //n表示存入的会员数量 
typedef struct Node {//酒水结构体
	char name[20];

	char category[20];
	char brand[20];//
	float price;
	float sale;
	int quantity;

	struct Node* next;
}node;
node* head = NULL;
node* end = NULL;
typedef struct Order2 {//订单结构体
	char name[20];
	int quantity;
	char brand[20];
	float singleprice;
	float sum;
	struct Order2* next;
}order_2;
order_2* head_1 = NULL;
typedef struct// 定义一个结构体，用于存储账户信息
{
	char username[20];
	char password[20];
	char id_code[20];
} Account;
int identity = 0;
Account accounts[100];// 定义一个全局变量，用于存储所有注册的账户
int num_accounts = 0;
void create_File2()
{
	FILE* fp;
	if ((fp = fopen("accounts.txt", "rb")) == NULL)                 /*如果此文件不存在*/
	{
		if ((fp = fopen("accounts.txt", "wb+")) == NULL)
		{
			printf("无法建立文件！\n");
			exit(0);

		}
	}
}
void save_accounts()// 将账户信息保存到文件中

{

	FILE* fp;
	fp = fopen("accounts.txt", "w"); // 打开文件，文件名为"accounts.txt"
	if (fp == NULL)
	{
		printf("Error: cannot open file.\n");
		return;
	}
	for (int i = 0; i < num_accounts; i++)
	{
		fprintf(fp, "%s,%s,%s\n", accounts[i].username, accounts[i].password, accounts->id_code); // 将账户信息写入文件中
	}
	fclose(fp); // 关闭文件
	printf("即将返回主菜单......");
	Sleep(3000);
	menu();
}
void load_accounts()// 从文件中读取账户信息
{
	create_File2();
	FILE* fp = fopen("accounts.txt", "r"); // 打开文件，文件名为"accounts.txt"
	if (fp == NULL)
	{
		printf("Error: cannot open file.\n");
		return;
	}
	char line[100];
	while (fgets(line, 100, fp) != NULL)   // 逐行读取文件内容
	{
		char* username = strtok(line, ","); // 使用逗号分隔用户名和密码
		char* password = strtok(NULL, ",");
		char* id_code = strtok(NULL, "\n");
		strcpy(accounts[num_accounts].username, username); // 将用户名和密码保存到账户结构体中
		strcpy(accounts[num_accounts].password, password);
		strcpy(accounts[num_accounts].id_code, id_code);
		num_accounts++;
	}
	fclose(fp); // 关闭文件
}
void register_account()// 注册新账户
{
	FILE* fp = fopen("accounts.txt", "r");
	char ch;
	ch = fgetc(fp);
	if (ch == -1 || ch == EOF)//判断是否有已注册用户
	{
		char username[20];
		char password[20];
		char id_code[20];
		printf("请输入用户名： ");
		scanf("%s", username);
		printf("请输入密码：");
		scanf("%s", password);
		printf("请输入身份证后六位:");
		scanf("%s", id_code);
		// 检查用户名是否已存在
		for (int i = 0; i < num_accounts; i++)
		{
			if (strcmp(accounts[i].username, username) == 0)
			{
				printf("Error: username already exists.\n");
				return;
			}
		}
		// 将新账户保存到账户结构体中
		strcpy(accounts[num_accounts].username, username);
		strcpy(accounts[num_accounts].password, password);
		strcpy(accounts[num_accounts].id_code, id_code);
		num_accounts++;
		printf("注册成功！\n");
		save_accounts(); // 将账户信息保存到文件中
	}
	else
	{
		printf("已存在注册用户，请联系管理员注册");
	}
}
void register_account1()// 注册新账户
{
	char username[20];
	char password[20];
	char id_code[20];
	printf("请输入用户名：");
	scanf("%s", username);
	printf("请输入密码：");
	scanf("%s", password);
	printf("请输入身份证后六位:");
	scanf("%s", id_code);
	// 检查用户名是否已存在
	for (int i = 0; i < num_accounts; i++)
	{
		if (strcmp(accounts[i].username, username) == 0)
		{
			printf("注册失败！该账户已经注册，正在返回个人中心......\n");
			Sleep(2000);
			individual1();
		}
	}
	// 将新账户保存到账户结构体中
	strcpy(accounts[num_accounts].username, username);
	strcpy(accounts[num_accounts].password, password);
	strcpy(accounts[num_accounts].id_code, id_code);

	num_accounts++;
	printf("注册成功！\n");
	save_accounts(); // 将账户信息保存到文件中
}
void login_account()//登录账户
{
	int found = 0;
	char username[20];
	char password[20];
	printf("请输入账号：");
	scanf("%s", username);
	printf("请输入密码：");
	scanf("%s", password);
	for (int i = 0; i < num_accounts; i++)
	{
		if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, password) == 0)
		{
			found = 1;
			printf("登陆成功！正在进入主菜单......");
			Sleep(1000);
			if (strcmp("mayf", username) == 0 && strcmp("123456", password) == 0)
				identity = 1;
			menu();
		}
	}
	if (!found)
	{
		printf("密码错误或用户未注册！");
	}
}
void logout_account()// 注销账户
{
	char username[20];
	char id_code[20];
	printf("Enter your username: ");
	scanf("%s", username);
	printf("请输入身份证后六位");
	scanf("%s", id_code);
	int found = 0;
	// 查找账户并删除
	for (int i = 0; i < num_accounts; i++)
	{
		if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].id_code, id_code) == 0)
		{
			found = 1;
			for (int j = i; j < num_accounts - 1; j++)
			{
				accounts[j] = accounts[j + 1];
			}
			num_accounts--;
			break;
		}
	}
	if (found)
	{
		printf("Account deleted successfully.\n");
		save_accounts(); // 将账户信息保存到文件中
		menu1();
	}
	else
	{
		printf("Error: account not found.\n");
	}
}
void change_password()//修改密码
{
	char username[20];
	char old_password[20];
	char new_password[20];
	printf("Enter your username: ");
	scanf("%s", username);
	printf("Enter your old password: ");
	scanf("%s", old_password);
	int found = 0;
	for (int i = 0; i < num_accounts; i++)
	{
		if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, old_password) == 0)
		{
			found = 1;
			printf("Enter your new password: ");
			scanf("%s", new_password);
			strcpy(accounts[i].password, new_password);
			printf("Password changed successfully.\n");
			save_accounts(); // 将账户信息保存到文件中
			menu1();
			break;
		}
	}
	if (!found)
	{
		printf("Error: account not found or old password is incorrect.\n");
		if (identity == 1)individual1();
		else individual2();

	}
}
void menu1()//登录菜单
{
	load_accounts(); // 从文件中读取账户信息
	int choice;
	int t = 1;

	printf("1. 登录账户\n");
	printf("2. 管理员注册\n");
	printf("3. 忘记密码\n");
	printf("0. 退出\n");
	printf("请选择（0-3） ： ");
	int k = 0; // 记录输入的字符数

	while (t) {


	flag:if (k = scanf("%d", &choice) != 1 || k > 1) {
		printf("Invalid input. Please enter your choice again.\n");
		while (getchar() != '\n')
			continue;// 清空输入缓冲区
		goto flag;

	}

	switch (choice) {
	case 1:
		t = 0;
		login_account();
		break;
	case 2:
		t = 0;
		register_account();
		break;
	case 3:
		t = 0;
		recover_password();
		break;
	case 0:
		t = 0;
		break;
	default:
		printf("选择非法，请重新输入！\n");
		break;
	}
	}
}

void recover_password()//找回密码
{
	int found = 0;
	char username[20];
	char id_code[20];
	printf("请输入账号:");
	scanf("%s", username);
	printf("请输入身份证后六位:");
	scanf("%s", id_code);
	for (int i = 0; i < num_accounts; i++)
	{
		if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].id_code, id_code) == 0)
		{
			char newpassword[20];
			printf("请输入新密码\n");
			scanf("%s", newpassword);
			found = 1;
			strcpy(accounts[i].password, newpassword);
			printf("修改成功\n");
			save_accounts();
			menu1();
		}
	}
	if (!found)
	{
		printf("身份证错误或用户未注册！");
	}
}

void menu() {//菜单
	system("cls");
	int choice, t = 1;

	printf("欢迎来到吉林大学酒馆\n");
	printf("\t\t\t\t1.热门酒水\n\n\t\t\t\t2.折扣酒水\n\n\t\t\t\t3.个人中心\n\n");
	if (identity == 1) printf("\t\t\t\t4.添加酒水\n\n\t\t\t\t5.会员管理\n\n\t\t\t\t6.退出\n\n");
	else printf("\t\t\t\t4.退出\n\n");
	scanf("%d", &choice);
	if (identity) {
		while (t) {
			switch (choice) {

			case 1:hotdrinks(); t = 0; break;

			case 2:discount(); t = 0; break;


			case 3:individual1();
				t = 0;
				break;

			case 4:Add(); t = 0; break;
			case 5:customer(); t = 0; break;
			case 6:return; break;
			default:printf("选择非法，请重新选择");
				scanf("%d", &choice);

			}
		}
	}
	else {
		while (t) {
			switch (choice) {

			case 1:hotdrinks(); t = 0; break;

			case 2:discount(); t = 0; break;


			case 3:individual2();
				t = 0;
				break;
			case 4: return; break;
			default:printf("选择非法，请重新选择");
				scanf("%d", &choice);

			}
		}
	}
}

void hotdrinks() {

	system("cls");
	printf("欢迎来到热销酒水界面\n\n");
	printf("\t\t品牌\t\t\t\t酒水\t\t\t\t价格\n");

	T_scanffile();
	node* p = head;

	while (p) {
		printf("\t\t%s\t\t\t\t%s\t\t\t\t%.2f\n", p->brand, p->name, p->price);
		p = p->next;
	}
	printf("输入'1'返回主菜单！");
	int choice;
	scanf("%d", &choice);
	if (choice == 1) {
		printf("正在返回菜单......");
		Sleep(3000);
		menu();
	}
}
void alldrinks() {

	system("cls");
	printf("欢迎来到酒水界面\n\n");
	printf("\t\t品牌\t\t\t\t酒水\t\t\t\t价格\t\t\t\t库存\n");

	T_scanffile();
	node* p = head;

	while (p) {
		printf("\t\t%s\t\t\t\t%s\t\t\t\t%.2f\t\t\t\t%d\n", p->brand, p->name, p->price, p->quantity);
		p = p->next;
	}
	printf("输入'1'返回主菜单！");
	int choice;
	scanf("%d", &choice);
	if (choice == 1) {
		printf("正在返回菜单......");
		Sleep(3000);
		inventory();
	}
}

void discount() {//折扣
	system("cls");
	printf("\t\t欢迎来到折扣酒水界面\n\n");
	printf("当前时间为：");
	char* wday[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
	time_t timep;
	struct tm* q;

	time(&timep);
	q = localtime(&timep); //取得当地时间
	printf("%d/%d/%d ", (q->tm_year + 1900), (q->tm_mon + 1), q->tm_mday);
	printf("%s %d:%d\n", wday[q->tm_wday], q->tm_hour, q->tm_min);

	printf("\t\t本店折扣规则\n\n\t\t1.周一到周五每种酒水各打九折出售一次！\n\n\t\t2.周末全酒水九折出售！\n\n");
	printf("\t\t3.周末所有酒水九折出售！！！！");
	T_scanffile();

	node* p = head;
	printf("\n\n\t\t品牌\t\t\t\t酒水\t\t\t\t原价\t\t\t\t折扣价\n\n");
	if (strcmp(wday[q->tm_wday], "Mon") == 0) {
		while (p) {
			if (strcmp(p->category, "啤酒") == 0) {

				printf("\t\t%s\t\t\t\t%s\t\t\t\t%.2f\t\t\t\t%.2f\n\n", p->brand, p->name, p->price, p->sale);

			}
			p = p->next;
		}
	}
	else if (strcmp(wday[q->tm_wday], "Tue") == 0) {
		while (p) {
			if (strcmp(p->category, "白酒") == 0) {

				printf("\t\t%s\t\t\t\t%s\t\t\t\t%.2f\t\t\t\t%.2f\n\n", p->brand, p->name, p->price, p->sale);

			}
			p = p->next;
		}
	}
	else if (strcmp(wday[q->tm_wday], "Wed") == 0) {
		while (p) {
			if (strcmp(p->category, "矿泉水") == 0) {

				printf("\t\t%s\t\t\t\t%s\t\t\t\t%.2f\t\t\t\t%.2f\n\n", p->brand, p->name, p->price, p->sale);

			}
			p = p->next;
		}
	}
	else if (strcmp(wday[q->tm_wday], "Thu") == 0) {
		while (p) {
			if (strcmp(p->category, "果汁") == 0) {
				printf("\t\t%s\t\t\t\t%s\t\t\t\t%.2f\t\t\t\t%.2f\n\n", p->brand, p->name, p->price, p->sale);

			}
			p = p->next;
		}
	}
	else if (strcmp(wday[q->tm_wday], "Fri") == 0) {
		while (p) {
			if (strcmp(p->category, "饮料") == 0) {

				printf("\t\t%s\t\t\t\t%s\t\t\t\t%.2f\t\t\t\t%.2f\n\n", p->brand, p->name, p->price, p->sale);

			}
			p = p->next;
		}
	}
	else {
		while (p) {
			printf("\t\t%s\t\t\t\t%s\t\t\t\t%.2f\t\t\t\t%.2f\n\n", p->brand, p->name, p->price, p->sale);

			p = p->next;
		}
	}
	printf("按下Y键返回菜单\n");
	getchar();
	char choice;
	scanf("%c", &choice);
	if (choice == 'y' || choice == 'Y') {
		printf("即将返回主菜单......");
		Sleep(3000);
		menu();
	}
}

void individual2() {

	printf("1.修改密码\n");
	printf("2.注销账户\n");
	printf("3.个人订单\n");
	printf("4.购买商品\n");
	printf("0.返回主菜单\n");
	printf("请输入你的选择:");
	int choice;
	scanf("%d", &choice);
	switch (choice)
	{

	case 1:
		change_password();
		break;
	case 2:
		logout_account();
		break;
	case 3:
		order2();
		break;
	case 4:
		shop_2();
		break;
	case 0:
		menu();
		break;
	default:
		printf("输入有误，请重新输入！\n");
		break;
	}
	while (choice != 0);
}
void order2() {//将订单文件读入链表
	system("cls");
	printf("查看个人订单\n\n");
	FILE* fp;
	fp = fopen("order2", "r");

	if (fp == NULL)
	{
		printf("文件不存在！\n");
		return;
	}
	int i = 0;
	order_2* p = NULL;

	while (!feof(fp))
	{


		order_2* q = (order_2*)malloc(sizeof(order_2));
		fscanf(fp, "%s %s %d %f %f", q->brand, q->name, &q->quantity, &q->singleprice, &q->sum);
		if (feof(fp)) break;

		if (0 == i) {
			head_1 = p = q;
			i++;
		}

		p->next = q;
		p = p->next;
		p->next = NULL;
	}
	p = head_1;
	int j = 1;
	printf("\t\tid\t\t酒水\t\t数量\t\t单价\t\t总价\n\n");
	while (p) {
		printf("\t\t%d\t\t%s\t\t%d\t\t%.2f\t\t%.2f\n\n", j, p->name, p->quantity, p->singleprice, (p->singleprice) * (p->quantity));
		j++;
		p = p->next;
	}
	fclose(fp);
	printf("\n\n按下'1'返回菜单！");
	int k, choice;
flag:if (k = scanf("%d", &choice) != 1 || k > 1) {
	printf("输入错误，请重新输入：\n");
	while (getchar() != '\n')
		continue;// 清空输入缓冲区
	goto flag;

}
printf("正在返回主菜单：");
Sleep(3000);
menu();
}
struct Node* search(char a[]) {//查询商品
	T_scanffile();
	node* p = head;
	while (p) {
		if (strcmp(p->name, a) == 0)
			return p;
		p = p->next;
	}

	return NULL;

}
void shop_2() {//购买商品
	system("cls");
	printf("\t\t欢迎来到购物界面！\n");
	FILE* fp;
	fp = fopen("order2", "a");
	char brr;
	if (fp == NULL)
	{
		printf("文件不存在！\n");
		return;
	}
	printf("请输入想要购买的商品：\t");
	char goods[20];
	scanf("%s", goods);
	brr = getchar();
	node* p = search(goods);
	while (!p) {
		printf("未找到该商品，请重新输入");
		scanf("%s", goods);
		brr = getchar();
	}
	printf("品牌：%s\n名称：%s\n单价：%.2f\n折扣价：%.2f\n", p->brand, p->name, p->price, p->sale);
	printf("请输入购买数量：\t");
	int i;
	scanf("%d", &i);
	printf("购买%s的总价是%.2f,是否确定购买？(1/0)", p->name, i * p->sale);
	int choice;
	scanf("%d", &choice);
	if (choice) {
		fprintf(fp, "%s %s %d %.2f %.2f\n", p->brand, p->name, i, p->sale, i * (p->sale));
		if (p->quantity < i) {

			printf("很抱歉购买失败，该商品暂时库存不足，我们已经通知管理员进货了，感谢您的理解！\n");
		}
		else {
			printf("购买成功！\n");
			p->quantity -= i;
		}
		addfile();
		fclose(fp);
		printf("\n\n按下'1'返回菜单！");
		int ch;
		scanf("%d", &ch);
		if (ch == 1)
		{
			printf("正在返回菜单.......");

			Sleep(3000);
			menu();
		}
	}
	else {
		printf("是否选择重新购买（1/0)?\n1.重新购买\n0.返回主菜单\n");
		int num;
		scanf("%d", &num);
		if (num) {
			fclose(fp);
			shop_2();
		}
		else {
			printf("正在返回菜单.......");
			fclose(fp);
			Sleep(3000);
			menu();
		}
	}
}
void individual1()//管理员个人中心
{
	system("cls");
	printf("\t\t\t\t1.注册新用户\n");
	printf("\t\t\t\t2.修改密码\n");
	printf("\t\t\t\t3.注销账户\n");
	printf("\t\t\t\t4.库存管理\n");
	printf("\t\t\t\t0.返回主菜单\n");
	printf("请输入你的选择:");
	int choice;
	scanf("%d", &choice);
	switch (choice)
	{
	case 1:
		register_account1();
		break;
	case 2:
		change_password();
		break;
	case 3:
		logout_account();
		break;
	case 4:
		inventory();
		break;

	case 0:
		menu();
		break;
	default:
		printf("输入有误，请重新输入！\n");
		break;
	}

}



void init()   //初始化（唯一的6位会员账号）
{
	int f = 1; //1唯一   0不唯一 
	printf("请输入会员的账号,姓名,身份证号码,联系电话,状态\n");
	printf("当输入会员号为0时停止输入\n");
	while (n <= 50)
	{
		printf("请输入会员的账号:\n");
		scanf("%ld", &s[n].no);
		while (s[n].no != 0)
		{
			if (s[n].no / 1000000 == 0 && s[n].no / 100000 != 0)
			{
				int i;
				for (i = 0; i < n && f == 1; i++)
				{
					if (s[n].no == s[i].no)
					{
						f = 0;
						printf("请输入唯一的6位会员账号\n");
					}

				}
				if (f == 1)
					break;
			}
			else
			{
				printf("请输入6位会员账号\n");
				printf("请重新输入会员的账号:\n");
				scanf("%d", &s[n].no);
			}
		}
		if (s[n].no == 0)
			break;         //如果输入的账号为0，结束输入
		printf("请输入会员的姓名:\n");
		scanf("%s", s[n].name);
		printf("请输入会员的身份证号，联系电话，状态:\n");
		scanf("%s%s%d", s[n].IDcard, s[n].phone, &s[n].zhuangtai);
		n++;
	}
	save_vip();
}

void print()  //输出 
{

	int j;
	printf("会员信息记录如下:\n");
	printf("     |===============================================================================|\n");
	printf("     |账号\t姓名\t身份证号\t联系电话\t   状态          \n");
	printf("     |-------------------------------------------------------------------------------|\n");
	for (j = 0; j < n; j++)
	{
		printf("     |%ld\t%s\t%s\t\t%s\t", s[j].no, s[j].name, s[j].IDcard, s[j].phone);
		if (s[j].zhuangtai == 1)
			printf("  正常           \n");
		else
			printf("  挂失           \n");
		if (j < (n - 1))
			printf("     |-------------------------------------------------------------------------------|\n");
	}
	printf("     |===================================================================================|\n");
}

struct VIP gete()       //输入 
{
	struct VIP e;
	printf("请输入账号:\n");
	scanf("%d", &e.no);
	int f = 1;
	while (e.no)
	{
		if (e.no / 1000000 == 0 && e.no / 100000 != 0)
		{
			int i;
			for (i = 0; i < n && f == 1; i++)
			{
				if (e.no == s[i].no)
				{
					f = 0;
					printf("请输入唯一的6位会员账号\n");
					scanf("%d", &e.no);
				}
			}
			if (f == 1)
				break;
		}
		else
		{
			printf("请输入6位会员账号\n");
			printf("请重新输入会员的账号:\n");
			scanf("%d", &e.no);
		}
	}
	printf("请输入姓名:\n");
	scanf("%s", &e.name);
	printf("请输入会员的身份证号，联系电话，状态:\n");
	scanf("%s%s%d", &e.IDcard, &e.phone, &e.zhuangtai);
	save_vip();
	return e;

}

void add1()   //添加新的会员信息 
{
	struct VIP e = gete();
	int i;
	printf("请输入要插入的位置（1-%d）：\n", n);
	scanf("%d", &i);
	while (i<1 || i>n + 1)
	{
		printf("您输入的位置有误！\n");
		printf("请重新输入要插入的位置（1-%d）：\n", n);
		scanf("%d", &i);
	}
	for (int j = n - 1; j >= i - 1; j--)
	{
		s[j + 1] = s[j];
	}
	s[i - 1] = e;
	n++;
	save_vip();
}

void findbyno()     //根据会员账号查找会员信息 
{
	int num, i;
	int found = 1;
	char choice;
	while (1)
	{
		printf("请输入要查找的会员的账号：\n");
		scanf("%d", &num);
		getchar();
		for (i = 0; i < n && found == 1; i++)
		{

			if (s[i].no == num)
			{
				found = 0;
				printf("%ld\t%s\t%d\t%d\t", s[i].no, s[i].name, s[i].IDcard, s[i].phone);
				if (s[i].zhuangtai == 1)
					printf("正常\n");
				else
					printf("挂失!\n");
			}
		}
		if (found == 1)
		{
			printf("未找到!\n");
		}
		found = 1;
		printf("是否继续查询(Y/N)\n");
		choice = getchar();
		if (choice == 'N' || choice == 'n')
			break;
	}
}

void findbyname()    //根据会员姓名查找会员信息 
{
	char name[20];
	char choice;
	int found = 1;
	int i;
	while (1)
	{
		printf("输入要查询会员的姓名：\n");
		scanf("%s", name);
		getchar();
		for (i = 0; i < n && found == 1; i++)
		{
			if (strcmp(s[i].name, name) == 0)
			{
				found = 0;
				printf("%ld\t%s\t%d\t%d\t", s[i].no, s[i].name, s[i].IDcard, s[i].phone);
				if (s[i].zhuangtai == 1)
					printf("正常\n");
				else
					printf("挂失!\n");
			}
		}
		if (found == 1)
		{
			printf("未找到!\n");
		}
		found = 1;
		printf("是否继续查询(Y/N)\n");
		choice = getchar();
		if (choice == 'N' || choice == 'n')
			break;
	}
}

void findbyIDcard()   //根据身份证号查找会员信息 
{
	char num[19];
	int i;
	int found = 1;
	char choice;
	while (1)
	{
		printf("请输入要查找的会员的身份证号：\n");
		scanf("%s", num);
		getchar();
		for (i = 0; i < n && found == 1; i++)
		{
			if (strcmp(s[i].IDcard, num) == 0)
			{
				found = 0;
				printf("%ld\t%s\t%d\t%d\t", s[i].no, s[i].name, s[i].IDcard, s[i].phone);
				if (s[i].zhuangtai == 1)
					printf("正常\n");
				else
					printf("挂失!\n");
			}
		}
		if (found == 1)
		{
			printf("未找到!\n");
		}
		found = 1;
		printf("是否继续查询(Y/N)\n");
		choice = getchar();
		if (choice == 'N' || choice == 'n')
			break;
	}
}

void findbyphone()    //根据联系电话查找会员信息 
{
	char num[12];
	int i;
	int found = 1;
	char choice;
	while (1)
	{
		printf("请输入要查找的会员的联系电话：\n");
		scanf("%s", num);
		getchar();
		for (i = 0; i < n && found == 1; i++)
		{
			if (strcmp(s[i].phone, num) == 0)
			{
				found = 0;
				printf("%ld\t%s\t%d\t%d\t", s[i].no, s[i].name, s[i].IDcard, s[i].phone);
				if (s[i].zhuangtai == 1)
					printf("正常\n");
				else
					printf("挂失!\n");
			}
		}
		if (found == 1)
		{
			printf("未找到!\n");
		}
		found = 1;
		printf("是否继续查询(Y/N)\n");
		choice = getchar();
		if (choice == 'N' || choice == 'n')
			break;
	}
}

void mod()     //修改已有的会员信息 
{
	int num, i;
	int found = 1;
	char choice;
	int opt;
	while (1)
	{
		printf("请输入要修改的会员的账号(会员号无法修改)：\n");
		scanf("%d", &num);
		getchar();
		for (i = 0; i < n && found == 1; i++)
		{
			if (s[i].no == num)
			{
				found = 0;
				printf("%ld\t%s\t%d\t%d\t", s[i].no, s[i].name, s[i].IDcard, s[i].phone);
				if (s[i].zhuangtai == 1)
					printf("正常\n");
				else
					printf("挂失\n");
				printf("--请选择--1.修改身份证号 2.修改联系电话 3.修改状态\n");
				scanf("%d", &opt);
				getchar();
				switch (opt)
				{
				case 1:
					printf("请输入身份证号新值:\n");
					scanf("%s", s[i].IDcard);
					getchar();
					break;
				case 2:
					printf("请输入联系电话新值:\n");
					scanf("%s", s[i].phone);
					getchar();
					break;
				case 3:
					printf("请输入状态新值:\n");
					scanf("%d", &s[i].zhuangtai);
					getchar();
					break;
				}
			}
		}
		if (found == 1)
		{
			printf("未找到!\n");
		}
		found = 1;
		printf("是否继续修改(Y or N)\n");
		choice = getchar();
		getchar();
		if (choice == 'N' || choice == 'n')
			break;
	}
	save_vip();
}

void del()     //删除已有会员信息 
{
	int num, i, j;
	int found = 1;
	char choice;
	while (1)
	{
		printf("请输入要删除的会员的账号：\n");
		scanf("%d", &num);
		getchar();
		for (i = 0; i < n && found == 1; i++)   //5  1-5      
		{
			if (s[i].no == num)
			{
				found = 0;
				printf("你要删除的会员信息为:\n");
				printf("会员账号     姓名      身份证号      联系电话       状态\n");
				printf("%ld\t%s\t%d\t%d\t", s[i].no, s[i].name, s[i].IDcard, s[i].phone);
				if (s[i].zhuangtai == 1)
					printf("正常\n");
				else
					printf("挂失!\n");
				for (j = i; j < n - 1; j++)
				{
					s[j] = s[j + 1];
				}
				n--;
			}
		}
		if (found == 1)
		{
			printf("未找到!\n");
		}
		found = 1;
		printf("是否继续（Y/N）\n");
		choice = getchar();
		getchar();
		if (choice == 'N' || choice == 'n')
			break;
	}
	save_vip();
}

void sort()     //根据会员账号从小到大排序 
{
	int i, j;
	struct VIP temp;
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			if (s[i].no > s[j].no)
			{
				temp = s[i];
				s[i] = s[j];
				s[j] = temp;
			}
		}
	}
	printf("\n排序后的会员信息:\n");
	save_vip();
}
void save_vip() {//将信息存入文件
	FILE* fp = NULL;
	fp = fopen("vip", "w");
	for (int i = 0; i < n; i++) {
		fprintf(fp, "%ld %s %s %s %d\n", s[i].no, s[i].name, s[i].IDcard, s[i].phone, s[i].zhuangtai);
	}
	fclose(fp);
}
void scanf_vip() {//从文件中读取VIP客户信息
	FILE* fp = NULL;
	fp = fopen("vip", "w");
	fclose(fp);
	fp = fopen("vip", "r");
	for (int i = 0; !feof(fp); i++)
	{
		if (feof(fp)) break;
		fscanf(fp, "%ld %s %s %s %d", &s[i].no, s[i].name, s[i].IDcard, s[i].phone, &s[i].zhuangtai);
		n++;
	}
	fclose(fp);

}
void  customer()
{
	scanf_vip();
	int opt;
	printf("     |*============================================*|\n");
	printf("     |*             欢迎使用会员管理系统           *|\n");
	printf("     |*============================================*|\n");
	printf("     |*    1.初始化                                *|\n");
	printf("     |*    2.添加新的会员记录                      *|\n");
	printf("     |*    3.修改已有会员记录/挂失                 *|\n");
	printf("     |*    4.根据账号查询已有会员记录              *|\n");
	printf("     |*    5.根据姓名查询已有会员记录              *|\n");
	printf("     |*    6.根据身份证号查询已有会员记录          *|\n");
	printf("     |*    7.根据联系电话查询已有会员记录          *|\n");
	printf("     |*    8.删除已有会员记录                      *|\n");
	printf("     |*    9.根据会员账号排序并显示                *|\n");
	printf("     |*    0.退出会员信息管理系统                  *|\n");
	printf("     |*============================================*|\n");
	while (1)
	{
		printf("请输入要完成的功能：0-10:");
		scanf("%d", &opt);
		getchar();    //吸收回车 
		switch (opt)
		{
		case 1:init(); print(); break;          //初始化 
		case 2:add1(); print(); break;          //添加 
		case 3:mod(); print(); break;           //修改 
		case 4:findbyno(); print(); break;      //根据账号查询 
		case 5:findbyname(); print(); break;    //根据姓名查询 
		case 6:findbyIDcard(); print(); break;  //根据身份证号查询 
		case 7:findbyphone(); print(); break;   //根据联系电话查询 
		case 8:del(); print(); break;           //删除 
		case 9:sort(); print(); break;          //排序 
		case 0:system("cls"); exit(0); break;   //退出 
		default:printf("请输入0-10中的数!\n"); break;
		}
	}
}
void inventory()
{

	system("cls");
	printf("\n\n\n\n\n");
	printf("\t\t|---------------------PRODUCT-------------------|\n");
	printf("\t\t|   1. 商品入库                                 |\n");
	printf("\t\t|   2. 商品出库                                 |\n");
	printf("\t\t|   3. 删除商品                                 |\n");
	printf("\t\t|   4. 修改商品                                 |\n");
	printf("\t\t|   5. 搜索商品                                 |\n");
	printf("\t\t|   6. 显示商品                                 |\n");
	printf("\t\t|   0. 退出                                     |\n");
	printf("\t\t|-----------------------------------------------|\n\n");
	printf("\t\t\t选择(0-6):");
	int iItem;
	scanf("%d", &iItem);          /*输入菜单项*/
	while (iItem)
	{
		switch (iItem)
		{

		case 1:modifystock(1); break;
		case 2:modifystock(2); break;
		case 3:delete(); break;
		case 4:modify(); break;
		case 5:Searchproduct(); break;
		case 6:alldrinks(); break;
		default:printf("请输入正确数字");
		}
		getch();
		inventory();
		scanf("%d", &iItem);
	}
	if (iItem == 0) {
		menu();
	}
}
void Searchproduct() {

	printf("请输入您要查询的商品：");
	char name[20];
	gets(name);
	node* p = search(name);
	if (p != NULL)
	{
		printf("\t\t品牌\t\t\t\t酒水\t\t\t\t价格\t\t\t\t库存\n");
		printf("\t\t%s\t\t\t\t%s\t\t\t\t%.2f\t\t\t\t%d\n", p->brand, p->name, p->price, p->quantity);
	}
	else
		printf("该商品不存在！");
	printf("输入‘1’来返回库存菜单");
	int choice;
	scanf("%d", &choice);
	if (choice == 1) {
		printf("正在返回库存菜单......");
		Sleep(3000);
		inventory();
	}


}
int check(char a[]) {
	T_scanffile();
	node* p = head;
	while (p) {
		if (strcmp(p->name, a) == 0)
			return 1;
		p = p->next;
	}
	return 0;
}



void Add() {//添加
	node* p;
	int choice;
	p = (node*)malloc(sizeof(node));
	printf("请输入酒水名称：");
	scanf("%s", &p->name);
	if (check(p->name) == 1) {
		printf("商品已存在,请重新输入！\n");
		Add();
	}
	printf("请输入品牌：");
	scanf("%s", &p->brand);
	printf("请输入酒水种类：");
	scanf("%s", &p->category);
	printf("请输入酒水价格：");
	scanf("%f", &(p->price));
	printf("请输入酒水库存量：");
	scanf("%d", &(p->quantity));
	if (head == NULL) {
		head = end = p;
		end->next = NULL;
	}
	else {
		end->next = p;
		end = p;
		end->next = NULL;
	}
	addfile();
	printf("是否继续添加（1/0）?");
	scanf("%d", &choice);
	if (choice == 1) {
		Add();
	}
	else {

		printf("正在返回菜单......");
		Sleep(3000);
		menu();
	}
}

void addfile() {//将链表写入文件
	node* p = head;
	FILE* fp;
	fp = fopen("drinks", "w");
	while (p) {
		fprintf(fp, "%s %s %s %.2f %d\n", p->brand, p->name, p->category, p->price, p->quantity);

		p = p->next;
	}
	printf("保存到文件成功!\n");

	fclose(fp);//关闭文件

}


void delete() //删除酒水
{


	T_scanffile();

	if (head == NULL) {
		printf("链表为空！\n");
		return;
	}
	printf("请输入要删除的酒水名称：");
	char name[55];
	scanf("%s", name);
	if (strcmp(head->name, name) == 0) {
		node* temp = head;
		head = head->next;
		free(temp);
		printf("删除成功！\n");
		Sleep(3000);
		addfile();
		inventory();
		return;
	}

	node* current = head;
	while (current->next != NULL) {
		if (strcmp(current->next->name, name) == 0) {
			node* temp = current->next;
			current->next = current->next->next;
			free(temp);
			printf("删除成功！34\n");
			Sleep(3000);
			addfile();
			menu();
			return;
		}
		current = current->next;
	}

	printf("未找到该酒水信息！\n");

}
void modify() //修改酒水信息
{
	T_scanffile();

	if (head == NULL) {
		printf("链表为空！\n");
		return;
	}
	char name[50];
	printf("请输入要修改的酒水名称：");
	scanf("%s", name);

	node* current = head;
	node* prev = NULL;
	while (current != NULL) {
		if (strcmp(current->name, name) == 0)
		{
			printf("原酒水信息为：\n");
			printf("品牌：%s\n", current->brand);
			printf("酒名：%s\n", current->name);
			printf("种类：%s\n", current->category);
			printf("价格：%.2f\n", current->price);
			printf("库存：%d\n", current->quantity);


			printf("请输入修改后的信息：\n\n");
			char newName[50], newCategory[50];
			float newPrice;
			int newStock;
			int  newIsDiscounted;
			char newBrand[20];
			printf("品牌：");
			scanf("%s", newBrand);
			strcpy(current->brand, newBrand);
			printf("名称：");
			scanf("%s", newName);
			strcpy(current->name, newName);
			printf("种类：");
			scanf("%s", newCategory);
			strcpy(current->category, newCategory);
			printf("价格：");
			scanf("%f", &newPrice);
			current->price = newPrice;
			printf("库存：");
			scanf("%d", &newStock);
			current->quantity = newStock;



			addfile();

			printf("正在返回库存菜单......");
			Sleep(3000);
			inventory();
		}
		prev = current;
		current = current->next;
	}
	printf("未找到该酒水信息！\n");
}
void modifystock(int n)//修改库存
{
	T_scanffile();

	if (head == NULL) {
		printf("链表为空！\n");
		return;
	}
	char name[50];
	if (n == 1)printf("请输入要进货的酒水名称：");
	else if (n == 2)printf("请输入要出货的酒水名称：");
	scanf("%s", name);


	node* current = head;
	node* prev = NULL;
	while (current != NULL) {
		if (strcmp(current->name, name) == 0)
		{
			printf("原酒水信息为：\n");
			printf("品牌：%s\n", current->brand);
			printf("酒名：%s\n", current->name);
			printf("种类：%s\n", current->category);
			printf("价格：%.2f\n", current->price);
			printf("库存：%d\n", current->quantity);

			int number;
			printf("请输入数量：");
			scanf("%d", &number);

			if (n == 1)
			{
				current->quantity += number;
			}
			else
			{
				current->quantity -= number;
			}
			addfile();

			printf("正在返回库存菜单......");
			Sleep(3000);
			inventory();
		}
		prev = current;
		current = current->next;
	}
	printf("未找到该酒水信息！\n");
}



void scanffile()// 从文件中读取酒水信息到链表中
{
	int i = 0;
	FILE* fp = fopen("drinks", "r");
	if (fp == NULL)
	{
		printf("文件不存在！\n");
		return;
	}
	node* p = head;

	while (!feof(fp))
	{
		node* q = (node*)malloc(sizeof(node));
		fscanf(fp, "%s%s%s%f%d", q->brand, q->name, q->category, &q->price, &q->quantity);
		q->sale = q->price;
		if (feof(fp)) break;
		if (0 == i) {
			head = p = q;
			i++;
		}
		//q->next = NULL;
		p->next = q;
		p = p->next;
		p->next = NULL;
	}
	end = p;

	fclose(fp);
}
void T_scanffile() {//获取商品折扣价
	char* wday[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

	time_t timep;
	struct tm* q;

	time(&timep);
	q = localtime(&timep);
	scanffile();
	node* p = head;
	if (strcmp(wday[q->tm_wday], "Mon") == 0) {
		while (p) {
			if (strcmp(p->category, "啤酒") == 0) {
				p->sale *= 0.9;
			}
			p = p->next;
		}
	}
	else if (strcmp(wday[q->tm_wday], "Tue") == 0) {
		while (p) {
			if (strcmp(p->category, "白酒") == 0) {
				p->sale *= 0.9;

			}
			p = p->next;
		}
	}
	else if (strcmp(wday[q->tm_wday], "Wed") == 0) {
		while (p) {
			if (strcmp(p->category, "矿泉水") == 0) {
				p->sale *= 0.9;

			}
			p = p->next;
		}
	}
	else if (strcmp(wday[q->tm_wday], "Thu") == 0) {
		while (p) {
			if (strcmp(p->category, "果汁") == 0) {
				p->sale *= 0.9;

			}
			p = p->next;
		}
	}
	else if (strcmp(wday[q->tm_wday], "Fri") == 0) {
		while (p) {
			if (strcmp(p->category, "饮料") == 0) {
				p->sale *= 0.9;

			}
			p = p->next;
		}
	}
	else {
		while (p) {
			p->sale *= 0.9;

			p = p->next;
		}
	}

}
void main() {
	menu1();
}