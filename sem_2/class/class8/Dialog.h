#pragma once
#include <C:/class/laba_8_main/tree.h>
#include <C:/class/laba_8_main/Event.h>

#include "Magazin.h"
#include <iostream>
#include <string>
using namespace std;

class Dialog : public tree
{
protected:
	int EndState;
public:
	Dialog(void);
	virtual ~Dialog(void);
	virtual void GetEvent(Event& event);
	virtual int Execute();
	virtual void HandEvent(Event& event);
	virtual void ClearEvent(Event& event);
	int Valid();
	void EndExec();

};

