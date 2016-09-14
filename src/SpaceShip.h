#pragma once
#include "Actor.h"
#include "Projectile.h"

using namespace ci;

class SpaceShip : public Actor {
public:
	SpaceShip(vec2 StartPosition = {0.f, 0.f});
	~SpaceShip();

	void Setup() override;
	void Update() override;
	void Draw() override;

	void Fire();

	//input events handlers
	void InputLeft();
	void InputRight();
	void InputMoveStop();
	void InputFireStart();
	void InputFireStop();

	float GetSize() { return Size; };

private:
	bool IsMovingLeft, IsMovingRight, IsShooting;
	float Speed;
	float Cooldown;
	Timer *Time;
	double DeltaShot;
	float Size;
};

