#include "Box.h"
#include <array>
using namespace MATH;
using namespace GEOMETRY;



void Box::generateVerticesAndNormals()
{
	//create triangles for the box with the half extents and the centre.
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

RayIntersectionInfo Box::rayIntersectionInfo(const Ray& ray) const
{

	std::array<slab, 3> slabs;
	slabs[0].normal = QMath::rotate(Vec3(1.0f, 0.0f, 0.0f), orientation);
	//assume the box is centered around (0,0,0)
	slabs[0].distFar = halfExtents.x + centre.x;
	slabs[0].distNear = -(halfExtents.x  + centre.x);

	slabs[1].normal = QMath::rotate(Vec3(0.0f, 1.0f, 0.0f), orientation);
	//assume the box is centered around (0,0,0)
	slabs[1].distFar = halfExtents.y + centre.y;
	slabs[1].distNear = -(centre.y + halfExtents.y);

	slabs[2].normal = QMath::rotate(Vec3(0.0f, 0.0f, 1.0f), orientation);;
	//assume the box is centered around (0,0,0)
	slabs[2].distFar = centre.z + halfExtents.z;
	slabs[2].distNear = -(centre.z + halfExtents.z);

	// Start of with the smallest and biggest possible values for the ray’s t value 
	float tmin = 0.0f;
	float tmax = FLT_MAX;
	float tNear = 0.0f, tFar = 0.0f;
	// Loop over the 3 slabs of the box along the x, y, and z axes 
	for (int i = 0; i < 3; i++) {
		if (ray.dir[i] != 0.0) {
			// Check intersection with the near plane. Do a ray-plane check for this
			//particular axis
			// Can follow Umer's scribbles on the board
			// t = (d - ray.start.x) / ray.dir.x 
			// t1 = (slabs[i].dNear - ray.start[i]) / ray.dir.[i] 
			float t1 = (slabs[i].distNear - ray.start[i]) / ray.dir[i];
			// Check intersection with the far plane. Do another ray-plane check
			float t2 = (slabs[i].distFar - ray.start[i]) / ray.dir[i];
			if (t1 > t2) {
				// Set tNear to be the smaller of the two t values
				tNear = t2;
				// Set tFar to be the larger of the two t values
				tFar = t1;
			}
			else {
				// Set tNear to be the smaller of the two t values
				tNear = t1;
				// Set tFar to be the larger of the two t values
				tFar = t2;
			}
			if (tmin < tNear) {
				// Update tmin so that it is the largest tNear value found so far
				tmin = tNear;
			}
			if (tmax > tFar) {
				// Update tmax so that it is the smallest tFar value found so far
				tmax = tFar;
			}
		}
		
	}
	if (tmin > tmax) {
		// If tmin is greater than tmax, then we didn't intersect the box, get outta
		//here
		return RayIntersectionInfo();
	}
	// If we made it this far, we have a valid intersection
	RayIntersectionInfo rayInfo;
	rayInfo.isIntersected = true;
	rayInfo.t = tmin;
	rayInfo.intersectionPoint = ray.currentPosition(rayInfo.t);
	return rayInfo;
	//todo
	//think abt the edge cases
	//what if the box is not centred at origin
	//what if the box is rotated
	//what if the ray dir has a zero?
	//like (1,0,0)

}
