#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Mod_euler {
	vector<double> d0;
	vector<double> d1;
	Mod_euler(const int m) : d0(m), d1(m) {}

	// this function fills in y1 with the estimate of y at time t+h
	void operator()(const vector<double>& y, const double t,
		const double h, vector<double>& y1,
		void f(const vector<double>&, const double, vector<double>&)) {
		f(y, t, d0);
		const int m = y.size();
		for (int j = 0; j<m; j++) {
			y1[j] = y[j] + h*d0[j];
		}
		f(y1, t+h, d1);
		for (int j = 0; j<m; j++) {
			y1[j] = y[j] + h/2.0*(d0[j] + d1[j]);
		}
	}
};

void f_sis(const vector<double> &y, const double t,
	vector<double> &dydt) {
	const double N = 10000.0;
	const double alpha = 0.1;
	const double beta = 3.0*alpha/N;
	const double S = y[0];
	const double I = y[1];

	dydt[0] = alpha*I-beta*S*I;
	dydt[1] = beta*S*I - alpha*I;
}

int main() {

	const double t0 = 0.0;
	const double T = 200.0;

	const int m = 2;
	vector<double> y0(m);
	const double N = 10000.0;
	y0[0] = N - 1.0;
	y0[1] = 1.0;

	const int n = 100;
	const double h = (T-t0)/double(n);

	// The code below works exactly the same for some other m>=1
	// Also, we can substitute another function for f_sis
	// And we can use a different type of object than Mod_euler
	// to use a different update method.
	Mod_euler mod_euler(m);
	vector<double> y(m);
	vector<double> y1(m);
	for (int j = 0; j<m; j++) {
		y[j] = y0[j];
	}
	double t = t0;
	for (int i = 0; i<n; i++) {
		mod_euler(y, t, h, y1, f_sis);

		for (int j = 0; j<m; j++) {
			y[j] = y1[j];
		}
		t += h;
	}
	for (int j = 0; j<m; j++) {
		cout << y[j] << endl;
	}
	
	const double alpha = 0.1;
	const double beta = 3.0*alpha/N;
	cout << "\nEquilibrium:\n";
	cout << alpha/beta << endl;
	cout << N-alpha/beta << endl;
}