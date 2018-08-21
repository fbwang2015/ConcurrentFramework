/*
 * agent.cpp
 *
 *  Created on: Aug 18, 2018
 *      Author: fabiao2018
 */

#include "agent.hpp"

template<typename T>
CAgent<T>::CAgent(CWorkflow<T>& workflow):m_workflow(workflow)
{

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
