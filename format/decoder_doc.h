#ifndef __DECODER_DOC_H__
#define __DECODER_DOC_H__

#include "format.h"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
    uint16 indent;
    uint16 n_fib;
    uint16 rev1;
    uint16 lid;
    uint16 page_next;
    uint8 flag_dot: 1;
    uint8 flag_glsy: 1;
    uint8 flag_complex: 1;
    uint8 flag_has_Pic: 1;
    uint8 flag_quick_saves: 4;
    uint8 flag_encrypted: 1;
    uint8 flag_which_table_stream: 1;
    uint8 flag_read_only: 1;
    uint8 flag_write_reservation: 1;
    uint8 flag_ext_char: 1;
    uint8 flag_load_override: 1;
    uint8 flag_far_east: 1;
    uint8 flag_obfuscated: 1;
    uint16 fib_back;
    uint32 l_key;
    uint8 envr;
    uint8 flag_s2;
    uint16 rev2;
    uint16 rev3;
    uint32 rev4;
    uint32 rev5;
} FIB_BASE;

typedef struct
{
    uint16 rev1;
    uint16 rev2;
    uint16 rev3;
    uint16 rev4;
    uint16 rev5;
    uint16 rev6;
    uint16 rev7;
    uint16 rev8;
    uint16 rev9;
    uint16 rev10;
    uint16 rev11;
    uint16 rev12;
    uint16 rev13;
    uint16 lid_fe;
} FIB_RG_W97;

typedef struct
{
    int32 cb_mac;
    int32 rev1;
    int32 rev2;
    int32 ccp_text;
    int32 ccp_ftn;
    int32 ccp_hdd;
    int32 rev3;
    int32 ccp_atn;
    int32 ccp_edn;
    int32 ccp_txbx;
    int32 ccp_hdr_txbx;
    int32 rev4;
    int32 rev5;
    int32 rev6;
    int32 rev7;
    int32 rev8;
    int32 rev9;
    int32 rev10;
    int32 rev11;
    int32 rev12;
    int32 rev13;
    int32 rev14;
} FIB_RG_LW97;

