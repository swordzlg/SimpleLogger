#include "SimpleLogger.h"

int main()
{
	LogConfig cfg = { L"D:\\1.log", false, 1024 };
	CSimpleLogger::Instance().InitLogger(cfg);

	LOG(L"Hello!");
	LOG(L"%d %s", 1, L"2");

	return 0;
}