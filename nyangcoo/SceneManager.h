#pragma once

class SceneManager
{
public:
	SceneManager();

	void LoadScene(CString& pName);
	void RenderScene(Gdiplus::Graphics* pGraphics);
	Scene* GetCurScene();
	static SceneManager& GetInstance();
	void SendLButtonDown(UINT nFlags, CPoint point);
	void SendMouseMove(UINT nFlags, CPoint point);
	void SendKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void Init();
	void Update(float Delta);
	void Release();
	Scene* GetSceneByName(CString& pName);

	Gdiplus::Rect ViewRC;			// �� ȭ�� ��ü ũ��

	Gdiplus::Point CameraPt;			// ȭ�� �̵� ���� ��ǥ ��ȭ�� �����

private:
	std::vector<Scene*> mScene;
	Scene* CurScene;
	
};