#ifndef CYLINDER_H // header guard
#define CYLINDER_H

#include "Shape.h"
#include <Vector.h>
#include <vector>
#include <VMath.h>
#include "QuadraticSolve.h"

namespace GEOMETRY {
	struct Cylinder : public Shape {
		// Represent a cylinder by the two end cap centre positions and the radius.
		//REFERENCE: p.195 of Real Time Collision Detection by Ericson
		float r = 1.0f;
		MATH::Vec3 capCentrePosA;
		MATH::Vec3 capCentrePosB;

		/// Just a little utility to populate a Cylinder.
		inline void set(float r_, MATH::Vec3 capCentrePosA_, MATH::Vec3 capCentrePosB_)
		{
			r = r_;
			capCentrePosA = capCentrePosA_;
			capCentrePosB = capCentrePosB_;
			generateVerticesAndNormals();
		}

		// Default constructor sets the radius and cap centre positions, and fires off the generateVerticesAndNormals method
		Cylinder() {
			set(1.0f, MATH::Vec3(0, 0, 0), MATH::Vec3(0, 1, 0));
		}
		//copy co nstructor
		Cylinder(const Cylinder& c) {
			set(c.r, c.capCentrePosA, c.capCentrePosB);
		}

		Cylinder(float r_, MATH::Vec3 capCentrePosA_, MATH::Vec3 capCentrePosB_) {
			set(r_, capCentrePosA_, capCentrePosB_);
		}

		// TODO for assignment 2:
		RayIntersectionInfo rayIntersectionInfo(const Ray& ray) const override;
		void generateVerticesAndNormals() override;

	};
}
#endif
