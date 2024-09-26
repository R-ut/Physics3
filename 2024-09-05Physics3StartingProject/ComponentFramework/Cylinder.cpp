#include "Cylinder.h"
void GEOMETRY::Cylinder::generateVerticesAndNormals()
{
	// For now, lets just make one circle
	// Use the sphere as a guide
	const float deltaTheta = 5.0f;
	for (float thetaDeg = 0.0f; thetaDeg <= 360.0f; thetaDeg += deltaTheta)
	{
		// Build a ring
		MATH::Vec3 circle(r * cos(thetaDeg * DEGREES_TO_RADIANS), r * sin(thetaDeg * DEGREES_TO_RADIANS), 0.0f);
		// Push the circle point to our vertices array
		vertices.push_back(circle);
		// The normal of a sphere points outwards from the center position Vec3(x, y, z)
		normals.push_back(circle); // will fix later
	}
	// Once we are all done filling the vertices and normals, use the base class method to store the data in the GPU
	StoreMeshData(GL_POINTS);
}
