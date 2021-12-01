#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Window/Event.h>
#include <SFML/Graphics/Sprite.h>
#include "Hurdle.h"

#define RADIUS 15.f
#define SCALE (sfVector2f) { 1.f, .5f }
#define JUMP_TIME 1.f
#define TIME_ANIMATION .5f
#define INVULNERABILITY 2.f
#define HURT_TIME .5f
#define DISTANCE 20000.f
#define INITIAL_SPEED 100.f

typedef struct
{
	int isJumping;
	int isHurt;
	float jump;
	float hurt;
	float maxAnimation;
	float animation;
	float distance;
	float speed;
	float speedMax;
	float backPos[2];
	float totalTime;
	float speedUpTime;
	Hurdle* hurdles;
	sfVector2f position;
	sfKeyCode button;
	sfSprite* sprite;
	sfSprite* background;
	sfSprite* track;
	sfCircleShape* shadow;
} Player;

Player* Player_create(char* _fileName, sfKeyCode _key, sfVector2f _position, sfVector2f _center);

void Player_handleEvent(Player* _player, sfEvent _event);

void Player_update(Player* _player);

void Player_draw(Player* _player, sfRenderWindow* _window);

#endif // !PLAYER_H
