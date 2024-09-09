#include "../../headers/excel/DataXLSXtraction.h"
#include "../../../external/tinyxml2/tinyxml2.h"
#include <filesystem>
#include <regex>
#include <iostream>


void DataXLSXtraction::extractData()
{
    std::string tempDirPath = "temp/xlsx_extracted"; // chemin vers le dossier temporaire

//    for (const auto& sheet : std::filesystem::directory_iterator(tempDirPath)) // pour chaque feuille
//    {
//
//    }
    tinyxml2::XMLDocument sheetFile; // init objet pour contenir feuille

    std::string sheetPath= tempDirPath + "/sheet1.xml"; // donnée brut pour test
    sheetFile.LoadFile(sheetPath.c_str()); // chargement xml dans objet

    // considérer un pointeur situe au niveau du balise
    // pour ne pas confondre avec un pointeur CPP, appelons ça un curseur
    tinyxml2::XMLElement* root = sheetFile.RootElement(); // curseur sur la balise racine

    tinyxml2::XMLElement* sheet = root->FirstChildElement("sheetData"); // curseur sur la balise sheetData

    int increment(0); // init increment 0 pour numero ligne

    // a chaque ligne
    for (tinyxml2::XMLElement* row = sheet->FirstChildElement("row"); // curseur sur 1e balise row
    row != nullptr; // jusqu'a pointeur 0 = plus de lignes
    row = row->NextSiblingElement("row")) // aller prochaine balise "row" = prochaine ligne
    {
        ++increment;

        // a chaque cellule
        for (tinyxml2::XMLElement* cell = row->FirstChildElement("c"); // curseur sur 1e balise c (cell)
        cell != nullptr; // jusqu'a pointeur 0 = plus de cellule sur ligne
        cell = cell->NextSiblingElement("c")) // aller prochaine cellule
        {
            // attention cellule vide au milieu !
            // considerons pour le moment que les reponses sont en lignes et non en colonnes

            std::string rowCellAttribute = cell->Attribute("r");
            switch (rowCellAttribute.find('A') == 0 ? 1 :
                    rowCellAttribute.find('B') == 0 ? 2 :
                    rowCellAttribute.find('C') == 0 ? 3 :
                    0)
            {
                case 1:
                    // une categorie peut pas être un bombre
                    // recuperer valeur v
                    // aller chercher dans liste sharedStrings à l'indice donne par v
                    break;
                case 2:
                    if (cell->Attribute("t") == "s")
                    {
                        // recuperer valeur v
                        // aller chercher dans liste sharedStrings à l'indice donne par v
                        continue;
                    }
                    break;
                case 3:
                    break;
                default:
                    break;
            }
                // sinon recupere valeur de v
            // sinon si r="C." lettre suivante
                // si t="s" = texte
                    // recuperer valeur v
                    // aller chercher dans liste sharedStrings à l'indice donne par v
                // sinon recuperer valeur de v
        }
    }
}

// renvoi de la map des données extraites
std::map<std::string, std::map<std::string, std::string>> DataXLSXtraction::getMap() { return dataMap; }
