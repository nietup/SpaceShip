#pragma once
#include <vector>
#include <iostream>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

//base gameplay class, everything placed in game inherits from this

using namespace ci;

class Actor {
public:
	Actor();
	~Actor();
	virtual void Setup();
	virtual void Update();
	virtual void Draw();
	virtual void AttachTo(Actor * Parent);    //actors should be attached using this function
	virtual void Attach(Actor * Child);       //because this function is called from within the former

	virtual vec2 GetPosition() { return Position; };
	virtual std::vector<Actor *> * GetChildren() { return Children; };
	virtual void RemoveChild(Actor *);

	virtual void Die();

protected:
	Actor * Parent;
	std::vector<Actor *> * Children;
	gl::BatchRef Mesh;
	vec2 Position;
};

