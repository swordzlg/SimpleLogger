#include "simplelogger.h"


CSimpleLogger::CSimpleLogger()
{

}

CSimpleLogger::~CSimpleLogger()
{
	if (m_outStream.is_open())
		m_outStream.close();
}

void CSimpleLogger::InitLogger(const LogConfig &logCfg)
{
	m_logConfig = logCfg;
	if (m_logConfig.nFileSizeLimit > kLogFileMaxSize)
		m_logConfig.nFileSizeLimit = kLogFileMaxSize / 2;
	m_logConfig.nFileSizeLimit /= 2;

	CheckLogFileSize();

	wofstream::openmode openMode = wofstream::out;
	if (!m_logConfig.bOverwrite)
		openMode |= wofstream::app;
	m_outStream.open(m_logConfig.wstrOutFile.c_str(), openMode);
}

void CSimpleLogger::WriteLog(const wstring &wstrData)
{
	m_outStream << wstrData;
}

//
// Func:
//   获取日志文件的大小
// Param:
//   无
// Return:
//   -1 - 获取失败
//   >=0 - 文件大小
//
int CSimpleLogger::GetLogFileSize()
{
	HANDLE hFile = ::CreateFile(
		m_logConfig.wstrOutFile.c_str(),
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
		);
	if (hFile == INVALID_HANDLE_VALUE)
		return -1;
	DWORD dwSize = ::GetFileSize(hFile, NULL);
	::CloseHandle(hFile);
	return dwSize != INVALID_FILE_SIZE ? dwSize : -1;
}

//
// Func:
//   检查日志文件大小是否超出设定值。
//   当日志文件大小超过${SizeLimit}/2，日志文件会被重命名为"${Filename}0.ext"，如果该文件已经存在则覆盖。
//   然后新建文件${Filename}.ext。这样，实际上日志文件被分成两个部分，${Filename}.ext和${Filename}0.ext.
// Param:
//   无
// Return:
//   -1 - 失败
//   >0 - 日志文件剩余容量
//
int CSimpleLogger::CheckLogFileSize()
{
	int nFileSize = GetLogFileSize();
	if (nFileSize == -1)
		return -1;
	if (nFileSize < m_logConfig.nFileSizeLimit)
		return m_logConfig.nFileSizeLimit - nFileSize;
	wstring wstrNewFileName = m_logConfig.wstrOutFile;
	size_t nPos = wstrNewFileName.find_last_of(L'.');
	if (nPos == wstring::npos)
		wstrNewFileName.append(L".part0");
	else
		wstrNewFileName.insert(nPos, L".part0");
	if (::DeleteFile(wstrNewFileName.c_str()) || ::GetLastError() == ERROR_FILE_NOT_FOUND)
	{
		::MoveFile(m_logConfig.wstrOutFile.c_str(), wstrNewFileName.c_str());
	}
	return m_logConfig.nFileSizeLimit;
}