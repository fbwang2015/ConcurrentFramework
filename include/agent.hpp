/*
 * agent.hpp
 *
 *  Created on: Aug 18, 2018
 *      Author: fabiao2018
 */

#ifndef INCLUDE_AGENT_HPP_
#define INCLUDE_AGENT_HPP_

#include <string>
#include <atomic>
#include <memory>

#include "logutil.hpp"
#include "data_queue.hpp"

template<typename T>
class CWorkflow;


template<typename T>
class COperator
{
public:
	void operator()(std::shared_ptr<T> data)
	{
		if(data)
		{
			process(data);
		}
	}
	virtual void process(std::shared_ptr<T> data)
	{
		std::cout<<"COperator processing"<<std::endl;
	}

	virtual ~COperator()
	{

	}
};

enum AgentType
{
	FirstNode = 0,
	NormalNode = 1,
	LastNode = 2
};

template<typename T>
class CAgent
{
public:
	CAgent(std::shared_ptr<CWorkflow<T>> workflow, std::string name, COperator<T>& ops, AgentType type = NormalNode);

	void SetWorkflow(std::shared_ptr<CWorkflow<T>> workflow);

	void SetInputDataQueue(std::shared_ptr<CDataQueue<T>> input_data);

	std::shared_ptr<CDataQueue<T>> GetInputDataQueue();

	void SetOutputDataQueue(std::shared_ptr<CDataQueue<T>> output_data);

	std::shared_ptr<CDataQueue<T>> GetOutputDataQueue();

	int GetInputDataCount();

	int GetProcessedDataCount();

	int GetThreadCount();

	std::string& GetAgentName();

	AgentType GetAgentType();

	void Processing();


private:
	std::string m_name;

	AgentType m_type;

	COperator<T>& m_operator;

	std::shared_ptr<CWorkflow<T>> m_workflow;

	std::shared_ptr<CDataQueue<T>>  m_inputdata, m_outputdata;

	std::atomic<int> m_processed_count;

	std::atomic<int> m_thread_count;
};

template<typename T>
CAgent<T>::CAgent(std::shared_ptr<CWorkflow<T>> workflow, std::string name, COperator<T>& ops, AgentType type): m_operator(ops)
{
	m_workflow = workflow;

	m_name = name;

	m_type = type;

	m_processed_count = 0;

	m_thread_count = 0;
}

template<typename T>
void CAgent<T>::SetWorkflow(std::shared_ptr<CWorkflow<T>> workflow)
{
	m_workflow = workflow;
}

template<typename T>
void CAgent<T>::SetInputDataQueue(std::shared_ptr<CDataQueue<T>> input_data)
{
	m_inputdata = input_data;
}


template<typename T>
std::shared_ptr<CDataQueue<T>> CAgent<T>::GetInputDataQueue()
{
	return m_inputdata;
}


template<typename T>
void CAgent<T>::SetOutputDataQueue(std::shared_ptr<CDataQueue<T>> output_data)
{
	m_outputdata = output_data;
}

template<typename T>
std::shared_ptr<CDataQueue<T>> CAgent<T>::GetOutputDataQueue()
{
	return m_outputdata;
}

template<typename T>
std::string& CAgent<T>::GetAgentName()
{
	return m_name;
}


template<typename T>
void CAgent<T>::Processing()
{
	m_thread_count++;

	std::shared_ptr<T> data = m_inputdata->GetOneData();

	if(data)
	{
		m_operator(data);

		m_outputdata->AddOneData(data);

		m_processed_count++;
	}

	m_thread_count--;
}

template<typename T>
AgentType CAgent<T>::GetAgentType()
{
	return m_type;
}

template<typename T>
int CAgent<T>::GetProcessedDataCount()
{
	return m_processed_count;
}


template<typename T>
int CAgent<T>::GetInputDataCount()
{
	return m_inputdata->GetSize();
}

template<typename T>
int CAgent<T>::GetThreadCount()
{
	return m_thread_count;
}


#endif /* INCLUDE_AGENT_HPP_ */
