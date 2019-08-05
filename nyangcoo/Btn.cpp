#include "pch.h"
#include "Btn.h"

Btn::Btn()
	: Object(EObjectType::eObjectType_Btn)
{

}

void Btn::SendLButtonDown()
{
	switch (ID)
	{
	case 0:
		SceneManager::GetInstance().LoadScene(CString("Scene_Game"));
		break;
	case 1:
		PostQuitMessage(0);
		break;
	}
}