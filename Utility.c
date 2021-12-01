#include <SFML/Graphics/CircleShape.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/RenderWindow.h>
#include <stdio.h>
#include "Utility.h"

//--------------------SFML---------------------

void sfCircleShape_centerOrigin(sfCircleShape* _fig)
{
	// Centers the origin of the circle
	sfFloatRect bounds = sfCircleShape_getLocalBounds(_fig);
	sfCircleShape_setOrigin(_fig, (sfVector2f) { bounds.width / 2, bounds.height / 2 });
}


void sfSprite_centerOrigin(sfSprite* _sprite)
{
	// Centers the origin of the sprite
	sfFloatRect bounds = sfSprite_getLocalBounds(_sprite);
	sfSprite_setOrigin(_sprite, (sfVector2f) { bounds.width / 2, bounds.height / 2 });
}

void sfText_centerOrigin(sfText* _text)
{
	// Centers the origin of the sprite
	sfFloatRect bounds = sfText_getLocalBounds(_text);
	sfText_setOrigin(_text, (sfVector2f) { bounds.width / 2, bounds.height / 2 });
}

sfSprite* sfSprite_loadFromFile(char* _name, int _isCentered)
{
	sfSprite* sprite = sfSprite_create();
	sfTexture* texture = sfTexture_createFromFile(_name, NULL);
	
	// tries to load the texture
	if (texture == NULL)
	{
		printf("FAILED TO LOAD TEXTURE %s", _name);
		return sprite;
	}

	sfSprite_setTexture(sprite, texture, sfTrue);
	// if requested centers the sprite
	if (_isCentered)
	{
		sfSprite_centerOrigin(sprite);
	}
	return sprite;
}

void sfSprite_drawAt(sfSprite* _sprite, sfVector2f _position, sfRenderWindow* _window)
{
	// places the sprite at the position (_x, _y)
	sfSprite_setPosition(_sprite, _position);
	sfRenderWindow_drawSprite(_window, _sprite, NULL);
}