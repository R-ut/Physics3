#include "Sphere.h"
#include <MMath.h>

using namespace MATH;
using namespace GEOMETRY;



RayIntersectionInfo Sphere::rayIntersectionInfo(const Ray& ray) const
{
	return RayIntersectionInfo();
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