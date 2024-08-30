#include "../../headers/excel/DataXLSXtraction.h"
#include "../../../external/tinyxml2/tinyxml2.h"
#include <filesystem>


void DataXLSXtraction::extractData()
{
    std::string tempDirPath = "temp/extracted_sheets"; // chemin vers le dossier temporaire

//    for (const auto& sheet : std::filesystem::directory_iterator(tempDirPath)) // pour chaque feuille
//    {
//
//    }
    tinyxml2::XMLDocument sheetFile; // init objet pour contenir feuille
    std::string sheetPath= tempDirPath + "/sheet1.xml"; // donnée brut pour test
    sheetFile.LoadFile(sheetPath.c_str()); // chargement xml dans objet

}

// renvoi de la map des données extraites
std::map<std::string, std::map<std::string, std::string>> DataXLSXtraction::getMap() { return dataMap; }
