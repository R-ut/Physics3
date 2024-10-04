#pragma once
namespace GEOMETRY {
	enum class NumSolutions {
		zero = 0,
		one,
		two
	};
	struct QuadraticSolve {

		NumSolutions numSolutions{
		NumSolutions::zero };
		// I'll use first root as the smallest of the two. Set them both to zero to begin with
		float firstSolution = 0.0f;
		float secondSolution = 0.0f;
		void print() const; // handy method that prints out the number of solutions and their value(s)

	};
	// To actually solve the quadratic equation, we don’t need an entire class - just a function! Here’s my signature:
	QuadraticSolve solveQuadratic(float a, float b, float c);
}