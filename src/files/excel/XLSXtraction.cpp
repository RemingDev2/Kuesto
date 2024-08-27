#include "../../headers/excel/XLSXtraction.h"
#include "../../../external/miniz/miniz.h"
#include <string>
#include <filesystem>


void extractSheets(const std::string& zipName)
{
    mz_zip_archive zipArchive; // init objet pour l'archive
    memset(&zipArchive, 0, sizeof(zipArchive)); // valeurs indéfinies = 0 de l'objet

    mz_zip_reader_init_file(&zipArchive, zipName.c_str(), 0); // init archive dans l'objet

    std::string tempSheetsDir = "temp/extracted_sheets/"; // chemin dossier temporaire
    std::filesystem::create_directories(tempSheetsDir); // init dossier temporaire pour traitement

    mz_uint nbrFiles = mz_zip_reader_get_num_files(&zipArchive); // recuperation nombre fichiers dans archive

    for (mz_uint incr = 0; incr < nbrFiles; incr++) // boucle pour chaque fichier (par index)
    {
        mz_zip_archive_file_stat fileStats; // init objet pour "metadatas" (pas le contenu) du fichier
        // recuperation metadatas dans l'objet
        mz_zip_reader_file_stat(&zipArchive, incr, &fileStats);

        std::string filePath = fileStats.m_filename; // recuperation chemin fichier acutellement traite

        std::string sheetsPath = "xl/worksheets/"; // chemin vers feuilles dans excel
        if (!filePath.find(sheetsPath + "sheet")) // verification si feuille excel
        {
            std::string outPath = tempSheetsDir + filePath.substr(sheetsPath.length()); // init chemin sortie

            mz_zip_reader_extract_to_file(&zipArchive, incr, outPath.c_str(),
                                          0); // extraction fichier
        }
    }

    mz_zip_reader_end(&zipArchive); // fermeture du zip
}
