#include <iostream>
#include "src/headers/excel/XLSXtraction.h"
#include <filesystem>


void clearTemp()
{
    std::filesystem::remove_all("temp/"); // suppression dossier "temp"
};

int main() {
    std::cout << "Starting !" << std::endl;

//    extractSheets("test.xlsx");

//    clearTemp();

    std::cout << "Ending !" << std::endl;

    return 0;
}
