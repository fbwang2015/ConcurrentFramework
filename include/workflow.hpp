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

#include "agent.hpp"

template<typename T>
class CWorkflow
{
public:

	bool AddNode(CAgent<T>& node);

	bool AddEdge(CAgent<T>& from_node, CAgent<T>& to_node);

	std::vector<std::shared_ptr<CAgent<T>>>& GetTargetNodes(CAgent<T>& node);

	std::vector<std::shared_ptr<CAgent<T>>>& GetSourceNodes(CAgent<T>& node);
private:

};


#endif /* INCLUDE_WORKFLOW_HPP_ */
