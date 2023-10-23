#include "com_log.h"
#include "decoder_xls.h"
#include "xls.h"

using namespace xls;

FileDecoderXls::FileDecoderXls()
{
}

FileDecoderXls::~FileDecoderXls()
{
}

FormatResult FileDecoderXls::decode(const char* file_path)
{
    xls_error_t error = LIBXLS_OK;
    xlsWorkBook* wb = xls_open_file(file_path, "UTF-8", &error);
    if(wb == NULL)
    {
        LOG_E("Error reading file%s:%s", file_path, xls_getError(error));
        return FormatResult();
    }
    FormatResult result;
    
    for(uint32 i = 0; i < wb->sheets.count; i++) // sheets
    {
        xlsWorkSheet* work_sheet = xls_getWorkSheet(wb, i);
        error = xls_parseWorkSheet(work_sheet);
        for(int j = 0; j <= work_sheet->rows.lastrow; j++) // rows
        {
            xlsRow* row = xls_row(work_sheet, j);
            for(int k = 0; k <= work_sheet->rows.lastcol; k++) // columns
            {
                xlsCell* cell = &row->cells.cell[k];
                if(cell == NULL || cell->str == NULL)
                {
                    continue;
                }
                result.text.append(cell->str).append(" ");
            }
        }
        xls_close_WS(work_sheet);
    }
    xls_close_WB(wb);

    return result;
}

FormatResult FileDecoderXls::decode(const CPPBytes& content)
{
    xls_error_t error = LIBXLS_OK;
    xlsWorkBook* wb = xls_open_buffer(content.getData(),content.getDataSize(), "UTF-8", &error);
    if(wb == NULL)
    {
        LOG_E("Error reading file:%s", xls_getError(error));
        return FormatResult();
    }
    FormatResult result;
    
    for(uint32 i = 0; i < wb->sheets.count; i++) // sheets
    {
        xlsWorkSheet* work_sheet = xls_getWorkSheet(wb, i);
        error = xls_parseWorkSheet(work_sheet);
        for(int j = 0; j <= work_sheet->rows.lastrow; j++) // rows
        {
            xlsRow* row = xls_row(work_sheet, j);
            for(int k = 0; k <= work_sheet->rows.lastcol; k++) // columns
            {
                xlsCell* cell = &row->cells.cell[k];
                if(cell == NULL || cell->str == NULL)
                {
                    continue;
                }
                result.text.append(cell->str).append(" ");
            }
        }
        xls_close_WS(work_sheet);
    }
    xls_close_WB(wb);

    return result;
}

