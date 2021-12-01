#include "Game.h"

int main()
{
	srand(time(0));

	Game* game = GameCreate();
	Run(game);

	return 0;
}

