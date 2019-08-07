#pragma once

class InputComponent
{
public:
	virtual ~InputComponent() {}
	virtual void update(Object* obj) = 0;
};

