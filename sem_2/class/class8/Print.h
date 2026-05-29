#pragma once
#include <iostream>
#include <string>
using namespace std;
#include <C:/class/laba_8_main/Object.h>
class Print : public Object
{
public:
	Print(void);
	virtual ~Print(void);
	void Show();
	void Input();
	Print(string, string);
	Print(const Print&);

	string GetName() { return name; };
	string GetAuthor() { return author; };

	void SetName(string);
	void SetAuthor(string);

	Print& operator=(const Print&);

	void HandlEvent(const Event& e);

protected:
	string name;
	string author;
};

