#include <iostream>
#include "src/headers/excel/XLSXtraction.h"

int main() {
    std::cout << "Starting !" << std::endl;

    extractSheets("QCM_100.xlsx");


    std::cout << "Ending !" << std::endl;
    return 0;
}
