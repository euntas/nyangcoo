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

	Gdiplus::Rect ViewRC;			// 뷰 화면 전체 크기

private:
	std::vector<Scene*> mScene;
	Scene* CurScene;
	
};