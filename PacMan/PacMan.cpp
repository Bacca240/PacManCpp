#include <iostream>
#include <stdio.h>
#include <string>
#include <windows.h>
#include <vector>

using namespace std;

char map[18][32]=
{
	"+#############################+",
	"#                             #",
	"#                             #",
	"### ########### ##   ##########",
	"#   #                         #",
	"# # #### #  #           #     #",
	"# #      #  # ####  #   #  #  #",
	"# # ######  # #      ## #     #",
	"# #           ####  #      #  #",
	"# ###### ###         ##       #",
	"#          ######  ####### ####",
	"#                             #",
	"## ### ####      ###   ########",
	"#                             #",
	"#                             #",
	"#                             #",
	"#                             #",
	"+#############################+"
};

char tmpMap[18][32];

void showMap()
{
	for (int i = 0; i < 18; i++)
		printf("%s\n", map[i]);
}

void gotoxy(int x, int y)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x,y };
	SetConsoleCursorPosition(hStdout, position);
}

class Entity {
public:
	Entity(int x, int y) {
		this ->x = x;
		this ->y = y;
	}
	void moveX(int p)
	{
		if (map[y][x + p] == ' ')
		{
			x += p;
		}
	}
	void moveY(int p)
	{
		if (map[y+p][x] == ' ')
		{
			y += p;
		}
	}
	int getX()
	{
		return x;
	}
	int getY()
	{
		return y;
	}
	void draw(char p)
	{
		map[x][y] = p;
		gotoxy(x, y);
		printf("%c", p);
	}
private:
	int x, y;
};

struct walk {
	int walk_count, x, y, back;
};

struct target {
	int x, y;
};

vector<target> walk_queue;
vector<walk> BFSArray;
void addArray(int x, int y, int wc, int back)
{
	if (tmpMap[y][x] == ' ' || tmpMap[y][x] == 'X')
	{
		tmpMap[y][x] = '#';
		walk tmp;
		tmp.x = x;
		tmp.y = y;
		tmp.walk_count = wc;
		tmp.back = back;
		BFSArray.push_back(tmp);
	}
}



void FindPath(int startX, int startY, int x, int y)
{
	memcpy(tmpMap, map, sizeof(map));
	BFSArray.clear();
	walk tmp;
	tmp.x = startX;
	tmp.y = startY;
	tmp.walk_count = 0;
	tmp.back = -1;
	BFSArray.push_back(tmp);
	int i = 0;
	while (i < BFSArray.size()) {
		if (BFSArray[i].x == x && BFSArray[i].y == y) {
			walk_queue.clear();
			target tmp2;
			while (BFSArray[i].walk_count != 0) {
				tmp2.x = BFSArray[i].x;
				tmp2.y = BFSArray[i].y;
				walk_queue.push_back(tmp2);
				i = BFSArray[i].back;
			}
			break;
		}
		addArray(BFSArray[i].x + 1, BFSArray[i].y, BFSArray[i].walk_count+1, i);
		addArray(BFSArray[i].x - 1, BFSArray[i].y, BFSArray[i].walk_count+1, i);
		addArray(BFSArray[i].x, BFSArray[i].y + 1, BFSArray[i].walk_count+1, i);
		addArray(BFSArray[i].x, BFSArray[i].y - 1, BFSArray[i].walk_count+1, i);
		addArray(BFSArray[i].x + 1, BFSArray[i].y - 1, BFSArray[i].walk_count+1, i);
		addArray(BFSArray[i].x + 1, BFSArray[i].y + 1, BFSArray[i].walk_count+1, i);
		addArray(BFSArray[i].x - 1, BFSArray[i].y - 1, BFSArray[i].walk_count+1, i);
		addArray(BFSArray[i].x - 1, BFSArray[i].y + 1, BFSArray[i].walk_count+1, i);
		i++;
	}
	BFSArray.clear();
}

	int main()
{
	bool isRunning = true;
	int x = 10, y = 10; //Caracter
	int oldx, oldy;
	int enemyX = 1, enemyY = 1;
	int points = 0;
	char difficulty;
	int speed = 3;
	cout << "Alege dificultatea (e, n ,h): ";
	cin >> difficulty;
	if (difficulty == 'n')
	{
		speed = 2;
	}
	else if (difficulty == 'h')
	{
		speed = 1;
	}
	system("cls");
	showMap();
	gotoxy(x, y);
	cout << "H";
	int frame = 0;
	FindPath(enemyX, enemyY, x, y);
	while (isRunning)
	{
		gotoxy(x, y);
		cout << " ";
		oldx = x;
		oldy = y;
		if (GetAsyncKeyState(VK_UP)) {
			if (map[y - 1][x] == 'X')
			{
				y--;
				points++;
			}
			else if (map[y - 1][x] == ' ')
			{
				y--;
			}	
		}
		if (GetAsyncKeyState(VK_DOWN)) {
			if (map[y + 1][x] == 'X')
			{
				y++;
				points++;
			}
			else if (map[y + 1][x] == ' ')
			{
				y++;
			}
		}
		if (GetAsyncKeyState(VK_LEFT)) {
			if (map[y][x - 1] == 'X')
			{
				x--;
				points++;
			}
			else if (map[y][x - 1] == ' ')
			{
				x--;
			}
		}
		if (GetAsyncKeyState(VK_RIGHT)) {
			if (map[y][x+1] == 'X')
			{
				x++;
				points++;
			}
			else if (map[y][x+1] == ' ')
			{
				x++;
			}
		}
		if (oldx != x || oldy != y) {
			FindPath(enemyX, enemyY, x, y);
		}
			
		gotoxy(x, y);
		cout << "H";
		map[enemyY][enemyX] = 'X';
		gotoxy(enemyX, enemyY);
		cout << "X";
		if (frame % speed == 0 && walk_queue.size() != 0) {
			enemyX = walk_queue.back().x;
			enemyY = walk_queue.back().y;
			walk_queue.pop_back();
		}
		gotoxy(enemyX, enemyY);
		cout << "E";
		if (enemyX == x && enemyY == y)
		{
			break;
		}
		gotoxy(32, 18);
		gotoxy(32, 1);
		cout << points;
		Sleep(100);
		frame++;
	}
	system("cls");
	cout << "Ai pierdut! Scorul tau a fost: " << points;
	cin.get();
	cin.get();
	cin.get();
	cin.get();
    return 0;
}


	

	