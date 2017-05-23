#include"Game.h"

Game::Game(){
	start();
	turn = 0;
	black = 0;
	white = 0;
	board[3][3] = 1;
	board[3][4] = 2;
	board[4][3] = 2;
	board[4][4] = 1;

	const Font fonts(30);
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
		board_draw();
		if (Input::KeySpace.clicked) {
			state = State::CLEAR;
		}
		break;
	case State::CLEAR:
		if (Input::KeySpace.clicked) {
			shoki();
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
		Rect(0, 0, 640, 480).draw(Palette::Green);
		font(L"Reversi").draw(225, 100,Palette::White);
		font(L"R  v  r  i").draw(225, 100, Palette::Black);

		font(L"Push Space Start!").draw(130, 350);
		break;
	case State::GAME:
		Rect(0, 0, 640, 480).draw(Palette::Black);

		Rect(0, 0, 440, 480).draw(Color(106, 64, 40));

		Rect(0, 20, 440, 440).draw(Palette::Green);

		line_x = 0;
		line_y = 0;
		for (int i = 0; i < 9; i++) {
			Line(line_x, 20, line_y, 460).draw(Palette::Black);
			line_x += 55;
			line_y += 55;
		}

		line_x = 20;
		line_y = 20;

		for (int i = 0; i < 9; i++) {
			Line(0, line_x, 440, line_y).draw(Palette::Black);
			line_x += 55;
			line_y += 55;
		}
		

		break;
	case State::CLEAR:
		font(L"Result").draw(235, 100);
		if (white > black) {
			font(L"White Win!").draw(190, 225);
		}
		if (white < black) {
			font(L"Black Win!").draw(190, 225);
		}
		if (white == black) {
			font(L"Draw!").draw(240, 225);
		}
		font(L"Push Space Menu").draw(130, 350);
		break;
	}
}

void Game::check(int board_x, int board_y) {
	const Circle circle(board_x * 55 + 27, board_y * 55 + 48, 24);
	const bool c = circle.leftReleased;
	if (c == 1) {
		switch (board[board_x][board_y]) {
		case 0:

			if (turn % 2 == 0) {
				board[board_x][board_y] = 1;
				revers(board_x, board_y, board[board_x][board_y]);
				if (flag == 0) {
					board[board_x][board_y] = 0;
					turn--;
				}
				turn++;
				
			}else if (turn % 2 != 0) {
				board[board_x][board_y] = 2;
				revers(board_x, board_y, board[board_x][board_y]);
				if (flag == 0) {
					board[board_x][board_y] = 0;
					turn--;
				}
				turn++;
			}
			break;
		}

	}
}

void Game::board_draw() {
	const Rect path(440, 300, 199, 100);
	path.draw(Palette::White);
	fonts(L"PATH").draw(500, 330,Palette::Black);
	const bool r = path.leftReleased;
	if (r == 1) {
		turn++;
	}
	result();
	fonts(L"White:", white).draw(455, 180);
	fonts(L"Black:", black).draw(457, 220);
	if (turn % 2 == 0) {
		fonts(L"White turn").draw(455, 100);
	}
	else {
		fonts(L"Black turn").draw(455, 100);
	}
	for (board_x = 0; board_x < 8; board_x++) {
		for (board_y = 0; board_y < 8; board_y++) {
			check(board_x, board_y);
			if (board[board_x][board_y] == 1) {
				Circle(board_x * 55 + 27, board_y * 55 + 48, 24).draw(Palette::White);
			}
			if (board[board_x][board_y] == 2) {
				Circle(board_x * 55 + 27, board_y * 55 + 48, 24).draw(Palette::Black);
			}
		}
	}
}

