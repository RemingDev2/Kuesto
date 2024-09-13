#include <string>
#include <fstream>
#include "external/json/json.hpp"

using json = nlohmann::json;

int main()
{
    std::string subscriptXML = R"(
        <w:p>
            <w:pPr>
                <w:rPr>
                    <w:vertAlign w:val="subscript" />
                </w:rPr>
            </w:pPr>
            <w:r>
                <w:t xml:space="preserve">{replacementText</w:t>
            </w:r>
            <w:r w:rsidRPr="007B4ECC">
                <w:rPr>
                    <w:vertAlign w:val="subscript" />
                </w:rPr>
                <w:t>{sbsReplacementText}</w:t>
            </w:r>
        </w:p>
)";

    std::string superscriptXML = R"(
        <w:p>
            <w:pPr>
                <w:rPr>
                    <w:vertAlign w:val="superscript" />
                </w:rPr>
            </w:pPr>
            <w:r>
                <w:t xml:space="preserve">{replacementText</w:t>
            </w:r>
            <w:r w:rsidRPr="007B4ECC">
                <w:rPr>
                    <w:vertAlign w:val="superscript" />
                </w:rPr>
                <w:t>{spsReplacementText}</w:t>
            </w:r>
        </w:p>
)";

    std::string listXML = R"(
        <w:p>
            <w:pPr>
                <w:pStyle w:val="Paragraphedeliste" />
                <w:numPr>
                    <w:ilvl w:val="0" />
                    <w:numId w:val="1" />
                </w:numPr>
            </w:pPr>
            <w:r>
                <w:t>{remplacementText}</w:t>
            </w:r>
        </w:p>
)";

    json jsonObject =
            {
                    {"subscript", subscriptXML},
                    {"superscript", superscriptXML},
                    {"list", listXML}
            };

    std::ofstream o("output.json");
    o << std::setw(4) << jsonObject << std::endl;

    return 0;
}