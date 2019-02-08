//***********************************************************
// OOP345 Milestone 3:                      Utilities.cpp   /
/////////////////////////////////////////////////////////////
// Name: Andre Machado do Monte     -  Date: Ago 12, 2018  //
/////////////////////////////////////////////////////////////
//**********************************************************/
#include <iostream>
#include <string>
#include "Utilities.h"

using namespace std;

	char Utilities::delimiter;

	Utilities::Utilities() {
		field_width = 1;
	}

	void Utilities::setFieldWidth(size_t fw) {
		field_width = fw;
	}

	size_t Utilities::getFieldWidth() const {
		return field_width;
	}

	const std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		size_t i;
		string result = "";
		
		for (i = next_pos; i < str.length(); i++) {
			if (str[i] != delimiter && str[i] != '\n' && str[i] != '\r') {
				result += str[i];
				
			} else if(str[i+1] == delimiter) {
				throw "There is no token between them";
			} else {
				break;
			}
		}

		//Verificando more e atualizando next_position
		// str.length() - 1 = porque o i contou até o delimitador.
		if (i < str.length() - 1) {
			more = true;
			next_pos = i+1; //i+1 porque i esta no delimitador.
		} else {
			more = false;
			next_pos = 0;
		}

		//Atualizando field_with
		if(field_width < result.length()) {
			field_width = result.length();
		}

		return result;
	}

	void Utilities::setDelimiter(const char character) {
			delimiter = character;
	}

	const char Utilities::getDelimiter() const {
		return delimiter;
	}

