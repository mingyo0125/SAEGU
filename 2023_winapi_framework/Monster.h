#pragma once
#include "Object.h"
#include "Player.h"
#include "Texture.h"

class Monster : public Object
{
public:
	Monster(Object* target, float speed, int hp);
	~Monster();
public:
	void Update() override;
	virtual void EnterCollision(Collider* _pOther) override;
	virtual void ExitCollision(Collider* _pOther)  override;
	virtual void StayCollision(Collider* _pOther)  override;
	void Render(HDC _dc) override;
public:
	void SetSpeed(float _f) { m_fSpeed = _f; }
	void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }
	void SetDie();
	const float& GetSpeed() const { return m_fSpeed; }
private:
	float m_fSpeed; // ���� ���ǵ�
	Vec2 m_vCenterPos; // �߽� ��ġ
	Object* m_target; // �̵��� �� �ִ� �ִ� �Ÿ�
	int   m_iHp; // ü��
	Texture* hpTex;
private:
	void SetHit();
};

