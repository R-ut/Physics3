#include "Cylinder.h"
using namespace MATH;
using namespace GEOMETRY;
RayIntersectionInfo Cylinder::rayIntersectionInfo(const Ray& ray) const
{
	//create a method would be easy to check infinity cylinder
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

	
	// If there are no solutions, there is no intersection with the cylinder
	if (soln.numSolutions == NumSolutions::zero) {
		return RayIntersectionInfo();  // Return the default false result (no intersection)
	}

	RayIntersectionInfo rayInfo;
	rayInfo.isIntersected = true;
	rayInfo.intersectionPoint = ray.currentPosition(soln.firstSolution);
	rayInfo.t = soln.firstSolution;
	Vec3 P = rayInfo.intersectionPoint;
	Vec3 AP = P - capCentrePosA;
	
	float ABDotAP = VMath::dot(AP, AB);
	if (ABDotAP < 0.0f)
	{
		//If you are clicking head on to a cylinder then the intersection point could be far in distance
		//Would need to examine this edge case. 
		if (DDotAB > 0.0f)
		{
			//Ray has a chance of hitiing the cap
			
			// Do a ray-plane intersection
			// Don't need normalized AB vectors here, but should still work
			// Based on my whiteboard scribbles
			float t = -ASDotAB / DDotAB;
			//In umers scrible he called it Q
			Vec3 Q = ray.currentPosition(t);
			if (VMath::distance(P, Q) <= r)
			{
				//We have hit the endcap A
				rayInfo.intersectionPoint = Q;
				rayInfo.t = t;
				rayInfo.isIntersected = true;
				return rayInfo; 
			}
			else {
				//point Q is outside the radius
				return RayIntersectionInfo();  // Return the default false result (no intersection)
			}
		}
		else {
			return RayIntersectionInfo();  // Return the default false result (no intersection)
		}
		//We know we ae outside A
		//else if (Figure out what goes here for endcap b)
		//Hint( ABDotAP > 0.0f)


		//Else we know we are inside the cylinder
		// The infinite cylinder intersection point
		// is actually in between A & B
		// Hooray
		// Return the rayInfo we built on line 36

	}


	// If there is one solution, the ray grazes the cylinder
	if (soln.numSolutions == NumSolutions::one) {
		rayInfo.isIntersected = true;
		rayInfo.t = soln.firstSolution;  // Return the intersection info with one solution
	}

	// If there are two solutions, choose the smallest positive one (the nearest intersection point)
	if (soln.numSolutions == NumSolutions::two) {
		// Assuming the first solution is the nearest intersection
		rayInfo.isIntersected = true;
		rayInfo.t = soln.firstSolution < soln.secondSolution ? soln.firstSolution : soln.secondSolution;

		// Compute the intersection point using the ray equation
		
	}
	rayInfo.intersectionPoint = ray.currentPosition(rayInfo.t);
	// In future, you may want to handle cylinder caps if required.
	// The current code assumes an infinitely long cylinder.

	return rayInfo;
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