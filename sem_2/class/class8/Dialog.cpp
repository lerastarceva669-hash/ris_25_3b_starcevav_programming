#include "Dialog.h"
#include "tree.h"
#include "Magazin.h"
#include "Print.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

Dialog::Dialog(void):tree() { EndState = 0; }
Dialog::~Dialog(void){}
void Dialog::GetEvent(Event& event)
{
	string OpInt = "+-?/qam";
	string s;
	string param;

	char code;
	cout << ">";
	cin >> s; code = s[0];
	if (OpInt.find(code) >= 0)
	{
		event.what = evMessage;
		switch (code)
		{
		case 'm':event.command = cmMake; break;
		case '+':event.command = cmAdd; break;
		case '-': event.command = cmDel; break;
		case '?': event.command = cmShow; break;
		case 'q': event.command = cmQuit; break;
		case '/': event.command = cmGet; break;
		}

		if (s.size() > 1)
		{
			param = s.substr(1, s.size() - 1);
			int A = atoi(param.c_str());
			event.a = A;
		}
	}
	else event.what = evNothing;
}

int Dialog::Execute()
{
	Event event;
	do
	{
		EndState = 0;
		GetEvent(event);
		HandEvent(event);
	} while (!Valid());
		return EndState;
}

int Dialog::Valid()
{
	return (EndState == 0) ? 0 : 1;
}
void Dialog::ClearEvent(Event& event)
{
	event.what = evNothing;
}
void Dialog::EndExec()
{
	EndState = 1;
}
void Dialog::HandEvent(Event& event)
{
	if (event.what == evMessage)
	{
		switch (event.command)
		{
		case cmMake:
			size = event.a;
			beg = new Object * [size];
			cur = 0;
			ClearEvent(event);
			break;
		case cmAdd:
			Add();
			ClearEvent(event);
			break;
		case cmDel:Del();
			ClearEvent(event);
			break;
		case cmShow:Show();
			ClearEvent(event);
			break;
		case cmQuit:EndExec();
			ClearEvent(event);
			break;
		default:tree::HandlEvent(event);

		};
	};
}