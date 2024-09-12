#include "ShapeComponent.h"
using namespace GEOMETRY;
using namespace MATH;
ShapeComponent::ShapeComponent(Component* parent_, Sphere sphere_) :Component(parent_)
{
	shapeType = ShapeType::sphere;
	// We are sure at this point that shape should be a sphere
	// So we can safely make a shared pointer of type sphere with the constructor Sphere(MATH::Vec3 centre, float r)
	shape = std::make_shared<Sphere>(Vec3(sphere_.x, sphere_.y, sphere_.z), sphere_.r);
}

ShapeComponent::ShapeComponent(Component* parent_, Cylinder cylinder_) :Component(parent_)
{
	shapeType = ShapeType::cylinder;
	shape = std::make_shared<Cylinder>(cylinder_.r, cylinder_.capCentrePosA, cylinder_.capCentrePosB);
}

// TODO for Assignment 1:
// The other constructors that take in Capsule, or Box 

ShapeComponent::~ShapeComponent()
{
}

bool ShapeComponent::OnCreate()
{
	return true;
}

void ShapeComponent::OnDestroy()
{
}

void ShapeComponent::Update(const float deltaTime_)
{
}

void ShapeComponent::Render() const
{
	shape->debugDraw();
}
