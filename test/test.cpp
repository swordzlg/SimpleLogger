#include "SimpleLogger.h"

int main()
{
	CSimpleLogger::Instance().InitLogger({ L"D:\\1.log", false, 1024 });
	LOG(L"Hello!");

	return 0;
}