#include "Writers.h"
#include "ONP.h"
#include <iostream>
#include <string>


using namespace std; 

void ConsoleWriter::Write(string s)
{
	cout << s;
}
//----------------------------------------------------------------------
void FileWriter::Write(string s)// TODO w konstruktorze FileWriter( const char * // nazwa pliku){ otweramy plik , a w dekstruktorze zamykamy plik}
{
	plik1 << s; 
}
//---------------------------------------------------------------------
void TCPWriter::Write(string s)
{
	// sprawdzamy czy nowy napis sie zmiesci 
	int l =  1024; 

	if (bufflen + s.length() > l)
	{
		Send();
	}

	//strcpy(buff + bufflen, s.c_str());
	sprintf(buff, "%s%s", buff, s.c_str());
	bufflen = bufflen + s.length(); 
	// dopisujemy na koniec
	// jezeli przekracza jakas wartosc to wyslij

	if(bufflen > 100) Send(); 
}
//----------------------------------------------------------------------
void TCPWriter::Send()
{	
	send(Socket,buff, bufflen + 1, 0);
	bufflen = 0;
	memset(buff, 0, 1024);
}
//----------------------------------------------------------------------