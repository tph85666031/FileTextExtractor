#include "com_log.h"
#include "com_file.h"
#include "comex_iconv.h"
#include "decoder_doc.h"
#include "compoundfilereader.h"
#include "utf.h"

FileDecoderDoc::FileDecoderDoc()
{
}

FileDecoderDoc::~FileDecoderDoc()
{
}

FormatResult FileDecoderDoc::decode(const char* file_path)
{
    return decode(com_file_readall(file_path));
}

bool FileDecoderDoc::decodeFIB()
{
    fib = (FIB*)doc_raw.getData();
    if(fib == NULL)
    {
        return false;
    }

    lcb_97 = (FIB_RG_FC_LCB_97*)fib->data;

    if(fib->base.n_fib == 0xC1)
    {
        csw_new = (FIB_RG_CSW_NEW*)lcb_97->data;
    }
    else if(fib->base.n_fib == 0xD9)
    {
        lcb_2000 = (FIB_RG_FC_LCB_2000*)lcb_97->data;
        csw_new = (FIB_RG_CSW_NEW*)lcb_2000->data;
    }
    else if(fib->base.n_fib == 0x101)
    {
        lcb_2000 = (FIB_RG_FC_LCB_2000*)lcb_97->data;
        lcb_2002 = (FIB_RG_FC_LCB_2002*)lcb_2000->data;
        csw_new = (FIB_RG_CSW_NEW*)lcb_2002->data;
    }
    else if(fib->base.n_fib == 0x10C)
    {
        lcb_2000 = (FIB_RG_FC_LCB_2000*)lcb_97->data;
        lcb_2002 = (FIB_RG_FC_LCB_2002*)lcb_2000->data;
        lcb_2003 = (FIB_RG_FC_LCB_2003*)lcb_2002->data;
        csw_new = (FIB_RG_CSW_NEW*)lcb_2003->data;
    }
    else if(fib->base.n_fib == 0x112)
    {
        lcb_2000 = (FIB_RG_FC_LCB_2000*)lcb_97->data;
        lcb_2002 = (FIB_RG_FC_LCB_2002*)lcb_2000->data;
        lcb_2003 = (FIB_RG_FC_LCB_2003*)lcb_2002->data;
        lcb_2007 = (FIB_RG_FC_LCB_2007*)lcb_2003->data;
        csw_new = (FIB_RG_CSW_NEW*)lcb_2007->data;
    }

    if(csw_new != NULL && csw_new->csw_new != 0)
    {
        if(csw_new->n_fib_new == 0xD9
                || csw_new->n_fib_new == 0x101
                || csw_new->n_fib_new == 0x10C)
        {
            csw_new_data_2000 = (FIB_RG_CSW_NEW_DATA_2000*)csw_new->data;
        }
        else if(csw_new->n_fib_new == 0x112)
        {
            csw_new_data_2007 = (FIB_RG_CSW_NEW_DATA_2007*)csw_new->data;
        }
    }

    return true;
}

