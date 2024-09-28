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

	Vec3 bottomRightFront = centre + Vec3(halfExtents.x, -halfExtents.y, halfExtents.z);
	bottomRightFront = QMath::rotate(bottomRightFront, orientation);


	Vec3 topRightBack = centre + Vec3(halfExtents.x, halfExtents.y, -halfExtents.z);
	topRightBack = QMath::rotate(topRightBack ,orientation);

	Vec3 bottomRightBack = centre + Vec3(halfExtents.x, -halfExtents.y, -halfExtents.z);
	bottomRightBack = QMath::rotate(bottomRightBack, orientation);

	Vec3 topLeftBack  = centre + Vec3(-halfExtents.x, halfExtents.y, -halfExtents.z);
	topLeftBack = QMath::rotate(topLeftBack, orientation);

	Vec3 bottomLeftBack = centre + Vec3(-halfExtents.x, -halfExtents.y, -halfExtents.z);
	bottomLeftFront = QMath::rotate(bottomLeftFront, orientation);


	//let's make front face triangle 1 from the assignment doc
	vertices.push_back(topRightFront);
	vertices.push_back(topLeftFront);
	vertices.push_back(bottomLeftFront);

	//front 2
	vertices.push_back(topRightFront);
	vertices.push_back(bottomLeftFront);
	vertices.push_back(bottomRightFront);

	//right side left
	vertices.push_back(topRightBack);
	vertices.push_back(topRightFront);
	vertices.push_back(bottomRightFront);

	//right side right
	vertices.push_back(topRightBack);
	vertices.push_back(bottomRightFront);
	vertices.push_back(bottomRightBack);

	//back side left
	vertices.push_back(topLeftBack);
	vertices.push_back(topRightBack);
	vertices.push_back(bottomRightBack);

	//back side right
	vertices.push_back(topLeftBack);
	vertices.push_back(bottomRightBack);
	vertices.push_back(bottomLeftBack);

	//left side left
	vertices.push_back(topLeftFront);
	vertices.push_back(topLeftBack);
	vertices.push_back(bottomLeftBack);

	//left side right
	vertices.push_back(topLeftFront);
	vertices.push_back(bottomLeftBack);
	vertices.push_back(bottomLeftFront);

	//topLeft
	vertices.push_back(topLeftFront);
	vertices.push_back(topLeftBack);
	vertices.push_back(topRightBack);

	//topRight
	vertices.push_back(topRightFront);
	vertices.push_back(topLeftFront);
	vertices.push_back(topRightBack);

	//bottomLeft
	vertices.push_back(bottomLeftFront);
	vertices.push_back(bottomLeftBack);
	vertices.push_back(bottomRightBack);

	//bottomRight
	vertices.push_back(bottomRightFront);
	vertices.push_back(bottomLeftFront);
	vertices.push_back(bottomRightBack);





	//front normal
	normals.push_back(Vec3(0, 0, 1.0f));
	normals.push_back(Vec3(0, 0, 1.0f));
	normals.push_back(Vec3(0, 0, 1.0f));
	normals.push_back(Vec3(0, 0, 1.0f));
	normals.push_back(Vec3(0, 0, 1.0f));
	normals.push_back(Vec3(0, 0, 1.0f));

	//right normal 
	normals.push_back(Vec3( 1.0f, 0,0));
	normals.push_back(Vec3(1.0f, 0, 0));
	normals.push_back(Vec3(1.0f, 0, 0));
	normals.push_back(Vec3(1.0f, 0, 0));
	normals.push_back(Vec3(1.0f, 0, 0));
	normals.push_back(Vec3(1.0f, 0, 0));

	//back normal
	normals.push_back(Vec3(0, 0, -1.0f));
	normals.push_back(Vec3(0, 0, -1.0f));
	normals.push_back(Vec3(0, 0, -1.0f));
	normals.push_back(Vec3(0, 0, -1.0f));
	normals.push_back(Vec3(0, 0, -1.0f));
	normals.push_back(Vec3(0, 0, -1.0f));

	//Left Normal
	normals.push_back(Vec3(-1.0f, 0, 0));
	normals.push_back(Vec3(-1.0f, 0, 0));
	normals.push_back(Vec3(-1.0f, 0, 0));
	normals.push_back(Vec3(-1.0f, 0, 0));
	normals.push_back(Vec3(-1.0f, 0, 0));
	normals.push_back(Vec3(-1.0f, 0, 0));

	//top normal
	normals.push_back(Vec3(0,1.0f, 0));
	normals.push_back(Vec3(0, 1.0f, 0));
	normals.push_back(Vec3(0, 1.0f, 0));
	normals.push_back(Vec3(0, 1.0f, 0));
	normals.push_back(Vec3(0, 1.0f, 0));
	normals.push_back(Vec3(0, 1.0f, 0));

	//bottom normal
	normals.push_back(Vec3(0, -1.0f, 0));
	normals.push_back(Vec3(0, -1.0f, 0));
	normals.push_back(Vec3(0, -1.0f, 0));
	normals.push_back(Vec3(0, -1.0f, 0));
	normals.push_back(Vec3(0, -1.0f, 0));
	normals.push_back(Vec3(0, -1.0f, 0));

	StoreMeshData(GL_TRIANGLES);
}
