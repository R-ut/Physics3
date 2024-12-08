#include "Capsule.h"
#include <MMath.h>
#include <Vector.h>
#include "Cylinder.h"
#include "Sphere.h"
using namespace MATH;
using namespace GEOMETRY;

void Capsule::generateVerticesAndNormals() {

	const float deltaTheta = 5.0f;
	const float deltaPhi = 10.0f;
	float distance = VMath::distance(sphereCentrePosA, sphereCentrePosB);
	Vec3 dir = VMath::normalize(sphereCentrePosB - sphereCentrePosA);
	float noOfCirlces = 25;
	
	//Capsule is nothing but 2 spheres with added centre position of the top and bottom of cylinder.
	//And a cylinder. 




	//Sphere A
	
	for (float thetaDeg = 0.0f; thetaDeg <= 360.0f; thetaDeg += deltaTheta) {
		// Build a ring
		MATH::Vec3 circle(r * cos(thetaDeg * DEGREES_TO_RADIANS), r * sin(thetaDeg * DEGREES_TO_RADIANS), 0.0f);
		for (float phiDeg = 0.0f; phiDeg <= 180.0f; phiDeg += deltaPhi) {
			// Rotate a point in the ring around the y-axis to build a sphere!
			MATH::Matrix3 rotationMatrix = MATH::MMath::rotate(deltaPhi, MATH::Vec3(0.0f, 1.0f, 0.0f));
			circle = rotationMatrix * circle;
			// Push the circle point to our vertices array
			vertices.push_back(circle + sphereCentrePosA);
			// The normal of a sphere points outwards from the center position Vec3(x, y, z)
			normals.push_back(circle - Vec3(sphereCentrePosA.x, sphereCentrePosA.y, sphereCentrePosA.z));
		}
	}

	

	//sphere B
	
	for (float thetaDeg = 0.0f; thetaDeg <= 360.0f; thetaDeg += deltaTheta)
	{
		// Build a ring
		//x2 + y2 = r2
		MATH::Vec3 circle(r * cos(thetaDeg * DEGREES_TO_RADIANS), r * sin(thetaDeg * DEGREES_TO_RADIANS), 0.0f);
		for (float phiDeg = 0.0f; phiDeg <= 180.0f; phiDeg += deltaPhi) {
			// Rotate a point in the ring around the y-axis to build a sphere!
			MATH::Matrix3 rotationMatrix = MATH::MMath::rotate(deltaPhi, MATH::Vec3(0.0f, 1.0f, 0.0f));
			circle = rotationMatrix * circle;
			// Push the circle point to our vertices array
			vertices.push_back(circle + sphereCentrePosB);
			// The normal of a sphere points outwards from the center position Vec3(x, y, z)
			normals.push_back(circle - Vec3(sphereCentrePosB.x, sphereCentrePosB.y, sphereCentrePosB.z));
		}
	}
	for (int i = 0; i < noOfCirlces; i++) {
		MATH::Vec3 circle(r, 0, 0.0f);
		for (float thetaDeg = 0.0f; thetaDeg <= 360.0f; thetaDeg += deltaTheta) {
			// Build a ring

			MATH::Matrix3 rotationMatrix = MATH::MMath::rotate(deltaPhi, MATH::Vec3(0.0f, 1.0f, 0.0f));
			circle = rotationMatrix * circle;
			vertices.push_back(circle+ sphereCentrePosA + ((dir * i * (distance / noOfCirlces))));
			normals.push_back(VMath::normalize(circle));
		}
	}
	
	
	// Once we are all done filling the vertices and normals, use the base class method to store the data in the GPU
	StoreMeshData(GL_POINTS);
}

RayIntersectionInfo Capsule::rayIntersectionInfo(const Ray& ray) const
{
	//ToDo
	//Reuse the ray cylinder and ray sphere code
	//first intersect with infintely long cylinder. 
	Cylinder cylinder(r, sphereCentrePosA, sphereCentrePosB);
	//Use a checkInfinityCylinder method 
	RayIntersectionInfo rayInfo = cylinder.checkInfiniteCylinder(ray);
	// rayInfo = infyLongCylinder.checkInfiniteCylinder(ray);
	// 
	// If there are no intersection with an infinitely long cylinder. 
	// Just get outta here
	if (!rayInfo.isIntersected)
	{
		return rayInfo; // return and get outta here
	}
	// If we are still here, we have at least intersected with an infy long cylinder
	// Check the end spheres
	// We are outside end sphere centre A if....
	Vec3 AB = sphereCentrePosB - sphereCentrePosA;
	Vec3 P = rayInfo.intersectionPoint;
	Vec3 AP = P - sphereCentrePosA;
	float ab_dot_ap = VMath::dot(AB, AP);
	Vec3 BP = P - sphereCentrePosB;
	float ab_dot_bp = VMath::dot(-AB, BP);
	if (ab_dot_ap < 0) {
		// We are outside sphere centre A's pos
		//let's reuse our sphere code
		Sphere sphereAtA(sphereCentrePosA, r);
		RayIntersectionInfo rayInfoAtA = sphereAtA.rayIntersectionInfo(ray);
		return rayInfoAtA;
	}
	// TODO FOR YOU
//	else if (figure out what goes here for sphere centre B) {
	else if (ab_dot_bp < 0) {
		// We are outside sphere centre B's pos
		Sphere sphereAtB(sphereCentrePosB, r);
		RayIntersectionInfo rayInfoAtB = sphereAtB.rayIntersectionInfo(ray);
		return rayInfoAtB;
	}
	else {
		// We are inside both spheres
		return rayInfo;
	}
//	} else{
	// The infinite cylinder intersection point
	// is actually in between A & B
	// Hooray
	// Return the rayInfo we built on line 16/17
}
