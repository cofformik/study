#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define MAX_NAME_LENGTH 20
#define MAX_ORIGIN_LENGTH 20
#define MAX_BRAND_LENGTH 20
void save_accounts();//���浽�ļ�
void load_accounts();//��ȡ�ļ�
void register_account();//ע��
void login_account();//��¼
void logout_account();//ע���˻�
void change_password();//�޸�����
void menu1();//��¼�˵�
void register_account1();
void recover_password();//�һ�����
void menu();//���˵�
void delete();//ɾ����ˮ
void hotdrinks();//������ˮ
void discount();//�ۿ�
void individual1();//����Ա����
void individual2();//�û�����
void Add();//���
void addfile();//������д���ļ�
void scanffile();// ���ļ��ж�ȡ��ˮ��Ϣ��������
void T_scanffile();//��ȡ��Ʒ�ۿۼ�
int check(char a[]);//����Ƿ��ظ�
struct Node* search(char a[]);//������Ʒ
void shop_2();//�û�����
void order2();//�û�����
void modify();//�޸���Ʒ��Ϣ
void modifystock(int n);//�޸Ŀ��
void alldrinks();//�鿴���о�ˮ���
void inventory();//���˵�
void Searchproduct();//Ѱ����Ʒ
void init();          //��ʼ��
void print();//��ʾ
struct VIP gete();//���
void add1();//����µĻ�Ա��Ϣ 
void findbyno();//�����˺Ų��һ�Ա��Ϣ 
void findbyname();//�����������һ�Ա��Ϣ 
void findbyIDcard();//�������֤�Ų��һ�Ա��Ϣ 
void findbyphone();//�����ֻ��Ų��һ�Ա��Ϣ 
void mod();////�޸����еĻ�Ա��Ϣ 
void del();//ɾ�����л�Ա��Ϣ 
void sort();//���ݻ�Ա�˺Ŵ�С�������� 
void save_vip();//����Ϣ�����ļ�
void scanf_vip();//���ļ�����Ϣ��������
void customer();//�ͻ���Ϣ
struct VIP             //����ṹ�壬�洢��Ա�˺š����������֤�š���ϵ��ʽ��״̬
{
	long no;
	char name[20];    //���������֤�ź����ַ���ʹ��char���� 
	char IDcard[19];
	char phone[12];   //��ϵ�绰��11λ��������int�ķ�Χ��ʹ���ַ������� 
	int zhuangtai;      //���״̬Ϊ1������������Ϊ0����״̬Ϊ��ʧ 
	//int yue;
};
struct VIP s[50];     //����ṹ������ 
int n = 0;              //n��ʾ����Ļ�Ա���� 
typedef struct Node {//��ˮ�ṹ��
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
typedef struct Order2 {//�����ṹ��
	char name[20];
	int quantity;
	char brand[20];
	float singleprice;
	float sum;
	struct Order2* next;
}order_2;
order_2* head_1 = NULL;
typedef struct// ����һ���ṹ�壬���ڴ洢�˻���Ϣ
{
	char username[20];
	char password[20];
	char id_code[20];
} Account;
int identity = 0;
Account accounts[100];// ����һ��ȫ�ֱ��������ڴ洢����ע����˻�
int num_accounts = 0;
void create_File2()
{
	FILE* fp;
	if ((fp = fopen("accounts.txt", "rb")) == NULL)                 /*������ļ�������*/
	{
		if ((fp = fopen("accounts.txt", "wb+")) == NULL)
		{
			printf("�޷������ļ���\n");
			exit(0);

		}
	}
}
void save_accounts()// ���˻���Ϣ���浽�ļ���

{

	FILE* fp;
	fp = fopen("accounts.txt", "w"); // ���ļ����ļ���Ϊ"accounts.txt"
	if (fp == NULL)
	{
		printf("Error: cannot open file.\n");
		return;
	}
	for (int i = 0; i < num_accounts; i++)
	{
		fprintf(fp, "%s,%s,%s\n", accounts[i].username, accounts[i].password, accounts->id_code); // ���˻���Ϣд���ļ���
	}
	fclose(fp); // �ر��ļ�
	printf("�����������˵�......");
	Sleep(3000);
	menu();
}
void load_accounts()// ���ļ��ж�ȡ�˻���Ϣ
{
	create_File2();
	FILE* fp = fopen("accounts.txt", "r"); // ���ļ����ļ���Ϊ"accounts.txt"
	if (fp == NULL)
	{
		printf("Error: cannot open file.\n");
		return;
	}
	char line[100];
	while (fgets(line, 100, fp) != NULL)   // ���ж�ȡ�ļ�����
	{
		char* username = strtok(line, ","); // ʹ�ö��ŷָ��û���������
		char* password = strtok(NULL, ",");
		char* id_code = strtok(NULL, "\n");
		strcpy(accounts[num_accounts].username, username); // ���û��������뱣�浽�˻��ṹ����
		strcpy(accounts[num_accounts].password, password);
		strcpy(accounts[num_accounts].id_code, id_code);
		num_accounts++;
	}
	fclose(fp); // �ر��ļ�
}
void register_account()// ע�����˻�
{
	FILE* fp = fopen("accounts.txt", "r");
	char ch;
	ch = fgetc(fp);
	if (ch == -1 || ch == EOF)//�ж��Ƿ�����ע���û�
	{
		char username[20];
		char password[20];
		char id_code[20];
		printf("�������û����� ");
		scanf("%s", username);
		printf("���������룺");
		scanf("%s", password);
		printf("���������֤����λ:");
		scanf("%s", id_code);
		// ����û����Ƿ��Ѵ���
		for (int i = 0; i < num_accounts; i++)
		{
			if (strcmp(accounts[i].username, username) == 0)
			{
				printf("Error: username already exists.\n");
				return;
			}
		}
		// �����˻����浽�˻��ṹ����
		strcpy(accounts[num_accounts].username, username);
		strcpy(accounts[num_accounts].password, password);
		strcpy(accounts[num_accounts].id_code, id_code);
		num_accounts++;
		printf("ע��ɹ���\n");
		save_accounts(); // ���˻���Ϣ���浽�ļ���
	}
	else
	{
		printf("�Ѵ���ע���û�������ϵ����Աע��");
	}
}
void register_account1()// ע�����˻�
{
	char username[20];
	char password[20];
	char id_code[20];
	printf("�������û�����");
	scanf("%s", username);
	printf("���������룺");
	scanf("%s", password);
	printf("���������֤����λ:");
	scanf("%s", id_code);
	// ����û����Ƿ��Ѵ���
	for (int i = 0; i < num_accounts; i++)
	{
		if (strcmp(accounts[i].username, username) == 0)
		{
			printf("ע��ʧ�ܣ����˻��Ѿ�ע�ᣬ���ڷ��ظ�������......\n");
			Sleep(2000);
			individual1();
		}
	}
	// �����˻����浽�˻��ṹ����
	strcpy(accounts[num_accounts].username, username);
	strcpy(accounts[num_accounts].password, password);
	strcpy(accounts[num_accounts].id_code, id_code);

	num_accounts++;
	printf("ע��ɹ���\n");
	save_accounts(); // ���˻���Ϣ���浽�ļ���
}
void login_account()//��¼�˻�
{
	int found = 0;
	char username[20];
	char password[20];
	printf("�������˺ţ�");
	scanf("%s", username);
	printf("���������룺");
	scanf("%s", password);
	for (int i = 0; i < num_accounts; i++)
	{
		if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, password) == 0)
		{
			found = 1;
			printf("��½�ɹ������ڽ������˵�......");
			Sleep(1000);
			if (strcmp("mayf", username) == 0 && strcmp("123456", password) == 0)
				identity = 1;
			menu();
		}
	}
	if (!found)
	{
		printf("���������û�δע�ᣡ");
	}
}
void logout_account()// ע���˻�
{
	char username[20];
	char id_code[20];
	printf("Enter your username: ");
	scanf("%s", username);
	printf("���������֤����λ");
	scanf("%s", id_code);
	int found = 0;
	// �����˻���ɾ��
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
		save_accounts(); // ���˻���Ϣ���浽�ļ���
		menu1();
	}
	else
	{
		printf("Error: account not found.\n");
	}
}
void change_password()//�޸�����
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
			save_accounts(); // ���˻���Ϣ���浽�ļ���
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
void menu1()//��¼�˵�
{
	load_accounts(); // ���ļ��ж�ȡ�˻���Ϣ
	int choice;
	int t = 1;

	printf("1. ��¼�˻�\n");
	printf("2. ����Աע��\n");
	printf("3. ��������\n");
	printf("0. �˳�\n");
	printf("��ѡ��0-3�� �� ");
	int k = 0; // ��¼������ַ���

	while (t) {


	flag:if (k = scanf("%d", &choice) != 1 || k > 1) {
		printf("Invalid input. Please enter your choice again.\n");
		while (getchar() != '\n')
			continue;// ������뻺����
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
		printf("ѡ��Ƿ������������룡\n");
		break;
	}
	}
}

