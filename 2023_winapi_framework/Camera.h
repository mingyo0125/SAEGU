#pragma once
class Object;

 class Camera
{
	 SINGLE(Camera);
private:
	Vec2 _lookAt; // ī�޶� ������ �ٶ󺸰� �ִ� ��ġ
	Object* _targetObj; // ī�޶� �ٶ󺸴� ������Ʈ
	Vec2 _diffVec; 

	float shakeMagnitude;
	float shakeTime;
	float currentTime;
	bool isCameraShake;

	float originShakeMagnitude;
	Vec2 _originLookAt;

public:
	void SetLookAt(Vec2 look) { _lookAt = look; }
	void SetTarget(Object* lookObj) { _targetObj = lookObj; }
	Vec2 GetRenderPos(Vec2 objPos) { return objPos - _diffVec; }

private:
	void ApplyShake();
	void CalDiff();

public:
	void Init();
	void Update();
	void CameraShake();

};

