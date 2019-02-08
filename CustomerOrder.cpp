//***********************************************************
// OOP345 Milestone 3:                   CustomerOrder.cpp  /
/////////////////////////////////////////////////////////////
// Name: Andre Machado do Monte     - Date: Ago 12, 2018   //
/////////////////////////////////////////////////////////////
//**********************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include "CustomerOrder.h"
#include "Utilities.h"
#include "Item.h"

using namespace std;

    //Default Constructor

    CustomerOrder::CustomerOrder() {
        Name = "";
        Product = "";
        ItemCount = 0;
        ItemList = nullptr;
        field_width = 0;
    }

    CustomerOrder::CustomerOrder(std::string& str) : CustomerOrder() {
        Utilities ut;
        std::string token;
        size_t next_p = 0;
        bool more = true;
        int n = 0;

        while (more) {
            ++n;
            token = ut.extractToken(str, next_p, more);

            switch (n) {
                case 1:
                    Name = token;
                    break;

                case 2:
                    Product = token;
                    break;

                default:
                    addItemList(token);
                    break;

            }
        }
    }

    CustomerOrder::~CustomerOrder() {
        limparDados();
    }


    void CustomerOrder::limparDados() {
        unsigned int i;

        if (ItemList != nullptr && ItemCount > 0) {
            for (i = 0; i < ItemCount; i++) {
                delete ItemList[i]; //apagando dentro do array/vetor
            }

            delete [] ItemList;//apagando o array/vetor propriamente dito
            ItemList = nullptr;
            ItemCount = 0;
        }
    }


    CustomerOrder::CustomerOrder(CustomerOrder&& p) : CustomerOrder() {
        *this = move(p);
    }

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& z) {
        if(&z != this) {
            limparDados();

            Name = z.Name;
            Product = z.Product;
            ItemCount = z.ItemCount;
            ItemList = z.ItemList;
            field_width = z.field_width;

            z.Name = "";
            z.Product = "";
            z.ItemCount = 0;
            z.ItemList = nullptr;
            z.field_width = 0;
        }
        return *this;
    }

    //Adicionando 1 item
    void CustomerOrder::addItemList(std::string str) {
        ItemInfo** newList;
        unsigned int i, newCount;

        //Verificando se a String não eh vazia
        if (str == "") {
            return;
        }

        //Criando novo array/vetor com mais uma posição
        newList = new ItemInfo*[ItemCount + 1];
        newCount = ItemCount + 1;

        //Copiando todos os itens antigos para o novo array/vetor
        for(i = 0; i < ItemCount; i++) {
            newList[i] = ItemList[i];
        }

        //Adicionando novo item no vetor novo
        newList[ItemCount] = new ItemInfo(str);

        //Deletando vetor antigo
        if(ItemList != nullptr) {
            delete [] ItemList;
            ItemList = nullptr;
        }

        //Substituindo o vetor antigo pelo vetor novo
        ItemList = newList;
        ItemCount = newCount;//valor atualizado(la em cima);
        newList = nullptr;
    }

//Returns true if order completely filled, false otherwise
    //itera pelos itemInfo da itemList, se todos os itemInfos tiverem o
    //property filledState em true, retorna true, otherwise false.
	bool CustomerOrder::getOrderFillState() {
        unsigned i;
        bool r = true;

        for (i = 0; i < ItemCount; i++) {
            if (ItemList[i]->FillState == false) {
                r = false;
            }
        }
        
        return r;
    }

    //Returns true if the given item has been filled
    //itera pela itemList até achar itemInfo com o mesmo nome da string.
    //retorna fillState do iteminfo
    bool CustomerOrder::getItemFillState(std::string str) {
        unsigned i;
        bool r = true;

        for(i = 0; i < ItemCount; i++) {
            if(ItemList[i]->ItemName == str) {
                if (ItemList[i]->FillState == false) {
                    r = false;
                }
            }
        }

        return r;
    }

    //Fills the customer order item if the inventory on Item is available
    //itera pela itemList até achar o itemInfo com o mesmo nome do item que é o primeiro
    //parametro da funcao. Achando ele copia o name e o serialNumber para o itemInfor e coloca o fillState true;
    //depois imprime.
    void CustomerOrder::fillItem(Item& item, std::ostream& os) {
        unsigned i;

        for(i = 0; i < ItemCount; i++) {
            if(ItemList[i]->ItemName == item.getName()) {
                ItemList[i]->ItemName = item.getName();
                ItemList[i]->SerialNumber = item.getSerialNumber();
                ItemList[i]->FillState = true;
                //imprimindo os dados da lista.
                os << "Filled " << Name << ", " << Product << '[' << ItemList[i]->ItemName << ']' << endl;
            }
        }
    }

	void CustomerOrder::Display(std::ostream& os) {
        unsigned i;

        os << Name << endl;
        os << Product << endl;

        for (i = 0; i < ItemCount; i++) {
            os << '[' << ItemList[i]->SerialNumber << "] ";
            os << ItemList[i]->ItemName << " - ";

            if(ItemList[i]->FillState == true) {
                os << "FILLED" << endl;
            }
            else {
                os << "MISSING" << endl;
            }


        }
    }
