#pragma once

using namespace std;

class Scene
{
public:
	virtual void Init();
	virtual void Update(float Delta);
	virtual void Render(Gdiplus::Graphics* pGraphics);
	virtual void Release();

	void ClearAll();

	// Getter, Setter
	bool getBLoop();
	void setBLoop(bool _bLoop);
	
	CString getName();
	void setName(CString _name);

	vector<Object*> getInfoObj();
	void setInfoObj(vector<Object*> _infoObj);

	vector<StaticObject*> getInfoStaticObj();
	void setInfoStaticObj(vector<StaticObject*> _infoStaticObj);

	vector<StaticObject*> getInfoUIObj();
	void setInfoUIObj(vector<StaticObject*> _infoUIObj);

protected:
	bool bLoop;
	CString name;
	vector<Object*> infoObj;				// 플레이어 저장용
	vector<StaticObject*> infoStaticObj;	// 정적 그림 저장용 (배경그림 등)
	vector<StaticObject*> infoUIObj;		// UI용 그림 저장용 (팝업창 등)

private:

};

