// MatrixDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "MatrixDll.h"

class MyMatrix : public Matrix {
    int n, m;
	int** arr;
public:
	// MyMatrix constructor
	MyMatrix() {};

	// MyMatrix destructor
	~MyMatrix() {
		for (int i = 0; i < n; ++i) {
			delete arr[i];
		}
	}

	// Set size
	void Matrix::set_size(int _n, int _m) {
		n = _n;
		m = _m;
	}

    // Create matrix
    void Matrix::create_matrix() {
        arr = new int*[n];
		for (int i = 0; i < n; ++i) {
			arr[i] = new int[m];
		}
    }

	// Fill matrix
	void Matrix::fill_matrix(int min, int max) {
		// Init random
		std::random_device rd;							 // only used once to initialise (seed) engine
		std::mt19937 rng(rd());					         // random-number engine used (Mersenne-Twister in this case)
		std::uniform_int_distribution<int> uni(min,max); // guaranteed unbiased

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				arr[i][j] = uni(rng);
			}
		}
	}

	// Show matrix
	void Matrix::show_matrix() {
		cout << endl;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				cout << setw(4) << arr[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}

	// Change matrix
	void Matrix::change_matrix() {
		int counter = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (arr[i][j] < 0) {
					arr[i][j] = 0;
					counter++;
				}
			}
		}
		cout << "Number of numbers less than zero: " << counter << endl;
	}
};

extern "C" __declspec(dllexport) Matrix* __cdecl create_klass()
{
    return new MyMatrix();
}