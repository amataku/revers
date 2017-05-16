#include"Game.h"

Game::Game(){
	start();
	aaw = 0;
	aab = 0;
	abw = 0;
	abb = 0;
	turn = 0;
}

void Game::start() {
	state = State::START;

}

void Game::update() {
	switch (state)
	{
	case State::START:
		if (Input::KeySpace.clicked) {
			state = State::GAME;
		}
		break;
	case State::GAME:
		check();
		/*if (Input::KeySpace.clicked) {
			state = State::CLEAR;
		}*/
		break;
	case State::CLEAR:
		if (Input::KeySpace.clicked) {
			state = State::START;
			start();
		}
		break;
	}
}

void Game::draw() {
	static Font font(30);

	switch (state)
	{
	case State::START:
		font(L"Reversi").draw(200, 100);
		font(L"Push Space").draw(50, 200);
		break;
	case State::GAME:
		Rect(0, 0, 640, 480).draw(Palette::Black);

		Rect(0, 0, 440, 480).draw(Color(106, 64, 40));

		Rect(0, 20, 440, 440).draw(Palette::Green);

		Line(0, 20, 0, 460).draw(Palette::Black);
		Line(55, 20, 55, 460).draw(Palette::Black);
		Line(110, 20, 110, 460).draw(Palette::Black);
		Line(165, 20, 165, 460).draw(Palette::Black);
		Line(220, 20, 220, 460).draw(Palette::Black);
		Line(275, 20, 275, 460).draw(Palette::Black);
		Line(330, 20, 330, 460).draw(Palette::Black);
		Line(385, 20, 385, 460).draw(Palette::Black);
		Line(440, 20, 440, 460).draw(Palette::Black);

		Line(0, 20, 440, 20).draw(Palette::Black);
		Line(0, 75, 440, 75).draw(Palette::Black);
		Line(0, 130, 440, 130).draw(Palette::Black);
		Line(0, 185, 440, 185).draw(Palette::Black);
		Line(0, 240, 440, 240).draw(Palette::Black);
		Line(0, 295, 440, 295).draw(Palette::Black);
		Line(0, 350, 440, 350).draw(Palette::Black);
		Line(0, 405, 440, 405).draw(Palette::Black);
		Line(0, 460, 440, 460).draw(Palette::Black);

		break;
	case State::CLEAR:
		font(L"Result").draw(200, 100);
		font(L"Push Space ").draw(50, 200);
		break;
	}
}

void Game::check() {
	const Circle circle1(27, 48, 24);
	const Circle circle2(82, 48, 24);
	const bool raa = circle1.leftPressed;
	const bool rab = circle2.leftPressed;
	if (turn % 2 == 0) {
		if (aab == 0) {
			if (raa == true) {
				aaw = 1;
				turn++;
			}
		}
	}
	if (aaw == 1) {
		circle1.draw(Palette::White);
	}
	if (turn % 2 != 0) {
		if (aaw == 0) {
			if (raa == true) {
				aab = 1;
				turn++;
			}
		}
	}
	if (aab == 1) {
		circle1.draw(Palette::Black);
	}
	if (turn % 2 == 0) {
		if (abb == 0) {
			if (rab == true) {
				abw = 1;
				turn++;
			}
		}
	}
	if (abw == 1) {
		circle2.draw(Palette::White);
	}
	if (turn % 2 != 0) {
		if (abw == 0) {
			if (rab == true) {
				abb = 1;
				turn++;
			}
		}
	}
	if (abb == 1) {
		.draw(Palette::Black);
	}
}