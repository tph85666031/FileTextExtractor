# FileTextExtractor

Extract text from file.   
Supported file: doc,ppt,xls,docx,pptx,xlsx,pdf,rtf  
Supported archive: zip,rar,bz2,gz,xz,7z,iso,asar  

## 3rd lib required：  
libcom.so from https://github.com/tph85666031/libcom  
libcomex.so from https://github.com/tph85666031/libcomex  
libxlsreader.a https://github.com/libxls/libxls  
put above .so .a in directory lib  
put above .h in directory lib/include  


## compile  
run ./build.sh  

## example  
```
#include "com_log.h"
#include "decoder.h"

com_log_init();
GetFormatTypeManager().loadConfigFromFile("config.json");
FormatResult result = GetFileDecoder().decode("./1.xls");
LOG_I("text=%s", result.text.toString().c_str());
```

