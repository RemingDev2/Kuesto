/* Ce fichier permet l'extraction des fichiers XML qui composent le fichier XLSX
 * On a besoin des feuilles (1 ou+) (sheet)
 * Du texte présent dans la feuille (1) (sharedStrings)
 * Des images handlers (0+) (drawing)
 * Des images elles même (0+) (image) */

#include "../../headers/excel/XLSXtraction.h"
#include "../../../external/miniz/miniz.h"
#include <string>
#include <filesystem>
#include <iostream>


void extractSheets(const std::string& zipName)
{
    mz_zip_archive zipArchive; // init objet pour l'archive
    memset(&zipArchive, 0, sizeof(zipArchive)); // valeurs indéfinies = 0 de l'objet

    mz_zip_reader_init_file(&zipArchive, zipName.c_str(), 0); // init archive dans l'objet

    std::string tempSheetsDir = "temp/xlsx_extracted/"; // chemin dossier temporaire
    std::filesystem::create_directories(tempSheetsDir); // init dossier temporaire pour traitement
    // init dossier feuille temporaire pour traitement (car toujours 1 feuille min)
    std::filesystem::create_directories(tempSheetsDir+"sheetsDir/");


    mz_uint nbrFiles = mz_zip_reader_get_num_files(&zipArchive); // recuperation nombre fichiers dans archive

    for (mz_uint incr = 0; incr < nbrFiles; incr++) // boucle pour chaque fichier (par index)
    {
        mz_zip_archive_file_stat fileStats; // init objet pour "metadatas" (pas le contenu) du fichier
        // recuperation metadatas dans l'objet
        mz_zip_reader_file_stat(&zipArchive, incr, &fileStats);

        std::string filePath = fileStats.m_filename; // recuperation chemin fichier acutellement traite

        std::string sheetsPath = "xl/worksheets/"; // chemin vers feuilles dans excel
        std::string sharedStringsPath = "xl/"; // chemin vers le texte present des les feuilles
        std::string imagePath = "xl/media/"; // chemin vers les images
        std::string drawingsPath = "xl/drawings/"; // chemin vers le fichier gérant les images

        std::string outPath = tempSheetsDir; // init chemin sortie

        // update chemin sortie selon le cas
        switch (filePath.find(sheetsPath + "sheet") == 0 ? 1 :
                filePath.find(sharedStringsPath + "sharedStrings") == 0 ? 2 :
                filePath.find(imagePath +  "image") == 0 ? 3 :
                filePath.find(drawingsPath + "drawing") == 0 ? 4 :
                0)
                {
                    case 1:
                        // c'est une feuille
                        outPath += "sheetsDir/" + filePath.substr(sheetsPath.length());
                        break;

                    case 2:
                        // c'est le sharedStrings
                        outPath += filePath.substr(sharedStringsPath.length());
                        break;

                    case 3:
                        // c'est une image
                        // init dossier temporaire images pour traitement
                        std::filesystem::create_directories(tempSheetsDir+"imagesDir/");
                        outPath += "imagesDir/" + filePath.substr(imagePath.length());
                        break;

                    case 4:
                        // c'est un handler d'image
                        // init dossier temporaire drawings pour traitement
                        std::filesystem::create_directories(tempSheetsDir+"drawingsDir/");
                        outPath += "drawingsDir/" + filePath.substr(drawingsPath.length());
                        break;

                    default:
                        break;
                }

        mz_zip_reader_extract_to_file(&zipArchive, incr, outPath.c_str(),
                                      0); // extraction fichier
    }

    mz_zip_reader_end(&zipArchive); // fermeture du zip
}
