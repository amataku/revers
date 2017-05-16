
#include <Siv3D.hpp>

#include "Game.h"

void Main()
{
	Game game;
	
	while (System::Update())
	{
		game.draw();
		game.update();
	}
}
