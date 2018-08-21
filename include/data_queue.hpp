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

template<class T>
class CDataQueue
{
public:
	CDataQueue();

	std::shared_ptr<T> GetOneData();

	bool AddOneData(std::shared_ptr<T> data);

private:
	std::mutex m_mutex;

	std::queue<std::shared_ptr<T>> m_dataqueue;
};



#endif /* INCLUDE_DATA_QUEUE_HPP_ */