typedef struct
{
    uint32 fc_stshf_orig;
    uint32 lcb_stshf_orig;
    uint32 fc_stshf;
    uint32 lcb_stshf;
    uint32 fc_plcffnd_ref;
    uint32 lcb_plcffnd_ref;
    uint32 fc_plcffnd_txt;
    uint32 lcb_plcffnd_txt;
    uint32 fc_plcfand_ref;
    uint32 lcb_plcfand_ref;
    uint32 fc_plcfand_txt;
    uint32 lcb_plcfand_txt;
    uint32 fc_plcf_sed;
    uint32 lcb_plcf_sed;
    uint32 fc_plc_pad;
    uint32 lcb_plc_pad;
    uint32 fc_plcf_phe;
    uint32 lcb_plcf_phe;
    uint32 fc_sttbf_glsy;
    uint32 lcb_sttbf_glsy;
    uint32 fc_plcf_glsy;
    uint32 lcb_plcf_glsy;
    uint32 fc_plcf_hdd;
    uint32 lcb_plcf_hdd;
    uint32 fc_plcf_bte_chpx;
    uint32 lcb_plcf_bte_chpx;
    uint32 fc_plcf_bte_papx;
    uint32 lcb_plcf_bte_papx;
    uint32 fc_plcf_sea;
    uint32 lcb_plcf_sea;
    uint32 fc_sttbf_ffn;
    uint32 lcb_sttbf_ffn;
    uint32 fc_plcf_fld_mom;
    uint32 lcb_plcf_fld_mom;
    uint32 fc_plcf_fld_hdr;
    uint32 lcb_plcf_fld_hdr;
    uint32 fc_plcf_fld_ftn;
    uint32 lcb_plcf_fld_ftn;
    uint32 fc_plcf_fld_atn;
    uint32 lcb_plcf_fld_atn;
    uint32 fc_plcf_fld_mcr;
    uint32 lcb_plcf_fld_mcr;
    uint32 fc_sttbf_bkmk;
    uint32 lcb_sttbf_bkmk;
    uint32 fc_plcf_bkf;
    uint32 lcb_plcf_bkf;
    uint32 fc_plcf_bkl;
    uint32 lcb_plcf_bkl;
    uint32 fc_cmds;
    uint32 lcb_cmds;
    uint32 fc_unused1;
    uint32 lcb_unused1;
    uint32 fc_sttbf_mcr;
    uint32 lcb_sttbf_mcr;
    uint32 fc_pr_drvr;
    uint32 lcb_pr_drvr;
    uint32 fc_p_renv_p_ort;
    uint32 lcb_p_renv_p_ort;
    uint32 fc_p_renv_land;
    uint32 lcb_p_renv_land;
    uint32 fc_wss;
    uint32 lcb_wss;
    uint32 fc_dop;
    uint32 lcb_dop;
    uint32 fc_sttbf_assoc;
    uint32 lcb_sttbf_assoc;
    uint32 fc_clx;
    uint32 lcb_clx;
    uint32 fc_plcf_pgd_ftn;
    uint32 lcb_plcf_pgd_ftn;
    uint32 fc_autosave_source;
    uint32 lcb_autosave_source;
    uint32 fc_grp_x_st_atn_owners;
    uint32 lcb_grp_x_st_atn_owners;
    uint32 fc_sttbf_atn_bkmk;
    uint32 lcb_sttbf_atn_bkmk;
    uint32 fc_unused2;
    uint32 lcb_unused2;
    uint32 fc_unused3;
    uint32 lcb_unused3;
    uint32 fc_plc_spa_mom;
    uint32 lcb_plc_spa_mom;
    uint32 fc_plc_spa_hdr;
    uint32 lcb_plc_spa_hdr;
    uint32 fc_plcf_atn_bkf;
    uint32 lcb_plcf_atn_bkf;
    uint32 fc_plcf_atn_bkl;
    uint32 lcb_plcf_atn_bkl;
    uint32 fc_pms;
    uint32 lcb_pms;
    uint32 fc_f_orm_fld_sttbs;
    uint32 lcb_f_orm_fld_sttbs;
    uint32 fc_plcfend_ref;
    uint32 lcb_plcfend_ref;
    uint32 fc_plcfend_txt;
    uint32 lcb_plcfend_txt;
    uint32 fc_plcf_fld_edn;
    uint32 lcb_plcf_fld_edn;
    uint32 fc_unused4;
    uint32 lcb_unused4;
    uint32 fc_dgg_info;
    uint32 lcb_dgg_info;
    uint32 fc_sttbf_r_mark;
    uint32 lcb_sttbf_r_mark;
    uint32 fc_sttbf_caption;
    uint32 lcb_sttbf_caption;
    uint32 fc_sttbf_auto_caption;
    uint32 lcb_sttbf_auto_caption;
    uint32 fc_plcf_wkb;
    uint32 lcb_plcf_wkb;
    uint32 fc_plcf_spl;
    uint32 lcb_plcf_spl;
    uint32 fc_plcftxbx_txt;
    uint32 lcb_plcftxbx_txt;
    uint32 fc_plcf_fld_txbx;
    uint32 lcb_plcf_fld_txbx;
    uint32 fc_plcf_hdrtxbx_txt;
    uint32 lcb_plcf_hdrtxbx_txt;
    uint32 fc_plcffld_hdr_txbx;
    uint32 lcb_plcffld_hdr_txbx;
    uint32 fc_stw_user;
    uint32 lcb_stw_user;
    uint32 fc_sttb_ttmbd;
    uint32 lcb_sttb_ttmbd;
    uint32 fc_cookie_data;
    uint32 lcb_cookie_data;
    uint32 fc_pgd_mother_old_old;
    uint32 lcb_pgd_mother_old_old;
    uint32 fc_bkd_mother_old_old;
    uint32 lcb_bkd_mother_old_old;
    uint32 fc_pgd_ftn_old_old;
    uint32 lcb_pgd_ftn_old_old;
    uint32 fc_bkd_ftn_old_old;
    uint32 lcb_bkd_ftn_old_old;
    uint32 fc_pgd_edn_old_old;
    uint32 lcb_pgd_edn_old_old;
    uint32 fc_bkd_edn_old_old;
    uint32 lcb_bkd_edn_old_old;
    uint32 fc_sttbf_intl_fld;
    uint32 lcb_sttbf_intl_fld;
    uint32 fc_route_slip;
    uint32 lcb_route_slip;
    uint32 fc_sttb_saved_by;
    uint32 lcb_sttb_saved_by;
    uint32 fc_sttb_fnm;
    uint32 lcb_sttb_fnm;
    uint32 fc_plf_l_st;
    uint32 lcb_plf_l_st;
    uint32 fc_plf_lfo;
    uint32 lcb_plf_lfo;
    uint32 fc_plcf_txbx_bkd;
    uint32 lcb_plcf_txbx_bkd;
    uint32 fc_plcf_txbx_hdr_bkd;
    uint32 lcb_plcf_txbx_hdr_bkd;
    uint32 fc_doc_undo_w_ord9;
    uint32 lcb_doc_undo_w_ord9;
    uint32 fc_rgb_use;
    uint32 lcb_rgb_use;
    uint32 fc_usp;
    uint32 lcb_usp;
    uint32 fc_uskf;
    uint32 lcb_uskf;
    uint32 fc_plcupc_rgb_use;
    uint32 lcb_plcupc_rgb_use;
    uint32 fc_plcupc_usp;
    uint32 lcb_plcupc_usp;
    uint32 fc_sttb_glsy_style;
    uint32 lcb_sttb_glsy_style;
    uint32 fc_plgosl;
    uint32 lcb_plgosl;
    uint32 fc_plcocx;
    uint32 lcb_plcocx;
    uint32 fc_plcf_bte_lvc;
    uint32 lcb_plcf_bte_lvc;
    uint32 dw_low_date_time;
    uint32 dw_high_date_time;
    uint32 fc_plcf_lvc_p_re10;
    uint32 lcb_plcf_lvc_p_re10;
    uint32 fc_plcf_asumy;
    uint32 lcb_plcf_asumy;
    uint32 fc_plcf_gram;
    uint32 lcb_plcf_gram;
    uint32 fc_sttb_li_st_names;
    uint32 lcb_sttb_li_st_names;
    uint32 fc_sttbf_ussr;
    uint32 lcb_sttbf_ussr;
    uint8 data[0];
} FIB_RG_FC_LCB_97;

