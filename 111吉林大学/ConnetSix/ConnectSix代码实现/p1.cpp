#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include<cstring>
#define GRIDSIZE 15
#define judge_black 0
#define judge_white 1
#define grid_blank 0
#define grid_black 1
#define grid_white -1
struct battletree {
	battletree* son = NULL;
	int color = grid_white;
	double alpha = 20000000;
	double beta = -20000000;
	battletree(int c = grid_white) {
		color = c;
	}
};
//博弈树 
using namespace std;
int currBotColor; // 本方所执子颜色（1为黑，-1为白，棋盘状态亦同）
int gridInfo[GRIDSIZE][GRIDSIZE] = { 0 }; // 先x后y，记录棋盘状态
int dx[] = { -1,-1,-1,0,0,1,1,1 };
int dy[] = { -1,0,1,-1,1,-1,0,1 };
// 判断是否在棋盘内
inline bool inMap(int x, int y)
{
	if (x < 0 || x >= GRIDSIZE || y < 0 || y >= GRIDSIZE)
		return false;
	return true;
}
int Score_myroad2[7] = { 0,1,20,40,200,50,1000000 };
int Score_yourroad2[7] = { 0,2,15,50,6000,6000,1000000 };
int Score_myroad1[7] = { 0,1,10,40,240,50,1000000 };
int Score_yourroad1[7] = { 0,1,5,30,2000,2000,1000000 };
int Score_myroad[7] = { 0,1,20,40,200,50,1000000 };
int Score_yourroad[7] = { 0,1,15,50,6000,6000,1000000 };
int Number_of_wroad[7];
int Number_of_broad[7];
void swap_ranges(int* a, int* b, int* c) {
	int k = b - a;
	for (int i = 0; i <= k - 1; i++) {
		swap(a[i], c[i]);
	}
}
double weight = 0.5;
void rand_s(int& a, int& b, int& c, int& d, int color, int x0, int y0, int x1, int y1) {
	a = (rand() % (x1 - x0 + 1)) + x0;
	b = (rand() % (y1 - y0 + 1)) + y0;
	c = (rand() % (x1 - x0 + 1)) + x0;
	d = (rand() % (y1 - y0 + 1)) + y0;
}
int heng(int x, int y, int color, int c) {
	if (c) {
		swap_ranges(Score_myroad, Score_myroad + 7, Score_yourroad);
	}
	int m_road[7] = { 0 };
	int y_road[7] = { 0 };
	int left_bound, right_bound;
	if (x - 5 >= 0) {
		left_bound = x - 5;
	}
	else {
		left_bound = 0;
	}
	if (x + 5 <= 14) {
		right_bound = x + 5;
	}
	else {
		right_bound = 14;
	}
	int m_benefit = 0;
	int k = 0;
	int x0;
	int r = 0;
	x0 = left_bound;
	for (int i = 0; i <= 5; i++) {
		if (x0 + i > right_bound) {
			goto flag;
		}
		if (gridInfo[x0 + i][y] == color) {
			r++;
		}
		else if (gridInfo[x0 + i][y] == 0) {
		}
		else {
			if (x0 + i > x) {
				goto flag;
			}
			r = 0;
			x0 = x0 + i + 1;
			i = -1;
		}
		if (i == 5) x0 = x0 + 6;
	}
	m_road[r]++;
	while (x0 <= right_bound) {
		if (gridInfo[x0][y] == -color) {
			break;
		}
		else if (gridInfo[x0][y] == color) {
			if (gridInfo[x0 - 6][y] == 0) {
				r++;
				m_road[r]++;
			}
			else {
				m_road[r]++;
			}
		}
		else {
			if (gridInfo[x0 - 6][y] == 0)
				m_road[r]++;
			else {
				r--;
				m_road[r]++;
			}
		}
		x0++;
	}
flag:
	for (int i = 1; i <= 6; i++) {
		m_benefit += (m_road[i] * (1 - weight) * Score_myroad[i] - m_road[i] * (1 - weight) * Score_myroad[i - 1]);
	}
	x0 = left_bound;
	gridInfo[x][y] = 0;
	r = 0;
	for (int i = 0; i <= 5; i++) {
		if (x0 + i > right_bound) {
			goto flag2;
		}
		if (gridInfo[x0 + i][y] == 0) {
		}
		else if (gridInfo[x0 + i][y] == -color) {
			r++;
		}
		else {
			if (x0 + i > x) {
				goto flag2;
			}
			r = 0;
			x0 = x0 + i + 1;
			i = -1;
		}
		if (i == 5) x0 += 6;
	}
	y_road[r]++;
	while (x0 <= right_bound) {
		if (gridInfo[x0][y] == color) {
			break;
		}
		else if (gridInfo[x0][y] == -color) {
			if (gridInfo[x0 - 6][y] == 0) {
				r++;
				y_road[r]++;
			}
			else {
				y_road[r]++;
			}
		}
		else {
			if (gridInfo[x0 - 6][y] == 0)
				y_road[r]++;
			else {
				r--;
				y_road[r]++;
			}
		}
		x0++;
	}
flag2:
	int y_lost = 0;
	for (int i = 1; i <= 5; i++) {
		y_lost += y_road[i] * weight * Score_yourroad[i];
	}

	int total_benefit = y_lost + m_benefit;
	gridInfo[x][y] = color;
	if (c) {
		swap_ranges(Score_myroad, Score_myroad + 7, Score_yourroad);
	}
	return total_benefit;
}
int shu(int x, int y, int color, int c) {
	if (c) {
		swap_ranges(Score_myroad, Score_myroad + 7, Score_yourroad);
	}
	int m_road[7] = { 0 };
	int y_road[7] = { 0 };
	int left_bound, right_bound;
	if (y - 5 >= 0) {
		left_bound = y - 5;
	}
	else {
		left_bound = 0;
	}
	if (y + 5 <= 14) {
		right_bound = y + 5;
	}
	else {
		right_bound = 14;
	}
	int m_benefit = 0;
	int k = 0;
	int y0;
	int r = 0;
	y0 = left_bound;
	for (int i = 0; i <= 5; i++) {
		if (y0 + i > right_bound) {
			goto flag;
		}
		if (gridInfo[x][y0 + i] == color) {
			r++;
		}
		else if (gridInfo[x][y0 + i] == 0) {
		}
		else {
			if (y0 + i > y) {
				goto flag;
			}
			r = 0;
			y0 = y0 + i + 1;
			i = -1;
		}
		if (i == 5) y0 = y0 + 6;
	}
	m_road[r]++;
	while (y0 <= right_bound) {
		if (gridInfo[x][y0] == -color) {
			break;
		}
		else if (gridInfo[x][y0] == color) {
			if (gridInfo[x][y0 - 6] == 0) {
				r++;
				m_road[r]++;
			}
			else {
				m_road[r]++;
			}
		}
		else {
			if (gridInfo[x][y0 - 6] == 0)
				m_road[r]++;
			else {
				r--;
				m_road[r]++;
			}
		}
		y0++;
	}
flag:
	for (int i = 1; i <= 6; i++) {
		m_benefit += (m_road[i] * (1 - weight) * Score_myroad[i] - m_road[i] * (1 - weight) * Score_myroad[i - 1]);
	}
	y0 = left_bound;
	gridInfo[x][y] = 0;
	r = 0;
	for (int i = 0; i <= 5; i++) {
		if (y0 + i > right_bound) {
			goto flag2;
		}
		if (gridInfo[x][y0 + i] == 0) {
		}
		else if (gridInfo[x][y0 + i] == -color) {
			r++;
		}
		else {
			if (y0 + i > y) {
				goto flag2;
			}
			r = 0;
			y0 = y0 + i + 1;
			i = -1;
		}
		if (i == 5) y0 += 6;
	}
	y_road[r]++;
	while (y0 <= right_bound) {
		if (gridInfo[x][y0] == color) {
			break;
		}
		else if (gridInfo[x][y0] == -color) {
			if (gridInfo[x][y0 - 6] == 0) {
				r++;
				y_road[r]++;
			}
			else {
				y_road[r]++;
			}
		}
		else {
			if (gridInfo[x][y0 - 6] == 0)
				y_road[r]++;
			else {
				r--;
				y_road[r]++;
			}
		}
		y0++;
	}
flag2:
	int y_lost = 0;
	for (int i = 1; i <= 5; i++) {
		y_lost += y_road[i] * weight * Score_yourroad[i];//cout<<y_lost<<endl;
	}

	int total_benefit = y_lost + m_benefit;
	gridInfo[x][y] = color;
	if (c) {
		swap_ranges(Score_myroad, Score_myroad + 7, Score_yourroad);
	}
	return total_benefit;
}
int zx(int x, int y, int color, int c) {
	if (c) {
		swap_ranges(Score_myroad, Score_myroad + 7, Score_yourroad);
	}
	int m_road[7] = { 0 };
	int y_road[7] = { 0 };
	int lb, rb;
	int m_benefit = 0, y_benefit;
	if (x + 5 <= 14 && y - 5 >= 0) {
		rb = x + 5;
	}
	if (x + 5 <= 14 && y - 5 < 0) {
		rb = x + y;
	}
	if (x + 5 > 14 && y - 5 >= 0) {
		rb = 14;
	}
	if (x + 5 > 14 && y - 5 < 0) {
		rb = x + y;
	}
	if (x - 5 >= 0 && y + 5 <= 14) {
		lb = x - 5;
	}
	if (x - 5 >= 0 && y + 5 > 14) {
		lb = x - (14 - y);
	}
	if (x < 5 && y + 5 <= 14) {
		lb = 0;
	}
	if (x < 5 && y + 5>14) {
		lb = x - (14 - y);
	}
	if (rb > 14)
		rb = 14;
	if (lb < 0)
		lb = 0;
	int x0, y0;
	x0 = lb;
	y0 = x - lb + y;
	int r = 0;

	for (int i = 0; i <= 5; i++) {
		if (x0 + i > rb) {
			goto flag;
		}
		if (gridInfo[x0 + i][y0 - i] == color) {
			r++;
		}
		else if (gridInfo[x0 + i][y0 - i] == 0) {
		}
		else {
			if (x0 + i > x) {
				goto flag;
			}
			r = 0;
			x0 = x0 + i + 1;
			y0 = y0 - i - 1;
			i = -1;
		}
		if (i == 5) {
			x0 = x0 + 6;
			y0 = y0 - 6;
		}
	}
	m_road[r]++;
	while (x0 <= rb) {
		if (gridInfo[x0][y0] == -color) {
			break;
		}
		else if (gridInfo[x0][y0] == color) {
			if (gridInfo[x0 - 6][y0 + 6] == 0) {
				r++;
				m_road[r]++;
			}
			else {
				m_road[r]++;
			}
		}
		else {
			if (gridInfo[x0 - 6][y0 + 6] == 0)
				m_road[r]++;
			else {
				r--;
				m_road[r]++;
			}
		}
		x0++;
		y0--;
	}
flag:
	for (int i = 1; i <= 6; i++) {
		m_benefit += (m_road[i] * (1 - weight) * Score_myroad[i] - m_road[i] * (1 - weight) * Score_myroad[i - 1]);
	}
	x0 = lb;
	y0 = x - lb + y;
	gridInfo[x][y] = 0;
	r = 0;
	for (int i = 0; i <= 5; i++) {
		if (x0 + i > rb) {
			goto flag2;
		}
		if (gridInfo[x0 + i][y0 - i] == 0) {
		}
		else if (gridInfo[x0 + i][y0 - i] == -color) {
			r++;
		}
		else {
			if (x0 + i > x) {
				goto flag2;
			}
			r = 0;
			x0 = x0 + i + 1;
			y0 = y0 - i - 1;
			i = -1;
		}
		if (i == 5) {
			x0 += 6;
			y0 -= 6;
		}
	}
	y_road[r]++;
	while (x0 <= rb) {
		if (gridInfo[x0][y0] == color) {
			break;
		}
		else if (gridInfo[x0][y0] == -color) {
			if (gridInfo[x0 - 6][y0 + 6] == 0) {
				r++;
				y_road[r]++;
			}
			else {
				y_road[r]++;
			}
		}
		else {
			if (gridInfo[x0 - 6][y0 + 6] == 0)
				y_road[r]++;
			else {
				r--;
				y_road[r]++;
			}
		}
		x0++;
		y0--;
	}
flag2:
	int y_lost = 0;
	for (int i = 1; i <= 5; i++) {
		y_lost += y_road[i] * weight * Score_yourroad[i];//cout<<y_lost<<endl;
	}
	int total_benefit = y_lost + m_benefit;
	gridInfo[x][y] = color;
	if (c) {
		swap_ranges(Score_myroad, Score_myroad + 7, Score_yourroad);
	}
	return total_benefit;
}
int yx(int x, int y, int color, int c) {
	if (c) {
		swap_ranges(Score_myroad, Score_myroad + 7, Score_yourroad);
	}
	int m_road[7] = { 0 };
	int y_road[7] = { 0 };
	int lb, rb;
	int m_benefit = 0, y_benefit;
	if (x + 5 <= 14 && y + 5 <= 14) {
		rb = x + 5;
	}
	if (x + 5 <= 14 && y + 5 > 14) {
		rb = 14 - y + x;
	}
	if (x + 5 > 14 && y + 5 <= 14) {
		rb = 14;
	}
	if (x + 5 > 14 && y + 5 > 14) {
		rb = x + 14 - y;
	}
	if (x - 5 >= 0 && y - 5 >= 0) {
		lb = x - 5;
	}
	if (x - 5 >= 0 && y - 5 < 0) {
		lb = x - y;
	}
	if (x < 5 && y - 5 >= 0) {
		lb = 0;
	}
	if (x < 5 && y - 5 < 0) {
		lb = x - y;
	}
	if (rb > 14)
		rb = 14;
	if (lb < 0)
		lb = 0;
	int x0, y0;
	x0 = lb;
	y0 = y - (x - lb);
	int r = 0;
	for (int i = 0; i <= 5; i++) {
		if (x0 + i > rb) {
			goto flag;
		}
		if (gridInfo[x0 + i][y0 + i] == color) {
			r++;
		}
		else if (gridInfo[x0 + i][y0 + i] == 0) {
		}
		else {
			if (x0 + i > x) {
				goto flag;
			}
			r = 0;
			x0 = x0 + i + 1;
			y0 = y0 + i + 1;
			i = -1;
		}
		if (i == 5) {
			x0 = x0 + 6;
			y0 = y0 + 6;
		}
	}
	m_road[r]++;
	while (x0 <= rb) {
		if (gridInfo[x0][y0] == -color) {
			break;
		}
		else if (gridInfo[x0][y0] == color) {
			if (gridInfo[x0 - 6][y0 - 6] == 0) {
				r++;
				m_road[r]++;
			}
			else {
				m_road[r]++;
			}
		}
		else {
			if (gridInfo[x0 - 6][y0 - 6] == 0)
				m_road[r]++;
			else {
				r--;
				m_road[r]++;
			}
		}
		x0++;
		y0++;
	}
flag:
	for (int i = 1; i <= 6; i++) {
		m_benefit += (m_road[i] * (1 - weight) * Score_myroad[i] - m_road[i] * (1 - weight) * Score_myroad[i - 1]);
	}
	x0 = lb;
	y0 = y - (x - lb);
	gridInfo[x][y] = 0;
	r = 0;
	for (int i = 0; i <= 5; i++) {
		if (x0 + i > rb) {
			goto flag2;
		}
		if (gridInfo[x0 + i][y0 + i] == 0) {
		}
		else if (gridInfo[x0 + i][y0 + i] == -color) {
			r++;
		}
		else {
			if (x0 + i > x) {
				goto flag2;
			}
			r = 0;
			x0 = x0 + i + 1;
			y0 = y0 + i + 1;
			i = -1;
		}
		if (i == 5) {
			x0 += 6;
			y0 += 6;
		}
	}
	y_road[r]++;
	while (x0 <= rb) {
		if (gridInfo[x0][y0] == color) {
			break;
		}
		else if (gridInfo[x0][y0] == -color) {
			if (gridInfo[x0 - 6][y0 - 6] == 0) {
				r++;
				y_road[r]++;
			}
			else {
				y_road[r]++;
			}
		}
		else {
			if (gridInfo[x0 - 6][y0 - 6] == 0)
				y_road[r]++;
			else {
				r--;
				y_road[r]++;
			}
		}
		x0++;
		y0++;
	}
flag2:
	int y_lost = 0;
	for (int i = 1; i <= 5; i++) {
		y_lost += y_road[i] * weight * Score_yourroad[i];//cout<<y_lost<<endl;
	}
	int total_benefit = y_lost + m_benefit;
	gridInfo[x][y] = color;
	if (c) {
		swap_ranges(Score_myroad, Score_myroad + 7, Score_yourroad);
	}
	return total_benefit;
}
int numn[3] = { 7 ,0,1 };
void Evaluate()
{
	memset(Number_of_wroad, 0, sizeof Number_of_wroad);
	memset(Number_of_broad, 0, sizeof Number_of_broad);
	//	
	for (int i = 0; i < GRIDSIZE; ++i) {
		for (int j = 0; j < (GRIDSIZE - 5); j++) {
			int num = numn[gridInfo[i][j] + 1] + numn[gridInfo[i][j + 1] + 1] + numn[gridInfo[i][j + 2] + 1] + numn[gridInfo[i][j + 3] + 1] + numn[gridInfo[i][j + 4] + 1] + numn[gridInfo[i][j + 5] + 1];
			if (num == 0 || (num > 6 && num % 7 != 0))//invalid
				continue;
			else if (num < 7) {//这条路为黑色
				Number_of_broad[num]++;
			}
			else {//这条路为白色
				Number_of_wroad[num / 7]++;
			}
		}
	}
	for (int i = 0; i < (GRIDSIZE - 5); ++i) {
		for (int j = 0; j < (GRIDSIZE); j++) {
			int num = numn[gridInfo[i][j] + 1] + numn[gridInfo[i + 1][j] + 1] + numn[gridInfo[i + 2][j] + 1] + numn[gridInfo[i + 3][j] + 1] + numn[gridInfo[i + 4][j] + 1] + numn[gridInfo[i + 5][j] + 1];
			if (num == 0 || (num > 6 && num % 7 != 0))//invalid
				continue;
			else if (num < 7) {//这条路为黑色
				Number_of_broad[num]++;
			}
			else {//这条路为白色
				Number_of_wroad[num / 7]++;
			}
		}
	}
	for (int i = 0; i < (GRIDSIZE - 5); ++i) {
		for (int j = 0; j < (GRIDSIZE - 5); j++) {
			int num = numn[gridInfo[i][j] + 1] + numn[gridInfo[i + 1][j + 1] + 1] + numn[gridInfo[i + 2][j + 2] + 1] + numn[gridInfo[i + 3][j + 3] + 1] + numn[gridInfo[i + 4][j + 4] + 1] + numn[gridInfo[i + 5][j + 5] + 1];
			if (num == 0 || (num > 6 && num % 7 != 0))//invalid
				continue;
			else if (num < 7) {//这条路为黑色
				Number_of_broad[num]++;
			}
			else {//这条路为白色
				Number_of_wroad[num / 7]++;
			}
		}
	}
	for (int i = 5; i < (GRIDSIZE); ++i) {
		for (int j = 0; j < (GRIDSIZE - 5); j++) {
			int num = numn[gridInfo[i][j] + 1] + numn[gridInfo[i - 1][j + 1] + 1] + numn[gridInfo[i - 2][j + 2] + 1] + numn[gridInfo[i - 3][j + 3] + 1] + numn[gridInfo[i - 4][j + 4] + 1] + numn[gridInfo[i - 5][j + 5] + 1];
			if (num == 0 || (num > 6 && num % 7 != 0))//invalid
				continue;
			else if (num < 7) {//这条路为黑色
				Number_of_broad[num]++;
			}
			else {//这条路为白色
				Number_of_wroad[num / 7]++;
			}
		}
	}
}

