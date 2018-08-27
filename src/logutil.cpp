/*
 * logutil.cpp
 *
 *  Created on: Aug 25, 2018
 *      Author: fabiao2018
 */

#include "logutil.hpp"
#include <functional>

CLog::CLog():m_log(nullptr), m_writethread(std::bind(&CLog::Write, this))
{

}

CLog* CLog::GetInstance()
{
	if(m_log == nullptr)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		if(m_log == nullptr)
		{
			m_log = new CLog();
		}
	}

	return m_log;
}
void CLog::Log(std::string& str)
{
	std::lock_guard<std::mutex> lock(m_msgmutex);

	m_msg.push(str);
}

void CLog::Write()
{
	std::string str;

	while(true)
	{
		std::lock_guard<std::mutex> lock(m_msgmutex);

		if(!m_msg.empty())
		{
			str = m_msg.front();
			m_msg.pop();
		}else
		{
			std::this_thread::sleep_for(std::chrono::seconds(2));
		}

		WriteToFile(str);
	}
}


void CLog::WriteToFile(std::string& str)
{

}

int CLog::GetMsgQueueSize()
{
	std::lock_guard<std::mutex> lock(m_msgmutex);

	return m_msg.size();
}