void recover_password()//�һ�����
{
	int found = 0;
	char username[20];
	char id_code[20];
	printf("�������˺�:");
	scanf("%s", username);
	printf("���������֤����λ:");
	scanf("%s", id_code);
	for (int i = 0; i < num_accounts; i++)
	{
		if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].id_code, id_code) == 0)
		{
			char newpassword[20];
			printf("������������\n");
			scanf("%s", newpassword);
			found = 1;
			strcpy(accounts[i].password, newpassword);
			printf("�޸ĳɹ�\n");
			save_accounts();
			menu1();
		}
	}
	if (!found)
	{
		printf("���֤������û�δע�ᣡ");
	}
}

void menu() {//�˵�
	system("cls");
	int choice, t = 1;

	printf("��ӭ�������ִ�ѧ�ƹ�\n");
	printf("\t\t\t\t1.���ž�ˮ\n\n\t\t\t\t2.�ۿ۾�ˮ\n\n\t\t\t\t3.��������\n\n");
	if (identity == 1) printf("\t\t\t\t4.��Ӿ�ˮ\n\n\t\t\t\t5.��Ա����\n\n\t\t\t\t6.�˳�\n\n");
	else printf("\t\t\t\t4.�˳�\n\n");
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
			default:printf("ѡ��Ƿ���������ѡ��");
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
			default:printf("ѡ��Ƿ���������ѡ��");
				scanf("%d", &choice);

			}
		}
	}
}

