/*
 * agent.hpp
 *
 *  Created on: Aug 18, 2018
 *      Author: fabiao2018
 */

#ifndef INCLUDE_AGENT_HPP_
#define INCLUDE_AGENT_HPP_

#include <memory>

#include "data_queue.hpp"

template<typename T>
class CWorkflow;

template<typename T>
class CAgent
{
public:
	CAgent(CWorkflow<T>& workflow);

	void SetInputDataQueue(std::shared_ptr<CDataQueue<T>> input_data);

	void SetOutputDataQueue(std::shared_ptr<CDataQueue<T>> output_data);

	int GetInputDataCount();

	int GetOutputDataCount();


private:

	std::shared_ptr<CDataQueue<T>>  m_inputdata, m_outputdata;

	CWorkflow<T>& m_workflow;
};

#endif /* INCLUDE_AGENT_HPP_ */