int ccc = 0;
int black_white_score = 0;
int black_score = 0;
int white_score = 0;

double evaluate_e() {
	return (1.0 * (black_score) / black_white_score);
}
int get_value() {

	Evaluate();
	int ans = 0;
	for (int i = 0; i <= 6; ++i) {
		if (!ccc) {//我方为白 
			white_score += Number_of_wroad[i] * Score_myroad[i];
			black_score += Number_of_broad[i] * Score_yourroad[i];
		}
		else {
			white_score += Number_of_wroad[i] * Score_yourroad[i];
			black_score += Number_of_broad[i] * Score_myroad[i];
		}
		ans = white_score - black_score;
		black_white_score = white_score + black_score;
	}
	return ans;
}
double get_value2(int x, int y, int color, int c) {
	double ans = 0;
	ans = heng(x, y, color, c) + shu(x, y, color, c) + yx(x, y, color, c) + zx(x, y, color, c);
	return ans;
}
void square(int gridInfo[20][15], int& x0, int& y0, int& x1, int& y1) {
	x0 = 20;
	y0 = 20;
	x1 = -1;
	y1 = -1;
	for (int i = 0; i <= 14; i++) {
		for (int j = 0; j <= 14; j++) {
			if (gridInfo[i][j]) {
				if (i <= x0) {
					x0 = i;
				}
				if (i >= x1) {
					x1 = i;
				}
				if (j <= y0) {
					y0 = j;
				}
				if (j >= y1) {
					y1 = j;
				}
			}
			else continue;
		}
	}
	if (x1 == -1) {
		x0 = 6;
		x1 = 11;
		y0 = 6;
		y1 = 11;
		return;
	}
	if (y0 - 2 >= 0)y0 = y0 - 2;
	else y0 = 0;
	if (x0 - 2 >= 0)x0 = x0 - 2;
	else x0 = 0;
	if (y1 + 2 <= 14) y1 = y1 + 2;
	else y1 = 14;
	if (x1 + 2 <= 14) x1 = x1 + 2;
	else x1 = 14;
}
double max(double a, double b) {
	return a > b ? a : b;
}
double min(double a, double b) {
	return a < b ? a : b;
}
time_t tim = time(NULL);
clock_t clo = clock();
int Count = 0;
int X0, Y0, X1, Y1;
int xx0, yy0, xx1, yy1;
int lo = 0;
double total_value = 0; int turnID;
void all(int x0, int y0, int x1, int y1, battletree* root, int depth) {
	int dd = 0;
	if ((x1 - x0 + 1) * (y1 - y0 + 1) <= 56) dd = 3;
	else dd = 2;
	if (turnID == 2)dd = 2;
	if (depth == dd) {
		if (root->color == grid_black)
		{
			root->alpha = total_value;
		}
		else {
			root->beta = total_value;
		}
		return;
	}
	int colo = root->color;
	for (int i = x0; i <= x1; i++) {
		for (int j = y0; j <= y1; j++) {
			if (!gridInfo[i][j]) gridInfo[i][j] = colo;
			else continue;
			for (int a = i; a <= x1; a++) {
				int ppp;
				if (a == i)ppp = j;
				else ppp = y0;
				for (int b = ppp; b <= y1; b++) {
					if (gridInfo[a][b]) continue;
					Count++;
					if (lo) {
						if (depth == 1) {
							X0 = i;
							Y0 = j;
							X1 = a;
							Y1 = b;
						}
						return;
					}
					double temp;
					if (root->color == grid_white) {
						root->son = new battletree;
						root->son->color = grid_black;
						root->son->beta = root->beta;
						temp = get_value2(i, j, root->color, ccc);
						gridInfo[a][b] = colo;
						temp += get_value2(a, b, root->color, ccc);
						total_value += temp;
						all(x0, y0, x1, y1, root->son, depth + 1);
						if (depth == 1 && root->beta < root->son->alpha) {
							X0 = i;
							Y0 = j;
							X1 = a;
							Y1 = b;
						}
						root->beta = max(root->beta, root->son->alpha);
						total_value -= temp;
					}
					else {
						temp = get_value2(i, j, root->color, abs(ccc - 1));
						gridInfo[a][b] = colo;
						temp += get_value2(a, b, root->color, abs(ccc - 1));
						total_value -= temp;
						root->son = new battletree;
						root->son->color = grid_white;
						root->son->alpha = root->alpha;
						all(x0, y0, x1, y1, root->son, depth + 1);
						if (depth == 1 && root->alpha > root->son->beta) {
							X0 = i;
							Y0 = j;
							X1 = a;
							Y1 = b;
						}
						root->alpha = min(root->alpha, root->son->beta);
						total_value += temp;
					}
					if (root->alpha <= root->beta) {
						gridInfo[a][b] = 0;
						gridInfo[i][j] = 0;
						return;
					}
					gridInfo[a][b] = 0;
				}
			}
			gridInfo[i][j] = 0;
		}
	}
	return;
}
// 在坐标处落子，检查是否合法或模拟落子
bool ProcStep(int x0, int y0, int x1, int y1, int grid_color, bool check_only)
{
	if (x1 == -1 || y1 == -1) {
		if (!inMap(x0, y0) || gridInfo[x0][y0] != grid_blank)
			return false;
		if (!check_only) {
			gridInfo[x0][y0] = grid_color;
		}
		return true;
	}
	else {
		if ((!inMap(x0, y0)) || (!inMap(x1, y1)))
			return false;
		if (gridInfo[x0][y0] != grid_blank || gridInfo[x1][y1] != grid_blank)
			return false;
		if (!check_only) {
			gridInfo[x0][y0] = grid_color;
			gridInfo[x1][y1] = grid_color;
		}
		return true;
	}
}

