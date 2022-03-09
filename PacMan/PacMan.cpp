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

	int main()
{
	showMap();
    return 0;
}