typedef struct
{
    uint32 fc_plcf_tch;
    uint32 lcb_plcf_tch;
    uint32 fc_rmd_threading;
    uint32 lcb_rmd_threading;
    uint32 fc_mid;
    uint32 lcb_mid;
    uint32 fcSttb_rgtplc;
    uint32 lcbSttb_rgtplc;
    uint32 fc_mso_envelope;
    uint32 lcb_mso_envelope;
    uint32 fc_plcfLad;
    uint32 lcb_plcfLad;
    uint32 fc_rg_dofr;
    uint32 lcb_rg_dofr;
    uint32 fc_plcosl;
    uint32 lcb_plcosl;
    uint32 fc_plcf_cookie_old;
    uint32 lcb_plcf_cookie_old;
    uint32 fc_pgd_mother_old;
    uint32 lcb_pgd_mother_old;
    uint32 fc_bkd_mother_old;
    uint32 lcb_bkd_mother_old;
    uint32 fc_pgd_ftn_old;
    uint32 lcb_pgd_ftn_old;
    uint32 fc_bkd_ftn_old;
    uint32 lcb_bkd_ftn_old;
    uint32 fc_pgd_edn_old;
    uint32 lcb_pgd_edn_old;
    uint32 fc_bkd_edn_old;
    uint32 lcb_bkd_edn_old;
    uint8 data[0];
} FIB_RG_FC_LCB_2000;