void hotdrinks() {

	system("cls");
	printf("��ӭ����������ˮ����\n\n");
	printf("\t\tƷ��\t\t\t\t��ˮ\t\t\t\t�۸�\n");

	T_scanffile();
	node* p = head;

	while (p) {
		printf("\t\t%s\t\t\t\t%s\t\t\t\t%.2f\n", p->brand, p->name, p->price);
		p = p->next;
	}
	printf("����'1'�������˵���");
	int choice;
	scanf("%d", &choice);
	if (choice == 1) {
		printf("���ڷ��ز˵�......");
		Sleep(3000);
		menu();
	}
}
void alldrinks() {

	system("cls");
	printf("��ӭ������ˮ����\n\n");
	printf("\t\tƷ��\t\t\t\t��ˮ\t\t\t\t�۸�\t\t\t\t���\n");

	T_scanffile();
	node* p = head;

	while (p) {
		printf("\t\t%s\t\t\t\t%s\t\t\t\t%.2f\t\t\t\t%d\n", p->brand, p->name, p->price, p->quantity);
		p = p->next;
	}
	printf("����'1'�������˵���");
	int choice;
	scanf("%d", &choice);
	if (choice == 1) {
		printf("���ڷ��ز˵�......");
		Sleep(3000);
		inventory();
	}
}

