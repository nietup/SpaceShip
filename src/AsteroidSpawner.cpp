#include "AsteroidSpawner.h"



AsteroidSpawner::AsteroidSpawner() {
	SpawnRate = 1.f;
	Time = new Timer(true);
	DeltaShot = 0;
}


AsteroidSpawner::~AsteroidSpawner() {
}

void AsteroidSpawner::SpawnAsteroid() {
	vec2 StartPosition = { std::rand() % 24 - 12, 6 };
	vec2 Velocity = { (float)((std::rand() % 30) - 15) / 1000.f, -0.025f };
	vec3 Rotation = { std::rand() % 2, std::rand() % 2, std::rand() % 2};
	Asteroid *a = new Asteroid(StartPosition, Velocity, Rotation);

	a->AttachTo(this);
}

void AsteroidSpawner::Update() {
	for (auto &t : *Children)
		t->Update();


	if ((Time->getSeconds() - DeltaShot) < SpawnRate)
		return;

	DeltaShot = Time->getSeconds();

	SpawnAsteroid();
}

bool AsteroidSpawner::IsCollidingWith(SpaceShip * Ship, Map * Level) {
	vec2 ShipPosition = Ship->GetPosition();
	float ShipSize = Ship->GetSize();
	std::vector<Actor *> * Projectiles = Ship->GetChildren();

	vec2 MapSize = Level->GetSize();

	for (auto &t : *Children) {

		Asteroid *A = (Asteroid *)t;
		vec2 AsteroidPosition = A->GetPosition();

		bool IfContinue = false;    //we need it so we don't check asteroid we already deleted

		//check for collisions with projectiles
		for (auto &u : *Projectiles) {

			Projectile *P = (Projectile *)u;
			if (glm::distance(AsteroidPosition, P->GetPosition()) < (0.4f*((P->GetBig() + P->GetSmall()) + (A->GetBig() + A->GetSmall())))) {
				A->Die();
				P->Die();
				IfContinue = true;
				SpawnRate *= 0.95f;    //the more asteroids player destroyed, the quicker they gonna spawn
			}
			else if (P->GetPosition().y > (MapSize.y / 2.f)) {     //check for projectiles that are out of bounds
				P->Die();
				IfContinue = true;
			}

			if (IfContinue)
				break;
		}

		if (IfContinue)
			break;

		//check for asteroids that are out of bounds
		if (AsteroidPosition.x > (MapSize.x / 2.f) ||
			AsteroidPosition.x < -(MapSize.x / 2.f) ||
			AsteroidPosition.y < -(MapSize.y / 2.f)) {
			A->Die();
			IfContinue = true;
		}

		if (IfContinue)
			break;

		//check for collisions with space ship
		if (glm::distance(ShipPosition, AsteroidPosition) < (0.4f*(ShipSize + 0.7f*(A->GetBig() + A->GetSmall()))))
			return true;
	}

	return false;
}