typedef struct
{
    uint32 fc_unused1;
    uint32 lcb_unused1;
    uint32 fc_plcf_pgp;
    uint32 lcb_plcf_pgp;
    uint32 fc_plcfuim;
    uint32 lcb_plcfuim;
    uint32 fc_plfguid_uim;
    uint32 lcb_plfguid_uim;
    uint32 fc_atrd_extra;
    uint32 lcb_atrd_extra;
    uint32 fc_plrsid;
    uint32 lcb_plrsid;
    uint32 fc_sttbf_bkmk_factoid;
    uint32 lcb_sttbf_bkmk_factoid;
    uint32 fc_plcf_bkf_factoid;
    uint32 lcb_plcf_bkf_factoid;
    uint32 fc_plcfcookie;
    uint32 lcb_plcfcookie;
    uint32 fc_plcf_bkl_factoid;
    uint32 lcb_plcf_bkl_factoid;
    uint32 fc_factoid_data;
    uint32 lcb_factoid_data;
    uint32 fc_doc_undo;
    uint32 lcb_doc_undo;
    uint32 fc_sttbf_bkmk_fcc;
    uint32 lcb_sttbf_bkmk_fcc;
    uint32 fc_plcf_bkf_fcc;
    uint32 lcb_plcf_bkf_fcc;
    uint32 fc_plcf_bkl_fcc;
    uint32 lcb_plcf_bkl_fcc;
    uint32 fc_sttbfbkmk_b_p_repairs;
    uint32 lcb_sttbfbkmk_b_p_repairs;
    uint32 fc_plcfbkf_b_p_repairs;
    uint32 lcb_plcfbkf_b_p_repairs;
    uint32 fc_plcfbkl_b_p_repairs;
    uint32 lcb_plcfbkl_b_p_repairs;
    uint32 fc_pms_new;
    uint32 lcb_pms_new;
    uint32 fc_o_d_s_o;
    uint32 lcb_o_d_s_o;
    uint32 fc_plcfpmi_old_x_p;
    uint32 lcb_plcfpmi_old_x_p;
    uint32 fc_plcfpmi_new_x_p;
    uint32 lcb_plcfpmi_new_x_p;
    uint32 fc_plcfpmi_mixed_x_p;
    uint32 lcb_plcfpmi_mixed_x_p;
    uint32 fc_unused2;
    uint32 lcb_unused2;
    uint32 fc_plcffactoid;
    uint32 lcb_plcffactoid;
    uint32 fc_plcflvc_old_x_p;
    uint32 lcb_plcflvc_old_x_p;
    uint32 fc_plcflvc_new_x_p;
    uint32 lcb_plcflvc_new_x_p;
    uint32 fc_plcflvc_mixed_x_p;
    uint32 lcb_plcflvc_mixed_x_p;
    uint8 data[0];
} FIB_RG_FC_LCB_2002;

typedef struct
{
    uint32 fc_hplxsdr;
    uint32 lcb_hplxsdr;
    uint32 fc_sttbf_bkmk_sdt;
    uint32 lcb_sttbf_bkmk_sdt;
    uint32 fc_plcf_bkf_sdt;
    uint32 lcb_plcf_bkf_sdt;
    uint32 fc_plcf_bkl_sdt;
    uint32 lcb_plcf_bkl_sdt;
    uint32 fc_custom_x_form;
    uint32 lcb_custom_x_form;
    uint32 fc_sttbf_bkmk_prot;
    uint32 lcb_sttbf_bkmk_prot;
    uint32 fc_plcf_bkf_prot;
    uint32 lcb_plcf_bkf_prot;
    uint32 fc_plcf_bkl_prot;
    uint32 lcb_plcf_bkl_prot;
    uint32 fc_sttb_prot_user;
    uint32 lcb_sttb_prot_user;
    uint32 fc_unused;
    uint32 lcb_unused;
    uint32 fc_plcfpmi_old;
    uint32 lcb_plcfpmi_old;
    uint32 fc_plcfpmi_old_inline;
    uint32 lcb_plcfpmi_old_inline;
    uint32 fc_plcfpmi_new;
    uint32 lcb_plcfpmi_new;
    uint32 fc_plcfpmi_new_inline;
    uint32 lcb_plcfpmi_new_inline;
    uint32 fc_plcflvc_old;
    uint32 lcb_plcflvc_old;
    uint32 fc_plcflvc_old_inline;
    uint32 lcb_plcflvc_old_inline;
    uint32 fc_plcflvc_new;
    uint32 lcb_plcflvc_new;
    uint32 fc_plcflvc_new_inline;
    uint32 lcb_plcflvc_new_inline;
    uint32 fc_pgd_mother;
    uint32 lcb_pgd_mother;
    uint32 fc_bkd_mother;
    uint32 lcb_bkd_mother;
    uint32 fc_afd_mother;
    uint32 lcb_afd_mother;
    uint32 fc_pgd_ftn;
    uint32 lcb_pgd_ftn;
    uint32 fc_bkd_ftn;
    uint32 lcb_bkd_ftn;
    uint32 fc_afd_ftn;
    uint32 lcb_afd_ftn;
    uint32 fc_pgd_edn;
    uint32 lcb_pgd_edn;
    uint32 fc_bkd_edn;
    uint32 lcb_bkd_edn;
    uint32 fc_afd_edn;
    uint32 lcb_afd_edn;
    uint32 fc_afd;
    uint32 lcb_afd;
    uint8 data[0];
} FIB_RG_FC_LCB_2003;