void discount() {//�ۿ�
	system("cls");
	printf("\t\t��ӭ�����ۿ۾�ˮ����\n\n");
	printf("��ǰʱ��Ϊ��");
	char* wday[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
	time_t timep;
	struct tm* q;

	time(&timep);
	q = localtime(&timep); //ȡ�õ���ʱ��
	printf("%d/%d/%d ", (q->tm_year + 1900), (q->tm_mon + 1), q->tm_mday);
	printf("%s %d:%d\n", wday[q->tm_wday], q->tm_hour, q->tm_min);

	printf("\t\t�����ۿ۹���\n\n\t\t1.��һ������ÿ�־�ˮ������۳���һ�Σ�\n\n\t\t2.��ĩȫ��ˮ���۳��ۣ�\n\n");
	printf("\t\t3.��ĩ���о�ˮ���۳��ۣ�������");
	T_scanffile();

	node* p = head;
	printf("\n\n\t\tƷ��\t\t\t\t��ˮ\t\t\t\tԭ��\t\t\t\t�ۿۼ�\n\n");
	if (strcmp(wday[q->tm_wday], "Mon") == 0) {
		while (p) {
			if (strcmp(p->category, "ơ��") == 0) {

				printf("\t\t%s\t\t\t\t%s\t\t\t\t%.2f\t\t\t\t%.2f\n\n", p->brand, p->name, p->price, p->sale);

			}
			p = p->next;
		}
	}
	else if (strcmp(wday[q->tm_wday], "Tue") == 0) {
		while (p) {
			if (strcmp(p->category, "�׾�") == 0) {

				printf("\t\t%s\t\t\t\t%s\t\t\t\t%.2f\t\t\t\t%.2f\n\n", p->brand, p->name, p->price, p->sale);

			}
			p = p->next;
		}
	}
	else if (strcmp(wday[q->tm_wday], "Wed") == 0) {
		while (p) {
			if (strcmp(p->category, "��Ȫˮ") == 0) {

				printf("\t\t%s\t\t\t\t%s\t\t\t\t%.2f\t\t\t\t%.2f\n\n", p->brand, p->name, p->price, p->sale);

			}
			p = p->next;
		}
	}
	else if (strcmp(wday[q->tm_wday], "Thu") == 0) {
		while (p) {
			if (strcmp(p->category, "��֭") == 0) {
				printf("\t\t%s\t\t\t\t%s\t\t\t\t%.2f\t\t\t\t%.2f\n\n", p->brand, p->name, p->price, p->sale);

			}
			p = p->next;
		}
	}
	else if (strcmp(wday[q->tm_wday], "Fri") == 0) {
		while (p) {
			if (strcmp(p->category, "����") == 0) {

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
	printf("����Y�����ز˵�\n");
	getchar();
	char choice;
	scanf("%c", &choice);
	if (choice == 'y' || choice == 'Y') {
		printf("�����������˵�......");
		Sleep(3000);
		menu();
	}
}

void individual2() {

	printf("1.�޸�����\n");
	printf("2.ע���˻�\n");
	printf("3.���˶���\n");
	printf("4.������Ʒ\n");
	printf("0.�������˵�\n");
	printf("���������ѡ��:");
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
		printf("�����������������룡\n");
		break;
	}
	while (choice != 0);
}
void order2() {//�������ļ���������
	system("cls");
	printf("�鿴���˶���\n\n");
	FILE* fp;
	fp = fopen("order2", "r");

	if (fp == NULL)
	{
		printf("�ļ������ڣ�\n");
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
	printf("\t\tid\t\t��ˮ\t\t����\t\t����\t\t�ܼ�\n\n");
	while (p) {
		printf("\t\t%d\t\t%s\t\t%d\t\t%.2f\t\t%.2f\n\n", j, p->name, p->quantity, p->singleprice, (p->singleprice) * (p->quantity));
		j++;
		p = p->next;
	}
	fclose(fp);
	printf("\n\n����'1'���ز˵���");
	int k, choice;
flag:if (k = scanf("%d", &choice) != 1 || k > 1) {
	printf("����������������룺\n");
	while (getchar() != '\n')
		continue;// ������뻺����
	goto flag;

}
printf("���ڷ������˵���");
Sleep(3000);
menu();
}
struct Node* search(char a[]) {//��ѯ��Ʒ
	T_scanffile();
	node* p = head;
	while (p) {
		if (strcmp(p->name, a) == 0)
			return p;
		p = p->next;
	}

	return NULL;

}
void shop_2() {//������Ʒ
	system("cls");
	printf("\t\t��ӭ����������棡\n");
	FILE* fp;
	fp = fopen("order2", "a");
	char brr;
	if (fp == NULL)
	{
		printf("�ļ������ڣ�\n");
		return;
	}
	printf("��������Ҫ�������Ʒ��\t");
	char goods[20];
	scanf("%s", goods);
	brr = getchar();
	node* p = search(goods);
	while (!p) {
		printf("δ�ҵ�����Ʒ������������");
		scanf("%s", goods);
		brr = getchar();
	}
	printf("Ʒ�ƣ�%s\n���ƣ�%s\n���ۣ�%.2f\n�ۿۼۣ�%.2f\n", p->brand, p->name, p->price, p->sale);
	printf("�����빺��������\t");
	int i;
	scanf("%d", &i);
	printf("����%s���ܼ���%.2f,�Ƿ�ȷ������(1/0)", p->name, i * p->sale);
	int choice;
	scanf("%d", &choice);
	if (choice) {
		fprintf(fp, "%s %s %d %.2f %.2f\n", p->brand, p->name, i, p->sale, i * (p->sale));
		if (p->quantity < i) {

			printf("�ܱ�Ǹ����ʧ�ܣ�����Ʒ��ʱ��治�㣬�����Ѿ�֪ͨ����Ա�����ˣ���л������⣡\n");
		}
		else {
			printf("����ɹ���\n");
			p->quantity -= i;
		}
		addfile();
		fclose(fp);
		printf("\n\n����'1'���ز˵���");
		int ch;
		scanf("%d", &ch);
		if (ch == 1)
		{
			printf("���ڷ��ز˵�.......");

			Sleep(3000);
			menu();
		}
	}
	else {
		printf("�Ƿ�ѡ�����¹���1/0)?\n1.���¹���\n0.�������˵�\n");
		int num;
		scanf("%d", &num);
		if (num) {
			fclose(fp);
			shop_2();
		}
		else {
			printf("���ڷ��ز˵�.......");
			fclose(fp);
			Sleep(3000);
			menu();
		}
	}
}
void individual1()//����Ա��������
{
	system("cls");
	printf("\t\t\t\t1.ע�����û�\n");
	printf("\t\t\t\t2.�޸�����\n");
	printf("\t\t\t\t3.ע���˻�\n");
	printf("\t\t\t\t4.������\n");
	printf("\t\t\t\t0.�������˵�\n");
	printf("���������ѡ��:");
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
		printf("�����������������룡\n");
		break;
	}

}



void init()   //��ʼ����Ψһ��6λ��Ա�˺ţ�
{
	int f = 1; //1Ψһ   0��Ψһ 
	printf("�������Ա���˺�,����,���֤����,��ϵ�绰,״̬\n");
	printf("�������Ա��Ϊ0ʱֹͣ����\n");
	while (n <= 50)
	{
		printf("�������Ա���˺�:\n");
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
						printf("������Ψһ��6λ��Ա�˺�\n");
					}

				}
				if (f == 1)
					break;
			}
			else
			{
				printf("������6λ��Ա�˺�\n");
				printf("�����������Ա���˺�:\n");
				scanf("%d", &s[n].no);
			}
		}
		if (s[n].no == 0)
			break;         //���������˺�Ϊ0����������
		printf("�������Ա������:\n");
		scanf("%s", s[n].name);
		printf("�������Ա�����֤�ţ���ϵ�绰��״̬:\n");
		scanf("%s%s%d", s[n].IDcard, s[n].phone, &s[n].zhuangtai);
		n++;
	}
	save_vip();
}

