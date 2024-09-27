#include "Cylinder.h"
using namespace MATH;

void GEOMETRY::Cylinder::generateVerticesAndNormals() {
	float distance = VMath::distance(capCentrePosA, capCentrePosB);
	Vec3 dir = VMath::normalize(capCentrePosB - capCentrePosA);
	float noOfCirlces = 99;
	const float deltaTheta = 5.0f;

	for (int i = -1; i < noOfCirlces; i++) {
		for (float thetaDeg = 0.0f; thetaDeg <= 360.0f; thetaDeg += deltaTheta) {
			// Build a ring
			MATH::Vec3 circle(r * cos(thetaDeg * DEGREES_TO_RADIANS), r * sin(thetaDeg * DEGREES_TO_RADIANS), 0.0f);
			vertices.push_back(circle + ((dir * i*distance)/(noOfCirlces)));
			normals.push_back(circle);
		}
	}

	//Once we are all done filling the vertices and normals, use the base class method to store the data in the GPU
	StoreMeshData(GL_POINTS);
}