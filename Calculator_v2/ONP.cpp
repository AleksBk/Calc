#include "ONP.h"
#include <stack>
#include <Math.h>
#include <string>
#include <cstdlib>
#include "Writers.h"
#include <sstream>
using namespace std;
//---------------------------------------------------
std::string doubleToString(double val)
{
	std::ostringstream out;
	out << val;
	return out.str();
}
//---------------------------------------------------
int piorytet(char c)
{
	switch (c)
	{
	case ')':
	case '(': return 0;
	case '+':
	case '-': return 1;
	case '*':
	case '/': return 2;
	case '^': return 3;
	}
	return -1; 
};
//---------------------------------------------------
void ONPCalculation::Init()
{

	cout << "ONPCalculator , zakoncz wpisywanie znakiem '='\n" ; 
}
//-------------------------------------------------
void ONPCalculation::Calculate()
{
	stack<double>* NumbStack = new stack<double>;
	stack<char>* CharStack = new stack<char>;
 
	bool number = false;

	while (true)
	{
		char znak = 0;
		cin >> znak;
			
		if (znak == '=')
		{
			EndOnp(CharStack, NumbStack);  // jeœli koniec wpisywnia to wyœwitelam 

			_wr->Write( "\nWynik " );
			_wr->Write(doubleToString(NumbStack->top()));
			_wr->Write("\n"); 
			_wr->Write("\n");
		
			NumbStack->pop(); // ostateczny wynik
			break;
		}

		switch (znak)
		{
		case ' ': break; // ignore spacje
		case '(': CharStack->push(znak); number = false; break;  // zawsze wrzucam na stos otwerajacy znak
		case ')':
			{
				while (CharStack->top() != '(')
				{

					_wr->Write(string(1, CharStack->top())); // os³uga wypisywania ; 
					_wr->Write(" ");
					MakeAllOperation(CharStack->top(), NumbStack);
					CharStack->pop();
					
				}
				CharStack->pop(); // sciagniecie otwerajacego ;
				number = false;
				break;
			}
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
		{
			PushOrPop(znak, CharStack, NumbStack);
			number = false;
			break;
		}
	/*	case '.':
		{
			DigitalC(NumbStack);
			_wr->Write(doubleToString(NumbStack->top()));
			number = false;
			break;
		}*/
		default:
			DigitalD(znak, NumbStack); 
			_wr->Write(doubleToString(NumbStack->top())); // os³uga wypisywania ; 
			_wr->Write(" ");
		}
	}

	delete NumbStack;
	delete CharStack;
}
//----------------------------------------------------------------------
void ONPCalculation::EndOnp(stack<char>* CharS, stack <double>* NumberSta)
{
	while (!CharS->empty()) // jeœli cos zosta³o na stosie to wyœwietlam 
	{
		_wr->Write(string(1, CharS->top())); // os³uga wypisywania ; 
		_wr->Write(" ");
		MakeAllOperation(CharS->top(), NumberSta);
		CharS->pop();
	}

}
//-------------------------------------------------------------------------
void ONPCalculation::PushOrPop(char c, stack<char>* CharS, stack<double>* NumberS)
{
	while (CharS->empty() == false)
	{
		if (piorytet(c) < piorytet(CharS->top()))
		{
			_wr->Write( string(1,CharS->top()) ); // os³uga wypisywania ; 
			_wr->Write(" ");// zszycam ze stosu wszystkie o piorytecie wy¿szym ni¿ wczytany		
			MakeAllOperation(CharS->top(), NumberS); // przesy³am znak  do f-cji  wykonujacej odpowiednie obliczenia;
			CharS->pop(); // zrzucam znak ze stosu 
		}
		else
		{
			CharS->push(c); // to wrzucam moj znak na stos ; 
			return;
		}
	}
	CharS->push(c); // to wrzucam moj znak na stos ;

}
//----------------------------------------------------------------------------
double ONPCalculation::Operation(double a, double b, char z)
{
	switch (z)
	{
	case '+': return Add(a, b);
	case '-': return Sub(a, b);
	case '*': return Multi(a, b);
	case '/': return Div(a, b); 
	case '^': return Pow(a, b);  
	default:
		break;
	}
	return -1;
}
//----------------------------------------------------------------------------
double ONPCalculation::Add(double a, double b)
{
	return a + b;
}
//----------------------------------------------------------------------------
double ONPCalculation::Sub(double a, double b)
{
	return b-a;
}
//----------------------------------------------------------------------------
double ONPCalculation::Multi(double a, double b)
{
	return a * b;
}
//----------------------------------------------------------------------------
double ONPCalculation::Div(double a, double b)
{
	if (a == 0) { cout << "Error Math!"; return 0; }
	return b / a;
}
//----------------------------------------------------------------------------
double ONPCalculation::Pow(double a, double b)
{
	return pow(b, a);
}
//----------------------------------------------------------------------------
void ONPCalculation::MakeAllOperation(char znak, stack<double>* NumbS)
{
	// biore znak , wyciagam dwie liczby , licze i wyrzucam do liczbowego
	double liczba = NumbS->top(); // !!! czy odwroacac ??
	NumbS->pop();
	double wynik = Operation(liczba, NumbS->top(), znak);
	NumbS->pop();
	NumbS->push(wynik);
	return;
}
//------------------------------------------------------------------------------
bool ONPCalculation::IfD(char c) {
	if ((c >= '0') && (c <= '9'))
		return true;
	return false;
}
//-----------------------------------------------------------------------------
void ONPCalculation::DigitalD(char l, stack<double>* NS) // dla liczb dziesietnych
{ 
	double wynik; 
	NS->push(l - '0');// wrzucam liczbe na stos 
	while (true)
	{
		cin >> l; 
		if (IfD(l)) // jezeli jest kolejna liczba to œciagam poprzedni¹ * 10 + nowa ; i ppushuje
		{
			wynik = NS->top() * 10 + (l-'0') ;
			NS->pop(); 
			NS->push(wynik);
		}
		else if (l == '.')
		{
			DigitalC(NS); // to liczymy jako dziesatna
			return; 
		}
		else
		{
			ungetc(l, stdin);
			return; 
		}
	}
}
//-----------------------------------------------------------------------------
void ONPCalculation::DigitalC(stack<double>* NS2) // dla liczb po przecinku
{
	double wynik = NS2->top();
	NS2->pop(); // si¹gnelam poprzednia liczbe 
	double mn = 0.1;

	char z;

	while (true) // dopunku liczba 
	{
		cin >> z;

		if (IfD(z))
		{
			wynik = wynik + (z - '0')*mn;
			mn = mn*0.1;
		}
		else
		{
			ungetc(z, stdin);
			break;
		}
	}
	NS2->push(wynik);
}
//-----------------------------------------------------------------------------