/*
 * data_queue.hpp
 *
 *  Created on: Aug 21, 2018
 *      Author: fabiao2018
 */

#ifndef INCLUDE_DATA_QUEUE_HPP_
#define INCLUDE_DATA_QUEUE_HPP_

#include <queue>
#include <memory>
#include <mutex>
#include <string>

#include "logutil.hpp"

template<class T>
class CDataQueue
{
public:
	CDataQueue(std::string& name);

	std::shared_ptr<T> GetOneData();

	bool AddOneData(std::shared_ptr<T> data);

	int  GetSize();

private:
	std::mutex m_mutex;

	std::string m_name;

	std::queue<std::shared_ptr<T>> m_dataqueue;
};


template<class T>
CDataQueue<T>::CDataQueue(std::string& name)
{
	m_name = name;
}

template<class T>
std::shared_ptr<T> CDataQueue<T>::GetOneData()
{
	std::shared_ptr<T> data = nullptr;

	std::lock_guard<std::mutex> lock(m_mutex);

	if(!m_dataqueue.empty())
	{
		data = m_dataqueue.front();
		m_dataqueue.pop();
	}

	return data;
}

template<class T>
bool CDataQueue<T>::AddOneData(std::shared_ptr<T> data)
{
	std::lock_guard<std::mutex> lock(m_mutex);

	m_dataqueue.push(data);

}

template<class T>
int CDataQueue<T>::GetSize()
{
	return m_dataqueue.size();
}


#endif /* INCLUDE_DATA_QUEUE_HPP_ */
