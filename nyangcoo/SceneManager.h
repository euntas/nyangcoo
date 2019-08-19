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

	Gdiplus::Rect ViewRC;			// 뷰 화면 전체 크기

	Gdiplus::Point CameraPt;			// 화면 이동 위한 좌표 변화량 저장용

private:
	std::vector<Scene*> mScene;
	Scene* CurScene;
	
};