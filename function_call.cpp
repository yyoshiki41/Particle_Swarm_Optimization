#include <iostream>
#include <fstream>
#include <math.h>

#define N 2   // The number of dimensions
#define I 5   // The number of initial points
#define K 100 // The number of iterations

using namespace std;

double __2n_minima (double *x, int *call);

int main()
{
	// Initial points
	double x[I][N];
	for (int i = 0; i < I; i++) {
		for (int n = 0; n < N; n++) {
			x[i][n] = ((double)rand() / ((double)RAND_MAX + 1)) * 10 - 5;
		}
	}

	// Parameters
	double λ, r1, r2;
	double λ_max = 0.9, λ_min = 0.4;
	double c1 = 2.0, c2 = 2.0;
	// Amount of movement
	double v[I][N] = {{}};
	// Best points
	double x_gbest[N], x_pbest[I][N];
	// Function value
	double f_gbest, f_pbest[I], f_temp;
	// Function call
	int call = 0;

	// Output file
	ofstream fout;
	fout.open("2n-minima/function_call.tsv");
	fout << "function_call\tfunction_value\tx_best" << endl;

	for(int k = 0; k < K; k++) {
		// PSO Algorithm
		for (int i = 0; i < I; i++) {
			f_temp = __2n_minima(x[i], &call);
			if (k == 0) {
				f_pbest[i] = f_temp;
				if (i == 0 || f_gbest > f_temp) {
					f_gbest = f_temp;
					memcpy(x_gbest, x[i], sizeof(x[i]));
				}
			} else {
				if (f_pbest[i] > f_temp) {
					f_pbest[i] = f_temp;
					memcpy(x_pbest[i], x[i], sizeof(x[i]));
					if (f_gbest > f_temp) {
						f_gbest = f_temp;
						memcpy(x_gbest, x[i], sizeof(x[i]));
					}
				}
			}
		}

		fout << call << "\t" << f_gbest;
		for (int n = 0; n < N; n++) {
			fout << "\t" << x_gbest[n];
		}
		fout << endl;

		// Inertia Weight Approach
		λ = λ_max - (λ_max - λ_min) * k / K;
		// Update
		for (int i = 0; i < I; i++) {
			r1 = ((double)rand() / ((double)RAND_MAX + 1)) * 1.0;
			r2 = ((double)rand() / ((double)RAND_MAX + 1)) * 1.0;
			for (int n = 0; n < N; n++) {
				v[i][n] = λ * v[i][n] + c1 * r1 * (x_pbest[i][n] - x[i][n]) + c2 * r2 * (x_gbest[n] - x[i][n]);
				x[i][n] = x[i][n] + v[i][n];
			}
		}
	}
}

/*
 * Objective function
 * 2N-minima
 */
double __2n_minima (double x[N], int *call)
{
	(*call)++;
	double f = 0;
	for (int n = 0; n < N; n++) {
		f += pow(x[n], 4) - 16 * pow(x[n], 2) + 5 * x[n];
	}
	return f;
}
