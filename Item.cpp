//***********************************************************
// OOP345 Milestone 3:                          Item.cpp    /
/////////////////////////////////////////////////////////////
// Name: Andre Machado do Monte     - Date: Ago 12, 2018   //
/////////////////////////////////////////////////////////////
//**********************************************************/
#include <iostream>
#include "Item.h"

using namespace std;

    //takes a record from the items file and parses the data
    Item::Item(std::string& record) {
        Utilities ut;
        std::string token;
        size_t next_p = 0;
        bool more = true;
        int n = 0;

        while (more) {
            ++n;
            token = ut.extractToken(record, next_p, more);

            switch (n) {
                case 1:
                    name = token;
                    break;

                case 2:
                    serialNumber = stoi(token);
                    break;

                case 3:
                    Quantity = stoi(token);
                    break;

                case 4:
                    description = token;
                    break;
            }
        }
        
        if(ut.getFieldWidth() > Item::field_width) {
            Item::field_width = ut.getFieldWidth();
        }
    }						

    //Returns a reference to the items name
    const std::string& Item::getName() const {
        return name;
    }				

    //Returns a reference to the serial number
    const unsigned int Item::getSerialNumber() {
        return serialNumber++;
    }

    //Returns a reference to the remaining quantity			
    const unsigned int Item::getQuantity() {
        return Quantity;
    }

    //Removes 1 from the quantity
    void Item::updateQuantity() {
        if(Quantity > 0) {
            Quantity = Quantity - 1;
        }
    }					

    void Item::display(std::ostream& os, bool full) const {
        if (full) {
             os << left << setw(13) << name << '[' << serialNumber << ']'
        << " Quantity " << left << setw(4) << Quantity << "Description: " << description << endl;
        } 
        
        else {
              os << left << setw(13) << name << '[' << serialNumber << ']';
        }
      
       
    }
