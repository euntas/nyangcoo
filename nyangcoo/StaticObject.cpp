#include "pch.h"
#include "StaticObject.h"

StaticObject::StaticObject()
	: Objtype(eObjectType_None)
	, Enable(true)
{

}

StaticObject::StaticObject(EObjectType InType)
	: Objtype(InType)
	, Enable(true)
{

}
