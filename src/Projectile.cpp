#include "Projectile.h"



Projectile::Projectile(vec2 StartPosition) {
	Position = StartPosition;
	Setup();
}


Projectile::~Projectile() {
}

void Projectile::Setup() {
	Big = 0.5f;
	Small = 0.25f;
	auto lambert = gl::ShaderDef().lambert().color();
	gl::GlslProgRef	shader = gl::getStockShader(lambert);
	Mesh = gl::Batch::create(geom::Cube() >> geom::Scale(0.25f, 0.5f, 0.5f) >> geom::Constant(geom::COLOR, Color(CM_RGB, vec3(1.f, 0.7f, 0.5f))), shader);

	Speed = 0.075f;
}

void Projectile::Update() {
	Position.y += Speed;
}

void Projectile::Draw() {
	gl::ScopedModelMatrix SMM;
	gl::translate(Position);
	Mesh->draw();
}