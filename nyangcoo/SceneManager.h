#pragma once

class SceneManager
{
public:
	SceneManager();

	void LoadScene(CString& pName);
	// void RenderScene(CDC* pDC);
	void RenderScene(Gdiplus::Graphics* pGraphics);
	Scene* GetCurScene();
	static SceneManager& GetInstance();
	void SendLButtonDown(UINT nFlags, CPoint point);
	void Update(float Delta);

private:
	std::vector<Scene*> mScene;
	Scene* CurScene;
};