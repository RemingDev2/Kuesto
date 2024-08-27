#include "../../headers/excel/DataXLSXtraction.h"
#include "../../../external/tinyxml2/tinyxml2.h"

void DataXLSXtraction::extractData()
{

}

// renvoi de la map des données extraites
std::map<std::string, std::map<std::string, std::string>> DataXLSXtraction::getMap() { return dataMap; }
