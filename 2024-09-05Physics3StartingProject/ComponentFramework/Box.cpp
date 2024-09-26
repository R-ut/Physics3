#include "Box.h"
using namespace MATH;
void GEOMETRY::Box::generateVerticesAndNormals()
{
	// Umer will put a random triangle in for now
	Vec3 topRightFront = centre + Vec3(halfExtents.x, halfExtents.y, halfExtents.z);
	topRightFront = QMath::rotate(topRightFront, orientation);

	Vec3 topLeftFront = centre + Vec3(-halfExtents.x, halfExtents.y, halfExtents.z);
	topLeftFront = QMath::rotate(topLeftFront, orientation);

	Vec3 bottomLeftFront = centre + Vec3(-halfExtents.x, -halfExtents.y, halfExtents.z);
	bottomLeftFront = QMath::rotate(bottomLeftFront, orientation);

	//let's make front face triangle 1 from the assignment doc
	vertices.push_back(topRightFront);
	vertices.push_back(topLeftFront);
	vertices.push_back(bottomLeftFront);
	//all normals point along z for this triangle
	normals.push_back(Vec3(0, 0, 1.0f));
	normals.push_back(Vec3(0, 0, 1.0f));
	normals.push_back(Vec3(0, 0, 1.0f));

}
