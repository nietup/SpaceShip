#include "Actor.h"



Actor::Actor() {
	Children = new std::vector<Actor *>();
}


Actor::~Actor() {
}

void Actor::Setup() {
	for (auto &t : *Children)
		t->Setup();
}

void Actor::Update() {
	for (auto &t : *Children)
		t->Update();
}

void Actor::Draw() {
	for (auto &t : *Children)
		t->Draw();
}

void Actor::AttachTo(Actor * aParent) {
	Parent = aParent;
	Parent->Attach(this);
}

void Actor::Attach(Actor * Child) {
	Children->push_back(Child);
}

void Actor::RemoveChild(Actor * Child) {
	for (auto t = Children->begin(); t != Children->end(); t++) {
		if (*t == Child) {
			Children->erase(t);
			return;
		}
	}
}

void Actor::Die() {
	for (auto &t : *Children)
		t->Die();

	if (nullptr != Parent)
		Parent->RemoveChild(this);
}
