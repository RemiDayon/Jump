#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <stdlib.h>
#include "World.h"
#include "Utility.h"
#include <SFML/Graphics/Font.h>
#include <SFML/Graphics/Text.h>
#include <stdio.h>
#include <string.h>

#define OFFSET 192.f
#define HEIGHT_OFFSET 50.f
#define GOLD (sfColor) {178, 151, 0, 255}
#define SILVER (sfColor) {177, 189, 201, 255}
#define CUIVRE (sfColor) {179, 103, 0, 255}

void FloatToTime(char* str, float _time)
{
	char st[20];

	int m = ((int)_time) / 60;
	int s = ((int)_time) % 60;
	int c = (_time - ((int)_time))*1000;
	
	sprintf(st, "%d'%d''%d\n", m, s, c);
	strcat(str, st);
}

void FloatToSpeed(char* str, float _speed)
{
	char st[10];

	int speed = ((int)_speed / 32.f * 3.6f);
	
	sprintf(st, "%d km/h", speed);
	strcat(str, st);
}

World* World_create()
{
	World* world = malloc(sizeof(World));

	// creates the four players
	world->player[0] = Player_create("resources/bonhomme.png", sfKeyA, 
		(sfVector2f) { (SCREEN_WIDTH - OFFSET) * 0 / (PLAYER_COUNT - 1) + OFFSET / 2.f, SCREEN_HEIGHT - HEIGHT_OFFSET }, (sfVector2f) { 32, 64 });
	world->player[1] = Player_create("resources/shark.png", sfKeyG,
		(sfVector2f) { (SCREEN_WIDTH - OFFSET) / (PLAYER_COUNT - 1) + OFFSET / 2.f, SCREEN_HEIGHT - HEIGHT_OFFSET }, (sfVector2f) { 32, 48 });
	world->player[2] = Player_create("resources/obama2.png", sfKeyUp,
		(sfVector2f) { (SCREEN_WIDTH - OFFSET) * 2 / (PLAYER_COUNT - 1) + OFFSET / 2.f, SCREEN_HEIGHT - HEIGHT_OFFSET }, (sfVector2f) { 32, 48 });
	world->player[3] = Player_create("resources/waluigi.png", sfKeyNumpad7,
		(sfVector2f) { (SCREEN_WIDTH - OFFSET) * 3 / (PLAYER_COUNT - 1) + OFFSET / 2.f, SCREEN_HEIGHT - HEIGHT_OFFSET }, (sfVector2f) { 32, 64 });
/*	world->player[4] = Player_create("resources/snek.png", sfKeyW,
		(sfVector2f) { (SCREEN_WIDTH - OFFSET) * 4/ (PLAYER_COUNT - 1) + OFFSET / 2.f, SCREEN_HEIGHT - HEIGHT_OFFSET }, (sfVector2f) { 32, 64 });
	world->player[5] = Player_create("resources/Naruto.png", sfKeySlash,
		(sfVector2f) {	(SCREEN_WIDTH - OFFSET) * 5/ (PLAYER_COUNT - 1) + OFFSET / 2.f, SCREEN_HEIGHT - HEIGHT_OFFSET }, (sfVector2f) { 32, 48 });
	world->player[6] = Player_create("resources/tank.png", sfKeyNum1,
		(sfVector2f) { (SCREEN_WIDTH - OFFSET) * 6 / (PLAYER_COUNT - 1) + OFFSET / 2.f, SCREEN_HEIGHT - HEIGHT_OFFSET }, (sfVector2f) { 32, 64 });
	world->player[7] = Player_create("resources/waluigi.png", sfKeyNumpad3,
		(sfVector2f) { (SCREEN_WIDTH - OFFSET) * 7 / (PLAYER_COUNT - 1) + OFFSET / 2.f, SCREEN_HEIGHT - HEIGHT_OFFSET }, (sfVector2f) { 32, 64 });
	world->player[8] = Player_create("resources/snek.png", sfKeyRBracket,
		(sfVector2f) { (SCREEN_WIDTH - OFFSET) * 8 / (PLAYER_COUNT - 1) + OFFSET / 2.f, SCREEN_HEIGHT - HEIGHT_OFFSET }, (sfVector2f) { 32, 64 });
	world->player[9] = Player_create("resources/Naruto.png", sfKeyNum0,
		(sfVector2f) { (SCREEN_WIDTH - OFFSET) * 9 / (PLAYER_COUNT - 1) + OFFSET / 2.f, SCREEN_HEIGHT - HEIGHT_OFFSET }, (sfVector2f) { 32, 48 });
	world->player[10] = Player_create("resources/tank.png", sfKeyR,
		(sfVector2f) { (SCREEN_WIDTH - OFFSET) * 10 / (PLAYER_COUNT - 1) + OFFSET / 2.f, SCREEN_HEIGHT - HEIGHT_OFFSET }, (sfVector2f) { 32, 64 });
	world->player[11] = Player_create("resources/waluigi.png", sfKeyDelete,
		(sfVector2f) { (SCREEN_WIDTH - OFFSET) * 11 / (PLAYER_COUNT - 1) + OFFSET / 2.f, SCREEN_HEIGHT - HEIGHT_OFFSET }, (sfVector2f) { 32, 48 });*/

	sfFont* font = sfFont_createFromFile("resources/dealerplate california.ttf");
	
	for (int x = 0; x < PLAYER_COUNT; x++)
	{
		world->place[x] = sfText_create();
		sfText_setFont(world->place[x], font);
		sfText_setPosition(world->place[x], (sfVector2f) { world->player[x]->position.x, HEIGHT_OFFSET });
		sfText_setCharacterSize(world->place[x], 50);
		sfText_setFillColor(world->place[x], GOLD);	
		sfText_setString(world->place[x], "1");
		sfText_centerOrigin(world->place[x]);
		sfText_setOutlineThickness(world->place[x], 3.f);
		sfText_setOutlineColor(world->place[x], sfBlack);
		world->texts[x] = malloc(sizeof(char) * 50);
	}
	return world;
}

