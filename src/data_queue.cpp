/*
 * data_queue.cpp
 *
 *  Created on: Aug 21, 2018
 *      Author: fabiao2018
 */

#include "data_queue.hpp"

template<class T>
CDataQueue<T>::CDataQueue()
{

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
