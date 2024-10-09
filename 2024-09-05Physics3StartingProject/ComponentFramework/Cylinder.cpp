#include "Cylinder.h"
using namespace MATH;
using namespace GEOMETRY;
RayIntersectionInfo Cylinder::rayIntersectionInfo(const Ray& ray) const
{
	return RayIntersectionInfo();
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