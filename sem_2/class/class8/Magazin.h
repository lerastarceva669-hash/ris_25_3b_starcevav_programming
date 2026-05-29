#pragma once
#include <C:/class/laba_8_main/Print.h>


#include <iostream>
#include <string>
using namespace std;

class Magazin : public Print
{
protected:
	int page;
public:
	Magazin(void);
	~Magazin(void);
	virtual void Show();
	virtual void Input();
	Magazin(string, string, int);
	Magazin(const Magazin& );
	int GetPage() { return page; }
	void SetPage(int);
	Magazin& operator=(const Magazin&);

};

