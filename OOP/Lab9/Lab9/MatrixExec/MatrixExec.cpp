// MatrixExec.cpp

#include "stdafx.h"
#include "MatrixDll.h"

// A factory of IKlass-implementing objects looks thus
typedef Matrix* (__cdecl *iklass_factory)();

int main()
{
    // Load the DLL 
    HINSTANCE dll_handle = ::LoadLibrary(TEXT("MatrixDll.dll"));
    if (!dll_handle) {
        cerr << "Unable to load DLL!\n";
        return 1;
    }

    // Get the function from the DLL
    iklass_factory factory_func = reinterpret_cast<iklass_factory>(
        ::GetProcAddress(dll_handle, "create_klass"));
    if (!factory_func) {
        cerr << "Unable to load create_klass from DLL!\n";
        ::FreeLibrary(dll_handle);
        return 1;
    }

    // Ask the factory for a new object implementing the IKlass
    // interface
    Matrix* instance = factory_func();

	string n_str, m_str;
	int n, m;
	while (true) {
		try {
			cout << "Please enter size of the matrix" << endl;
			cout << "n: ";
			cin >> n_str;
			cout << "m: ";
			cin >> m_str;

			n = stoi(n_str);
			m = stoi(m_str);
			if (n < 1 || m < 1) {
				throw invalid_argument("N and M nust be greater than zero");
			}
			break;
		} catch (const invalid_argument &e) {
			cerr << e.what() << endl;
		} catch(...) {
			cerr << "N and M must be integers, not string" << endl;
		}
	}

    // Main part
	instance->set_size(n, m);
    instance->create_matrix();
    instance->fill_matrix();
	instance->show_matrix();
	instance->change_matrix();
	instance->show_matrix();

    // Destroy it explicitly
    ::FreeLibrary(dll_handle);

    return 0;
}