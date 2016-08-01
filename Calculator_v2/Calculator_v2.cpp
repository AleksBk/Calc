// Calculator_v2.cpp : Defines the entry point for the console application.
//
#include "Writers.h"
#include "stdafx.h"
#include "ONP.h"
#include "Derivative.h"

#include "Integral.h"
void Menu();

int main()
{
//	AbstractWriter* vsk = new FileWriter( "mojplik.txt") ; 
	/*AbstractWriter* vsk = new ConsoleWriter();
	AbstractCalculation* a = new ONPCalculation( vsk );
	*/
	char choice; 
	AbstractWriter* vsk1;
	//-----------------------------------------------------------------------------------------
	try
	{
		vsk1 = new TCPWriter();
	}
	catch(exception& s)
	{
		cout << s.what() << endl;
		return 1;
	}
	//------------------------------------------------------------------------------------------
	AbstractCalculation* a;

	Menu();
	cout << ">"; 
	cin >> choice; 

	switch ( choice )
	{
	case '1':
		{
			a = new ONPCalculation(vsk1); 
			break; 
		}
	case '2':
		{
			a = new DerivativeCalculations(vsk1);
			break;
		}
	case '3':
		{
			a = new IntegralCalculations(vsk1);
			break;
		}
	case '4':
		{
			return 0; 
		}

	default:
		return 0;
	}

	std::system("cls"); 
	a->Init();
	a->Calculate(); 

	delete a; 
	//delete vsk1;
    return 0;
}

//-------------------------------------------------------------------------
void Menu()
{

	cout << "------------------Kalkulator-------------------\n";
	cout << "         1 Kalkulator ONP numeryczny\n";
	cout << "         2 Kalkulator pochodnych\n";
	cout << "         3 Kalkulator calek\n";
	cout << "         4 Wyjscie\n";
	cout << "-----------------------------------------------\n\n";

}
//---------------------------------------------------------------------------