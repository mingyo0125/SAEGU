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
    void SetUnDestroyedBullet();
private:
    void CreateBullet();
    void TextureLoad();
    void MSetUnDestroyedBullet();

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
<<<<<<< HEAD
<<<<<<< HEAD
    Texture* _dashTex;
    Texture* _ammoTex;
    Texture* _reloadTex;
=======

    Texture* _dashTex;
    Texture* _ammoTex;
    Texture* _reloadTex;

    Texture* _normalBullet;
    Texture* _unDBullet;
>>>>>>> d2440e97b2212db3b34f6299acd421751a82ea2d
=======
    Texture* _normalBullet;
    Texture* _unDBullet;
>>>>>>> parent of 46992be (Merge branch 'King')
    int* Hp;
    int MaxHp;
    bool isKeyPressing;
    bool isLeft;
    bool isShooting;
    bool isDie;
    bool isIdle;
    bool isHit;
    bool isUnDestroyed;
    float dashCooldown;
    float dashCooldownTime;
    float shootCooldown;
    float shootCooldownTime;
    float curTime;
    float bulletCurTime;
    float speed;
    float dashSpeed;
    float targetTime;
    float unDestroyedTime;
};

