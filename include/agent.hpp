/*
 * agent.hpp
 *
 *  Created on: Aug 18, 2018
 *      Author: fabiao2018
 */

#ifndef INCLUDE_AGENT_HPP_
#define INCLUDE_AGENT_HPP_

#include <string>
#include <memory>

#include "data_queue.hpp"

template<typename T>
class CWorkflow;


template<typename T>
class COperator
{
public:
	void operator()(std::shared_ptr<T> data)
	{
		process(data);
	}
	virtual void process(std::shared_ptr<T> data)
	{

	}

	virtual ~COperator()
	{

	}
};


template<typename T>
class CAgent
{
public:
	CAgent(std::shared_ptr<CWorkflow<T>> workflow, std::string name);

	void SetWorkflow(std::shared_ptr<CWorkflow<T>> workflow);

	void SetInputDataQueue(std::shared_ptr<CDataQueue<T>> input_data);

	void SetOutputDataQueue(std::shared_ptr<CDataQueue<T>> output_data);

	int GetInputDataCount();

	int GetOutputDataCount();

	void SetOperator(COperator<T> & ops);

	void Processing();


private:
	std::string m_name;

	COperator<T> m_operator;

	std::shared_ptr<CWorkflow<T>> m_workflow;

	std::shared_ptr<CDataQueue<T>>  m_inputdata, m_outputdata;
};



template<typename T>
CAgent<T>::CAgent(std::shared_ptr<CWorkflow<T>> workflow, std::string name)
{
	m_workflow = workflow;

	m_name = name;
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
void CAgent<T>::SetOutputDataQueue(std::shared_ptr<CDataQueue<T>> output_data)
{
	m_outputdata = output_data;
}

template<typename T>
void CAgent<T>::SetOperator(COperator<T> & ops)
{

}


template<typename T>
void CAgent<T>::Processing()
{
	m_operator(m_inputdata.GetOneData());
}


#endif /* INCLUDE_AGENT_HPP_ */
