#include "QuadraticSolve.h"
#include <iostream>
#include <Vector.h>
using namespace GEOMETRY;
using namespace std;
QuadraticSolve GEOMETRY::solveQuadratic(float a, float b, float c)
{
    QuadraticSolve result;
    float discriminant = (b * b )- (4 * a * c);
    if (discriminant < 0)
    {
        result.numSolutions = NumSolutions::zero;
        return result;
    }

    if (discriminant < VERY_SMALL ) {
        //In this case , we have one soln 
        //so return a result with NumSolutions = 1
        //and set firs sol to be -b/2a.
        //U can chose ehat the secod solve is 
        //Rut choses the second soln to be -b/2a
		result.numSolutions = NumSolutions::one;
		result.firstSolution = -b / (2 * a);

        return result;
    }

    //if the code reaches here , we have two solutions
	//so return a result with NumSolutions = 2
	//and set first sol to be (-b + sqrt(discriminant)) / (2a)
	//and second sol to be (-b - sqrt(discriminant)) / (2a)
    result.numSolutions = NumSolutions::two;
	result.firstSolution = (-b - sqrt(discriminant)) / (2 * a);
	result.secondSolution = (-b + sqrt(discriminant)) / (2 * a);
    if (result.firstSolution == result.secondSolution)
    {
        std::swap(result.firstSolution, result.secondSolution);
    }
    return result;
}

void GEOMETRY::QuadraticSolve::print() const
{
    if (numSolutions == NumSolutions::zero) {
		cout << "No solutions" << endl;
    }
    else if (numSolutions == NumSolutions::one) {
		cout << "One solution: " << firstSolution << endl;
    }
    else if (numSolutions == NumSolutions::two) {
		cout << "Two solutions: " << firstSolution << " and " << secondSolution << endl;
	}
}