void print()  //��� 
{

	int j;
	printf("��Ա��Ϣ��¼����:\n");
	printf("     |===============================================================================|\n");
	printf("     |�˺�\t����\t���֤��\t��ϵ�绰\t   ״̬          \n");
	printf("     |-------------------------------------------------------------------------------|\n");
	for (j = 0; j < n; j++)
	{
		printf("     |%ld\t%s\t%s\t\t%s\t", s[j].no, s[j].name, s[j].IDcard, s[j].phone);
		if (s[j].zhuangtai == 1)
			printf("  ����           \n");
		else
			printf("  ��ʧ           \n");
		if (j < (n - 1))
			printf("     |-------------------------------------------------------------------------------|\n");
	}
	printf("     |===================================================================================|\n");
}

struct VIP gete()       //���� 
{
	struct VIP e;
	printf("�������˺�:\n");
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
					printf("������Ψһ��6λ��Ա�˺�\n");
					scanf("%d", &e.no);
				}
			}
			if (f == 1)
				break;
		}
		else
		{
			printf("������6λ��Ա�˺�\n");
			printf("�����������Ա���˺�:\n");
			scanf("%d", &e.no);
		}
	}
	printf("����������:\n");
	scanf("%s", &e.name);
	printf("�������Ա�����֤�ţ���ϵ�绰��״̬:\n");
	scanf("%s%s%d", &e.IDcard, &e.phone, &e.zhuangtai);
	save_vip();
	return e;

}

