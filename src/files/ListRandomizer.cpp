#include "../headers/ListRandomizer.h"
#include <algorithm>
#include <random>


void ListRandomizer::randomize(std::vector<std::string> contentToRandomize)
{
    std::random_device rd; // generer une seed
    std::mt19937 gen(rd()); // generer un nombre avec une seed
    std::shuffle(contentToRandomize.begin(), contentToRandomize.end(), gen); // melanger liste
}
