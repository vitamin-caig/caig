71FUN   H                        �0�� �v������                �"STS*",#C6;FIND,TOKENS;NEW SAVE/LOAD�_3d13ldMODE=5;odd!svMODE=6;even!�ldMODE=#E5;odd!svMODE=#CA;even!�RESIDENT_W	�reswin�WINDOW�5,7�13,12,"Resident",0�	�oldres�REST_RFON�
ReSET_RES	�reswin��,#C16�
rezxy=$+2	��,#1713���,(RES_ADR)	�INPUT_W��,��#C0!;MD_RES_COM ;JP PE/JP Z:48K MODE��,ReSET_RES�(RES_ADR),�
SAVE_RFON;twice;�� ��???7;���������� 䮭 ��� १����⮬ � ��⠥� RES+6, RES+11���,(RES_ADR)	�oldres����,OLD_RES
�RES_LDIR��
��,6;B=0���,6���,��(RES_ADR6),�;!!!�(RES_ADR6A),�;???;RSTART_LEN=8  FOR 4.x  !��,5��,��(RES_ADR11),�;+11	�_3d13�"�(RES_ADR11A),�;+11 for exit DOS���;twiceRESIDENT_HL	�pgreg���,(BANKS);�㦭� ����RESIDENT_H��,0;���� STS�RESIDENT_H	��,#1F18
BANKS=$-2�
STSPG=$-1	RESIDENT	��,#7FFD�RESRES_ADR=$-2	�oldres
REST_RFON��,OLD_RES	�RES_SET�
FINDASMpp"��,(STSPG);�⮡� �� ��/������(BANKS),�RES_INP��,#1A�$+4RES_PUT��,#12�(RES_IO_COM),���,SUB_RES_IORES_SET��,(RES_ADR)	RES_LDIR��,RES_LEN��
Save_Sect��,svMODE<8+8;2D73 ;SAVE
�L_S_Sect
Load_Sect��,ldMODE<8+7;2F1B ;LOAD	L_S_Sect��,��(SL_MODE),���,��(SL_TXT2),��#F�(SL_TXT3),���,4;12/11�(SL_TXT1),��WINDOW�5,#43SL_TXT1=$+2�15,9,12,10,#A0�23,11,10,2
SEC_TXT�0�8,12,10,5,2
LEN_TXT�1SL_TXT3=$+2�23,12,8," "+W	�28,12,1	TO_ADR�0�8,11
SL_TXT2�7
�"Trk",0��,#B13��,TRSEC+1�INPUT_B_D��,#B1E	��,TRSEC�INPUT_B_D�(SEC_TXT),���,#C13��,LEN_TXT�INPUT_B_D����,#C1C
��,TO_ADR�INPUT_W_D;HL=TO	��;=LENS_L_SECTOR	�oldres��REST_RFON��
LD_SV_SEC	�_3d13���,0
TRSEC=$-2�TRSEC=#5CF4��,(TRSEC)��lD_SV_SEC2SAVE_1_SEC��,svMODE;2D73�$+4LOAD_1_SEC��,ldMODE;2F1B�(SL_MODE),���,0;1(LOAD_FILE)SL_BUF_SEC��,BUFFER,�,1
;1(FILER)SL_STS_SEC��,#18,(DR_COM),�;_1lD_SV_SEC2;DE=(TRSEC);HL=DEST_MEM_ADR;B=SEC_LEN���(DR_SET_JR),�	�_3d13�����,���,(OUT_FF_3C)��,#1FF3;OUT (FF),A�DOS*;�᫨ FF=0,� ���� ��������� ����⠭���-�
��,#3DFD�DOS�����	�GOTO_TR	DISK_CKL������,���	��,#105F��,#2A53;OUT (C),A�DOSRE_CKL��,��CANCEL_TEST ��,(SL_MODE);E5:LOAD / CA:SAVE�#DF;FF:L,DF:S�#7F�OUT_1F��,#3FE5;:LOAD;#3FCA:SAVESL_MODE=$-2��,#7F��,��#BF�READ_WRITE_DOS	�TEST_1F�;��諮 4+11 ⠪⮢ ��᫥ EI��;A=1����,NO_ERROR	��,#5CD6�����RE_CKL�ERROR	NO_ERROR�������4,���,NO_TRACK	��,�;=0��GOTO_TR����,�����,#3COUT_FF_3C=$-1;#3C..3F:A..D��,$+4�#10��,#2F4D;TRACK�DOS;wait 51*65280*3t����,16066;�� NO DISK ��᭥�;LD DE,#3EF5�DOS���	;LD B,6	;LD D,B	;INC DE	;LD A,D;OR E�;JR NZ,$-3;DJNZ $-6��	NO_TRACK����
�DISK_CKL�(TRSEC),���,#38,(DR_COM),���,(DR_SET_JR)����;B=0�SAVE_RFON�	DISK_CKL����,0��,�٢,�SL_MODE=$+1��,ldMODE+#100;5:LOAD/6:SAVE��,���,��	��,$+4��#C0;OR A ;CY,�᫨ � ��࠭�窥1;NC - ��� १�����(��祬?��㧨�� ������ ����?)�READ_WRITE_DOS����,(#5CF4);LD (TRSEC),DE��,#38,(DR_COM),���,(DR_SET_JR)��
��;B=0 ?�SAVE_RFON�;1READ_WRITE_DOS!DR_COM;#18/#38:IN_7PAGE/IN_BANK��,DOS�$+2DR_SET_JR=$-1;0/..�SAVE_RFON;WITH EXX..EXX��,NO_DR_SET-DR_SET_JR-1�(DR_SET_JR),�
NO_DR_SET���,DISK_RES	�RES_SET��,(BANKS)	�pgreg���,(STSPG)��,���4,�	�_3d13���,�,�,�;=0��,���,(RES_ADR11)��,��
�RESIDENT	�_3d13�DOS�
��,32765��,(STSPG)��,���,�;D=(STSPG)DISK_RES��,0��,�*��,(REG_SP);�᫨ SP=call3D13,� 21 ����;�� ⮣�� �⥪� �� 墠����,��
;PUSH IY ��,23610;!!!��祬� �� ᭠�㦨?�1�#3D13�	;POP IY���,���,���;27�DISK_RES��,��DOS��JP_3D2F�#3D2F;��᮪ �⥪� ��� PUSH DE��#3FE5;:LOAD;#3FCA:SAVE;�⥪ १�����:#RES_ADR11A�RES+DR_RETURN-DISK_RES;8DR_RETURN;+11 /+18(3d13)���,���,���TEST_1F��,1��,$-1��,�	��,#2099�DOSOUT_1F��,#2FC3;OUT (1F),A�DOS�dIO��RES_IO��,��7,�
��,NO_ROM�6,�DOS_JR;JR/JR_NZ:BASIC/DOS�NORMAL_IO
��,IO_END����,#1D73;A(HL)��	��,�,�,�	�_3d13��#3D2F�	�JP_3D2F�NO_ROM;8000.FFFF�6,�
NORMAL_IO�RESIDENT_HLIO_END��,����SUB_RES_IO��,�RES_IO_COM��,���,��TEST_ROOM��,8�LOAD_1_SEC��,(#FFE5)
��,(FLEN)��,�����,$+3;ST2��
��,�;ST2��,0��,��(FLENSEC),���,���,No_Room�(#FFE5),���,(#FFE4)����No_Room��,5	�(-2),�;RET�CANCELTR_CANCEL=$-2;???Write�TEST_ROOM��,�;=(#FFE4)	��,�;=0�"))))��,�;=CAT_SEC����,��(CAT_ADR),���,(#FFE1)�(TRSEC),��(FTRSEC),���,svMODE;2D73 ;SAVE�(SL_MODE),�
�SL_FILE3Write_CALL=$-2��;E=CAT_SEC��,(TRSEC)��;NewFirst_TrSec���LOAD_1_SEC
��,BUFFERCAT_ADR=$-2��,FNAME_TXT;B=0?���,8�������,����,FILE_INFO+1�"B	��,$+4���,���;BC=8����,FILE_INFO+3���;E=CAT_SEC�SAVE_1_SEC�TEST_ROOM;DEC (DiskFree)��;=NewFirst_TrSec�(#FFE1),�	��,#FFE4��	��;=8!!!�
SAVE_FILE��,11	�SL_FILE��,SAVE_NEW_F;SaveExistFile��,svMODE;2D73 ;SAVE�(SL_MODE),�;!!!	�_8020����,SL_FILE3��,EXIST_TXT�PRINT_T_AT
�SL_FILE2;OverWrite�Write;E=8��,#F4;HL=FFF4���SAVE_1_SEC��,0DEL_F_SEC=$-1�LOAD_1_SEC��,1�(0),�DEL_F_ADR=$-2��;DE=DelFileTrSec	�SAV_CAN
EXIST_TXT	�16,#17�9,"exist",0SAVE_NEW_F��,FILE_INFO��,(EXT_TXT)�SL_FILE1_1
�SL_FILE2WR_DS_NAME�Write;E=8 ;SAVE_NEWSAV_CAN�SAVE_1_SEC
FILE_INFOFSTART�$+1	FLEN�$+3FLENSEC�$+5FTRSEC�$+6)�"C",0,0,1,0,1,0,0,0;-FOR LAST FILE !!!
LOAD_FILE��,12	�SL_FILE��,LOAD_EXIST
LF_NFOUND��,NFOUND_TXT�PRINT_T_AT�INKEYNFOUND_TXT�#12,#17,"No ",9,0;DB #D,#17,9,"not found",0LOAD_EXIST
�SL_FILE2	SL_FILE3��,(FSTART)
��,(FLEN)��������,S_L_SECTOR����������,1��,(SL_MODE)���,S_L_SECTOR;SaveLastSec��,���,(TRSEC)�SL_BUF_SEC	�RES_PUT
��,BUFFER��,���,�;B=ByteLenOfLastSec��MEM_STS_COPY����,��RES_IO;A<=(DE) INC DEԡ,��MEM_STS_COPY�Fadr������,��7�#D0
MD_11=$-1��,���,��#F0���,��SL_FILE�(SLF_TXT),���,(FILER_END)��
��,NO_FR�ENTER_SET�Fadr��,FNAME_TXT	��,#920	SLFR��,����#7F����,$+3��,�ԡ,���,����2	��,$-3��SLFRNO_FR�WINDOW�5,#43;IFN hints�10,11;ENDIF�20,"  NONAME   C"FNAME_TXT�$-10EXT_TXT�$-1�#A0,10,12�17,1FSTART_TXT�0�22,12,5,1FLEN_TXT�0��16,9SLF_TXT�11,9,0
��,#0B15��,FNAME_TXT��,8�INPUT_REWR
��,#0B1E��,EXT_TXT��,1�INPUT_REWRSL_FILE1_0��,0;=0=CAT_SECCAT_CKL��,��(DEL_F_SEC),��LOAD_1_SEC;DE=NewCatTrSec����;HL=BUFFER
FNAME_CKL��,FNAME_TXT��,�����;@@��,END_CAT����,8�(DEL_F_ADR),�	FSYM_CKL��,�ء��,NEXT_FNAME��,�
�FSYM_CKL����,�ء��,FNAME_OKNEXT_FNAME��,�
;AND #F0;ADD A,#10�#F����,���,FNAME_CKL;END_FNAME_CKL���3,���,CAT_CKLEND_CAT�;FILE ABSENT, C=1�%FNAME_OK;FILE EXIST C=0 ,A=EXT_NAME��SL_FILE1_1����,�����,�;FSTART����,�����,��"B"��,NOT_BASIC;LD C,E,B,D��,(#5C53);=PROG
NOT_BASIC�(FSTART),�
�(FLEN),���,���,�����,��(TRSEC),���;Cf=0 ,Zf=1�	SL_FILE2��,#0C10;#1610
��,FSTART�INPUT_W_D�(FSTART_TXT),�REINPFL��,#0C1A;#161A��,FLEN;_TXT�INPUT_W_D;A=L=C����,REINPFL�(FLEN_TXT),��FILER
��,#DA00
MD_13=$-1
��,#DA01
MD_14=$-1;LD D,H,E,1��,��(PANEL_ZONE),��(PANEL_Y),�	��,#FF�	ԡ,�;2��
��,(ADR)�(FSTART),�
��,#D000
MD_10=$-1
�(ADR),�	��,�;0��,ldMODE;2F1B LOAD�(SL_MODE),���,8�SL_STS_SEC;LD      A,LIST-PANEL_JR-1;LD      (PANEL_JR),A���(FILER_END),�	�WINDOW�2,0,0,32,16,0�0,0,0�FILER_REFR%;   SCROLL ZONE DPgUp YDN  X,Y,W, H�3;                 B    S   S S B  S����������������-13*8,14,0,1,32,13	�1,1,30�LOAD_FILE,#0101FILL_BLOCK�WINDOW�5,#44	�hints��16,09,"Fill",6,#A0��23,11,4,1	FL_END�0�9,12,3FL_TXT�1�8�9,11,17,0;Fill_Block2	�RES_PUT��,#B0F��,FL_START�INPUT_W_D��,#B1B
��,FL_END�INPUT_W_D;A=C=L��,#C09
��,FL_TXT�INPUT_HD;A=FL_LEN��,0FL_START=$-2��,�;=FL_LEN
FL_HD_CKL��,FL_TXT+1��,�	FL_B_CKL��,��#C0���,RES_PUT���,���,$+3Ԡ,�����,RES_IO;(DE)<=A������,(FL_END)����,���������,�
�FL_B_CKL�FL_HD_CKLCO_START�0COPY_BLOCK�WINDOW�5,#44	�hints��16,9,"Copy",6,#A0��23,11,4,1	CO_END�0�17,12,8,1CO_TO�0�9,11,17,0CO_REINPUT��,CO_START��,#B0F�INPUT_W_D��
��,CO_END��,#B1B�INPUT_W_D��	��,CO_TO��,#C14�INPUT_W_D;A=0 Cf=0��;=CO_END��;=CO_START��,���,CO_REINPUT���(CO_LEN),���,���,�;HL=CO_TO��,��;HL=CO_START��,�;DE=CO_TO��,���,0CO_LEN=$-2��,#B0; LDIR��,CO_PUT_OPR��,(CO_LEN);CO_LDD����,��;DE=CO_TO_END��,(CO_END);HL=CO_END��,#B8; LDDRCO_PUT_OPR�(CO_OPR),�;HL=FROM,DE=TO���,CO_RES;CO_RES_PUT	�RES_SET�RESIDENT_HL;C_CANCEL JP CANCELCO_RES;(HL)=>(DE)��,�;=#18��CO_OPR=$-1���,�;=#1F�FIND�WINDOW�4,3,7,#18,9,#45	�hints��#12,7,"Fin",#80+"d"�5,9�"As","m"+#80��#E,9
F_ASM_BUF�"NOP             "�#A0;IFN hints�5,#A,"Cod","e"+#80;ENDIF	�#B,#A,3	FIND_BUF�1�8�5,#B,"Mas","k"+#80	�#B,#B,3F_MASK_BUF�1�8,-1	�hints��5,#C,"Tex","t"+W��#11,#CF_TEXT_BUF"�#1E,#1F,#1F,#1F,#1F,#1F,#1F,#1F�#A0,#13,#D,"Inv"FIND_I_TXT�#9C�#14,#E,"GO"�0
�#9,10,14�FIND_ASM,#A0E	�#A,8,18�SET_FIND,#B09	�#B,8,18�SET_MASK,#C0A	�#C,#C,8�SET_TEXT,#D0B
�#D,#0E,4�FIND_INV,#E0C	�#E,#E,4�FIND_GO,#90D	FIND_INV��,FIND_I_JR��,8��ԡ,���,FIND_I_TXT	�XOR_1HL	FIND_ASM�FINDASMpp��,#90E�(ASM_AT),���,FIND_BUF+1���INPUT_ASM���;=Find_Buffer+1	;AND A�;SBC HL,DE��,����(FIND_BUF),���,26�(ASM_AT),��FIND_END_T	SET_FIND��,#A0B��,FIND_BUF
�INPUT_HDFIND_END_T��,FIND_BUF��,���,8����,F_TEXT_BUFFTXTCKL��,����#7F�" "��,$+4��,#1EԠ,�����	�FTXTCKL��,fIND_END��,#1FFTXT_2Ԡ,�����
��,FTXT_2FINDE=F_MASK_BUF+1	fIND_END�FINDASMpp��,FIND_BUF+1�CL_DIS_INS��,ENT_TXT;=ASM_BUFFER��,F_ASM_BUF��,16���,(FIND_BUF)�(F_MASK_BUF),�	��,FINDE�(F_END_TST),�	�trfind�(TF_END_TST),��	�pgreg�
BANK3=$+1��,0���,(BANK3)��(BANKS),��	SET_MASK��,F_MASK_BUF��,#B0B
�INPUT_HD;LD A,(F_Mask_Buffer)��,FIND_BUFء��,SET_MASK�	SET_TEXT��,#1F�(ULINE),���,F_TEXT_BUF����,#C11��,8�INPUT_REWR��;=F_Text_Buffer��,FIND_BUF+1��,#800fT_CKL��,��#1E
��,fT_IGN�#1F
��,fT_ENDԠ,�fT_IGN��,�,��fT_CKLfT_END��,�����,SET_TEXT�(FIND_BUF),�
�fIND_END
FIND_NEXT�ENTER_SET;Cf=0	��,(ADR)��,�;=-DELTA_ADR���(FIND_START),�;=CUR_ADR+1��,0	FIND_CKL��,0FIND_START=$-2���(FIND_START),���,FIND_BUF+1��,F_MASK_BUF+1����,�����,NOT_FOUND	F_CP_CKL�RES_IO;A<=(DE) INC DE����
FIND_I_JR��,FIND_CKL��,���,�	�FINDE+1F_END_TST=$-1��,F_CP_CKL;FIND_END_OK  Zf=1,Cf=0��,(FIND_START)����,�	�(ADR),��
NOT_FOUND	;LD A,2;OUT (-2),A;RET��ERROR��,2�(-2),��CANCEL;!!!
PR_AT�#7F�PR�PRINT_T_AT;HL=ADR_TXT_AT��,�����,����
PRT_AT�AT��,3�(PRINT+1),�PRT_T_CKL;DE=ADR_TXT��,����#1C��,NORM_SYM����,PR_AT_END����,TST_BYT���,�����,���	�PRINT_W	PR_BWH�����PRINT_T_AT
TST_BYT��
��,TST_HD��,���	�PRINT_B�PR_BWH	TST_HD��
��,PR_TOK);PRINT_H_DUMP       ;DE<=ADR_HDUMP_BYTES;HL<=YX             ;NEXT_HD_BYT=>DE    ��,8;=MAIN_LEN��,���,�;=BYTE_LEN�CONV_HDBUF;HL_SOHR��
��,BUFFER	�HDUMPPR�PR_BWHPR_TOK��,TOKENS��,�TOK_S_CKL�7,�����,TOK_S_CKL�TOK_S_CKLTOK_CKL��,��#7F���PR���7,�����,TOK_CKL��," "NORM_SYM�#80	��,PR_AT�PR�PRT_T_CKLPR_AT_END�(PRINT+1),�;=0�TOKENS�W,"En","d"+W,"Le","n"+W�" Bloc",W+"k","Fro",W+"m"�"T","o"+W�"Fil",W+"e","Secto",W+"r"�"Sav","e"+W,"Loa","d"+W�"Stop i","f"+W,"Ban","k"+W�"Qui","t"+W�"Trac","e"+W,"Star","t"+W�"Disas","m"+W," DEF","B"+W�"FileNam","e"+W�"BASI","C"+W," DO","S"+W;21,22
STAT_KEYS�#B�KEY_LEFT;UP�#A�KEY_RIGHT;DOWN�sinc�"9"�KEY_LEFT;UP�"8"�KEY_RIGHT;DOWN�PANEL_KEYS�#D�KEY_ENTER�sinc�"0"�KEY_ENTER��8
�KEY_LEFT�9�KEY_RIGHT�sinc�"6"
�KEY_LEFT�"7"�KEY_RIGHT�	STAT_END�#B	�KEY_UP�#A�KEY_DOWN
�scrolls�")"�SCROLL_DOWN�"("�SCROLL_UP��4	�PAGE_UP�5�PAGE_DOWN�" "	�CANCEL�"l"�LOAD_FILE�"s"�SAVE_FILE�"="�Load_Sect�"|";SS+S�Save_Sect�"#"�SWI_DECHEX	�drives�"!";"d"�SET_DRIVE��7�SCREEN_SET
FILER_END�":";SS+Z
�STEP_COM�"`";SS+X�STEP_COM_X�">";SS+T�STEP_SUBR�"w"�SET_BREAK�"p"�MEM_TO_ADR�#22�RETURN_MTA�"v"�ADR_TO_ML�"m"�MEMORYSET�",";SS+N
�ML_TO_SP�".";SS+M�MEM_TO_PC�"z"�PC_TO_CUR	�pgreg��"b"
�BANK_SET��"$"�dIS_LIST_S�"r"�RESIDENT_W�"f"�FIND�"n"�FIND_NEXT�"i"�FILL_BLOCK�"o"�COPY_BLOCK�"t"�TRACE�"c"�CALL_SUBR�"j"�JUMP_SUBR�user�"u";U
�SET_USER�"]";SS+U�USER��"q"�QUIT�"%"�DIS_LABEL�xxx�"x"	�SET_XXX��ssk�"+"�SS_K;JP_TO_PC SCR=1�"-"�SS_J;JP_TO_PC SCR=0��"a"�SET_AP	;KEY_48K�#E�FILER�"e"	�SWI_DOS�ruswi�"y"	�SWI_RUS�
�disdisk�"d"
�DIS_DISK��0 