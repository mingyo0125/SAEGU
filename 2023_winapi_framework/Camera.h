#pragma once
class Object;

 class Camera
{
	 SINGLE(Camera);
private:
	Vec2 _lookAt; // ī�޶� ������ �ٶ󺸰� �ִ� ��ġ
	Object* _targetObj; // ī�޶� �ٶ󺸴� ������Ʈ

	Vec2 _diffVec; // �ػ� �߽� ��ġ�� ī�޶� Lookat���� ���� �� 
public:
	void SetLookAt(Vec2 look) { _lookAt = look; }
	void SetTarget(Object* lookObj) { _targetObj = lookObj; }
	Vec2 GetRenderPos(Vec2 objPos) { return objPos - _diffVec; }
private:
	void CalDiff();
public:
	void Update();
};

