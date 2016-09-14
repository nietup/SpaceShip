#pragma once
#include "Actor.h"

using namespace ci;

class Asteroid :
	public Actor {
public:
	Asteroid(vec2 StartPosition = { 0.f, 0.f }, vec2 Velocity = { 0.f, -0.075f }, vec3 RotationAxis = { 0, 0, 1 });
	~Asteroid();

	void Setup() override;
	void Update() override;
	void Draw() override;

	float GetBig() { return Big; };        //largest and smallest edge of the asteroid (used for collision check)
	float GetSmall() { return Small; };

private:
	void SetBigSmall(vec3);

	vec2 Velocity;
	vec3 RotationAxis;
	float Angle;
	float Big, Small;
};

