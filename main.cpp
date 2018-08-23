/*
 * main.cpp
 *
 *  Created on: Aug 18, 2018
 *      Author: fabiao2018
 */
#include <memory>
#include <string>

#include "logutil.hpp"
#include "workflow.hpp"
#include "agent.hpp"
#include "data_queue.hpp"

struct DataItem
{
	std::string name;
	int 		age;

};

template<typename T>
class CAgent1Operator:public COperator<T>
{
	void process(std::shared_ptr<T> data)
	{
		std::cout<<"CAgentOperator 1 processing"<<std::endl;
	}
};

template<typename T>
class CAgent2Operator:public COperator<T>
{
	void process(std::shared_ptr<T> data)
	{
		std::cout<<"CAgentOperator 2 processing"<<std::endl;
	}
};

template<typename T>
class CAgent3Operator:public COperator<T>
{
	void process(std::shared_ptr<T> data)
	{
		std::cout<<"CAgentOperator 3 processing"<<std::endl;
	}
};

template<typename T>
class CAgent4Operator:public COperator<T>
{
	void process(std::shared_ptr<T> data)
	{
		std::cout<<"CAgentOperator 4 processing"<<std::endl;
	}
};

int main()
{
	std::shared_ptr<CWorkflow<DataItem>> workflow = std::make_shared<CWorkflow<DataItem>>();

	auto op1 = CAgent1Operator<DataItem>();
	auto op2 = CAgent1Operator<DataItem>();
	auto op3 = CAgent1Operator<DataItem>();
	auto op4 = CAgent1Operator<DataItem>();

	std::shared_ptr<CAgent<DataItem>> node1 = std::make_shared<CAgent<DataItem>>(workflow, "Node1", op1, FirstNode);
	std::shared_ptr<CAgent<DataItem>> node2 = std::make_shared<CAgent<DataItem>>(workflow, "Node2", op2, NormalNode);
	std::shared_ptr<CAgent<DataItem>> node3 = std::make_shared<CAgent<DataItem>>(workflow, "Node3", op3, NormalNode);
	std::shared_ptr<CAgent<DataItem>> node4 = std::make_shared<CAgent<DataItem>>(workflow, "Node4", op4, LastNode);

	workflow->AddNode(node1);
	workflow->AddNode(node2);
	workflow->AddNode(node3);
	workflow->AddNode(node4);

	workflow->AddEdge(node1, node2);
	workflow->AddEdge(node2, node3);
    workflow->AddEdge(node3, node4);

	workflow->Start(10);

	return 0;
}


