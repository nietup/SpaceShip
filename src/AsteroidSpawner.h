#pragma once
#include "Actor.h"
#include "SpaceShip.h"
#include "Map.h"
#include "Asteroid.h"

class AsteroidSpawner :
	public Actor {
public:
	AsteroidSpawner();
	~AsteroidSpawner();

	void SpawnAsteroid();
	void Update() override;

	bool IsCollidingWith(SpaceShip *, Map *);    //collision handler

private:
	float SpawnRate;
	Timer *Time;
	double DeltaShot;
};

