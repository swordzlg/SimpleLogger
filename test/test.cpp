#include "SimpleLogger.h"
using namespace slog;
int main()
{
	LogConfig cfg = { L"D:\\1.log", false, 1024 };
	CSimpleLogger::Instance().InitLogger(cfg);

	LOG_DEBUG(L"Hello!");
	LOG_DEBUG(L"%d %s", 1, L"2");

	return 0;
}