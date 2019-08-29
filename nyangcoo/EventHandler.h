#pragma once
class EventHandler
{
public:
	EventHandler();
	~EventHandler();

	EventHandler& GetInstance();

	//�̺�Ʈ�� �߰��Ѵ�
	void AddEvent(std::function<void()> func, EEvent);

	//�̺�Ʈ�� �߻� �� ��ϵ� ��� �Լ� ����
	void OnEvent(EEvent);

private:
	//�̺�Ʈ(Key)�� ���� ������ �Լ��� ������ Map 
	std::unordered_map<EEvent, std::vector<std::function<void()>>> dicEvent;
};

