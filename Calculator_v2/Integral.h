#pragma once
#include "Writers.h"
#include "Calculator.h"
#include <vector>


class IntegralCalculations : public AbstractCalculation
{
public:
	double _h;
	double _a;
	double _b; 
	
	void Init();
	void Calculate(); 
	double Sum();
	IntegralCalculations(AbstractWriter* k); 
	~IntegralCalculations();

private:
	AbstractWriter* _wr; 
	vector<double>* _ygreki; 
};
//-----------------------------------------------------------------
std::string doubleToString2(double val);
//------------------------------------------------------------------
