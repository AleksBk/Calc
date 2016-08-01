#pragma once
#include "Calculator.h"
#include "Writers.h"
#include <vector>

class DerivativeCalculations : public AbstractCalculation
{
public:
	double _h; 
	double _x1; 
	int _i;

	void Init();
	void Calculate(); 

	//DerivativeCalculation(AbstractWriter* k); 
	DerivativeCalculations(AbstractWriter * k);
	~DerivativeCalculations();


	double CalcPoint( int k);
	void All(double x, double t);
	int Exeption();

private:
	AbstractWriter* _wr; 
	vector<double>* _vsk; 
	

};
//-------------------------------------------------------------------
//std::string doubleToString(double val);
//-------------------------------------------------------------------