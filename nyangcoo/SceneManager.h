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
	
	void Init();
	void Update(float Delta);

	Gdiplus::Rect ViewRC;			// �� ȭ�� ��ü ũ��

private:
	std::vector<Scene*> mScene;
	Scene* CurScene;
	
};