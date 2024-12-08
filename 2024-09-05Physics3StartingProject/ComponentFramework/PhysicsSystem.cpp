#include "PhysicsSystem.h"
#include "TransformComponent.h"
#include "MMath.h"

//Copy from physics 1 and 2
void PhysicsSystem::ApplyForce(Ref<PhysicsComponent> body, const MATH::Vec3& force)
{
	body->accel = force / body->mass;
}

void PhysicsSystem::UpdatePos(Ref<PhysicsComponent> body, float deltaTime)
{
	body->pos += body->vel * deltaTime + 0.5f * body->accel * deltaTime * deltaTime;
}

void PhysicsSystem::UpdateVel(Ref<PhysicsComponent> body, float deltaTime)
{
	body->vel += body->accel * deltaTime;
}

void PhysicsSystem::UpdateOrientation(Ref<PhysicsComponent> body, float deltaTime)
{
	//step1
	//find angle we are rotating
	float angleRadians = VMath::mag(body->angularVel) * deltaTime;
	//step 2
	//angle = 0
	if (angleRadians < VERY_SMALL) {
		return;
	}

	//step 3 find axis of rotation
	Vec3 axis = VMath::normalize(body->angularVel);

	//build quaternion
	float angleDegrees = angleRadians * RADIANS_TO_DEGREES;
	Quaternion rotation = QMath::angleAxisRotation(angleDegrees, axis);

	//apply the rotation to orient..
	body->orientation = rotation * body->orientation;
}

void PhysicsSystem::UpdateTransform(Ref<Actor> actor)
{
	Ref<PhysicsComponent> physicsComponent = actor->GetComponent<PhysicsComponent>();
	Ref<TransformComponent> transformComponent = actor->GetComponent<TransformComponent>();

	// Make sure transform matches physics
	transformComponent->pos = physicsComponent->pos;
	transformComponent->orientation = physicsComponent->orientation;
}

void PhysicsSystem::StraightLineConstant(Ref<PhysicsComponent> body, float slope, float yIntercept, float deltaTime)
{
	//based on umer's scribble
	float positionConstraint = -slope * body->pos.x + body->pos.y + yIntercept;
	float baumgarteStabilizationParameter = 0.2f;
	float bais = -baumgarteStabilizationParameter * positionConstraint / deltaTime;
	Vec3 JT = Vec3(-slope, 1.0f, 0.0f);
	float JJT = slope*slope + 1.0f;
	float JV = -slope * body->vel.x + body->vel.y;

	float lagrangianMultiplier = body->mass * (JV - bais) / JJT;
	Vec3 deltaV = JT * lagrangianMultiplier/body->mass;

	body->vel += deltaV;
}

void PhysicsSystem::MouseConstraint(Ref<PhysicsComponent> body, const Vec3& mousePos, float deltaTime)
{
	//based on umer's scribble
	//we are going to ignore the bias term and pretend that mass is 1 and rotational intertia is identity

	//vel constraint
	// r vector == 
	//Vec3 Jv = vel + angular velocity cross product r vector

	Vec3 centreOfMass = body->pos;
	Vec3 rVector = mousePos - centreOfMass;
	 Vec3 Jv = body->vel + VMath::cross(body->angularVel, rVector);

	 Matrix3 JJT; 
	 Vec3 column0;
	 column0.x = 1 + rVector.z * rVector.z + rVector.y * rVector.y;
	 column0.y = -rVector.x * rVector.z;
	 column0.z = -rVector.x * rVector.y;

	 Vec3 column1;
	 column1.x = -rVector.x * rVector.x;
	 column1.y = 1 + rVector.x * rVector.x + rVector.z * rVector.z;
	 column0.z = -rVector.y * rVector.z;

	 Vec3 column2;
	 column2.x = -rVector.x * rVector.z;
	 column2.y = -rVector.y * rVector.z;
	 column2.z = 1 + rVector.x * rVector.x + rVector.y * rVector.y;

	 JJT.setColumn(Matrix3::Column::zero, column0);
	 JJT.setColumn(Matrix3::Column::one, column1);
	 JJT.setColumn(Matrix3::Column::two, column2);


	   Vec3 lagrangianMultiplier =  MMath::inverse(JJT) * (-Jv);

	   // Vec3 deltaV = JT * lagrangianMultiplier/body->mass;
	   Vec3 deltaV = lagrangianMultiplier;
	   Vec3 deltaAngularV = VMath::cross(rVector, lagrangianMultiplier);

	   body->vel += deltaV;
	   body->angularVel += deltaAngularV;
	
}