void Game::revers(int board_x,int board_y,int now) {
	int x, y, count = 0;
	x = board_x;
	y = board_y;
	flag = 0;
	//©
	while (board_x != 0) {
		board_x--;
		count++;
		if (board[board_x][board_y] == now) {
			board_x = x;
			while (count!=0){
				board_x--;
				count--;
				if (board[board_x][board_y] != 0&&board[board_x][board_y]!=now) {
					board[board_x][board_y] = now;
					flag++;
				}
				if (board[board_x][board_y] == 0) {
					break;
				}
			}
		break;
		}
	}
	//¨
	board_x = x;
	count = 0;
	while (board_x != 7) {
		board_x++;
		count++;
		if (board[board_x][board_y] == now) {
			board_x = x;
			while (count != 0) {
				board_x++;
				count--;
				if (board[board_x][board_y] != 0 && board[board_x][board_y] != now) {
					board[board_x][board_y] = now;
					flag++;
				}
				if (board[board_x][board_y] == 0) {
					break;
				}
			}
			break;
		}
	}

	//ª
	board_x = x;
	count = 0;
	while (board_y != 0) {
		board_y--;
		count++;
		if (board[board_x][board_y] == now) {
			board_y = y;
			while (count != 0) {
				board_y--;
				count--;
				if (board[board_x][board_y] != 0 && board[board_x][board_y] != now) {
					board[board_x][board_y] = now;
					flag++;
				}
				if (board[board_x][board_y] == 0) {
					break;
				}
			}
			break;
		}
	}
	//«
	board_y = y;
	count = 0;
	while (board_y != 7) {
		board_y++;
		count++;
		if (board[board_x][board_y] == now) {
			board_y = y;
			while (count != 0) {
				board_y++;
				count--;
				if (board[board_x][board_y] != 0 && board[board_x][board_y] != now) {
					board[board_x][board_y] = now;
					flag++;
				}
				if (board[board_x][board_y] == 0) {
					break;
				}
			}
			break;
		}
	}
	//©ª
	board_x = x;
	board_y = y;
	count = 0;
	while (board_x != 0 && board_y != 0) {
		board_x--;
		board_y--;
		count++;
		if (board[board_x][board_y] == now) {
			board_x = x;
			board_y = y;
			while (count != 0) {
				board_x--;
				board_y--;
				count--;
				if (board[board_x][board_y] == 0) {
					break;
				}
				if (board[board_x][board_y] != 0 && board[board_x][board_y] != now) {
					board[board_x][board_y] = now;
					flag++;
				}
			}
			break;
		}
	}
	//¨ª
	board_x = x;
	board_y = y;
	count = 0;
	while (board_x != 7 && board_y != 0) {
		board_x++;
		board_y--;
		count++;
		if (board[board_x][board_y] == now) {
			board_x = x;
			board_y = y;
			while (count != 0) {
				board_x++;
				board_y--;
				count--;
				if (board[board_x][board_y] == 0) {
					break;
				}
				if (board[board_x][board_y] != 0 && board[board_x][board_y] != now) {
					board[board_x][board_y] = now;
					flag++;
				}
			}
			break;
		}
	}
	//©«
	board_x = x;
	board_y = y;
	count = 0;
	while (board_x != 0 && board_y != 7) {
		board_x--;
		board_y++;
		count++;
		if (board[board_x][board_y] == now) {
			board_x = x;
			board_y = y;
			while (count != 0) {
				board_x--;
				board_y++;
				count--;
				if (board[board_x][board_y] == 0) {
					break;
				}
				if (board[board_x][board_y] != 0 && board[board_x][board_y] != now) {
					board[board_x][board_y] = now;
					flag++;
				}
			}
			break;
		}
	}
	//¨«
	board_x = x;
	board_y = y;
	count = 0;
	while (board_x != 7 && board_y != 7) {
		board_x++;
		board_y++;
		count++;
		if (board[board_x][board_y] == now) {
			board_x = x;
			board_y = y;
			while (count != 0) {
				board_x++;
				board_y++;
				count--;
				if (board[board_x][board_y] == 0) {
					break;
				}
				if (board[board_x][board_y] != 0 && board[board_x][board_y] != now) {
					board[board_x][board_y] = now;
					flag++;
				}
			}
			break;
		}
	}
}

void Game::result() {
	white = 0;
	black = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j]==1) {
				white++;
			}
			if (board[i][j] == 2) {
				black++;
			}
		}
	}
	if (white + black == 64 || white==0 || black==0) {
		state = State::CLEAR;
	}
}

void Game::shoki() {
	turn = 0;
	black = 0;
	white = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = 0;
		}
	}
	board[3][3] = 1;
	board[3][4] = 2;
	board[4][3] = 2;
	board[4][4] = 1;
}