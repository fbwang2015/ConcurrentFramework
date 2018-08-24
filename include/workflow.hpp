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
#include <mutex>

#include "agent.hpp"
#include "worker.hpp"
#include "logutil.hpp"
#include "environment.hpp"

template<typename T>
class CWorkflow
{
public:
	CWorkflow(CEnvironment& env);

	bool AddNode(std::shared_ptr<CAgent<T>> node);

	bool AddEdge(std::shared_ptr<CAgent<T>> from_node, std::shared_ptr<CAgent<T>> to_node);

	std::vector<std::shared_ptr<CAgent<T>>> GetTargetNodes(std::shared_ptr<CAgent<T>> node);

	std::vector<std::shared_ptr<CAgent<T>>> GetSourceNodes(std::shared_ptr<CAgent<T>> node);

	std::shared_ptr<CAgent<T>> GetFirstNode();

	std::shared_ptr<CAgent<T>> GetLastNode();

	std::shared_ptr<CDataQueue<T>> GetInputDataQueue();

	std::shared_ptr<CDataQueue<T>> GetOutputDataQueue();

	std::shared_ptr<CAgent<T>> GetNextRequestNode();

	CEnvironment& GetEnvironment();

	void Start(int thread_num);

	bool Stop();


private:
	bool m_active;

	CEnvironment& m_env;

	std::mutex m_mutex;

	std::vector<std::shared_ptr<std::thread>> m_threadpool;

	std::vector<std::shared_ptr<CAgent<T>>> m_vertexs;

	std::vector<std::pair<std::string, std::string>> m_edges;

	std::map<std::string, std::shared_ptr<CDataQueue<T>>> m_dataqueues;

};

template<typename T>
CWorkflow<T>::CWorkflow(CEnvironment& env):m_active(false), m_env(env)
{

}

template<typename T>
bool CWorkflow<T>::AddNode(std::shared_ptr<CAgent<T>> node )
{

	std::shared_ptr<CDataQueue<T>> dataqueue =  std::make_shared<CDataQueue<T>>(node->GetAgentName());

	m_dataqueues.insert(std::pair<std::string, std::shared_ptr<CDataQueue<T>>>(node->GetAgentName(),dataqueue));

	node->SetInputDataQueue(dataqueue);

	if(node->GetAgentType() == LastNode)
	{
		std::string output("output");
		std::shared_ptr<CDataQueue<T>> dataqueue =  std::make_shared<CDataQueue<T>>(output);

		m_dataqueues.insert(std::pair<std::string, std::shared_ptr<CDataQueue<T>>>(output,dataqueue));

		node->SetOutputDataQueue(dataqueue);
	}

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
{
	std::lock_guard<std::mutex> lock(m_mutex);

	std::shared_ptr<CAgent<T>> next_node = nullptr;

	if(m_active)
	{
		int process_data_count = 0;
		for(auto& node : m_vertexs)
		{
			if(node->GetInputDataCount() > 0)
			{
				if( node->GetThreadCount()<= 0)
				{
					next_node = node;

					break;
				}else
				{
					if(next_node == nullptr)
					{
						next_node = node;
					}else
					{
						if(node->GetProcessedDataCount() < next_node->GetProcessedDataCount())
						{
							next_node = node;
						}
					}
				}
			}
		}
	}

	return next_node;
}

template<typename T>
void CWorkflow<T>::Start(int thread_num)
{
	m_active = true;

	for(int i = 0; i<thread_num; i++)
	{
		std::shared_ptr<std::thread> thread = std::make_shared<std::thread>(CWorker<T>(*this));

		m_threadpool.push_back(thread);
	}
}

template<typename T>
bool CWorkflow<T>::Stop()
{
	m_active = false;

	for(auto& thread : m_threadpool)
	{
		if(thread->joinable())
		{
			thread->join();
		}
	}
}

template<typename T>
std::shared_ptr<CAgent<T>> CWorkflow<T>::GetFirstNode()
{
	std::shared_ptr<CAgent<T>> node = nullptr;

	for(auto nd : m_vertexs)
	{
		if(nd->GetAgentType() == FirstNode)
		{
			node = nd;
		}
	}

	return node;
}

template<typename T>
std::shared_ptr<CAgent<T>> CWorkflow<T>::GetLastNode()
{
	std::shared_ptr<CAgent<T>> node = nullptr;

	for(auto nd : m_vertexs)
	{
		if(nd->GetAgentType() == LastNode)
		{
			node = nd;
		}
	}

	return node;
}

template<typename T>
std::shared_ptr<CDataQueue<T>> CWorkflow<T>::GetInputDataQueue()
{
	return GetFirstNode()->GetInputDataQueue();
}

template<typename T>
std::shared_ptr<CDataQueue<T>> CWorkflow<T>::GetOutputDataQueue()
{
	return GetLastNode()->GetOutputDataQueue();
}

template<typename T>
CEnvironment& CWorkflow<T>::GetEnvironment()
{
	return m_env;
}


#endif /* INCLUDE_WORKFLOW_HPP_ */
