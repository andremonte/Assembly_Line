//***********************************************************
// OOP345 Milestone 3:                      LineManager.h   /
/////////////////////////////////////////////////////////////
// Name: Andre Machado do Monte     - Date: Ago 12, 2018   //
/////////////////////////////////////////////////////////////
//**********************************************************/
#pragma once
#include <iostream>
#include <deque>
#include <fstream>
#include <vector>
#include "CustomerOrder.h"
#include "Task.h"

class LineManager
{
	std::vector<Task*> AssemblyLine;		  //using task i know what is the next task
	std::deque<CustomerOrder> ToBeFilled;	  //Queue of Customer Orders to be filled
	std::deque<CustomerOrder> Completed;	  //Queue of Customer Orders completed
	unsigned int CustomerOrder_Count;		  //The number of customer orders the process started with

	Task* getStartAssembleLine();
	

public:
	//Constructor sets the assembly line up by setting up the tasks pNextTask information
	//and moves all the CustomerOrder objects into the ToBeFilled queue
	LineManager(std::string& str, std::vector<Task*>& tarefa, std::vector<CustomerOrder>& ordem);

	//Processes each assembly line task and moves the CustomerOrders through the line
	//Returning true if all items have been completed
	bool Run(std::ostream&);
};