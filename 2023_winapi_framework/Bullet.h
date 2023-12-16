#pragma once
#include "Object.h"
class Texture;
class Bullet :
    public Object
{
private:
    
public:
    Bullet(Texture* tex);
    ~Bullet();
public:
    void Update() override;
    void Render(HDC _dc) override;
    void SetDir(float _f) { m_fTheta = _f; }
    void SetDir(Vec2 _vDir) 
    { 
        m_vDir = _vDir; 
        m_vDir.Normalize();
    }
    void SetUnDestroyedBullet() { isUnDestroyed = true; }
private:
//    float m_fDir; // �Ѿ� ����(-1 ��, 1 �Ʒ�);
    float m_fTheta; // �ﰢ�Լ� ����.
    Vec2 m_vDir;
    Texture* m_pTex1;
    bool isUnDestroyed;
    float curTime;
private:
    virtual void EnterCollision(Collider* _pOther) override;
    virtual void ExitCollision(Collider* _pOther)  override;
    virtual void StayCollision(Collider* _pOther)  override;
};

