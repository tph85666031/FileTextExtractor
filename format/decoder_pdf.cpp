#include "com_log.h"
#include "com_file.h"
#include "comex_podofo.h"
#include "decoder_pdf.h"

FileDecoderPdf::FileDecoderPdf()
{
}

FileDecoderPdf::~FileDecoderPdf()
{
}

FormatResult FileDecoderPdf::decode(const char* file_path)
{
    PdfExtrator extractor;
    extractor.loadFromFile(file_path);
    extractor.extractText();
    extractor.extractImage();

    FormatResult result;
    result.text.append(extractor.getText());
    result.images = extractor.getImage();

    return result;
}

FormatResult FileDecoderPdf::decode(const CPPBytes& content)
{
    PdfExtrator extractor;
    extractor.loadFromMemory(content);
    extractor.extractText();
    extractor.extractImage();

    FormatResult result;
    result.text.append(extractor.getText());
    result.images = extractor.getImage();

    return FormatResult();
}

