#include "../../headers/excel/DataXLSXtraction.h"
#include "../../../external/tinyxml2/tinyxml2.h"
#include <filesystem>
#include <iostream>

void DataXLSXtraction::sharedStringsExctraction()
{
    tinyxml2::XMLDocument sharedStringsFile;
    std::string sharedStringsPath = temporaryDir + "sharedStrings.xml";
    sharedStringsFile.LoadFile(sharedStringsPath.c_str());
    tinyxml2::XMLElement* ssRoot = sharedStringsFile.RootElement();

    for (tinyxml2::XMLElement* si = ssRoot->FirstChildElement("si");
        si != nullptr;
        si = si->NextSiblingElement("si"))
    {
        sharedStringsVector.emplace_back(si->FirstChildElement("t")->GetText());
    }
}

// NE PRENDS PAS ENCORE CHARGE LES IMAGES (next work)
void DataXLSXtraction::extractData()
{
    tinyxml2::XMLDocument sheetFile; // init objet pour contenir feuille

    // pour chaque feuille
    for (const auto& sheet : std::filesystem::directory_iterator(temporaryDir))
    {
        // transformation directory_entry en string pour recuperer le pointeur avec c_str (demande par LoadFile)
        sheetFile.LoadFile(sheet.path().string().c_str());

        // considérer un pointeur situe au niveau du balise
        // pour ne pas confondre avec un pointeur CPP, appelons ça un curseur
        tinyxml2::XMLElement* sheetRoot = sheetFile.RootElement(); // curseur sur la balise racine

        // curseur sur la balise sheetData (contient info sur lignes, colonnes, cellules, etc...)
        tinyxml2::XMLElement* sheetData = sheetRoot->FirstChildElement("sheetData");

        std::string lastCat, lastQuest; // init variable lastCategorie et lastQuestion

        // pour chaque ligne

        // ERREUR BOUCLE !
        for (tinyxml2::XMLElement* row = sheetData->FirstChildElement("row");
            row != nullptr;
            row = row->NextSiblingElement("row"))
        {
            std::cout << "rowPass\n";
            // pour chacque cellule
            for (tinyxml2::XMLElement* cell = row->FirstChildElement("cell");
                cell != nullptr;
                cell = cell->NextSiblingElement("cell"))
            {
                std::cout << "cellPass\n";
                std::string cellAttribute = cell->Attribute("r"); // recuperation nom cellule
                int index = 0; // init pour indice sharedStrings
                std::string dataText; // init pour stocker resultat sharedStrings

                // chercher quelle cellule c'est
                switch (cellAttribute.find('A') == 0 ? 1 :
                        cellAttribute.find('B') == 0 ? 2 :
                        0)
                {
                    // si c'est un categorie ("A.")
                case 1:
                    // indice = valeur stocker par balise v -> transformer en int car stockee en strings
                    index = std::stoi(cell->FirstChildElement("v")->GetText());
                    dataText = sharedStringsVector[index]; // chercher correspondance indice dans sharedStrings

                    dataMap[dataText] = {}; // ajouter categorie dans map

                    lastCat = dataText; // update lastCategorie pour ajouter questions et reponse dans map

                case 2:
                    // indice = valeur stocker par balise v -> transformer en int car stockee en strings
                    index = std::stoi(cell->FirstChildElement("v")->GetText());
                    dataText = sharedStringsVector[index]; // chercher correspondance indice dans sharedStrings

                    dataMap[lastCat][dataText] = {}; // ajouter question dans map

                    lastQuest = dataText; // update lastQuestion pour ajouter reponse dans map

                default:
                    const tinyxml2::XMLAttribute* tAtttribute = cell->FindAttribute("t");
                    if (tAtttribute != nullptr)
                    {
                        // indice = valeur stocker par balise v -> transformer en int car stockee en strings
                        index = std::stoi(cell->FirstChildElement("v")->GetText());
                        dataText = sharedStringsVector[index]; // chercher correspondance indice dans sharedStrings

                        dataMap[lastCat][lastQuest].emplace_back(dataText); // ajouter reponse dans map
                    }
                    else
                    {
                        // recuperer valeur de v
                        dataText = cell->FirstChildElement("v")->GetText();

                        dataMap[lastCat][lastQuest].emplace_back(dataText); // ajouter reponse dans map
                    }
                }
            }
        }
    }
}

// renvoi de la map des données extraites
std::map<std::string, std::map<std::string, std::vector<std::string>>> DataXLSXtraction::getMap() { return dataMap; }
