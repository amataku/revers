#pragma once

#include<Siv3D.hpp>

class Game {
public:
	int aaw;
	int aab;
	int abw;
	int abb;
	int turn;
	enum State {
		START,
		GAME,
		CLEAR,
	};
	Game();
	void start();

	void update();
	void draw();

	void input();
	void check();

private:
	State state;
};
