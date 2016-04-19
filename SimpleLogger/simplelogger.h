#pragma once

#include <windows.h>
#include <string>
#include <fstream>

using std::wstring;
using std::wofstream;

#define BEGIN_NAMESPACE_SLOG namespace slog {
#define END_NAMESPACE_SLOG };

BEGIN_NAMESPACE_SLOG

const int kLogMaxBufSize = 1024 * 4;

#define LOG_DEBUG(format, ...) do { \
	wchar_t buf[kLogMaxBufSize] = {0}; \
	swprintf_s(buf, L" [DEBUG] " format, ##__VA_ARGS__); \
	CSimpleLogger::Instance().WriteLog(buf); \
}while (0);

#define LOG_INFO(format, ...) do { \
	wchar_t buf[kLogMaxBufSize] = {0}; \
	swprintf_s(buf, L" [INFO] " format, ##__VA_ARGS__); \
	CSimpleLogger::Instance().WriteLog(buf); \
}while (0);

#define LOG_WARN(format, ...) do { \
	wchar_t buf[kLogMaxBufSize] = {0}; \
	swprintf_s(buf, L" [WARN] " format, ##__VA_ARGS__); \
	CSimpleLogger::Instance().WriteLog(buf); \
}while (0);

#define LOG_ERROR(format, ...) do { \
	wchar_t buf[kLogMaxBufSize] = {0}; \
	swprintf_s(buf, L" [ERROR] " format, ##__VA_ARGS__); \
	CSimpleLogger::Instance().WriteLog(buf); \
}while (0);

#define LOG_FATAL(format, ...) do { \
	wchar_t buf[kLogMaxBufSize] = {0}; \
	swprintf_s(buf, L" [FATAL] " format, ##__VA_ARGS__); \
	CSimpleLogger::Instance().WriteLog(buf); \
}while (0);

struct LogConfig
{
	wstring wstrOutFile;
	bool bOverwrite;
	int nFileSizeLimit;		// log文件大小限制（字节）
};

class CSimpleLogger
{
public:
	static CSimpleLogger& Instance()
	{
		static CSimpleLogger instance;
		return instance;
	}
	~CSimpleLogger();

	// 初始化设置
	void InitLogger(const LogConfig &logCfg);
	void WriteLog(const wstring &wstrData);

private:
	CSimpleLogger();
	CSimpleLogger(CSimpleLogger&);
	void operator = (CSimpleLogger&);

	int GetLogFileSize();
	int CheckLogFileSize();

private:
	static const int kLogFileMaxSize = 1024 * 1024 * 100;
	LogConfig m_logConfig;
	wofstream m_outStream;
};

END_NAMESPACE_SLOG