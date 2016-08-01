#include "Integral.h"
#include <math.h>
#include <sstream>
//--------------------------------------------------------------------------------
std::string doubleToString2(double val)
{
	std::ostringstream out;
	out << val;
	return out.str();
}
//--------------------------------------------------------------------------------
void IntegralCalculations::Init()
{
	// pobieram od user przedzial , h i tablice ygrekow;
	// 
	int ilPunkt;
	double y;

	cout << "Kalkulator Calek\n";

	cout << "Podaj przedzial <a,b>\n"; 
	cout << "a = ";
	cin >> _a; 

	cout << "b = ";
	cin >> _b; 

	cout << "Podaj h = ";
	cin >> _h; 

	ilPunkt =(int)(abs((_b - _a)) / _h + 1); 
	cout << "\nPodaj wartosci yi\n";

	for( int i=0 ; i< ilPunkt ; i++ )  
	{
		cout << "x" << i << " = " << _a + i*_h << "\t"; 
		cout << "y" << i << " = ";
		cin >> y; 
		_ygreki->push_back(y);
	}
	cout << endl;
}
//-----------------------------------------------------------------------
void IntegralCalculations::Calculate()
{
	double wynik ;
	int size = _ygreki->size() -1 ; 

	wynik = _h*(((*_ygreki)[0] + (*_ygreki)[size]) / 2 + Sum()); 

	_wr->Write( "Calka z przedzialu <");
	_wr->Write(doubleToString2(_a) );
	_wr->Write(";");
	_wr->Write(doubleToString2(_b));
	_wr->Write(  "> F(x)= " );
	_wr->Write(doubleToString2(wynik));
	_wr->Write("\n");
	cout << endl;
}
//------------------------------------------------------------------------
IntegralCalculations::IntegralCalculations(AbstractWriter* k)
{
	_wr = k;
	_ygreki = new vector<double>; 
}
//-----------------------------------------------------------------------
IntegralCalculations::~IntegralCalculations()
{
	delete _wr; 
	delete _ygreki; 
}
//------------------------------------------------------------------------
double IntegralCalculations::Sum()
{
	double suma = 0;
	for (int i = 1; i < (_ygreki->size() - 1); i++)
	{
		suma = suma + (*_ygreki)[i] ;
	}
	return suma; 
}
//------------------------------------------------------------------------------------