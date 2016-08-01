#pragma once
#include <iostream>
using namespace std; 
//----------------------------------
class AbstractWriter
{
public:
	virtual void Write(string) = 0;
	virtual ~AbstractWriter()
	{}
};
//----------------------------------
class AbstractCalculation
{
public:
	virtual void Init() = 0;
	virtual void Calculate() = 0;
	virtual ~AbstractCalculation() {}
};
//-------------------------------------
