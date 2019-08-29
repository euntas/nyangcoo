#include "pch.h"
#include "EffectManager.h"

EffectManager::EffectManager()
{
	//testEf = nullptr;
	
}

EffectManager::~EffectManager()
{
	skillEffectDic.clear();
}

EffectManager& EffectManager::GetInstance()
{
	static EffectManager mgr;
	return mgr;
}

Effect* EffectManager::GetEffect(std::wstring str)
{
	return nullptr;
}

Effect* EffectManager::MyLoadEffect(std::wstring str)
{
	/*std::wstring temp(TEXT("Asset\\"));
	temp.append(str);
	Effect effect = _effect;
	std::hash<std::wstring> a;
	skillEffectDic.insert(std::make_pair(a(str), effect));
	return effect;*/

	return nullptr;
}

//Effect* EffectManager::testEffect()
//{
//	testEf = new Effect();
//	/*testEf->EffectXmlFileName = "Asset\\effect\\effect_fox_hit.xml";
//	XmlManager::GetInstance().ParseEffectData(*testEf);
//	testEf->Init(new EffectGraphicsComponent(testEf));*/
//
//	return testEf;
//}