#pragma once

#include <windows.h>
#include <string>
#include <fstream>

using std::wstring;
using std::wofstream;

const int kLogMaxBufSize = 1024 * 4;

//snwprintf(buf, kLogMaxBufSize, format, ##__VA_ARGS__);
#define LOG(format, ...) do { \
	wchar_t buf[kLogMaxBufSize] = {0}; \
	swprintf_s(buf, format, ##__VA_ARGS__); \
	CSimpleLogger::Instance().WriteLog(buf); \
}while (0);

typedef struct _LogConfig
{
	wstring wstrOutFile;
	bool bOverwrite;
	int nFileLimitSize;		// log文件大小限制（字节）
}LogConfig;

class CSimpleLogger
{
public:
	static CSimpleLogger& Instance()
	{
		static CSimpleLogger instance;
		return instance;
	}

	// 初始化设置
	void InitLogger(const LogConfig &logCfg);
	void WriteLog(const wstring &wstrData);

private:
	CSimpleLogger();
	~CSimpleLogger();
	LogConfig m_logConfig;
	wofstream m_outStream;
};