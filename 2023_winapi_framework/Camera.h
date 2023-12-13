#pragma once
class Object;

 class Camera
{
	 SINGLE(Camera);
private:
	Vec2 _lookAt; // 카메라가 실제로 바라보고 있는 위치
	Object* _targetObj; // 카메라가 바라보는 오브젝트

	Vec2 _diffVec; // 해상도 중심 위치와 카메라 Lookat간의 차이 값 
public:
	void SetLookAt(Vec2 look) { _lookAt = look; }
	void SetTarget(Object* lookObj) { _targetObj = lookObj; }
	Vec2 GetRenderPos(Vec2 objPos) { return objPos - _diffVec; }
private:
	void CalDiff();
public:
	void Update();
};

