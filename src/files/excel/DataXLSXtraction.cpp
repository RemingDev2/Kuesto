#include "../../headers/excel/DataXLSXtraction.h"
#include "../../../external/tinyxml2/tinyxml2.h"
#include <filesystem>
#include <iostream>

void DataXLSXtraction::sharedStringsExctraction()
{
    tinyxml2::XMLDocument sharedStringsFile;
    std::string sharedStringsPath = temporaryDir + "sharedStrings.xml";
    sharedStringsFile.LoadFile(sharedStringsPath.c_str());

    std::string block;

    tinyxml2::XMLElement* ssRoot = sharedStringsFile.RootElement();
    // parcourir balises <si>
    for (tinyxml2::XMLElement* si = ssRoot->FirstChildElement("si");
        si != nullptr;
        si = si->NextSiblingElement("si"))
    {
        // parcourir prochaines balises
        for (tinyxml2::XMLElement* tag = si->FirstChildElement();
            tag != nullptr;
            tag = tag->NextSiblingElement())
        {
            // si balise t
            if (strcmp(tag->Name(), "t") == 0)
            {
                // ajouter dans liste
                sharedStringsVector.emplace_back(tag->GetText());
            }
            // on wait, traiter les blocks entiers pour des styles differents
            else if (strcmp(tag->Name(), "r") == 0)
            {
                // si on rencontre un "r" ajouter dans block depuis <r> jusqu'à ne plus en avoir (= </si>)

                sharedStringsVector.emplace_back();
            }
            else
            {
                // sinon sortie erreur nouvelle balise a gerer
                std::cerr << std::endl << "Unknow tag: " << tag->Name() << std::endl;
            }
        }
    }
}

// NE PRENDS PAS ENCORE CHARGE LES IMAGES (on wait)
void DataXLSXtraction::extractData()
{
    sharedStringsExctraction(); // appel fonction recuperer texte

    bool firstRow = true;

    std::cout << "shared pass";

    tinyxml2::XMLDocument sheetFile; // init objet pour contenir feuille

    // pour chaque feuille
    for (const auto& sheet : std::filesystem::directory_iterator(temporaryDir + "sheetsDir"))
    {
        // transformation directory_entry en string pour recuperer le pointeur avec c_str (demande par LoadFile)
        sheetFile.LoadFile(sheet.path().string().c_str());

        // considérer un pointeur situe au niveau de la balise
        // pour ne pas confondre avec un pointeur CPP, appelons ça un curseur
        tinyxml2::XMLElement* sheetRoot = sheetFile.RootElement(); // curseur sur la balise racine

        // curseur sur la balise sheetData (contient info sur lignes, colonnes, cellules, etc...)

        // ERREUR nullptr !
        tinyxml2::XMLElement* sheetData = sheetRoot->FirstChildElement("sheetData");

        std::string lastCat, lastQuest; // init variable lastCategorie et lastQuestion

        // pour chaque ligne

        for (tinyxml2::XMLElement* row = sheetData->FirstChildElement("row");
            row != nullptr;
            row = row->NextSiblingElement("row"))
        {
            if (firstRow)
            {
                // pour chacque cellule
                for (tinyxml2::XMLElement* cell = row->FirstChildElement("c");
                    cell != nullptr;
                    cell = cell->NextSiblingElement("c"))
                {
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

                        break;

                    case 2:
                        // indice = valeur stocker par balise v -> transformer en int car stockee en strings
                            index = std::stoi(cell->FirstChildElement("v")->GetText());
                        dataText = sharedStringsVector[index]; // chercher correspondance indice dans sharedStrings

                        dataMap[lastCat][dataText] = {}; // ajouter question dans map

                        lastQuest = dataText; // update lastQuestion pour ajouter reponse dans map

                        break;

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

                        break;
                    }
                }
            }
            firstRow = false;
        }
    }
}

// renvoi de la map des données extraites
std::map<std::string, std::map<std::string, std::vector<std::string>>> DataXLSXtraction::getMap() { return dataMap; }
