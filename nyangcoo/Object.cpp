#include "pch.h"
#include "Object.h"

Object::Object()
	: Objtype(eObjectType_None)
	, Enable(true)
{

}

Object::Object(EObjectType InType)
	: Objtype(InType)
	, Enable(true)
{

}