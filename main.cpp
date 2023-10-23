#include "com_log.h"
#include "com_file.h"
#include "decoder.h"


int main(int argc, char* argv[])
{
    com_log_init();

    GetFormatTypeManager().loadConfigFromFile("config.json");

    FormatResult result = GetFileDecoder().decode(argv[1]);
    LOG_I("[%s]format_text=%s", argv[1], result.text.toString().c_str());
    return 0;
}

