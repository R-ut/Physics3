#ifndef BOX_H
#define BOX_H

#include "Shape.h"
#include <VMath.h>
#include <QMath.h>

namespace GEOMETRY {

	struct slab {
		// REFERENCE: Ch. 4 Real Time Collision Detection by Ericson
// This is called a Kay-Kajiya Slab volume
// Region R = { (x, y, z) | distNear <= a*x + b*y + c*z <= distFar }
		MATH::Vec3 normal;
		float distNear; // Signed distance from origin for near plane
		float distFar; // Signed distance from origin for far plane

	};
	struct Box : public Shape
	{
		MATH::Vec3 centre;
		MATH::Vec3 halfExtents;
		MATH::Quaternion orientation;

		inline void set(MATH::Vec3 centre_, MATH::Vec3 halfExtents_, MATH::Quaternion orientation_) {
			centre = centre_;
			halfExtents = halfExtents_;
			orientation = orientation_;
			generateVerticesAndNormals();
		}
		Box() {
			//For default box, centre (0,0,0) and halfExtents (1,1,1) and orientation (1,0,0,0)
			set(MATH::Vec3(0, 0, 0), MATH::Vec3(1, 1, 1), MATH::Quaternion());
		}

		Box(MATH::Vec3 centre_, MATH::Vec3 halfExtents_, MATH::Quaternion orientation_) {
			set(centre_, halfExtents_, orientation_);
		}

		//Copy constructor
		Box(const Box& box) {
			set(box.centre, box.halfExtents, box.orientation);
		}
		void generateVerticesAndNormals() override;
		RayIntersectionInfo rayIntersectionInfo(const Ray& ray) const override;
	};

}

#endif

