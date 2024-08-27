#ifndef KUESTO_DATAXLSXTRACTION_H
    #define KUESTO_DATAXLSXTRACTION_H

#include <map>
#include <string>
#include <vector>


class DataXLSXtraction {

public:
    void extractData();
    std::map<std::string, std::map<std::string, std::string>> getMap();

private:
    std::map<std::string, std::map<std::string, std::string>> dataMap;
    std::vector<std::string> answers;
    std::vector<std::string> questions;
};


#endif