void World_handleEvent(World* _world, sfEvent _event)
{
	for (int x = 0; x < PLAYER_COUNT; x++)
	{
		Player_handleEvent(_world->player[x], _event);
	}
}

void World_update(World* _world)
{
	for (int x = 0; x < PLAYER_COUNT; x++)
	{
		Player_update(_world->player[x]);
		int place = 1;
			
		for (int y = 0; y < PLAYER_COUNT; y++)
		{
			if (_world->player[y]->distance != 0.f)
			{
				if (_world->player[y]->distance < _world->player[x]->distance)
				{
					place++;
				}
			}
			else
			{
				if (_world->player[y]->totalTime < _world->player[x]->totalTime)
				{
					place++;
				}
			}
		}


		if (_world->player[x]->distance == 0.f)
		{
			sprintf(_world->texts[x], "%d\n", place);
			FloatToTime(_world->texts[x], _world->player[x]->totalTime);
			FloatToSpeed(_world->texts[x], _world->player[x]->speedMax);
			sfText_setString(_world->place[x], _world->texts[x]);
			sfText_centerOrigin(_world->place[x]);
			sfText_setPosition(_world->place[x], (sfVector2f) { _world->player[x]->position.x, SCREEN_HEIGHT / 2 });
		}
		else
		{	

			sprintf(_world->texts[x], "%d", place);
			sfText_setString(_world->place[x], _world->texts[x]);
			sfText_centerOrigin(_world->place[x]);
		}

		switch (place)
		{
		case 1:
			sfText_setFillColor(_world->place[x], GOLD);
			break;

		case 2:
			sfText_setFillColor(_world->place[x], SILVER);
			break;

		case 3:
			sfText_setFillColor(_world->place[x], CUIVRE);
			break;

		default:
			sfText_setFillColor(_world->place[x], sfWhite);
			break;
		}
	}
}

void World_draw(World* _world, sfRenderWindow* _window)
{
	for (int x = 0; x < PLAYER_COUNT; x++)
	{
		Player_draw(_world->player[x], _window);
		sfRenderWindow_drawText(_window, _world->place[x], NULL);
	}
}