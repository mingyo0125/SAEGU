#pragma once
#include "Object.h"
#include "Player.h"
class Monster : public Object
{
public:
	Monster();
	~Monster();
public:
	void Update() override;
	virtual void EnterCollision(Collider* _pOther) override;
	virtual void ExitCollision(Collider* _pOther)  override;
	virtual void StayCollision(Collider* _pOther)  override;

public:
	void SetSpeed(float _f) { m_fSpeed = _f; }
	void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }
	const float& GetSpeed() const { return m_fSpeed; }
private:
	float m_fSpeed; // ���� ���ǵ�
	Vec2 m_vCenterPos; // �߽� ��ġ
	Object m_target; // �̵��� �� �ִ� �ִ� �Ÿ�
	int   m_iHp; // ü��
};

