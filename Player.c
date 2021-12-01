#include "Player.h"
#include "Utility.h"
#include <stdlib.h>
#include <math.h>

#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/CircleShape.h>
#include <SFML/Graphics/Texture.h>

#define STEP 20.f
#define SPEED_STEP 0.02f
#define SPEED_UP 1.f

Player* Player_create(char* _fileName, sfKeyCode _key, sfVector2f _position, sfVector2f _center)
{
	Player* player = malloc(sizeof(Player));

	player->position = _position;
	player->speedUpTime = 0.f;
	player->totalTime = 0.f;

	// animation speed, increase with player's speed
	player->maxAnimation = TIME_ANIMATION;
	
	// the player starts à 100 m.s
	player->speed = INITIAL_SPEED;
	player->speedMax = 0.f;

	// the player doesn't jump at the begining
	player->isJumping = sfFalse;
	player->jump = 0.f;

	// the player isn't hurt at the begining
	player->isHurt = sfFalse;
	player->hurt = 0.f;

	player->button = _key;
	
	// set run animation at 0
	player->animation = 0.f;

	// loads the sprite
	player->sprite = sfSprite_loadFromFile(_fileName, sfFalse);
	sfSprite_setTextureRect(player->sprite, (sfIntRect) {0, 0, 64, 64});
	sfSprite_setOrigin(player->sprite, _center);
	sfSprite_setPosition(player->sprite, _position);

	sfTexture* background = sfTexture_createFromFile("resources/grass.png", NULL);
	sfTexture_setRepeated(background, sfTrue);
	player->background = sfSprite_create();
	sfSprite_setTexture(player->background, background, sfTrue);
	sfSprite_setTextureRect(player->background, (sfIntRect) { 0, 0, 196, SCREEN_HEIGHT });
	sfSprite_setOrigin(player->background, (sfVector2f) { 98.f, 0.f});
	sfSprite_setPosition(player->background, _position);

	sfTexture* track = sfTexture_createFromFile("resources/track.png", NULL);
	sfTexture_setRepeated(track, sfTrue);
	player->track = sfSprite_create();
	sfSprite_setTexture(player->track, track, sfTrue);
	sfSprite_setTextureRect(player->track, (sfIntRect) { 0, 0, 64, SCREEN_HEIGHT });
	sfSprite_setOrigin(player->track, (sfVector2f) { 32.f, 0.f });
	sfSprite_setPosition(player->track, (sfVector2f) { _position.x, 0.f });
	
	// creates player's whadow
	player->shadow = sfCircleShape_create();
	sfCircleShape_setRadius(player->shadow, RADIUS);
	sfCircleShape_setFillColor(player->shadow, (sfColor) { 0, 0, 0, 150 });
	sfCircleShape_centerOrigin(player->shadow);
	sfCircleShape_setPosition(player->shadow, _position);
	sfCircleShape_scale(player->shadow, SCALE);

	// distance to browse to reach the end
	player->distance = DISTANCE;

	player->backPos[0] = 0;
	player->backPos[1] = -SCREEN_HEIGHT;

	player->hurdles = Hurdle_create(_position.x);

	return player;
}

void Player_handleEvent(Player* _player, sfEvent _event)
{
	// to press the player's key make him jump
	if (_event.type == sfEvtKeyPressed && _event.key.code == _player->button)
	{
		_player->isJumping = sfTrue;
	}
}

