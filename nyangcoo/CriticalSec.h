#pragma once
class CriticalSec {
public:
	CriticalSec()
	{
		cs.Lock();
	}
	~CriticalSec()
	{
		cs.Unlock();
	}

	CCriticalSection cs;
};

