/*
 * workflow.hpp
 *
 *  Created on: Aug 20, 2018
 *      Author: fabiao2018
 */

#ifndef INCLUDE_WORKFLOW_HPP_
#define INCLUDE_WORKFLOW_HPP_

#include <map>
#include <memory>
#include <vector>
#include <thread>
#include <string>

#include "agent.hpp"
#include "worker.hpp"
#include "logutil.hpp"
#include "environment.hpp"

template<typename T>
class CWorkflow
{
public:
	bool AddNode(std::shared_ptr<CAgent<T>> node);

	bool AddEdge(std::shared_ptr<CAgent<T>> from_node, std::shared_ptr<CAgent<T>> to_node);

	std::vector<std::shared_ptr<CAgent<T>>> GetTargetNodes(std::shared_ptr<CAgent<T>> node);

	std::vector<std::shared_ptr<CAgent<T>>> GetSourceNodes(std::shared_ptr<CAgent<T>> node);

	std::shared_ptr<CAgent<T>> GetNextRequestNode();

	void Start(int thread_num);


private:

	std::vector<std::shared_ptr<std::thread>> m_threadpool;

	std::vector<std::shared_ptr<CAgent<T>>> m_vertexs;

	std::vector<std::pair<std::string, std::string>> m_edges;

	std::map<std::string, std::shared_ptr<CDataQueue<T>>> m_dataqueues;

};

template<typename T>
bool CWorkflow<T>::AddNode(std::shared_ptr<CAgent<T>> node )
{

	std::shared_ptr<CDataQueue<T>> dataqueue =  std::make_shared<CDataQueue<T>>(node->GetAgentName());

	m_dataqueues.insert(std::pair<std::string, std::shared_ptr<CDataQueue<T>>>(node->GetAgentName(),dataqueue));

	node->SetInputDataQueue(dataqueue);

	m_vertexs.push_back(node);

	return true;
}

template<typename T>
bool CWorkflow<T>::AddEdge(std::shared_ptr<CAgent<T>> from_node, std::shared_ptr<CAgent<T>> to_node)
{
	from_node->SetOutputDataQueue(to_node->GetInputDataQueue());

	m_edges.push_back(std::pair<std::string, std::string>(from_node->GetAgentName(), to_node->GetAgentName()));

	return true;
}

template<typename T>
std::vector<std::shared_ptr<CAgent<T>>> CWorkflow<T>::GetTargetNodes(std::shared_ptr<CAgent<T>> node)
{

	std::vector<std::shared_ptr<CAgent<T>>> nodes;

	return nodes;
}

template<typename T>
std::vector<std::shared_ptr<CAgent<T>>> CWorkflow<T>::GetSourceNodes(std::shared_ptr<CAgent<T>> node)
{
	std::vector<std::shared_ptr<CAgent<T>>> nodes;

	return nodes;
}

template<typename T>
std::shared_ptr<CAgent<T>> CWorkflow<T>::GetNextRequestNode()
{	//Thread safe requirement
	std::cout<<"=============GetNextRequestNode============="<<std::endl;
	std::shared_ptr<CAgent<T>> node = m_vertexs[0];

	return node;
}

template<typename T>
void CWorkflow<T>::Start(int thread_num)
{
	for(int i = 0; i<thread_num; i++)
	{
		std::shared_ptr<std::thread> thread = std::make_shared<std::thread>(CWorker<T>(*this));

		m_threadpool.push_back(thread);
	}
	for(int i = 0; i<thread_num; i++)
	{
		if(m_threadpool[i]->joinable())
		{
			m_threadpool[i]->join();
		}
	}
}


#endif /* INCLUDE_WORKFLOW_HPP_ */
