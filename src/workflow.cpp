/*
 * workflow.cpp
 *
 *  Created on: Aug 20, 2018
 *      Author: fabiao2018
 */

#include "workflow.hpp"

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


