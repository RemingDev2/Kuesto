#include <iostream>
#include "src/headers/excel/XLSXtraction.h"
#include "src/headers/excel/DataXLSXtraction.h"
#include <filesystem>


void clearTemp()
{
    std::filesystem::remove_all("temp/"); // suppression dossier "temp"
};

int main() {
    std::cout << "Starting !" << std::endl;

    extractSheets("QCM_100_2.xlsx");

    DataXLSXtraction obj;
    obj.extractData();

    for (const auto& keys : obj.getMap())
    {
        std::cout << keys.first << " ";

        for (const auto& keys2 : keys.second)
        {
            std::cout << keys2.first << " ";

            for (const auto& ans : keys2.second)
            {
                std::cout << ans << " ";
            }

            std::cout << std::endl << "  " ;
        }
        std::cout << std::endl;
    }


    clearTemp();

    std::cout << "Ending !" << std::endl;

    return 0;
}
