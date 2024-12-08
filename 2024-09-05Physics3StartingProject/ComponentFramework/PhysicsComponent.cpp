#include "PhysicsComponent.h"
#include "TransformComponent.h"

PhysicsComponent::PhysicsComponent(Component* parent_) : Component(parent_)
{

}

PhysicsComponent::PhysicsComponent(Component* parent_, Vec3 pos_, Quaternion orientation_) : Component(parent_), pos(pos_), orientation(orientation_)
{
}

bool PhysicsComponent::OnCreate()
{
	isCreated = true;
	return true;
}

void PhysicsComponent::OnDestroy()
{
}

void PhysicsComponent::Update(const float deltaTime_)
{
}

void PhysicsComponent::Render() const
{
}
