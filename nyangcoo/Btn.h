#pragma once
#include "StaticObject.h"
class Btn : public StaticObject
{
public:
	Btn();
	Btn(int _stageID);

	Btn(
		int _id, 
		std::wstring _assetFileName, 
		Gdiplus::Rect _imgRC, 
		Gdiplus::Rect _viewRC, 
		int _x, 
		int _y,
		int _stageID = 0
	);

	void SendLButtonDown();

	// Getter, Setter
	int getId();
	void setId(int _id);

	int getStageId();
	void setStageId(int _stageId);

	bool getIsClicked();
	void setIsClicked(bool _isClicked);

	int getSelectOption();
	void setSelectOption(int _selectOption);

	// 버튼 기능별 분류
	void ExecuteGameScene();			// 게임화면 실행
	void ExecuteLoadGameScene();		// 불러오기화면 실행
	void ExecuteStartScene();			// 메인화면 실행
	void ExecuteChapterSelectScene();	// 챕터선택화면 실행
	void ExecuteCookieSelectScene();	// 쿠키선택화면 실행
	void ExecuteScriptScene();			// 스크립트화면 실행
	void SelectMemorySlot();			// 세이브/로드 슬롯 선택
	void ExecuteLoad();					// 불러오기
	void ExecuteSave();					// 저장하기
	void ExecuteDelete();				// 슬롯에 저장된 내용 삭제
	void ShowHelp();					// 헬프 이미지 보이기
	void UpgradePlayer();				// 본진 플레이어 업그레이드
	void SuffleCookies();				// 쿠키 덱 섞기
	void ExecuteExit();					// 종료하기

private:
	int id;
	int stageId;
	bool isClicked;		// save, load 위함
	int selectOption;	// 선택지 선택 0 or 1 (선택없을 경우 -1)
};

