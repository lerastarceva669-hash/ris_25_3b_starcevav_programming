#pragma once
#include <C:/class/laba_8_main/Event.h>

class Object
{
public:
	Object(void);

	virtual void Show() = 0;
	virtual void Input() = 0;
	virtual ~Object(void);
	virtual void HandlEvent(const Event& e) = 0;
};