typedef struct
{
    uint32 fc_plcfmthd;
    uint32 lcb_plcfmthd;
    uint32 fc_sttbf_bkmk_move_from;
    uint32 lcb_sttbf_bkmk_move_from;
    uint32 fc_plcf_bkf_move_from;
    uint32 lcb_plcf_bkf_move_from;
    uint32 fc_plcf_bkl_move_from;
    uint32 lcb_plcf_bkl_move_from;
    uint32 fc_sttbf_bkmk_move_to;
    uint32 lcb_sttbf_bkmk_move_to;
    uint32 fc_plcf_bkf_move_to;
    uint32 lcb_plcf_bkf_move_to;
    uint32 fc_plcf_bkl_move_to;
    uint32 lcb_plcf_bkl_move_to;
    uint32 fc_unused1;
    uint32 lcb_unused1;
    uint32 fc_unused2;
    uint32 lcb_unused2;
    uint32 fc_unused3;
    uint32 lcb_unused3;
    uint32 fc_sttbf_bkmk_arto;
    uint32 lcb_sttbf_bkmk_arto;
    uint32 fc_plcf_bkf_arto;
    uint32 lcb_plcf_bkf_arto;
    uint32 fc_plcf_bkl_arto;
    uint32 lcb_plcf_bkl_arto;
    uint32 fc_arto_data;
    uint32 lcb_arto_data;
    uint32 fc_unused4;
    uint32 lcb_unused4;
    uint32 fc_unused5;
    uint32 lcb_unused5;
    uint32 fc_unused6;
    uint32 lcb_unused6;
    uint32 fc_oss_theme;
    uint32 lcb_oss_theme;
    uint32 fc_color_scheme_mapping;
    uint32 lcb_color_scheme_mapping;
    uint8 data[0];
} FIB_RG_FC_LCB_2007;

typedef struct
{
    uint16 quick_saves_new;
} FIB_RG_CSW_NEW_DATA_2000;

typedef struct
{
    uint16 quick_saves_new;
    uint16 lid_theme_other;
    uint16 lid_theme_fe;
    uint16 lid_theme_cs;
} FIB_RG_CSW_NEW_DATA_2007;

typedef struct
{
    uint16 csw_new;//following exist if cew_new not 0
    uint16 n_fib_new;//0x00D9,0x0101,0x010C  FIB_RG_CSW_NEW_DATA_2000; 0x0112 FIB_RG_CSW_NEW_DATA_2007
    uint8 data[0];
} FIB_RG_CSW_NEW;

typedef struct
{
    FIB_BASE base;

    uint16 csw;
    FIB_RG_W97 fib_rg_w97;
    uint16 cslw;
    FIB_RG_LW97 fib_rg_lw97;
    /*
        n_fib=0x00C1 data=FIB_RG_FC_LCB_97
        n_fib=0x00D9 data=FIB_RG_FC_LCB_2000
        n_fib=0x0101 data=FIB_RG_FC_LCB_2002
        n_fib=0x010C data=FIB_RG_FC_LCB_2003
        n_fib=0x0112 data=FIB_RG_FC_LCB_2007
    */
    uint16 cb_rg_fc_lcb;
    uint8 data[0];// ---->FIB_RG_FC_LCB_97... | csw_new,FIB_RG_CSW_NEW(csw_new!=0)
} FIB;
#pragma pack(pop)

class FileDecoderDoc
{
public:
    FileDecoderDoc();
    virtual ~FileDecoderDoc();

    FormatResult decode(const char* file_path);
    FormatResult decode(const CPPBytes& content);

private:
    bool decodeFIB();
    CPPBytes decodeText();
private:
    CPPBytes doc_raw;
    CPPBytes table_raw_0;
    CPPBytes table_raw_1;
    FIB* fib = NULL;
    FIB_RG_CSW_NEW* csw_new = NULL;
    FIB_RG_FC_LCB_97* lcb_97 = NULL;
    FIB_RG_FC_LCB_2000* lcb_2000 = NULL;
    FIB_RG_FC_LCB_2002* lcb_2002 = NULL;
    FIB_RG_FC_LCB_2003* lcb_2003 = NULL;
    FIB_RG_FC_LCB_2007* lcb_2007 = NULL;
    FIB_RG_CSW_NEW_DATA_2000* csw_new_data_2000 = NULL;
    FIB_RG_CSW_NEW_DATA_2007* csw_new_data_2007 = NULL;
};

#endif /* __DECODER_DOC_H__ */

