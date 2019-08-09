#pragma once

using namespace std;

class Scene
{
public:
	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* pGraphics);
	virtual void Release();

	bool bLoop;
	CString Name;
	vector<Object*> infoObj;				// 플레이어 저장용
	vector<StaticObject*> infoStaticObj;	// 정적 그림 저장용 (배경그림 등)
	vector<StaticObject*> infoUIObj;		// UI용 그림 저장용 (팝업창 등)
};

