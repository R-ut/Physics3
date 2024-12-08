#include "ShapeComponent.h"
using namespace GEOMETRY;
using namespace MATH;
ShapeComponent::ShapeComponent(Component* parent_, const Sphere& sphere_) :Component(parent_)
{
	shapeType = ShapeType::sphere;
	// We are sure at this point that shape should be a sphere
	// So we can safely make a shared pointer of type sphere with the constructor Sphere(MATH::Vec3 centre, float r)
	shape = std::make_shared<Sphere>(sphere_);
}

ShapeComponent::ShapeComponent(Component* parent_, const Cylinder& cylinder_) :Component(parent_)
{
	auto size = sizeof(cylinder_);
	shapeType = ShapeType::cylinder;
	shape = std::make_shared<Cylinder>(cylinder_);
}

// TODO for Assignment 1:
// The other constructors that take in Capsule, or Box 

ShapeComponent::ShapeComponent(Component* parent_,const Capsule& capsule_) :Component(parent_) {
	shapeType = ShapeType::capsule;
	// We are sure at this point that shape should be a sphere
	// So we can safely make a shared pointer of type sphere with the constructor Sphere(MATH::Vec3 centre, float r)
	shape = std::make_shared<Capsule>(capsule_);

}
ShapeComponent::ShapeComponent(Component* parent_,const Box& box_) :Component(parent_)
{
	shapeType = ShapeType::box;
	shape = std::make_shared<Box>(box_);
}
ShapeComponent::~ShapeComponent()
{
}

bool ShapeComponent::OnCreate()
{
	isCreated = true;
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
