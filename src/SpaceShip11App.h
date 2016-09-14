#pragma once

#include "Actor.h"
#include "Map.h"
#include "SpaceShip.h"
#include "Projectile.h"
#include "Asteroid.h"
#include "AsteroidSpawner.h"

using namespace ci;
using namespace ci::app;

class SpaceShip11App : public App {
public:
	void setup() override;
	void update() override;
	void draw() override;

	//input mapings
	void keyDown(KeyEvent) override;
	void keyUp(KeyEvent) override;

	void Reset();

private:
	Actor *RootNode;
	Map *Level;
	SpaceShip *Character;
	AsteroidSpawner *Spawner;
	CameraPersp Camera;
	bool GameOver;
};