void Player_update(Player* _player)
{	
	// when the player reach the arrival he die
	if (_player->distance <= 0.f)
	{
		sfSprite_setPosition(_player->sprite, _player->position);
		sfCircleShape_setPosition(_player->shadow, _player->position);
		sfSprite_setTextureRect(_player->sprite, (sfIntRect) { 0, 192, 64, 64 });
		_player->distance = 0.f;
		if (_player->speed > _player->speedMax)
		{
			_player->speedMax = _player->speed;
		}
	}
	else
	{	
		// updates the hurdles
		Hurdle_update(_player->hurdles, _player->speed);

		for (int x = 0; x < MAX_HURDLE; x++)
		{
			if (_player->hurdles->y[x] > _player->position.y - RADIUS * SCALE.y
				&& _player->hurdles->y[x] < _player->position.y + RADIUS * SCALE.y
				&& !_player->isJumping
				&& !_player->isHurt)
			{
				_player->isHurt = sfTrue;
				if (_player->speed > _player->speedMax)
				{
					_player->speedMax = _player->speed;
				}
				_player->speed = INITIAL_SPEED;
				_player->maxAnimation = TIME_ANIMATION;
				_player->speedUpTime = 0.f;
			}
		}

		// updates the terrain
		for (int x = 0; x < 2; x++)
		{
			_player->backPos[x] += DT * _player->speed;
			if (_player->backPos[x] > SCREEN_HEIGHT)
			{
				_player->backPos[x] -= 2 * SCREEN_HEIGHT;
			}
		}

		_player->speedUpTime += DT;
		if (_player->speedUpTime >= SPEED_UP)
		{
			_player->speed += STEP;
			_player->maxAnimation = MAX(_player->maxAnimation - SPEED_STEP, 4 * DT);
			_player->speedUpTime -= SPEED_UP;
		}

		_player->totalTime += DT;
		_player->distance -= _player->speed * DT;

		// increase the animation time
		_player->animation += DT;
		if (_player->animation > _player->maxAnimation)
		{
			_player->animation -= _player->maxAnimation;
		}

		// updates the texture
		sfSprite_setTextureRect(_player->sprite, (sfIntRect) { 64 * (int)(4 * _player->animation / _player->maxAnimation), 0, 64, 64 });

		if (_player->isHurt)
		{
			_player->hurt += DT;
			if (_player->hurt <= HURT_TIME)
			{
				sfSprite_setTextureRect(_player->sprite, (sfIntRect) { 0, 128, 64, 64 });
			}
			if (_player->hurt >= INVULNERABILITY)
			{
				_player->hurt = 0.f;
				_player->isHurt = sfFalse;
				sfSprite_setColor(_player->sprite, (sfColor) { 255, 255, 255, 255 });
			}
			else
			{
				int x = ((int)(_player->hurt * 10) % 2) ? 255 : 0;
				sfSprite_setColor(_player->sprite, (sfColor) { 255, 255, 255, x });
			}
		}

		// the player jumps for 1.s then he falls to the ground
		if (_player->isJumping)
		{
			sfSprite_setTextureRect(_player->sprite, (sfIntRect) { 0, 64, 64, 64 });
			sfVector2f position = _player->position;
			position.y -= sin(_player->jump / JUMP_TIME * PI) * 50;
			sfSprite_setPosition(_player->sprite, position);

			_player->jump += DT;
			if (_player->jump >= JUMP_TIME)
			{
				_player->isJumping = sfFalse;
				_player->jump = 0.f;
			}
		}
	}
}

void Player_draw(Player* _player, sfRenderWindow* _window)
{
	for (int x = 0; x < 2; x++)
	{
		sfSprite_setPosition(_player->background, (sfVector2f) { _player->position.x, _player->backPos[x] });
		sfRenderWindow_drawSprite(_window, _player->background, NULL);
	}
	sfRenderWindow_drawSprite(_window, _player->track, NULL);
	
	// draws the hurdle ahed of the player
	for (int x = 0; x < MAX_HURDLE; x++)
	{
		if (_player->hurdles->y[x] < _player->position.y)
		{
			sfSprite_setPosition(_player->hurdles->sprite, (sfVector2f) { _player->hurdles->x, _player->hurdles->y[x] });
			sfRenderWindow_drawSprite(_window, _player->hurdles->sprite, NULL);
		}
	}
	
	sfRenderWindow_drawCircleShape(_window, _player->shadow, NULL);
	sfRenderWindow_drawSprite(_window, _player->sprite, NULL);
	
	// draws the hurdle behind the player
	for (int x = 0; x < MAX_HURDLE; x++)
	{
		if (_player->hurdles->y[x] > _player->position.y)
		{
			sfSprite_setPosition(_player->hurdles->sprite, (sfVector2f) { _player->hurdles->x, _player->hurdles->y[x] });
			sfRenderWindow_drawSprite(_window, _player->hurdles->sprite, NULL);
		}
	}
}