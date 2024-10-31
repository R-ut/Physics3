#include "Cylinder.h"
using namespace MATH;
using namespace GEOMETRY;
RayIntersectionInfo Cylinder::rayIntersectionInfo(const Ray& ray) const
{
	Vec3 D = ray.dir;
	float DSquared = VMath::dot(D, D);
	Vec3 AB = capCentrePosB - capCentrePosA;
	Vec3 ABnormalized = VMath::normalize(AB);
	Vec3 AS = ray.start - capCentrePosA;
	float DDotAB = VMath::dot(D, ABnormalized);
	float DDotAS = VMath::dot(D, AS);
	float ASDotAB = VMath::dot(AS, ABnormalized);
	float ASSquared = VMath::dot(AS, AS);

	float a = DSquared - (DDotAB * DDotAB);
	float b = 2.0f * (DDotAS - (DDotAB * ASDotAB));
	float c = ASSquared - (ASDotAB*ASDotAB) - (r * r);

	QuadraticSolve soln = solveQuadratic(a, b, c);

	RayIntersectionInfo result;
	// If there are no solutions, there is no intersection with the cylinder
	if (soln.numSolutions == NumSolutions::zero) {
		return result;  // Return the default false result (no intersection)
	}

	// If there is one solution, the ray grazes the cylinder
	if (soln.numSolutions == NumSolutions::one) {
		result.isIntersected = true;
		result.t = soln.firstSolution;  // Return the intersection info with one solution
	}

	// If there are two solutions, choose the smallest positive one (the nearest intersection point)
	if (soln.numSolutions == NumSolutions::two) {
		// Assuming the first solution is the nearest intersection
		result.isIntersected = true;
		result.t = soln.firstSolution < soln.secondSolution ? soln.firstSolution : soln.secondSolution;

		// Compute the intersection point using the ray equation
		
	}
	result.intersectionPoint = ray.currentPosition(result.t);
	// In future, you may want to handle cylinder caps if required.
	// The current code assumes an infinitely long cylinder.

	return result;
}

void Cylinder::generateVerticesAndNormals() {
	float distance = VMath::distance(capCentrePosA, capCentrePosB);
	Vec3 dir = VMath::normalize(capCentrePosB - capCentrePosA);
	float noOfCirlces = 25;
	const float deltaTheta = 5.0f;

	for (int i = 0; i < noOfCirlces; i++) {
		for (float thetaDeg = 0.0f; thetaDeg <= 360.0f; thetaDeg += deltaTheta) {
			// Build a ring
			MATH::Vec3 circle(r * cos(thetaDeg * DEGREES_TO_RADIANS), r * sin(thetaDeg * DEGREES_TO_RADIANS), 0.0f);
			//create one circle and move it up in the direction of the normal between the two caps.
			//(distance/no of circle) give me the distance between each circle and I just increment it. 
			vertices.push_back(circle + ((dir * i*distance)/(noOfCirlces)));
			//as each point acts as a circle(cylinder formed by stack of circle). I normalise circle to get it's normal. 
			normals.push_back(VMath::normalize(circle));
		}
	}

	//Once we are all done filling the vertices and normals, use the base class method to store the data in the GPU
	StoreMeshData(GL_POINTS);
}