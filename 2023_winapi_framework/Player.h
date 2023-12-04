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
    float GetSpeed() const { return speed; }
private:
    void CreateBullet();
private:
    Texture* walkRightTex;
    Texture* walkLeftTex;
    Texture* shootLeftTex;
    Texture* shootRightTex;
    Texture* m_pTexIdle;
    Texture* hitTexRight;
    Texture* hitTexLeft;
    Texture* DieTexLeft;
    Texture* DieTexRight;
    Texture* StaticDieTexLeft;
    Texture* StaticDieTexRight;
    int* Hp;
    int MaxHp;
    bool isKeyPressing;
    bool isLeft;
    bool isShooting;
    bool isDie;
    float speed;
    float curTime;
};