int main()
{

	srand(tim);
	int x0, y0, x1, y1;

	// 分析自己收到的输入和自己过往的输出，并恢复棋盘状态

	cin >> turnID;
	currBotColor = grid_white; // 先假设自己是白方
	for (int i = 0; i < turnID; i++)
	{
		// 根据这些输入输出逐渐恢复状态到当前回合
		cin >> x0 >> y0 >> x1 >> y1;
		if (x0 == -1)
			currBotColor = grid_black; // 第一回合收到坐标是-1, -1，说明我是黑方
		if (x0 >= 0)
			ProcStep(x0, y0, x1, y1, -currBotColor, false); // 模拟对方落子
		if (i < turnID - 1) {
			cin >> x0 >> y0 >> x1 >> y1;
			if (x0 >= 0)
				ProcStep(x0, y0, x1, y1, currBotColor, false); // 模拟己方落子
		}
	}



	/************************************************************************************/
	/***在下面填充你的代码，决策结果（本方将落子的位置）存入startX、startY、resultX、resultY中*****/
	//下面仅为随机策略的示例代码，且效率低，可删除
	int startX, startY, resultX, resultY;
	int beginPos[GRIDSIZE * GRIDSIZE][2], possiblePos[GRIDSIZE * GRIDSIZE][2];
	bool selfFirstBlack = (turnID == 1 && currBotColor == grid_black);//本方是黑方先手
	int posCount = 0, choice0, choice1;
	for (int i = 0; i < GRIDSIZE; ++i) {
		for (int j = 0; j < GRIDSIZE; ++j) {
			if (gridInfo[i][j] == grid_blank) {
				beginPos[posCount][0] = i;
				beginPos[posCount][1] = j;
				possiblePos[posCount][0] = i;
				possiblePos[posCount++][1] = j;
			}
		}
	}
	get_value();
	double weight2 = evaluate_e();
	weight = weight2;
	if (turnID == 1)weight = 0.5;
	if (currBotColor == grid_black) {
		ccc = 1;
	}
	if (ccc) {
		weight2 = 1 - weight2;
		weight = 1 - weight;
	}
	// 做出决策
	if (posCount > 0) {
		if (currBotColor == grid_white) {
			Score_yourroad[1] = 2;
			Score_yourroad[2] = 25;
		}
		if (turnID <= 3) {
			Score_myroad[3] = 60;
			Score_myroad[4] = 60;
			Score_myroad[5] = 5;
		}
		battletree* root = new battletree(currBotColor);
		int lx, doy, rx, upy;
		square(gridInfo, lx, doy, rx, upy);
		all(lx, doy, rx, upy, root, 1);
		startX = X0;
		startY = Y0;
		resultX = X1;
		resultY = Y1;
	}
	else {
		startX = -1;
		startY = -1;
		resultX = -1;
		resultY = -1;
	}
	/****在上方填充你的代码，决策结果（本方将落子的位置）存入startX、startY、resultX、resultY中****/
	/************************************************************************************/

	// 决策结束，向平台输出决策结果
	if (selfFirstBlack) {
		resultX = -1;
		resultY = -1;
	}
	cout << startX << ' ' << startY << ' ' << resultX << ' ' << resultY << endl;
	return 0;
}