void add1()   //����µĻ�Ա��Ϣ 
{
	struct VIP e = gete();
	int i;
	printf("������Ҫ�����λ�ã�1-%d����\n", n);
	scanf("%d", &i);
	while (i<1 || i>n + 1)
	{
		printf("�������λ������\n");
		printf("����������Ҫ�����λ�ã�1-%d����\n", n);
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

void findbyno()     //���ݻ�Ա�˺Ų��һ�Ա��Ϣ 
{
	int num, i;
	int found = 1;
	char choice;
	while (1)
	{
		printf("������Ҫ���ҵĻ�Ա���˺ţ�\n");
		scanf("%d", &num);
		getchar();
		for (i = 0; i < n && found == 1; i++)
		{

			if (s[i].no == num)
			{
				found = 0;
				printf("%ld\t%s\t%d\t%d\t", s[i].no, s[i].name, s[i].IDcard, s[i].phone);
				if (s[i].zhuangtai == 1)
					printf("����\n");
				else
					printf("��ʧ!\n");
			}
		}
		if (found == 1)
		{
			printf("δ�ҵ�!\n");
		}
		found = 1;
		printf("�Ƿ������ѯ(Y/N)\n");
		choice = getchar();
		if (choice == 'N' || choice == 'n')
			break;
	}
}

void findbyname()    //���ݻ�Ա�������һ�Ա��Ϣ 
{
	char name[20];
	char choice;
	int found = 1;
	int i;
	while (1)
	{
		printf("����Ҫ��ѯ��Ա��������\n");
		scanf("%s", name);
		getchar();
		for (i = 0; i < n && found == 1; i++)
		{
			if (strcmp(s[i].name, name) == 0)
			{
				found = 0;
				printf("%ld\t%s\t%d\t%d\t", s[i].no, s[i].name, s[i].IDcard, s[i].phone);
				if (s[i].zhuangtai == 1)
					printf("����\n");
				else
					printf("��ʧ!\n");
			}
		}
		if (found == 1)
		{
			printf("δ�ҵ�!\n");
		}
		found = 1;
		printf("�Ƿ������ѯ(Y/N)\n");
		choice = getchar();
		if (choice == 'N' || choice == 'n')
			break;
	}
}

void findbyIDcard()   //�������֤�Ų��һ�Ա��Ϣ 
{
	char num[19];
	int i;
	int found = 1;
	char choice;
	while (1)
	{
		printf("������Ҫ���ҵĻ�Ա�����֤�ţ�\n");
		scanf("%s", num);
		getchar();
		for (i = 0; i < n && found == 1; i++)
		{
			if (strcmp(s[i].IDcard, num) == 0)
			{
				found = 0;
				printf("%ld\t%s\t%d\t%d\t", s[i].no, s[i].name, s[i].IDcard, s[i].phone);
				if (s[i].zhuangtai == 1)
					printf("����\n");
				else
					printf("��ʧ!\n");
			}
		}
		if (found == 1)
		{
			printf("δ�ҵ�!\n");
		}
		found = 1;
		printf("�Ƿ������ѯ(Y/N)\n");
		choice = getchar();
		if (choice == 'N' || choice == 'n')
			break;
	}
}

void findbyphone()    //������ϵ�绰���һ�Ա��Ϣ 
{
	char num[12];
	int i;
	int found = 1;
	char choice;
	while (1)
	{
		printf("������Ҫ���ҵĻ�Ա����ϵ�绰��\n");
		scanf("%s", num);
		getchar();
		for (i = 0; i < n && found == 1; i++)
		{
			if (strcmp(s[i].phone, num) == 0)
			{
				found = 0;
				printf("%ld\t%s\t%d\t%d\t", s[i].no, s[i].name, s[i].IDcard, s[i].phone);
				if (s[i].zhuangtai == 1)
					printf("����\n");
				else
					printf("��ʧ!\n");
			}
		}
		if (found == 1)
		{
			printf("δ�ҵ�!\n");
		}
		found = 1;
		printf("�Ƿ������ѯ(Y/N)\n");
		choice = getchar();
		if (choice == 'N' || choice == 'n')
			break;
	}
}

void mod()     //�޸����еĻ�Ա��Ϣ 
{
	int num, i;
	int found = 1;
	char choice;
	int opt;
	while (1)
	{
		printf("������Ҫ�޸ĵĻ�Ա���˺�(��Ա���޷��޸�)��\n");
		scanf("%d", &num);
		getchar();
		for (i = 0; i < n && found == 1; i++)
		{
			if (s[i].no == num)
			{
				found = 0;
				printf("%ld\t%s\t%d\t%d\t", s[i].no, s[i].name, s[i].IDcard, s[i].phone);
				if (s[i].zhuangtai == 1)
					printf("����\n");
				else
					printf("��ʧ\n");
				printf("--��ѡ��--1.�޸����֤�� 2.�޸���ϵ�绰 3.�޸�״̬\n");
				scanf("%d", &opt);
				getchar();
				switch (opt)
				{
				case 1:
					printf("���������֤����ֵ:\n");
					scanf("%s", s[i].IDcard);
					getchar();
					break;
				case 2:
					printf("��������ϵ�绰��ֵ:\n");
					scanf("%s", s[i].phone);
					getchar();
					break;
				case 3:
					printf("������״̬��ֵ:\n");
					scanf("%d", &s[i].zhuangtai);
					getchar();
					break;
				}
			}
		}
		if (found == 1)
		{
			printf("δ�ҵ�!\n");
		}
		found = 1;
		printf("�Ƿ�����޸�(Y or N)\n");
		choice = getchar();
		getchar();
		if (choice == 'N' || choice == 'n')
			break;
	}
	save_vip();
}

void del()     //ɾ�����л�Ա��Ϣ 
{
	int num, i, j;
	int found = 1;
	char choice;
	while (1)
	{
		printf("������Ҫɾ���Ļ�Ա���˺ţ�\n");
		scanf("%d", &num);
		getchar();
		for (i = 0; i < n && found == 1; i++)   //5  1-5      
		{
			if (s[i].no == num)
			{
				found = 0;
				printf("��Ҫɾ���Ļ�Ա��ϢΪ:\n");
				printf("��Ա�˺�     ����      ���֤��      ��ϵ�绰       ״̬\n");
				printf("%ld\t%s\t%d\t%d\t", s[i].no, s[i].name, s[i].IDcard, s[i].phone);
				if (s[i].zhuangtai == 1)
					printf("����\n");
				else
					printf("��ʧ!\n");
				for (j = i; j < n - 1; j++)
				{
					s[j] = s[j + 1];
				}
				n--;
			}
		}
		if (found == 1)
		{
			printf("δ�ҵ�!\n");
		}
		found = 1;
		printf("�Ƿ������Y/N��\n");
		choice = getchar();
		getchar();
		if (choice == 'N' || choice == 'n')
			break;
	}
	save_vip();
}

void sort()     //���ݻ�Ա�˺Ŵ�С�������� 
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
	printf("\n�����Ļ�Ա��Ϣ:\n");
	save_vip();
}
void save_vip() {//����Ϣ�����ļ�
	FILE* fp = NULL;
	fp = fopen("vip", "w");
	for (int i = 0; i < n; i++) {
		fprintf(fp, "%ld %s %s %s %d\n", s[i].no, s[i].name, s[i].IDcard, s[i].phone, s[i].zhuangtai);
	}
	fclose(fp);
}
void scanf_vip() {//���ļ��ж�ȡVIP�ͻ���Ϣ
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
	printf("     |*             ��ӭʹ�û�Ա����ϵͳ           *|\n");
	printf("     |*============================================*|\n");
	printf("     |*    1.��ʼ��                                *|\n");
	printf("     |*    2.����µĻ�Ա��¼                      *|\n");
	printf("     |*    3.�޸����л�Ա��¼/��ʧ                 *|\n");
	printf("     |*    4.�����˺Ų�ѯ���л�Ա��¼              *|\n");
	printf("     |*    5.����������ѯ���л�Ա��¼              *|\n");
	printf("     |*    6.�������֤�Ų�ѯ���л�Ա��¼          *|\n");
	printf("     |*    7.������ϵ�绰��ѯ���л�Ա��¼          *|\n");
	printf("     |*    8.ɾ�����л�Ա��¼                      *|\n");
	printf("     |*    9.���ݻ�Ա�˺�������ʾ                *|\n");
	printf("     |*    0.�˳���Ա��Ϣ����ϵͳ                  *|\n");
	printf("     |*============================================*|\n");
	while (1)
	{
		printf("������Ҫ��ɵĹ��ܣ�0-10:");
		scanf("%d", &opt);
		getchar();    //���ջس� 
		switch (opt)
		{
		case 1:init(); print(); break;          //��ʼ�� 
		case 2:add1(); print(); break;          //��� 
		case 3:mod(); print(); break;           //�޸� 
		case 4:findbyno(); print(); break;      //�����˺Ų�ѯ 
		case 5:findbyname(); print(); break;    //����������ѯ 
		case 6:findbyIDcard(); print(); break;  //�������֤�Ų�ѯ 
		case 7:findbyphone(); print(); break;   //������ϵ�绰��ѯ 
		case 8:del(); print(); break;           //ɾ�� 
		case 9:sort(); print(); break;          //���� 
		case 0:system("cls"); exit(0); break;   //�˳� 
		default:printf("������0-10�е���!\n"); break;
		}
	}
}
void inventory()
{

	system("cls");
	printf("\n\n\n\n\n");
	printf("\t\t|---------------------PRODUCT-------------------|\n");
	printf("\t\t|   1. ��Ʒ���                                 |\n");
	printf("\t\t|   2. ��Ʒ����                                 |\n");
	printf("\t\t|   3. ɾ����Ʒ                                 |\n");
	printf("\t\t|   4. �޸���Ʒ                                 |\n");
	printf("\t\t|   5. ������Ʒ                                 |\n");
	printf("\t\t|   6. ��ʾ��Ʒ                                 |\n");
	printf("\t\t|   0. �˳�                                     |\n");
	printf("\t\t|-----------------------------------------------|\n\n");
	printf("\t\t\tѡ��(0-6):");
	int iItem;
	scanf("%d", &iItem);          /*����˵���*/
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
		default:printf("��������ȷ����");
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

	printf("��������Ҫ��ѯ����Ʒ��");
	char name[20];
	gets(name);
	node* p = search(name);
	if (p != NULL)
	{
		printf("\t\tƷ��\t\t\t\t��ˮ\t\t\t\t�۸�\t\t\t\t���\n");
		printf("\t\t%s\t\t\t\t%s\t\t\t\t%.2f\t\t\t\t%d\n", p->brand, p->name, p->price, p->quantity);
	}
	else
		printf("����Ʒ�����ڣ�");
	printf("���롮1�������ؿ��˵�");
	int choice;
	scanf("%d", &choice);
	if (choice == 1) {
		printf("���ڷ��ؿ��˵�......");
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



void Add() {//���
	node* p;
	int choice;
	p = (node*)malloc(sizeof(node));
	printf("�������ˮ���ƣ�");
	scanf("%s", &p->name);
	if (check(p->name) == 1) {
		printf("��Ʒ�Ѵ���,���������룡\n");
		Add();
	}
	printf("������Ʒ�ƣ�");
	scanf("%s", &p->brand);
	printf("�������ˮ���ࣺ");
	scanf("%s", &p->category);
	printf("�������ˮ�۸�");
	scanf("%f", &(p->price));
	printf("�������ˮ�������");
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
	printf("�Ƿ������ӣ�1/0��?");
	scanf("%d", &choice);
	if (choice == 1) {
		Add();
	}
	else {

		printf("���ڷ��ز˵�......");
		Sleep(3000);
		menu();
	}
}

void addfile() {//������д���ļ�
	node* p = head;
	FILE* fp;
	fp = fopen("drinks", "w");
	while (p) {
		fprintf(fp, "%s %s %s %.2f %d\n", p->brand, p->name, p->category, p->price, p->quantity);

		p = p->next;
	}
	printf("���浽�ļ��ɹ�!\n");

	fclose(fp);//�ر��ļ�

}


void delete() //ɾ����ˮ
{


	T_scanffile();

	if (head == NULL) {
		printf("����Ϊ�գ�\n");
		return;
	}
	printf("������Ҫɾ���ľ�ˮ���ƣ�");
	char name[55];
	scanf("%s", name);
	if (strcmp(head->name, name) == 0) {
		node* temp = head;
		head = head->next;
		free(temp);
		printf("ɾ���ɹ���\n");
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
			printf("ɾ���ɹ���34\n");
			Sleep(3000);
			addfile();
			menu();
			return;
		}
		current = current->next;
	}

	printf("δ�ҵ��þ�ˮ��Ϣ��\n");

}
void modify() //�޸ľ�ˮ��Ϣ
{
	T_scanffile();

	if (head == NULL) {
		printf("����Ϊ�գ�\n");
		return;
	}
	char name[50];
	printf("������Ҫ�޸ĵľ�ˮ���ƣ�");
	scanf("%s", name);

	node* current = head;
	node* prev = NULL;
	while (current != NULL) {
		if (strcmp(current->name, name) == 0)
		{
			printf("ԭ��ˮ��ϢΪ��\n");
			printf("Ʒ�ƣ�%s\n", current->brand);
			printf("������%s\n", current->name);
			printf("���ࣺ%s\n", current->category);
			printf("�۸�%.2f\n", current->price);
			printf("��棺%d\n", current->quantity);


			printf("�������޸ĺ����Ϣ��\n\n");
			char newName[50], newCategory[50];
			float newPrice;
			int newStock;
			int  newIsDiscounted;
			char newBrand[20];
			printf("Ʒ�ƣ�");
			scanf("%s", newBrand);
			strcpy(current->brand, newBrand);
			printf("���ƣ�");
			scanf("%s", newName);
			strcpy(current->name, newName);
			printf("���ࣺ");
			scanf("%s", newCategory);
			strcpy(current->category, newCategory);
			printf("�۸�");
			scanf("%f", &newPrice);
			current->price = newPrice;
			printf("��棺");
			scanf("%d", &newStock);
			current->quantity = newStock;



			addfile();

			printf("���ڷ��ؿ��˵�......");
			Sleep(3000);
			inventory();
		}
		prev = current;
		current = current->next;
	}
	printf("δ�ҵ��þ�ˮ��Ϣ��\n");
}
void modifystock(int n)//�޸Ŀ��
{
	T_scanffile();

	if (head == NULL) {
		printf("����Ϊ�գ�\n");
		return;
	}
	char name[50];
	if (n == 1)printf("������Ҫ�����ľ�ˮ���ƣ�");
	else if (n == 2)printf("������Ҫ�����ľ�ˮ���ƣ�");
	scanf("%s", name);


	node* current = head;
	node* prev = NULL;
	while (current != NULL) {
		if (strcmp(current->name, name) == 0)
		{
			printf("ԭ��ˮ��ϢΪ��\n");
			printf("Ʒ�ƣ�%s\n", current->brand);
			printf("������%s\n", current->name);
			printf("���ࣺ%s\n", current->category);
			printf("�۸�%.2f\n", current->price);
			printf("��棺%d\n", current->quantity);

			int number;
			printf("������������");
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

			printf("���ڷ��ؿ��˵�......");
			Sleep(3000);
			inventory();
		}
		prev = current;
		current = current->next;
	}
	printf("δ�ҵ��þ�ˮ��Ϣ��\n");
}



void scanffile()// ���ļ��ж�ȡ��ˮ��Ϣ��������
{
	int i = 0;
	FILE* fp = fopen("drinks", "r");
	if (fp == NULL)
	{
		printf("�ļ������ڣ�\n");
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
void T_scanffile() {//��ȡ��Ʒ�ۿۼ�
	char* wday[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

	time_t timep;
	struct tm* q;

	time(&timep);
	q = localtime(&timep);
	scanffile();
	node* p = head;
	if (strcmp(wday[q->tm_wday], "Mon") == 0) {
		while (p) {
			if (strcmp(p->category, "ơ��") == 0) {
				p->sale *= 0.9;
			}
			p = p->next;
		}
	}
	else if (strcmp(wday[q->tm_wday], "Tue") == 0) {
		while (p) {
			if (strcmp(p->category, "�׾�") == 0) {
				p->sale *= 0.9;

			}
			p = p->next;
		}
	}
	else if (strcmp(wday[q->tm_wday], "Wed") == 0) {
		while (p) {
			if (strcmp(p->category, "��Ȫˮ") == 0) {
				p->sale *= 0.9;

			}
			p = p->next;
		}
	}
	else if (strcmp(wday[q->tm_wday], "Thu") == 0) {
		while (p) {
			if (strcmp(p->category, "��֭") == 0) {
				p->sale *= 0.9;

			}
			p = p->next;
		}
	}
	else if (strcmp(wday[q->tm_wday], "Fri") == 0) {
		while (p) {
			if (strcmp(p->category, "����") == 0) {
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