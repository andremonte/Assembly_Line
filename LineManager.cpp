//***********************************************************
// OOP345 Milestone 3:                    LineManager.cpp   /
/////////////////////////////////////////////////////////////
// Name: Andre Machado do Monte     - Date: Ago 12, 2018   //
/////////////////////////////////////////////////////////////
//**********************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "LineManager.h"
#include "Utilities.h"

	int findInVector(std::vector<Task*>& tarefa, std::string field) {
		int taskindex = -1;
		for(size_t index = 0; index < tarefa.size(); index++)
			if(*tarefa[index] == field)
			{
				taskindex = index;
				break;
			}
		return taskindex;
	}
	
	LineManager::LineManager(std::string& file, std::vector<Task*>& tarefa, std::vector<CustomerOrder>& ordem) {
		//tmp variables to this function;
		std::string line, nome1, nome2;
		Utilities ut;
        size_t next_p = 0;
        bool more = true;

		CustomerOrder_Count = ordem.size();
		AssemblyLine = tarefa;

		//reading file received as parameter.
		std::ifstream is(file, std::ios::in);
		if(is.is_open()) {
			while(is.good()) {
				getline(is, line);

				next_p = 0;
				more = true;
				nome1 = ut.extractToken(line, next_p, more);

				if (more) {
					nome2 = ut.extractToken(line, next_p, more);
				
					int secondTaskindex = findInVector(AssemblyLine, nome2);
					int firstfTaskindex = findInVector(AssemblyLine, nome1);

					if(firstfTaskindex != -1 && secondTaskindex != -1) {
						AssemblyLine[firstfTaskindex]->setNextTask(*AssemblyLine[secondTaskindex]);
					}
				}		
			}
		is.close();
		}/*
		for (size_t i = 0; i < AssemblyLine.size(); i++) {
			AssemblyLine[i]->Validate(std::cout);
		}*/

		for(size_t i = 0; i < ordem.size(); i++) {
			ToBeFilled.push_front(std::move(ordem[i]));
		}

		/*for (size_t i = 0; i < ToBeFilled.size(); i++) {
			ToBeFilled[i].Display(std::cout);
		}*/
	}


	//Processes each assembly line task and moves the CustomerOrders through the line
	//Returning true if all items have been completed
	//if there is customer order put assembly
	//
	
	bool LineManager::Run(std::ostream& os) {
		//for (unsigned i = 0; i < AssemblyLine.size(); i++) {
		//	AssemblyLine[i]->display(std::cout, false);
		//	std::cout << std::endl;
		//}
		//return true;

		//Adiciona a ultima ordem na primeira tarefa da linha de montagem
		if(!ToBeFilled.empty()) {
			(*getStartAssembleLine()) += (CustomerOrder&&)ToBeFilled.back();
			ToBeFilled.pop_back();
		}

		//Executa um ciclo nas tarefas de montagem
		for (unsigned i = 0; i < AssemblyLine.size(); i++) {
			AssemblyLine[i]->RunProcess(os);
		}

		//Movimenta as ordens para a proxima tarefa de montagem
		for(unsigned i = 0; i < AssemblyLine.size(); i++) {
			AssemblyLine[i]->MoveTask();
		}

		//Retira as ordens completas da linha de montagem
		for (size_t i = 0; i < AssemblyLine.size(); i++) {
			CustomerOrder c;

			if(AssemblyLine[i]->getCompleted(c) == true) {
				Completed.push_back(std::move(c));
			}
		}

		//Verifica se todas as ordens já foram completadas
		if (Completed.size() == CustomerOrder_Count) {
			os << std::endl << "COMPLETED" << std::endl;
			for (size_t i = 0; i < Completed.size(); i++) {
				Completed[i].Display(os);
			}

			return true;
		}

		return false;
	}

	Task* LineManager::getStartAssembleLine() {
		bool alguemAponta;
		Task *p = nullptr;

		for(unsigned i = 0; i < AssemblyLine.size(); i++) {
			//achando uma task que ninguem aponte p ela
			alguemAponta = false;

			for (unsigned z = 0; z < AssemblyLine.size(); z++) {
				if (AssemblyLine[z]->getNextTask() == AssemblyLine[i]) {
					alguemAponta = true;
				}
			}

			if (alguemAponta == false) {
				p = AssemblyLine[i];
			}			
		}
		return p;
	}