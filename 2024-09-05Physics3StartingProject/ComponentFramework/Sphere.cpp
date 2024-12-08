#include "Sphere.h"
#include <MMath.h>
#include <VMath.h>
#include "QuadraticSolve.h"

using namespace MATH;
using namespace GEOMETRY;


RayIntersectionInfo Sphere::rayIntersectionInfo(const Ray& ray) const
{
	//TODO
	//Solve the big equation Umer had on sphere
	Vec3 D = ray.dir;
	Vec3 S = ray.start;
	Vec3 C = Vec3(x, y, z);

	float a = VMath::dot(D, D);
	float b = 2 * (VMath::dot(S - C,D));
	float c = VMath::dot(S - C,S - C)  - r * r;

	QuadraticSolve soln = solveQuadratic(a, b, c);
	
	
	RayIntersectionInfo result; 
	result.isIntersected = true;
	//result.t would be the smallest soln
	result.t = soln.firstSolution;
	//based on no of soln result.isIntersected is set to true
	//result.t would be the smallest soln
	result.intersectionPoint = ray.currentPosition(result.t);

	if (soln.numSolutions == NumSolutions::zero)
	{
		result.isIntersected = false;
	}
	else {
		result.isIntersected = true;
	}

	return result;
}

void Sphere::generateVerticesAndNormals()
{
	// We need to fill the vertices and normals arrays with the correct data for a sphere
	// deltaTheta governs how many points per ring. Try messing with it
	const float deltaTheta = 3.0f;
	// deltaPhi governs how many rings there are in total. Try messing with it
	const float deltaPhi = 10.0f;
	for (float thetaDeg = 0.0f; thetaDeg <= 360.0f; thetaDeg += deltaTheta)
	{
		// Build a ring
		Vec3 circle(r * sin(thetaDeg * DEGREES_TO_RADIANS), r * cos(thetaDeg * DEGREES_TO_RADIANS), 0.0f);
		for (float phiDeg = 0.0f; phiDeg <= 360.0f; phiDeg += deltaPhi) {
			// Rotate a point in the ring around the y-axis to build a sphere!
			Matrix3 rotationMatrix = MMath::rotate(deltaPhi, Vec3(0.0f, 1.0f, 0.0f));
			circle = rotationMatrix * circle;
			// Push the circle point to our vertices array
			vertices.push_back(circle + Vec3(x, y, z));
			// The normal of a sphere points outwards from the center position Vec3(x, y, z)
			normals.push_back(circle - Vec3(x, y, z));
		}

	}
	// Once we are all done filling the vertices and normals, use the base class method to store the data in the GPU
	StoreMeshData(GL_POINTS);
}