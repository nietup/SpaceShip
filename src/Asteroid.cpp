#include "Asteroid.h"




Asteroid::Asteroid(vec2 StartPosition, vec2 aVelocity, vec3 aRotationAxis) {
	Position = StartPosition;
	Velocity = aVelocity;
	RotationAxis = aRotationAxis;
	Setup();
}

Asteroid::~Asteroid() {
}

void Asteroid::Setup() {
	auto lambert = gl::ShaderDef().lambert().color();
	gl::GlslProgRef	shader = gl::getStockShader(lambert);

	vec3 Scales = vec3(((std::rand() % 100) + 20) / 100.f, 
		((std::rand() % 100) + 20) / 100.f,
		((std::rand() % 100) + 20) / 100.f);

	SetBigSmall(Scales);

	Mesh = gl::Batch::create(geom::Cube() >> geom::Scale(Scales) >> geom::Constant(geom::COLOR, Color(CM_RGB, vec3(0.4f, 0.2f, 0.8f))), shader);

	Angle = 0.f;
}

void Asteroid::Update() {
	Position += Velocity;
	Angle += 0.05f;
}

void Asteroid::Draw() {
	gl::ScopedModelMatrix SMM;
	gl::translate(Position);
	gl::rotate(Angle, RotationAxis);
	Mesh->draw();
}

void Asteroid::SetBigSmall(vec3 Scales) {
	if (Scales.x >= Scales.y && Scales.x >= Scales.z) {
		Big = Scales.x;
		if (Scales.y < Scales.z)
			Small = Scales.y;
		else
			Small = Scales.z;
	}
	if (Scales.y >= Scales.x && Scales.y >= Scales.z) {
		Big = Scales.y;
		if (Scales.x < Scales.z)
			Small = Scales.x;
		else
			Small = Scales.z;
	}
	if (Scales.z >= Scales.y && Scales.z >= Scales.x) {
		Big = Scales.z;
		if (Scales.y < Scales.x)
			Small = Scales.y;
		else
			Small = Scales.x;
	}
}
