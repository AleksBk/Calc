#pragma once
#include "Calculator.h"
#include <fstream>
#include <time.h>
#include <winsock.h>
#include <conio.h>
#include <exception>
#pragma comment(lib, "ws2_32.lib")
class ConsoleWriter : public AbstractWriter 
{
public:
	void Write(string s); 

};
//------------------------------------------------------------------------------------------
class FileWriter : public AbstractWriter
{
	fstream plik1; 
public:
	FileWriter( char * nazwapliku)
	{
		plik1.open(nazwapliku, ios::app);
		time_t czas;
		struct tm* ptr; 
		time(&czas);
		ptr = localtime(&czas);
		char* data = asctime( ptr ); 

		plik1 << data;
	}
	//---------------------------------------------------------------------
	~FileWriter()
	{
		plik1.close(); 
	}
	void Write(string s);

};
//-------------------------------------------------------------------------------------------
class TCPWriter : public AbstractWriter
{
	WSADATA wsaData;
	int iResult;

	SOCKET Socket;
	sockaddr_in clientService;
	char buff[1024];
	int bufflen = 0;
	void Send(); 
public:
	void Write(string s);
	TCPWriter()
	{
		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

		if (iResult != NO_ERROR)
		{
			throw exception("WSAStartup failed");
		}

		Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		//tworzenie gniazda sieciowego , 
		//AF_INET rodzina protoko³u internetowego TP , charakter gniazda Sock_Stream -> gniazdo TCP, konkretny protokó³

		if (Socket == INVALID_SOCKET)
		{
			throw exception("Error at socket()");
		}

		clientService.sin_family = AF_INET;
		clientService.sin_addr.s_addr = inet_addr("127.0.0.1");

		clientService.sin_port = htons(27016);

		iResult = connect(Socket, (SOCKADDR*)&clientService, sizeof(clientService));
		//nawiazanie po³aczenia 
		if (iResult == SOCKET_ERROR)
		{
			closesocket(Socket);
			throw exception("Unable to connect to server");
		}
		memset(buff, 0, 1024);

	}
	virtual ~TCPWriter()
	{
		if (bufflen > 0) Send(); 
		iResult = shutdown(Socket, 2);
		if (iResult == SOCKET_ERROR)
		{
			cout << "shutdown failed" << endl;
			closesocket(Socket);
		}

		closesocket(Socket);
		WSACleanup();

	}
	
};
//-------------------------------------------------------------------------------------------