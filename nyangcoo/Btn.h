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

	// ��ư ��ɺ� �з�
	void ExecuteGameScene();			// ����ȭ�� ����
	void ExecuteLoadGameScene();		// �ҷ�����ȭ�� ����
	void ExecuteStartScene();			// ����ȭ�� ����
	void ExecuteChapterSelectScene();	// é�ͼ���ȭ�� ����
	void ExecuteCookieSelectScene();	// ��Ű����ȭ�� ����
	void ExecuteScriptScene();			// ��ũ��Ʈȭ�� ����
	void SelectMemorySlot();			// ���̺�/�ε� ���� ����
	void ExecuteLoad();					// �ҷ�����
	void ExecuteSave();					// �����ϱ�
	void ExecuteDelete();				// ���Կ� ����� ���� ����
	void ShowHelp();					// ���� �̹��� ���̱�
	void UpgradePlayer();				// ���� �÷��̾� ���׷��̵�
	void SuffleCookies();				// ��Ű �� ����
	void ExecuteExit();					// �����ϱ�

private:
	int id;
	int stageId;
	bool isClicked;		// save, load ����
	int selectOption;	// ������ ���� 0 or 1 (���þ��� ��� -1)
};

