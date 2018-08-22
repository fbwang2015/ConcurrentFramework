/*
 * workflow.hpp
 *
 *  Created on: Aug 20, 2018
 *      Author: fabiao2018
 */

#ifndef INCLUDE_WORKFLOW_HPP_
#define INCLUDE_WORKFLOW_HPP_

#include <memory>
#include <vector>
#include <thread>
#include <string>

#include "agent.hpp"
#include "worker.hpp"
#include "environment.hpp"

template<typename T>
class CWorkflow
{
public:
	bool AddNode(CAgent<T>& node);

	bool AddEdge(CAgent<T>& from_node, CAgent<T>& to_node);

	std::vector<std::shared_ptr<CAgent<T>>>& GetTargetNodes(CAgent<T>& node);

	std::vector<std::shared_ptr<CAgent<T>>>& GetSourceNodes(CAgent<T>& node);

	std::shared_ptr<CAgent<T>> GetNextRequestNode();

	void Start(int thread_num);


private:

	std::vector<std::shared_ptr<std::thread>> m_threadpool;

	std::vector<std::shared_ptr<CAgent<T>>> m_vertexs;

	std::vector<std::pair<std::string, std::string>> m_edges;

};

template<typename T>
bool CWorkflow<T>::AddNode(CAgent<T>& node)
{

	return true;
}

template<typename T>
bool CWorkflow<T>::AddEdge(CAgent<T>& from_node, CAgent<T>& to_node)
{

	return true;
}

template<typename T>
std::vector<std::shared_ptr<CAgent<T>>>& CWorkflow<T>::GetTargetNodes(CAgent<T>& node)
{

	std::vector<std::shared_ptr<CAgent<T>>> nodes;

	return nodes;
}

template<typename T>
std::vector<std::shared_ptr<CAgent<T>>>& CWorkflow<T>::GetSourceNodes(CAgent<T>& node)
{
	std::vector<std::shared_ptr<CAgent<T>>> nodes;

	return nodes;
}

template<typename T>
std::shared_ptr<CAgent<T>> CWorkflow<T>::GetNextRequestNode()
{

}

template<typename T>
void CWorkflow<T>::Start(int thread_num)
{
	for(int i = 0; i<thread_num; i++)
	{
		std::shared_ptr<std::thread> thread = std::make_shared<std::thread>(CWorker<T>(*this));

		m_threadpool.push_back(thread);
	}
}


#endif /* INCLUDE_WORKFLOW_HPP_ */
