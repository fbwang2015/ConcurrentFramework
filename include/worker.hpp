/*
 * worker.hpp
 *
 *  Created on: Aug 22, 2018
 *      Author: fabiao2018
 */

#ifndef INCLUDE_WORKER_HPP_
#define INCLUDE_WORKER_HPP_

#include <memory>

#include "agent.hpp"

#include <iostream>

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
	std::cout<<"============CWorker operator============="<<std::endl;

	std::shared_ptr<CAgent<T>> node = m_workflow.GetNextRequestNode();

	if(node)
	{
		node->Processing();
	}
}

template<typename T>
CWorker<T>::CWorker(CWorkflow<T>& workflow):m_workflow(workflow)
{

}


#endif /* INCLUDE_WORKER_HPP_ */
