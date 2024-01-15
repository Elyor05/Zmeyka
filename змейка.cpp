#include <iostream>
#include <conio.h>


bool gameOver;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailx[100], taily[100];
int ntail;
enum edirection { stop = 0 , left, right, up, down };
edirection dir;
void Setup() {// generating all props on the field
	gameOver = false;
	dir = stop;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}
void Draw() {
	system("cls");
	for (int i = 0; i < width + 1;i++) std::cout << "#";//draw upper barier
	std::cout << std::endl;
	
	for (int i = 0; i < height;i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1) std::cout << "#";//right and left barier 
			if (i == y && j == x) std::cout << "0";//змейка
			else if (i == fruitY && j == fruitX) std::cout << "F";//фрукт
			else {
				bool print = false;
				for (int k = 0; k < ntail; k++) {// tail
					if (tailx[k] == j && taily[k] == i) {
						print = true;
						std::cout << 'o';
					}
				}
				if(!print) std::cout << " ";
			}
		}
		std::cout << std::endl;
	}

	for (int i = 0; i < width + 1; i++) std::cout << "#";//draw down barier
	std::cout << std::endl;
	std::cout << "SCORE : " << score << std::endl;
}
void Input() {
	if (_kbhit()) {// control of the snake
		switch (_getch())
		{
		case 'a':
			dir = left;
			break;
		case 'd':
			dir = right;
			break;
		case 's':
			dir = down;
			break;

		case 'w':
			dir = up;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}
void Logic() {
	int prevx = tailx[0], prevy = taily[0];// logic of creating tail
	int prev2x, prev2y;
	tailx[0] = x;
	taily[0] = y;
	for (int i = 1; i < ntail; i++) {
		prev2x = tailx[i];
		prev2y = taily[i];
		tailx[i] = prevx;
		taily[i] = prevy;
		prevx = prev2x;
		prevy = prev2y;
	}
	switch (dir)//movement of snake
	{
	case left:
		x--;
		break;
	case right:
		x++;
		break;
	case up:
		y--;
		break;
	case down:
		y++;
		break;
	}

	for (int i = 0; i < ntail; i++) {// logic of tail
		if (tailx[i] == x && taily[i] == y) {
			gameOver = true;
			std::cout << "GAME OVER!!!";
			std::cout << "DONT EAT YOURSELF!!!";
		}
	}

	if (x == fruitX && y == fruitY) {// regeneration of a new fruit
		score+=10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		ntail++;
	}
}
void logic1() {
	if (x > width || x < 0 || y > height || y < 0) {// logic of barier
		gameOver = true;
		std::cout << "GAME OVER!!!";
		std::cout << "DONT YOU SEE THE FREAKING WALL!? ";
	}
}
void logic2() {
	if (x >= width - 1 )x = 0;// logic of no barier
	else if (x < 0)x = width - 1;
	if (y >= height)y = 0;
	else if (y < 0)y = height - 2;
}
int main()
{
	Setup();// generating all props on the field
	char cond;
	std::cout << "Would you like to play with barier ?" << std::endl;
	std::cout << "Y/N : ";
	std::cin >> cond;
	if (cond == 'Y' || cond == 'y') {
		while (!gameOver) {// work until game is over 
			Draw();
			Input();
			Logic();
			logic1();
		}
	}
	else if (cond == 'N' || cond == 'n') {
		while (!gameOver) {// work until game is over 
			Draw();
			Input();
			Logic();
			logic2();
		}
	}
}