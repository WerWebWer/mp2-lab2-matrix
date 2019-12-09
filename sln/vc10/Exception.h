#pragma once

#include <string.h>
#include <iostream>
using namespace std;



class Exception
{
	int Line;
	char* File;
	char* Function;
	char* Desc;
public:
	Exception(int _Line, const char* _File, const char* _Function, const char* _Desc)
	{
		Line = _Line;
		File = new char[strlen(_File) + 1];
		strcpy_s(File, strlen(_File) + 1, _File);
		Function = new char[strlen(_Function) + 1];
		strcpy_s(Function, strlen(_Function) + 1, _Function);
		Desc = new char[strlen(_Desc) + 1];
		strcpy_s(Desc, strlen(_Desc) + 1, _Desc);
	}
	Exception(const Exception &E)
	{
		Line = E.Line;
		File = new char[strlen(E.File) + 1];
		strcpy_s(File, strlen(E.File) + 1, E.File);
		Function = new char[strlen(E.Function) + 1];
		strcpy_s(Function, strlen(E.Function) + 1, E.Function);
		Desc = new char[strlen(E.Desc) + 1];
		strcpy_s(Desc, strlen(E.Desc) + 1, E.Desc);
	}
	~Exception()
	{
		delete[]File;
		delete[]Function;
		delete[]Desc;
	}
	friend ostream& operator <<(ostream & os, Exception &e);
};