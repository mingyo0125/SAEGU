#pragma once
#include "Monster.h"

class BirdMonster : public Monster
{
public:
	BirdMonster(Object* target, float speed, int hp);
	~BirdMonster();
private:
	Texture* m_moveTexture;
};
