//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Triangle.h
// Defines a triangle surface enclosed by three points m_a, m_b, m_c
//-----------------------------------------------------------------------------

#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "Intersection.h"
#include "Ray.h"
#include "STVector3.h"
#include "Surface.h"
#include <vector>

class Triangle : public Surface {
public:
    Triangle(STVector3 a, STVector3 b, STVector3 c, RGBR_f color);
    Triangle(STVector3 a, STVector3 b, STVector3 c, RGBR_f color, float transparent);
    Triangle(STVector3 a, STVector3 b, STVector3 c, RGBR_f color, bool reflective, float transparent);

    ~Triangle(void);

    bool FindIntersection(Ray ray, Intersection* pIntersection) override; // compute ray triangle intersections
    STVector3* getVertices();


public:
    std::vector<float> vertexArray;

private:
    // vertices
    STVector3 m_a;
    STVector3 m_b;
    STVector3 m_c;

    // linear systems
    bool IntersectionSolver(Ray ray, STVector3 A, STVector3 B, STVector3 C, double& u, double& v, double& w);
    // linear solver
    STVector3 ComputeNormalVector(void); // returns the normal
    void initVertexArray();
};

#endif //__TRIANGLE_H__