CPPBytes FileDecoderDoc::decodeText()
{
    if(fib == NULL || lcb_97 == NULL)
    {
        return CPPBytes();
    }
    CPPBytes text;
    uint8* table_data = NULL;
    int table_size = 0;
    if(fib->base.flag_which_table_stream)
    {
        table_data = table_raw_1.getData();
        table_size = table_raw_1.getDataSize();
    }
    else
    {
        table_data = table_raw_0.getData();
        table_size = table_raw_0.getDataSize();
    }

    uint8* p_clx = table_data + lcb_97->fc_clx;
    int clx_size = lcb_97->lcb_clx;
    if(clx_size > table_size)
    {
        return CPPBytes();
    }

    int ret1 = 0;
    Serializer s1(p_clx, clx_size);
    s1.disableByteOrderModify();

    std::vector<uint32> cps;
    std::vector<uint64> pcds;
    do
    {
        uint8 val_u8;
        ret1 += s1.detach(val_u8);
        if(val_u8 == 0x01)//is prc
        {
            int16 grp_prl_size;
            ret1 += s1.detach(grp_prl_size);

            CPPBytes grp_prl;
            ret1 += s1.detach(grp_prl, grp_prl_size);
        }
        else if(val_u8 == 0x02)//pcdt
        {
            uint32 lcb;
            ret1 += s1.detach(lcb);

            CPPBytes plc_pcd;
            ret1 += s1.detach(plc_pcd, lcb);

            int ret2 = 0;
            Serializer s2(plc_pcd.getData(), plc_pcd.getDataSize());
            s2.disableByteOrderModify();
            uint32 cp = 0;
            uint32 cp_pre = 0;
            uint32 cp_last = 0;
            if(fib->fib_rg_lw97.ccp_ftn != 0
                    || fib->fib_rg_lw97.ccp_hdd != 0
                    || fib->fib_rg_lw97.ccp_atn != 0
                    || fib->fib_rg_lw97.ccp_edn != 0
                    || fib->fib_rg_lw97.ccp_txbx != 0
                    || fib->fib_rg_lw97.ccp_hdr_txbx != 0)
            {
                cp_last = fib->fib_rg_lw97.ccp_ftn
                          + fib->fib_rg_lw97.ccp_hdd
                          + fib->fib_rg_lw97.ccp_atn
                          + fib->fib_rg_lw97.ccp_edn
                          + fib->fib_rg_lw97.ccp_txbx
                          + fib->fib_rg_lw97.ccp_hdr_txbx
                          + fib->fib_rg_lw97.ccp_text
                          + 1;
            }
            else
            {
                cp_last = fib->fib_rg_lw97.ccp_text;
            }
            LOG_D("cp_last=%u", cp_last);

            //detach cp
            do
            {
                ret2 += s2.detach(cp);
                if(ret2 != 0 || cp < cp_pre)
                {
                    break;
                }
                cps.push_back(cp);
                if(cp == cp_last)
                {
                    break;
                }
                cp_pre = cp;
            }
            while(ret2 == 0);

            //detach pcd
            uint64 pcd = 0;
            do
            {
                ret2 += s2.detach(pcd);
                if(ret2 != 0)
                {
                    break;
                }
                pcds.push_back(pcd);
            }
            while(ret2 == 0);
        }
        else
        {
            LOG_W("invalid:%hu", val_u8);
            break;
        }
    }
    while(ret1 == 0);

    for(size_t i = 0; i < cps.size() && i < pcds.size() && !doc_raw.empty(); i++)
    {
        int offset = ((pcds[i] >> 16) & 0xFFFFFFFF);
        int size = 0;
        if(offset & 0x02)//ansi
        {
            offset = offset > 1;
            size = cps[i + 1] - cps[i];
            if(doc_raw.getDataSize() > offset + size)
            {
                std::string str_ansi((char*)doc_raw.getData() + offset, size);
                text.append(com_string_ansi_to_utf8(str_ansi));
            }
        }
        else //utf16
        {
            size = 2 * (cps[i + 1] - cps[i]);
            if(doc_raw.getDataSize() > offset + size)
            {
                CPPBytes text_u16(doc_raw.getData() + offset, size);
                text.append(comex_iconv_utf16_to_utf8(text_u16));
            }
        }
    }
    for(int i = 0; i < text.getDataSize(); i++)
    {
        if(text.getAt(i) <= 0x1F)
        {
            text.setAt(i, ' ');
        }
    }
    return text;
}

FormatResult FileDecoderDoc::decode(const CPPBytes& content)
{
    CFB::CompoundFileReader reader(content.getData(), content.getDataSize());

    reader.EnumFiles(reader.GetRootEntry(), -1,
                     [&](const CFB::COMPOUND_FILE_ENTRY * entry, const CFB::utf16string & dir, int level)->void
    {
        std::string name = UTF16ToUTF8(entry->name);
        if(reader.IsStream(entry) && entry->size > 0)
        {
            LOG_D("name=%s", name.c_str());
            char* buf = new char[entry->size];
            reader.ReadFile(entry, 0, buf, entry->size);
            if(name == "WordDocument")
            {
                doc_raw.clear();
                doc_raw.append((uint8*)buf, entry->size);
            }
            else if(com_string_end_with(name.c_str(), "Table"))
            {
                int id = strtol(name.c_str(), NULL, 10);
                if(id == 0)
                {
                    table_raw_0.clear();
                    table_raw_0.append((uint8*)buf, entry->size);
                }
                else
                {
                    table_raw_1.clear();
                    table_raw_1.append((uint8*)buf, entry->size);
                }
            }
            delete[] buf;
        }
    });

    FormatResult result;
    if(doc_raw.empty() == false)
    {
        decodeFIB();
        result.text = decodeText();
    }

    return result;
}

