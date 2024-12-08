#include "Cylinder.h"
using namespace MATH;
using namespace GEOMETRY;
RayIntersectionInfo Cylinder::rayIntersectionInfo(const Ray& ray) const
{

	RayIntersectionInfo rayInfo;

	rayInfo = checkInfiniteCylinder(ray);

	return rayInfo;
}
RayIntersectionInfo GEOMETRY::Cylinder::checkInfiniteCylinder(const Ray& ray) const
{
	//create a method would be easy to check infinity cylinder
	Vec3 D = ray.dir;
	float DSquared = VMath::dot(D, D);
	Vec3 AB = capCentrePosB - capCentrePosA;
	Vec3 ABnormalized = VMath::normalize(AB);
	Vec3 AS = ray.start - capCentrePosA;
	float DDotAB = VMath::dot(D, ABnormalized);
	float DDotAS = VMath::dot(D, AS);
	float ASDotAB = VMath::dot(AS, ABnormalized);
	float ASSquared = VMath::dot(AS, AS);

	
	float a = DSquared - (DDotAB * DDotAB);
	float b = 2.0f * (DDotAS - DDotAB * ASDotAB);
	float c = ASSquared - (ASDotAB * ASDotAB) - (r * r);

	QuadraticSolve soln = solveQuadratic(a, b, c);

	

	RayIntersectionInfo rayInfo;
	// If there are no solutions, there is no intersection with the cylinder
	if (soln.numSolutions == NumSolutions::zero) {
		
		return rayInfo;  // Return the default false result (no intersection)
	}	

	if (soln.numSolutions == NumSolutions::one)
	{
		rayInfo.isIntersected = true;
		rayInfo.t = soln.firstSolution;  // Return the intersection info with one solution
		rayInfo.intersectionPoint = ray.currentPosition(soln.firstSolution);
	}

	// If there are two solutions, choose the smallest positive one (the nearest intersection)
	// Assuming the first solution is the nearest intersection
	if (soln.numSolutions == NumSolutions::two)
	{
		rayInfo.isIntersected = true;
		rayInfo.t = std::min(soln.firstSolution, soln.secondSolution);  // Return the intersection info with one solution
		rayInfo.intersectionPoint = ray.currentPosition(rayInfo.t);
		
	}

	Vec3 P = rayInfo.intersectionPoint;
	Vec3 AP = P - capCentrePosA;
	Vec3 BP = P - capCentrePosB;
	float AB_Dot_AP = VMath::dot(AB, AP);
	float AB_Dot_BP = VMath::dot(AB, BP);
RayIntersectionInfo CapA;RayIntersectionInfo CapB;
	if (AB_Dot_AP < 0 || AB_Dot_AP > VMath::dot(AB, AB)) {
		
		CapA = checkEndCap(ray, capCentrePosA, P); // Mark as false if outside cylinder ends
	}
	if (AB_Dot_BP < 0 || AB_Dot_BP > VMath::dot(AB, AB)) {
		
		CapB = checkEndCap(ray, capCentrePosB, P); // Mark as false if outside cylinder ends
	}
	if (CapA.isIntersected)
	{
		if (CapB.isIntersected)
		{
			rayInfo.t = std::min(rayInfo.t, CapB.t);
		}
		rayInfo.t = std::min(rayInfo.t, CapA.t);
	}
	return rayInfo;
}

RayIntersectionInfo GEOMETRY::Cylinder::checkEndCap(const Ray& ray, const MATH::Vec3& centrePointOnEndcap,const MATH::Vec3& P_) const
{

	RayIntersectionInfo rayInfo;
	Vec3 AB = capCentrePosB - capCentrePosA;
	Vec3 ABnormalized = VMath::normalize(AB);
	Vec3 AP = P_ - centrePointOnEndcap;
	Vec3 V = ray.dir;
	Vec3 AS = ray.start - centrePointOnEndcap;
	float APDotAB = VMath::dot(AP, ABnormalized);
	float VDotAB = VMath::dot(V, ABnormalized);
	float ASDotAB = VMath::dot(AS, ABnormalized);

	if (APDotAB > 0.0f)
	{
		if (VDotAB < 0.0f)
		{
			float t = - APDotAB / VDotAB;
			Vec3 Q = ray.currentPosition(t);
			if (VMath::distance(Q, centrePointOnEndcap) <= r) {
				rayInfo.isIntersected = true;
				rayInfo.t = VMath::mag(AS - (t * V));
				rayInfo.intersectionPoint =ray.currentPosition(rayInfo.t);
				return rayInfo;
			}
		}
	}

	return rayInfo;
}

void Cylinder::generateVerticesAndNormals() {
	float distance = VMath::distance(capCentrePosA, capCentrePosB);
	Vec3 dir = VMath::normalize(capCentrePosB - capCentrePosA); // Direction of the cylinder's axis
	float noOfCircles = 25;
	const float deltaTheta = 5.0f;

	for (int i = 0; i < noOfCircles; i++) {
		for (float thetaDeg = 0.0f; thetaDeg <= 360.0f; thetaDeg += deltaTheta) {
			// Calculate the circle in 3D space, not just in the X-Y plane
			MATH::Vec3 circle(r * cos(thetaDeg * DEGREES_TO_RADIANS), r * sin(thetaDeg * DEGREES_TO_RADIANS), 0.0f);

			// Translate the circle along the cylinder's length using `dir` and `i`
			vertices.push_back(circle + capCentrePosA + (dir * (i * distance / noOfCircles)));

			// Calculate the normal for each vertex based on its position on the surface
			normals.push_back(VMath::normalize(circle));  // Assuming normal is radial to the cylinder's axis
		}
	}

	// After generating vertices and normals, store data in GPU
	StoreMeshData(GL_POINTS);
}
