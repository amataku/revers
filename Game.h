#pragma once

#include<Siv3D.hpp>

class Game {
public:
	int turn;
	int board[8][8] = { 0 };
	enum State {
		START,
		GAME,
		CLEAR,
	};
	Game();
	void start();
	void shoki();

	void update();
	void draw();

	void input();
	void check(int ,int);

	void board_draw();
	void revers(int,int,int);

	void result();

private:
	State state;
	int line_x;
	int line_y;
	int board_x;
	int board_y;
	int flag;
	int white;
	int black;
	const Font fonts;
};
