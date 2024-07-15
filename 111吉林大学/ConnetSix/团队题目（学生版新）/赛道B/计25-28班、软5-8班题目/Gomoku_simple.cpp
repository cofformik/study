#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cstdio>
using namespace std;

const int SIZE = 15;
int board[SIZE][SIZE] = { 0 };//����1���Է�-1���հ�0

int main()
{
	int x, y, n;
	//�ָ�Ŀǰ��������Ϣ
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		cin >> x >> y; if (x != -1) board[x][y] = -1;	//�Է�
		cin >> x >> y; if (x != -1) board[x][y] = 1;	//�ҷ�
	}
	cin >> x >> y;
	if (x != -1) board[x][y] = -1;	//�Է�
	
	//��ʱboard[][]��洢�ľ��ǵ�ǰ���̵�����������Ϣ,x��y����ǶԷ����һ���µ���

	/************************************************************************************/
	/***********�����������Ĵ��룬���߽�������������ӵ�λ�ã�����new_x��new_y��****************/
	//�����Ϊ������Ե�ʾ�����룬��ɾ��
	int new_x, new_y;
	if (x != -1 && n == 1) {  //��һ�غϣ��ҷ����֣��ܻ���һ������
		new_x = -1; new_y = -1;
	} else {  //�ǵ�һ�غ��ҷ����֣����һ�غ��ҷ����֣����ܻ���
		int avail_x[SIZE*SIZE], avail_y[SIZE*SIZE]; //�Ϸ�λ�ñ�
		int cnt = 0;
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++)
				if (board[i][j] == 0) {
					avail_x[cnt] = i;
					avail_y[cnt] = j;
					cnt++;
				}
		srand(time(0));
		int rand_pos = rand() % cnt;
		new_x = avail_x[rand_pos];
		new_y = avail_y[rand_pos];

	}
	/***********���Ϸ������Ĵ��룬���߽�������������ӵ�λ�ã�����new_x��new_y��****************/
	/************************************************************************************/

	// ��ƽ̨������߽��
	printf("%d %d\n", new_x, new_y);
	return 0;
}