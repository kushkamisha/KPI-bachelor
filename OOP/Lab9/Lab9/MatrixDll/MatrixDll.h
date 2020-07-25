// MatrixDll.h

#ifdef MATHFUNCSDLL_EXPORTS
#define MATHFUNCSDLL_API __declspec(dllexport) 
#else
#define MATHFUNCSDLL_API __declspec(dllimport) 
#endif

class Matrix {
public:
	virtual void set_size(int, int) = 0;
    virtual void create_matrix() = 0;
    virtual void fill_matrix(int min=-9, int max=9) = 0;
    virtual void show_matrix() = 0;
	virtual void change_matrix() = 0;
};