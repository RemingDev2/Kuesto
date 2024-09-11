#ifndef KUESTO_DATAXLSXTRACTION_H
    #define KUESTO_DATAXLSXTRACTION_H

#include <map>
#include <string>
#include <vector>


class DataXLSXtraction {

public:
    void extractData();
    std::map<std::string, std::map<std::string, std::vector<std::string>>> getMap();

private:
    void sharedStringsExctraction();

    std::string temporaryDir = "temp/xlsx_extracted/"; // chemin vers dossier temporaire

    std::vector<std::string> sharedStringsVector;

    std::map<std::string, std::map<std::string, std::vector<std::string>>> dataMap; // map contenant les donnees du xlsx
};


#endif
