#include "Derivative.h"
#include <iostream> 
#include <string>
#include <sstream>
//-------------------------------------------------------------------------------------------
std::string doubleToString1(double val)
{
	std::ostringstream out;
	out << val;
	return out.str();
}
//------------------------------------------------------------------------------------------
void DerivativeCalculations::Init()
{
	//int i = 0;
	double k = 0; 
	double tmp;
	
	// przyjmuje podane punkty wylicza h ; 
	cout << "Podaj liczbe punktow\n";
	cin >> _i;
	if (!Exeption()) return;

	cout << ("Podaj H\n");
	cin >> _h;

	cout << ("Podaj x1\n");
	cin >> _x1; 

	while (_i != k)
	{
		cout << "x" << k << " = " << _x1 + k*_h << endl;
		cout << "y" << k << " = ";
		cin >> tmp;
		_vsk->push_back(tmp); 
		k=k+_h;
		cout << endl;
	}
	cout << endl;
}
//--------------------------------------------------------------
void DerivativeCalculations::Calculate()
{ // funkcja korzystajaca ze wzoru 5-cio punktowego na pochodne w punkcie ; 
	double wynik; 
	for (int i = 0 ; i < _i-4 ; i++ )
	{
		wynik = CalcPoint( i + 2 ); 	
		All(_x1 + (2+i)*_h, wynik ); 
	}

}

//---------------------------------------------------------------
DerivativeCalculations::DerivativeCalculations(AbstractWriter* k)
{
	_vsk = new vector<double>[10];
	_wr = k; 

}
//------------------------------------------------------------------
DerivativeCalculations::~DerivativeCalculations()
{
	delete[] _vsk;
	delete _wr;
}
//--------------------------------------------------------------------
double DerivativeCalculations::CalcPoint( int k )
{
	double wynik =  ( (-1 / (12*_h) ) * ( (*_vsk)[k + 2] - (*_vsk)[k - 2] - 8 * (*_vsk)[k + 1] + 8 * (*_vsk)[k - 1] ) );
	return wynik; 
}
//----------------------------------------------------------------------
void DerivativeCalculations::All( double x, double t)
{
		_wr->Write("f'(");
		_wr->Write(doubleToString1(x)); 
		_wr->Write(") = ");
		_wr->Write(doubleToString1(t));
		_wr->Write("\n");

}
//-------------------------------------------------------------------------
int DerivativeCalculations::Exeption()
{
	if (_i < 5)
	{
		cout << "Zbyt ma³a ilosc punktow, we wzorze 5-punktowym nalezy oscylowaæ funkcje przynajmniej 5-cioma punktawmi! "<<endl;
		return 0; 
	}
	return 1;
}
//------------------------------------------------------------------------------