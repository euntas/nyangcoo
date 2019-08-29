#pragma once
class EffectManager
{
public:
	EffectManager();
	~EffectManager();

	static EffectManager& GetInstance();

	Effect* GetEffect(std::wstring str);


	//Effect* testEffect();

private:
	Effect* MyLoadEffect(std::wstring str);

	std::unordered_map<size_t, Effect> skillEffectDic;

	//Effect* testEf;
};

