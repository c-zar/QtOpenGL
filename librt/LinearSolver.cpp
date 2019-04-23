//------------------------------------------------------------------------------------------------
// Solves for u, v, and w in a set of linear equations
//       Du + Ev + Fw + G = 0
//       Hu + Iv + Jw + K = 0
//       Lu + Mv + Nw + P = 0
//
// Linear Solver.cpp
//------------------------------------------------------------------------------------------------

#include "LinearSolver.h"

const double Tol = 1.0e-8;

LinearSolver::LinearSolver(void)
{
}

LinearSolver::~LinearSolver()
{
}

//----------------------------------------------------------------------
// Returns true if finds the solution, u, v, and w for a set of linear
// equations:
//----------------------------------------------------------------------
bool LinearSolver::Run_method1(double D, double E, double F, double G,
    double H, double I, double J, double K,
    double L, double M, double N, double P,
    double& u, double& v, double& w)
{
    if (fabs(F) >= Tol) {

        double b = E * J - F * I;
        if (fabs(b) >= Tol) {

            double a = D * J - F * H;
            double d = H * N - J * L;
            double e = I * N - J * M;

            double normVal = a * e - b * d;

            if (fabs(normVal) >= Tol) {
                const double c = G * J - F * K;
                const double f = K * N - J * P;

                u = (b * f - e * c) / normVal;
                v = -(a * u + c) / b;
                w = -(D * u + E * v + G) / F;

                // found solution
                return true;
            }
        }
    }

    return (false);
}

//----------------------------------------------------------------------
// Returns true if finds the solution, u, v, and w for a set of linear
// equations:
//----------------------------------------------------------------------
bool LinearSolver::Run_method2(double a, double b, double c, double d,
    double e, double f, double g, double h,
    double i, double j, double k, double l,
    double& x, double& y, double& z)
{
    bool isTrue = false;
    double D = a * (e * i - h * f) - b * (g * f - d * i) - c * (d * h - e * g);

    if (fabs(D) >= Tol) {
        x = (j * (e * i - h * f) + k * (g * f - d * i) + l * (d * h - e * g)) / D;
        y = (i * (a * k - j * b) + h * (j * c - a * l) + g * (b * l - k * c)) / D;
        z = -(f * (a * k - j * b) + e * (j * c - a * l) + d * (b * l - k * c)) / D;
        isTrue = true;
    }
    return (isTrue);
}

// reference: https://cplusplus.happycodings.com/mathematics/code5.html
// I could not get the other linear solvers to work
bool LinearSolver::Run_method3(double a, double b, double c, double d,
    double l, double m, double n, double k,
    double p, double q, double r, double s,
    double& x, double& y, double& z)
{
    bool isTrue = false;
    double D = (a * m * r + b * p * n + c * l * q) - (a * n * q + b * l * r + c * m * p);

    if (fabs(D) >= Tol) {
        x = ((b * r * k + c * m * s + d * n * q) - (b * n * s + c * q * k + d * m * r)) / D;
        y = ((a * n * s + c * p * k + d * l * r) - (a * r * k + c * l * s + d * n * p)) / D;
        z = ((a * q * k + b * l * s + d * m * p) - (a * m * s + b * p * k + d * l * q)) / D;
        isTrue = true;
    }
    return (isTrue);
}

//---------------------------------------- -
