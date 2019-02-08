//***********************************************************
// OOP345 Milestone 3:                        Taks.cpp      /
/////////////////////////////////////////////////////////////
// Name: Andre Machado do Monte     - Date: Ago 12, 2018   //
/////////////////////////////////////////////////////////////
//**********************************************************/
#include <iostream>
#include <vector>
#include <string>
#include "Task.h"
using namespace std;

    //Constructor
    Task::Task(std::string& lineOfText) : Item::Item(lineOfText) {
        pNextTask = nullptr;
    }					


    //This function fills the last order on the order queue
    void Task::RunProcess(std::ostream& os) {
        if(!Orders.empty()) {
            if(!Orders.back().getItemFillState(getName())) {
                Orders.back().fillItem(*this, os);                
            }
        }
    }
    

    //This function moves the completed task to the next part of the assembly line		
    bool Task::MoveTask() {
        if (Orders.empty()) {//if is empty return false
            return false;
        }
        else {//if is not empyt and fillstate is true
            if (Orders.back().getItemFillState(getName())) {
                if (pNextTask != nullptr) {
                    pNextTask->Orders.push_front(std::move(Orders.back()));
                    Orders.pop_back();
                }
            }
        }
            return true;
    }


    //Sets up the pointer to the next task if the tasks names line up		
    void Task::setNextTask(Task& proximaTarefa) {
        pNextTask = &proximaTarefa;
    }				

    Task* Task::getNextTask() {
        return pNextTask;
    }

    //Andre: seo vetor ORDERS nao estiver vazio, salvo a ultima ordem em uma variavel, removo essa ordem do vetor ORDERS, e passo a ultima ordem que esta na variavel para src.
    bool Task::getCompleted(CustomerOrder &src) {
  	    if (!Orders.empty()) {
            if (Orders.back().getOrderFillState()) {
                src = std::move(Orders.back());
                Orders.pop_back();
                return true;
            }
        }
        return false;
    }


    void Task::Validate(std::ostream& os) {
        os << "Task: " << getName();
        if (pNextTask != nullptr) {
            os << " moves to task: " << pNextTask->getName();
        }

        os << std::endl;
    }

    bool Task::operator==(std::string str) {
        return str == getName();
    }
    

    Task& Task::operator+=(CustomerOrder&& newOrder) {
        Orders.push_front(std::move(newOrder));
        return *this;
    }