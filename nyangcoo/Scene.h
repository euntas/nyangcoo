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

	multimap<int, Object*> getInfoObj();
	void setInfoObj(multimap<int, Object*> _infoObj);
	void addToInfoObj(Object* _object);

	multimap<int, StaticObject*> getInfoStaticObj();
	void setInfoStaticObj(multimap<int, StaticObject*> _infoStaticObj);

	multimap<int, StaticObject*> getInfoUIObj();
	void setInfoUIObj(multimap<int, StaticObject*> _infoUIObj);

protected:
	bool bLoop;
	CString name;
	multimap<int, Object*> infoObj;				// �÷��̾� �����
	multimap<int, StaticObject*> infoStaticObj;	// ���� �׸� ����� (���׸� ��)
	multimap<int, StaticObject*> infoUIObj;		// UI�� �׸� ����� (�˾�â ��)

private:

};

