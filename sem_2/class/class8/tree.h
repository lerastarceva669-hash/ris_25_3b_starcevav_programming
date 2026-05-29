#pragma once
#include <C:/class/laba_8_main/Object.h>
#include <C:/class/laba_8_main/Event.h>

class tree
{
protected:
	Object** beg;
	int size;
	int cur;

public:
	tree();
	tree(int);
	~tree(void);
	void Add();
	void Del();
	void Show();
	virtual void HandlEvent(const Event& e);
	int operator()();
};

