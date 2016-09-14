#include "SpaceShip.h"


SpaceShip::SpaceShip(vec2 StartPosition) {
	Position = StartPosition;
	IsMovingLeft = IsMovingRight = IsShooting = false;
	Time = new Timer(true);
	DeltaShot = 0;
}

SpaceShip::~SpaceShip() {
}

void SpaceShip::Setup() {
	for (auto &t : *Children)
		t->Setup();

	Size = 1.f;
	auto lambert = gl::ShaderDef().lambert().color();
	gl::GlslProgRef	shader = gl::getStockShader(lambert);
	Mesh = gl::Batch::create(geom::Cube() >> geom::Constant(geom::COLOR, Color(CM_RGB, vec3(1, 0, 1))), shader);

	Speed = 0.1f;
	Cooldown = 0.5f;
}

void SpaceShip::Update() {
	for (auto &t : *Children)
		t->Update();

	if (IsMovingLeft)
		Position.x -= Speed;
	if (IsMovingRight)
		Position.x += Speed;

	if (IsShooting)
		Fire();
}

void SpaceShip::Draw() {
	for (auto &t : *Children)
			t->Draw();

	gl::ScopedModelMatrix SMM;
	gl::translate(Position);
	Mesh->draw();
}

void SpaceShip::InputLeft() {
	if (!IsMovingRight)
		IsMovingLeft = true;
}

void SpaceShip::InputRight() {
	if (!IsMovingLeft)
	IsMovingRight = true;
}

void SpaceShip::InputMoveStop() {
	IsMovingLeft = IsMovingRight = false;
}

void SpaceShip::Fire() {

	if ((Time->getSeconds() - DeltaShot) < Cooldown)
		return;
	
	DeltaShot = Time->getSeconds();

	Projectile *p = new Projectile({ Position.x, Position.y + 0.5f });
	p->AttachTo(this);
}

void SpaceShip::InputFireStart() {
	IsShooting = true;
}

void SpaceShip::InputFireStop() {
	IsShooting = false;
}