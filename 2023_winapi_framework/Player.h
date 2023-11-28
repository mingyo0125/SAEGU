#pragma once
#include "Object.h"
class Texture;
class Player :
    public Object
{
public:
    Player();
    ~Player();
public:
    void Update() override;
    void Render(HDC _dc) override;
    void MinusHp(int damage);
    void Die();
private:
    void CreateBullet();
private:
    Texture* m_pTex;
    Texture* m_pTex2;
    Texture* m_pTexIdle;
    int* Hp;
    int MaxHp;
    bool isKeyPressing;
};

