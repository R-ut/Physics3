#ifndef BOX_H
#define BOX_H

#include "Shape.h"
#include <VMath.h>
#include <QMath.h>

namespace GEOMETRY {
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
	};

}

#endif

