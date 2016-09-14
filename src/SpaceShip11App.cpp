#include "SpaceShip11App.h"

void SpaceShip11App::setup() {
	std::srand(std::time(0));

	GameOver = false;

	RootNode = new Actor();

	Level = new Map({ 20, 14 });
	Level->AttachTo(RootNode);

	Character = new SpaceShip({ 0.f, -6.f });
	Character->AttachTo(Level);

	Spawner = new AsteroidSpawner();
	Spawner->AttachTo(Level);

	RootNode->Setup();

	Camera.lookAt(vec3(0, 0, 25), vec3(0));
}

void SpaceShip11App::update() {
	RootNode->Update();

	GameOver = Spawner->IsCollidingWith(Character, Level);    //handles collisions of asteroids with player, projectile or the map end 

	if (GameOver)
		Reset();
}

void SpaceShip11App::draw() {
	gl::clear(Color(0, 0, 0));
	gl::enableDepthRead();
	gl::enableDepthWrite();

	gl::setMatrices(Camera);

	RootNode->Draw();
}

void SpaceShip11App::keyDown(KeyEvent event) {
	if (event.getCode() == KeyEvent::KEY_ESCAPE)
		exit(0);
	if (event.getCode() == KeyEvent::KEY_LEFT)
		Character->InputLeft();
	if (event.getCode() == KeyEvent::KEY_RIGHT)
		Character->InputRight();
	if (event.getCode() == KeyEvent::KEY_UP)
		Character->InputFireStart();
}

void SpaceShip11App::keyUp(KeyEvent event) {
	if (event.getCode() == KeyEvent::KEY_LEFT || 
		event.getCode() == KeyEvent::KEY_RIGHT)
		Character->InputMoveStop();
	if (event.getCode() == KeyEvent::KEY_UP)
		Character->InputFireStop();
}

void SpaceShip11App::Reset() {
	delete RootNode;

	setup();
}

CINDER_APP(SpaceShip11App, RendererGl)
