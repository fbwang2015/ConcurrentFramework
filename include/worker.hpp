/*
 * worker.hpp
 *
 *  Created on: Aug 22, 2018
 *      Author: fabiao2018
 */

#ifndef INCLUDE_WORKER_HPP_
#define INCLUDE_WORKER_HPP_

#include "workflow.hpp"

template<typename T>
class CWorker
{
public:
	void operator()(CWorkflow<T>& workflow);
};



#endif /* INCLUDE_WORKER_HPP_ */
