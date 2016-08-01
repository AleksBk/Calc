#pragma once
#include <iostream>
#include "Calculator.h"
#include <stack>

class ONPCalculation : public AbstractCalculation
{
private:
	AbstractWriter* _wr;
public :
	void Init(); 
	void Calculate(); 

	ONPCalculation(AbstractWriter* k) : _wr(k) {} 
	~ONPCalculation()
	{
		delete _wr;
	}
	/////////////////////////////////////////////////////////////////////////////////////
	//-----------------------------------------------------------------------------------
	void EndOnp(stack<char>* CharS, stack<double>* NumberSta);
	//-----------------------------------------------------------------------------------
	void PushOrPop(char c, stack<char>* CharS, stack<double>* NumbS);
	//-----------------------------------------------------------------------------------
	double Operation(double a, double b, char z);
	//-----------------------------------------------------------------------------------
	double Add(double a, double b);
	//-----------------------------------------------------------------------------------
	double Sub(double a, double b);
	//-----------------------------------------------------------------------------------
	double Multi(double a, double b);
	//-----------------------------------------------------------------------------------
	double Div(double a, double b);
	//-----------------------------------------------------------------------------------
	double Pow(double a, double b);
	//-----------------------------------------------------------------------------------
	void MakeAllOperation(char znak, stack<double>* NumbS);
	//-----------------------------------------------------------------------------------
	void DigitalC(stack<double>* NS2);
	//-----------------------------------------------------------------------------------
	void DigitalD(char l, stack<double>* NS);
	//-----------------------------------------------------------------------------------
	bool IfD(char c);
	//-----------------------------------------------------------------------------------

};//TODO : metody w klasie te ponizej
