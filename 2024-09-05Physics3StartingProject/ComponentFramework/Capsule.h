#ifndef CAPSULE_H // header guard
#define CAPSULE_H
#include "Shape.h"

namespace GEOMETRY {
    struct Capsule : public Shape
    {
        float r = 1.0f;
        MATH::Vec3 sphereCentrePosA;
        MATH::Vec3 sphereCentrePosB;

        inline void set(float r_, MATH::Vec3 sphereCentrePosA_, MATH::Vec3 sphereCentrePosB_) {
			r = r_;
			sphereCentrePosA = sphereCentrePosA_;
			sphereCentrePosB = sphereCentrePosB_;
            generateVerticesAndNormals();
        }
        Capsule() {
            set(1.0f, MATH::Vec3(0.0f, 0.0f, 0.0f), MATH::Vec3(0.0f, 1.0f, 0.0f));
        }

        Capsule(float r_, MATH::Vec3 sphereCentrePosA_, MATH::Vec3 sphereCentrePosB_) {
            set(r_, sphereCentrePosA_, sphereCentrePosB_);
        }

        //copy constructor
        Capsule(const Capsule& c) {
            set(c.r, c.sphereCentrePosA, c.sphereCentrePosB);
        }
        void generateVerticesAndNormals() override;

        RayIntersectionInfo rayIntersectionInfo(const Ray& ray) const override;
        RayIntersectionInfo checkEndSphere(const Ray& ray, MATH::Vec3 sphereCentre) const;
};
}
#endif
