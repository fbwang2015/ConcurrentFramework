/*
 * worker.hpp
 *
 *  Created on: Aug 22, 2018
 *      Author: fabiao2018
 */

#ifndef INCLUDE_WORKER_HPP_
#define INCLUDE_WORKER_HPP_

#include <memory>
#include <thread>
#include <chrono>

#include "agent.hpp"
#include "logutil.hpp"

template<typename T>
class CWorker
{
public:
	CWorker(CWorkflow<T>& workflow);
	void operator()();
private:
	CWorkflow<T>& m_workflow;
};

template<typename T>
void CWorker<T>::operator ()()
{
	while(true)
	{
		std::shared_ptr<CAgent<T>> node = m_workflow.GetNextRequestNode();

		if(node)
		{
			node->Processing();
		}else
		{
			std::cout<<"all agent's data queue is empty, sleep 4s"<<std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(4));
		}
	}
}

template<typename T>
CWorker<T>::CWorker(CWorkflow<T>& workflow):m_workflow(workflow)
{

}


#endif /* INCLUDE_WORKER_HPP_ */
