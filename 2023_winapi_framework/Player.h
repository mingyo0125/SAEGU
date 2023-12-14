#pragma once
#include "Object.h"
class Texture;
class Player :
    public Object
{
public:
    Player();
    ~Player();
private:
    virtual void EnterCollision(Collider* _pOther) override;
    virtual void ExitCollision(Collider* _pOther)  override;
    virtual void StayCollision(Collider* _pOther)  override;
public:
    void Update() override;
    void Render(HDC _dc) override;
    void OnDamage(int damage);
    void Die();
private:
    void CreateBullet();
    void TextureLoad();
private:
    Texture* _walkRightTex;
    Texture* _walkLeftTex;
    Texture* _shootLeftTex;
    Texture* _shootRightTex;
    Texture* m_pTexIdle;
    Texture* _hitTexRight;
    Texture* _hitTexLeft;
    Texture* _dieTexLeft;
    Texture* _dieTexRight;
    Texture* _staticDieTexLeft;
    Texture* _staticDieTexRight;
    Texture* _hp1Tex;
    Texture* _hp2Tex;
    Texture* _hp3Tex;
    Texture* _hp4Tex;
    Texture* _hp5Tex;
    Texture* _hp6Tex;
    int* Hp;
    int MaxHp;
    bool isKeyPressing;
    bool isLeft;
    bool isShooting;
    bool isDie;
    bool isIdle;
    float curTime;
    float speed;
    float dashSpeed;
};

