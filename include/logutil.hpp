/*
 * logutil.hpp
 *
 *  Created on: Aug 23, 2018
 *      Author: fabiao2018
 */

#ifndef INCLUDE_LOGUTIL_HPP_
#define INCLUDE_LOGUTIL_HPP_

#include <string>
#include <thread>
#include <queue>
#include <mutex>

#include <iostream>

class CLog
{
public:
	CLog* GetInstance();

	void Log(std::string& str);

	void Write();

	int GetMsgQueueSize();

	virtual void WriteToFile(std::string& str);

private:
	CLog();

	CLog(CLog &);

	CLog& operator=(const CLog&);

	~CLog();

	CLog* m_log;

	std::mutex m_mutex;

	std::mutex m_msgmutex;

	std::thread m_writethread;

	std::queue<std::string> m_msg;
};

#endif /* INCLUDE_LOGUTIL_HPP_ */
