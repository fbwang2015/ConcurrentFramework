/*
 * main.cpp
 *
 *  Created on: Aug 18, 2018
 *      Author: fabiao2018
 */
#include <memory>
#include <string>

#include "workflow.hpp"
#include "agent.hpp"

struct DataItem
{
	std::string name;
	int 		age;


};

int main()
{
	std::shared_ptr<CWorkflow<DataItem>> workflow = std::make_shared<CWorkflow<DataItem>>();

	CAgent<DataItem> agent1(workflow, "Node1");
	CAgent<DataItem> agent2(workflow, "Node2");
	CAgent<DataItem> agent3(workflow, "Node3");
	CAgent<DataItem> agent4(workflow, "Node4");

	workflow->AddNode(agent1);
	workflow->AddNode(agent2);
	workflow->AddNode(agent3);
	workflow->AddNode(agent4);

	workflow->AddEdge(agent1, agent2);
	workflow->AddEdge(agent2, agent3);
	workflow->AddEdge(agent3, agent4);

	workflow->Start(10);

	return 0;
}


