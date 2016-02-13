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

	wofstream::openmode openMode = wofstream::out;
	if (!m_logConfig.bOverwrite)
		openMode |= wofstream::app;
	m_outStream.open(m_logConfig.wstrOutFile.c_str(), openMode);
}

void CSimpleLogger::WriteLog(const wstring &wstrData)
{
	m_outStream << wstrData;
}

