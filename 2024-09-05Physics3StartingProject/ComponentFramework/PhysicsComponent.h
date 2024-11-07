#pragma once
#include "Component.h"
#include <Quaternion.h>
using namespace MATH;
class PhysicsComponent :
    public Component
{
	float mass = 1.0f;
	Matrix3 rotationalInertia;
	Vec3 pos;
	Vec3 vel;
	Vec3 accel;
	Quaternion orientation;
	Vec3 angularVel;
	Vec3 angularAcc;
	PhysicsComponent(Component* parent_);
	PhysicsComponent(Component* parent_, Vec3 pos_, Quaternion orientation_); // that last argument (has to be the last set) allows to initialize without a 4th argument
	bool OnCreate();
	void OnDestroy();
	void Update(const float deltaTime_);
	void Render() const;
};

