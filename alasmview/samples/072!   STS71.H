STS71   H                        ]?�� �v������                3;todo ANYSCREEN (LDIR #4000,NO INDICATE)+ALASM res);todo labels(� �� ⮫쪮)�१ ALASM res;todo nextpage � labelpageends;KILL REDISASM?;�ࠩ� ����� �������?
;BUFFER:&;#FF00 - user ������� �� userarea=0�;#FF00 - ��᪮�� ����/;#FF80 ���� - P_BUFFER ��� ��."P" (P_BUF_ADR)�+;#FFBE - ���� ��ப,���������� �� ��࠭�!;#FFFF - ���⨬ ��� HALT �� IM2v1="7v2=".v3="1oldres=1;1            ;54rus=1;657rushole=1;-190rusend=0;66ruswi=1;9romfont=1;-489small=romfont	;-2_3d13=1;-117drives=1;38/27 ss1,fix=10onint=1;2mega=1;-2ARfix=0;5jASM=0;1=#C000,0=RET ;0reswin=0;12downs=1;1              ;9xxx=0;28pgreg=0;21	splash=0hints=0;1             ;41windows=1;86winatr=0;6titl=0;63shad=0;23beeps=0;1             ;11ssk=0;1                ;6scrolls=0;1            ;6sinc=0;24trbank=0;1            ;29user=1;1              ;37userarea=0trfind=0;1            ;64disdisk=1;1          ;829eof=0;10?eol=1-disdisk
;8?;P_BUF_END=#FF40P_BUFFER=#FF80BUFFER=#FF00DD_BUF=#4000;#9000!LOCEND_BUF=#5AFFVECTOR=#FF1CENT_TXT=#FF80ENT_BUFFER=#FF98_8020=8020
_28E=#28E
_31E=#31E
_334=#334
RES=23698�#DB00�(QUIT_SP),�;��室 �� १�����rETURN_COM
;resadr+4;4+LD()SP+LDSP+PUSH+PUSH=13;todo:";LD()BC+LD()A=7 (� ���� A,R:DI)�(RES+6),�;���ࠥ� � ᥡ�RES_ADR6=$-2#��,RES+6;�� �� ���뢠���...RES_ADR6A=$-2��,�	�ARfix���,�;����� �ਡ����� IFF��	��,#7FFD��,#1FSTSPG3=$-1;OUT (C),A�#ED,0jP_OUT_COM=$-1;0/#79�jP_RETURN;<=IN RESIDENTREND_LEN=$-rETURN_COM;�室 � १�����	JUMP_RES��,���,0JUMP_BC=$-2��,0JUMP_A=$-1EI_DI�RSTART_LEN=$-JUMP_RES;=8RES_LEN=RSTART_LEN+4+REND_LEN;���⠢��� ��絛����
SET_BREAK'�REST_BREAK;������ ���� ��絛�����ENTER_SET;BC=DE=���.�����BREAK_PSET�(BREAK_PC),���,BREAK_BUF-1��,3�MEM_STS_COPY;HL=BRET_CODE-1
BREAK_PUT�	�RES_PUT���,0BREAK_PC=$-2��,3�MEM_STS_COPY	�RES_INP$BREAK_BUF�3;�� ����஫ ��絛����;BRET_CODE�RES+RSTART_LEN+3;=+11RES_ADR11=$-2	TRACE_GO��,(TrC_TXT)���,NO_TR_CALL-STC_JR-1��,$+3���(STC_JR),���,TRACE_SIM;CALL ENTER_END+3�(W_KEY_JP),���,(Ind_TXT)�	��,STACK��,CANCEL+6��,(BANKS);MEM_BANK�8��,SCR_SET;!!!
TRACE_CKL�TRACE_SIM
�STEP_Z80�TRACE_CKL
TRACE_SIM��,#7F��,(-2)���,TRACE_END��,(StD_TXT);#9D=ON���,NO_TestDOS��,(DOS_JR)�#18��,TRACE_END;IN DOSNO_TestDOS	�trfind��,(StF_TXT);#9D=ON���,TRACE_FIND�����,(REG_PC)��,(TR_STOP_A)��,���,TRACE_END;NZ!�user��,(StU_TXT);#9D=ON���,USER��,TRACE_END���,(TrC_TXT);#9D=ON���,":";ssZ����,"`";ssX���$," DON'T CROSS PARAGRAPH!"
MASK_TABL�FC00�3F00�0FC0�03F0	�trfindTRACE_FIND	�RES_INP��,(REG_PC)��,FIND_BUF+1;!!!��,F_MASK_BUF+1;!!!
TF_CP_CKL�RES_IO;A<=(DE) INC DE��,���,���������,���,�	�FINDE+1TF_END_TST=$-1��,TF_CP_CKL;JR TRACE_END�
TRACE_END;4JRs;LD HL,INKEY;LD (W_KEY_JP),HL;RET�CANCEL	JmpFrAlm�"JUMP FROM ALASM=",$��(QUIT_SP),��CANCEL
jP_RETURN;1	��,STACK$JUMP_SP=$-2;��� ��室� �� JP/CALL?
�REG_SAVE	�CANCELJP_RET_JR=$-1;!!!;todo detect page;��,(REG_IR+1)�31�31��,-2;<2:IM1��,0�	���(imnom),���,(BREAK_PC)�(REG_PC),�;JP REST_BREAKREST_BREAK��,BREAK_BUF-1�BREAK_PUT�(BREAK_PC),�;=0�	RET_STEP;JR from JP_RET_JR��,1�ADD_IR;STEP_END2dIS_LIST_S��,PANEL_JR��,DISASM-PANEL_JR-1��ԡ,���,PANEL_ZONE��,�����,$+3���CANCELFIND_GO�FIND_NEXTCANCEL	��,STACK�START;RESTORE_VARS �ᥣ��START_JP=$-2��,(STSPG);RESTORE_MEM_BANK�8MD_SCR_COM��,SCR_SET��,FILER_END���(L_PC_CUR),�����,NOT_FILER��,":"��,(FSTART)��,���,NOT_FILER
�(ADR),�
NOT_FILER�DISASMPANEL_JR=$-1LIST�WINDOW�2,0,0,32,24,0�0,0,0�LIST_REFR";SCROLL ZONE DPgUp YDN  X,Y,W, H;B    S   S S B  S�-21*8,22,1,1,30,21�1,1,4�ENTER_ADR,#203�2,6,18�ENTER_DUMP,#301�3,25,6�ENTER_TEXT,#102DISASM�WINDOW	;FL5=$+4
;UD12=$+2�2,0,0,32,24,0
;UD29=$+1�xxx�2,10+1+pgreg��2,14+1+pgreg���small	�"int",0��	�"INT",0��
�DIS_REFR!;SCROLL ZONE DPgUp YDN X,Y,W, H;B    S  S S B  S�-21,22,9,1,25,21�0,0,7�ENTER_REG,#103�1,7,4�ENTER_ADR,#200�2,11,7�ENTER_CODE,#301
�3,#12,#E�ENTER_ASM,2SCR_SET��,(BANKS);MEM_BANK�8
�BANK_PUT	�pgreg�	BANK_SET	��,#1726��,(BANKS)	�INPUT_B�BANK_PUT_M�8MD_8_BANK=$-1	BANK_PUT�mega�#DF��(BANKS),��(BANK3),�;��� FINDASM�#18�0STSPG_0=$-1�(STSPG),��(STSPG3),�	��,#7FFD��,�;�㦭� ���+����8�(MD_8_BANK),��	�pgreg�
BANK_TEXT	�#21,#17	;UD5=$-1�14,2
BANK3�#18�0,0,0�REG_TXT��small�"PC�"SP�"ix�"iy�"hl�"de�"bc�"af�"IR�xxx�"hl�"de�"bc�"af����"PC�"SP�"IX�"IY�"HL�"DE�"BC�"AF�"IR�xxx�"HL�"DE�"BC�"AF����"IM	�pgreg��"PG�FLAG_TXT�"SZ5H3PNC
�disdiskDD_NAME=$-7�"@�	DIS_REFR��,DIS_LINE�REFR_STARTREG_PR
��,REG_PC�	�RES_INP;LD HL,(SUD12-1)��,0	��,#C000ML_ADR=$-2�LIST_LINE	;INC H�	;LD L,0	��,#100��,REG_TXT�xxx��,9+1+pgreg���,9+4+1+pgreg�
REG_CKL���AT��,��PR2INC_DE�xxx��,��2�4��,$+7SXX=$+1	��," "����,�
�2+pgreg�4;5��,$+7	��,"'"���PR����,�����,���٢,���,3	�PRINT_W���������	�REG_CKL����,6�AT��,#1DINT_TXT=$-1�PR�����AT��,(REG_AF)��,FLAG_TXT��,8
FPR_CKL����,�����,$+4	��," "��PR	�FPR_CKLPRINT_BANK;��� LIST_REFR;todo PRINT RESIDENT???	�pgreg�����,BANK_TEXT�PRINT_T_AT�	REG_SAVE
�(SSP1),�	�ARfix�;ROSHIN fix��,���,INrOFF��$+4INrOFF��,�����,#1D��,INT_OFF	�PUT_INT
INT_OFF��PUT_INT�(INT_TXT),���,REG_END��	��,�,�,�	��,�,�,�	��,�,�,�����,(RES_ADR)��������;SP��,REG_AF+2��,��	��,�,�,����';todo DETECT CACHE (use in GET,ssZ..)���,(#7B);cache off��,STACK-2	SSP1=$-2	�onint���,59������,���,#80-#22-(ARfix*2)ADD_IR��,REG_IR�����,��ԡ,���xxxSET_XXX��,(PANEL_JR)������,SXX��,7��ԡ,�
��,REG_HL��,REG_HLX��,8SWAP_X0��,���,�ԡ,���,�Ԡ,���,�	�SWAP_X0
�REFR_REG�
ENTER_REG��,(CUR_Y)��,��xxx�10+1+pgreg��10+4+1+pgreg���,ENTER_INT��,���,REG_PC-2��,��
;ADD A,0;UD32=$-1��,���,3�INPUT_W_D
�REFR_REGSTEP_COM_X���$+4	STEP_COM��,NO_TR_CALL-STC_JR-1�(STC_JR),�;STEP_COM_2
�STEP_Z80	;LD A,1;LD (WAIT_FAST),A��,(PANEL_JR)��REFR_OPER;_/Z, C9/C8
��;NZ???	REFR_REG�REG_PR;REG_PR+PC_CUR+NO;_REFR
NO_REFR_2���REFR+2SCREEN_SET=SCR_SET;CALL SCR_SET;JR NO_REFR_2
ENTER_INT��,INT_TXT	�XOR_1HL
�REFR_REGFILER_REFR��,FILER_LINE�REFR_START
LIST_REFR	�pgreg��PRINT_BANK��RESTORE_IX��,LIST_LINEREFR_START�(LINE_SUBR),�	�RES_INP	��,(ADR)��,0	;UD2=$-1REFR_L_CKL��
REFR_L_C2���PANEL_LINE��,(TABL_ADR)�(NEXT_ADR),�ԡ,���ԡ,����(TABL_ADR),���	��,�-5)����,REFR_L_CKL�PANEL_LINE
�DIS_LINELINE_SUBR=$-2
LIST_LINE��,1��,�	�PRINT_W��,�����,8��,�LBYTE�RES_IO��
�PRINT_HB����,�,��LBYTE���AT����,8LTX_CKL�TAKE_SYM�PR	�LTX_CKL	��,�,�,��FILER_LINE;BC=ADR_COORECT�Fadr������,1;3;for "filenam_"�AT�,;0123456789ABCDEF0123456789ABCDEF0123456789*;   FILENAME C  #5D3B #2000  #20  #A0 #02��,���,8FRP_CKL�PR_INC_DE
�FRP_CKL
�INC_POS�PR_INC_DE
;FR START��,�����,#F�	��,�+9)
��,�+10)
�PRINT_W;FR LENGTH������,#15
��,�+11)
��,�+12)
�PRINT_W;FR LEN SEC������,#1C
��,�+13)
�PRINT_B	;FR F.TR������,#21
��,�+14)
�PRINT_B
;FR F.SEC������,#25
��,�+15)
�PRINT_B��	��,16�	��,������������	TAKE_SYM�RES_IO;INC DE�rus�#7F�" "��	��,#1F��
�romfont�-16��,$+5��" "��	��,#1F���ENTER_TEXT��
��,BUFFER����;A=D��,8LE2CKL�TAKE_SYMԡ,����LE2CKL����,33��,8
�INPUT_1F��;=BUFFER����,8	LE2CKL2�	�RES_INP��RES_IO;A,(DE+)	�ruswi���,���,(Fruswi);#FF=rus�����#80���,��	�RES_PUT���,����#1F��,$+6;IGNNN���dIO;(DE),A	�LE2CKL2�ENTER_ENDENTER_ASM�(ASM_AT+1),��INPUT_ASM�ENTER_ENDENTER_CODE������,�����,����,���,���,-5��,�����,#F��,ENTER_L_OK��,���	��,�,�,���,4ENTER_L_OK��,INPUT_HLIN	�ENT_DL1ENTER_DUMP��,INPUT_HD��,���,8��,�ENT_DL1�(HLIN_CALL),���;=ADR_IN_MEM��;=YX_COORDS;ENTER_LOAD_MEM��,���,���,ENT_BUFFER��,�;MAIN_LENԡ,����MEM_STS_COPY��;=ENT_BUFFER��;=YX���0HLIN_CALL=$-2	�RES_PUT��;=ENT_BUFFER��;=ADR_IN_MEM��,�;<9,>1�MEM_STS_COPY
ENTER_END�RESTORE_VARSCRD_JR=$-1��,AUTO_ENT�(W_KEY_JP),���,RESTORE_VARS-CRD_JR-1�(CRD_JR),�	�CRDOWNRESTORE_VARS	��,INKEY�(W_KEY_JP),���,(NAME_PR_AT+1)�(ASM_AT),���,#C3�(JPC_COM),�	NORM_INP���(HD_OPER),���," "�(ULINE),�	��,PRINT�(IPRINT),���,�;FOR IHD (BIOS)�	INPUT_HD��,HDUMPPR�(IPRINT),���,#85;ADD A,L��,8�$+5INPUT_HLIN��,4���(HD_OPER),�;INPUT_HDUMP_REWRITE;DE=ADR_HDUMP_BYTES	;HL=YX;C=MAIN_LEN��,���,�;=BYTE_LEN��,��CONV_HDBUF	HD_REINP��������
�INPUT_1F��;CONV_BUF_HD��,��������;!!!CL
��,BUFFER���,0	CBHD_CKL��INP_2_HEX�0,��	��,HD_OK��,HD_REINP	�#1F-"0"��,HD_REINP	�IHD_END
HD_OKԠ,���,�����,CBHD_CKLIHD_END��,�����,HD_REINP��,�Ԡ,�
�NORM_INPQUIT�WINDOW�4,8,8,16,6,#47	�hints��19,8�#F,#A0��jASM�16,10�#F,8,"AS",#80+"M"��20,10�"RE",#80+"T"��15,11�#F,8,21,#A0;BASIC�19,12,22,0;DB 17,12;DB "Call ",22,0;TRDOS	�#A,9,14�QUIT_ASM,#B0C	�#B,9,14�QUIT_BAS,#C0A	�#C,9,14�CALL_DOS,#A0BQUIT_ASM�jASM
��,23610��,(QUIT_SP)����,#51AL_ASMBANK=$-1��"AL_ASMBANK=",AL_ASMBANK��,jASM�QUIT_PUSK�	QUIT_IM1
��,#5C3A�(REG_IY),���ԡ,#CC��,INT_TXTԡ,#1D;EIQUIT_PUSK��,0QUIT_SP=$-2
;Q_PUSK_2�#10;LD (BANKS),A ;v5+5;LD (REG_SP),HL;LD (JP_SP),HL�1;1CALL_START��,CANCEL-JP_RET_JR-1*256+#F7�QUIT_INITQUIT_BAS
��,#2758�(REG_HLX),�����,#58
�QUIT_IM1	CALL_DOS���(REG_IR+1),���,#CD�(JPC_COM),�	��,#3D00��,(BANKS)
�QUIT_IM1
STEP_SUBR�REST_BREAK��,(REG_PC)�IPRDIS_INS);STEP_CALL                              ��BREAK_PSET
SS_K��,-1�JUMP_INIT
CALL_SUBR��,#CD�(JPC_COM),��WINDOW�5,7�15,12
�"CALL",0��,#C14
��,REG_PC�INPUT_W_D;LD DE,(REG_PC)
��,�,�,���,(BANKS)��,(REG_SP)�CALL_START;18
JUMP_SUBR�WINDOW�5,7�16,12�"JP",0��,#C13
��,REG_PC�INPUT_W_DSS_J��,#F7
JUMP_INIT���(PC_CUR_COM),���,���,(BANKS)��,(REG_PC)��,(REG_SP);1
QUIT_INIT�(JP_SP),���,JP_RET_JRԡ,���,(RES_ADR6)	��,�;+8ԡ,#C3JPC_COM=$-1��ԡ,���ԡ,���;1
RET_Q_ASM���(JP_BANK),����,(INT_TXT)���,��#FB�#F3�(EI_DI),���,(REG_AF+1)�(JUMP_A),���,(REG_AF-2)�(JUMP_BC),���,rETURN_COM��,REND_LEN���,RSTART_LEN��,(RES_ADR)�%�(JUMP_SP),�;��� ��室� (jP_RETURN));JUMP_RES_PUT                           );REG_LOAD                               �1��,(imnom)��$+4�2��,128-#20�ADD_IR��,�
��,REG_IX��,�,�,�,�,�������,�	��,�,�,���;LD SP,(REG_SP)
JP_SP=$+1��,0��,#18JP_BANK=$-1�RESIDENT;RES_JUMPERTRACE�WINDOW#�4,7,7,17,9+trfind+user+trbank,#46	�hints��18,7	�#10,#A0��19,9,"G","O"+#80_y=10�1�12,_y�"Indicat","e"+#80�27,_yInd_TXT�#9C_y=_y+1��1�12,_y�"Re",18,#A0�27,_yReD_TXT�#9C_y=_y+1��1;STOP IF TR-DOS�12,_y,13,22,#A0�27,_yStD_TXT�#9D_y=_y+1�	�trfind�12,_y,13,"Fin","d"+#80�27,_yStF_TXT�#9C_y=_y+1��user�12,_y,13,"Use","r"+#80�27,_yStU_TXT�#9C_y=_y+1��1�12,_y,13,#A0�17,_y,"o","n"+#80	�24,_y,1TR_STOP_A�0_y=_y+1�	�trbank�12,_y�16,14,#A0�27,_yTrB_TXT�#9D_y=_y+1��1�12,_y�16,"CAL","L"+W�27,_yTrC_TXT�#1C��0�9,#E,3�TRACE_GO,finy_y=10	�_y,20,2_y=_y+1�SET_IND,_y*257-2	�_y,20,2_y=_y+1�SET_REDIS,_y*257-2	�_y,20,2_y=_y+1�SET_ST_DOS,_y*257-2	�trfind	�_y,20,2_y=_y+1�SET_ST_FND,_y*257-2��user	�_y,20,2_y=_y+1�SET_ST_USE,_y*257-2�	�_y,18,5_y=_y+1�SET_ST_ADR,_y*257-2	�trbank	�_y,20,2_y=_y+1�SET_TR_BAN,_y*257-2�	�_y,20,2�SET_TR_CALL,_y+#8FFfiny=_y+#A00	STEP_Z80�RES_INP;@@??	;LD A,1;CALL ADD_IR�RET_STEP���(NEW_PC+1),��(DEBUG_CNT),��(PC_CUR_COM),��(OVER_PREF),��(PREF_CNT),��(ED_DEB_COM),����(Debug_IF),�;=#FF��,(REG_PC);LD (OLD_PC),BC�DIS_IGN_PR��,#C5�(PR),��(REG_PC),�;NEXT_PC��,0DEBUG_CNT=$-1����,Step_RET;Step_Simple_CommandSTEP_SIMPL��,0OVER_PREF=$-1�ADD_IR��,0COM_ADR=$-2�RES_IO;A,(DE) INC DE	�trbank�NO_LD_AHL%STEP_B_JR=$-1;NO_LD_AHL/ BN_NO_BANK
NO_LD_AHL��#ED��,BN_OUT_A��,(REG_HL+4);=REG_BC;BIT 1,L     ;7FFD:b15=0,b1=0��,��#FD��,BN_NO_BANK�7,���,BN_NO_BANK�RES_IO;A,(DE)����,��#C7�#41��,BN_NO_BANK�������,�	�6;OUT (C),0	��,OUT_0���,BN_COM_TAB��,0��,���,�
��,REG_HL��,���,�OUT_0��,PREF_CNT��	BN_PUT�BANK_PUT_M;MASK�STEP_END;B C D E H L 0 ABN_COM_TAB�5,4,3,2,1,0,6,7
;nuBN_OUT_A�#D3��,BN_NO_BANK�RES_IO��;BIT 1,A ;7FFD:b15=0,b1=0�#FD��,BN_NO_BANK��,(REG_AF+1)�7,�
��,BN_PUTBN_NO_BANK����,#FFCOM_LEN=$-1��,(REG_SP)�(JP_SP),���,(RES_ADR6)���MEM_STS_COPY����,RET_STEP-JP_RET_JR-1;JP RETURN_LD;JR rET_Q_ASM;1;RETURN_LD ;HL=COM_ADR in RES�(JP_RET_JR),���,(BANKS)�RET_Q_ASM;rET_Q_ASMStep_RET��,(REG_SP)�3��,Step_DJNZ��,PREF_CNTED_DEB_COM�;/INC (HL)�IF_PC��,STEP_END�RES_IO;INC DE��,��RES_IO;INC DE��,��PUT_NEW+3	�STEP_SPStep_DJNZ��,Step_CLRST	��,REG_B����,PUT_NEW
�STEP_ENDStep_CLRST
;CALL&RST�3��,Step_JP_HL;DE=REG_SP�NO_TR_CALLSTC_JR=$-1�STEP_SIMPLNO_TR_CALL�IF_PC��,STEP_END�	�RES_PUT���,��dIO;INC DE����,��dIO;INC DE��
STEP_SP�(REG_SP),�STP_END�STEP_ENDStep_JP_HL��,Step_JUMP��,(REG_HL)JP_HLX_REG=$-2�PUT_NEW+3
�STEP_END
Step_JUMP;JP/JR�IF_PCSTEP_END��,0PREF_CNT=$-1;LD E,-1;NO_KEY�ADD_IR
IF_PC��,0Debug_IF=$-1����,PUT_NEW������,FLAG_MASKS-1������,$-2��,(REG_AF)��,$+3�����PUT_NEW��,0NEW_PC=$-2;SET_NEW_PC�(REG_PC),����,��#3D��,NO_SET_DOSI;SET_DOS                                ����������������������������������,#20�SET_DOS_JRNO_SET_DOS�#40
��,EXARETI;SET_BAS                                ����������������������������������,#18SET_DOS_JR�(DOS_JR),�EXARET��;DOS_JR: JR/JR_NZ:BASIC/DOSFLAG_MASKS�#40,1,4,#80	�drives
SET_DRIVE��,#101;#B1C	��,DRIVE��,1�INPUT_REWR
DRIVE=$+1��,"A�"A�4��,SET_DRIVE	�_3d13���,1�DOS	��,#18��DOS��#3C�(OUT_FF_3C),���,#1FF3;OUT (FF),A�DOS��,8	�OUT_1F��
�disdisk	DIS_DISK�"71DASM",#C0��"71FUN",#44�"disa72",#86�"biosrus",#46
�romfontFNT�A25408A200�020244A818�285028A8A8�2A552AAAAA�"STS4FONT"�rus�"RUS128",#70*5���rusFNT�"rus128-",#80*5	�rushole�$-(#100-#B3*5)
�#100-#DB	�{$+200}	�{$+200}	�{$+200}���rusend�$-70��SETKA�54AA54AA54AA54��/;DB "(C)STALKER STACK PLACED IN THIS MEMORY !"4�40+2;+(onint*8) ;�� 墠⠫� 2 ����+10 �� IM1�����STACK	�oldresOLD_RES	�RES_LEN�	;MMM=#23USER�-$,#C9�#FE62;#FEE4-125+5-10�"FREE=",$-USER�"END=",USERAP_BUF�#6000�#8000�#C000�#5D3B�#5CF4PRINT_WLAB
�$+2;0/3PRWW�PRINT_W��
��;=WORD
��,RES_WL	�RES_SET����	��,#FEF0AL_LSTART=$-2��"AL_LSTART=",AL_LSTART��,0�
��,(BANKS)	��,�	�#18	�#C3AL_LBANK=$-1��"AL_LBANK=",AL_LBANK	�(LAB_BANK),�;todo alasm res 23584;AL_LBANK=$-1;LD A,#43;LD SP,  ;prog SP;;LD BC,ALLBQ
;PUSH BC;LD BC,RESIDENT
;PUSH BC;JP 23584;ALLBQ;LD A,(BANKS);LD BC,32765;OUT (C),A;	�RESIDENT_H�	��,�	���	�RES_INP��,�,����,PRWW�3;!�11��,$+4��,10��,���,(PRINT+1)����,AT;DE=LAB_TEXT_ADR in PGSYM	��,BANKS�	��,�	ԡ,#18+3���LAB_BANK=$-1
PLW_CKL���RES_IO;A<=(DE)���#20��,PLW_END�PR	�PLW_CKLPLW_END��ԡ,�
;LD A,C�;LD (BANKS),A�RES_WL	��,��RWL_CKL��,�
;AND #3F�2;LD E,A ;for nextpage��,RWL_END;!!!�#3F��,�����,�ء����,���,���,RWL_CKL����,RWL_CKL;XOR A ;Z=1	;LD A,E	RWL_END�;EXA;AL_STS_BANK=$+1	;LD A,0;JP 23584	��,�	��"label resident=",$-RES_WL�0RES_WLP
PLWrCKL��LABrBANK=$+1��,0	�23584���,�����AL_STS_BANK=$+1��,0	�23584����#20���PR;���� � �⥪�� STS'�	�PLWrCKL��"label2resident=",$-RES_WLP�"�"skip after labelview=",#FEE0-$�#FEE0-$;E4-$REG_PC�#8000REG_SP�#5AFFREG_IX�#0000REG_IY�#5C3A;HL    DE    BCREG_HL�#0000,#0000,#0000
REG_B=$-1REG_AF�#0000REG_IR�#3F00;HL'   DE'   BC'  AF' REG_HLX�#2758,#0000,#0000,#0000REG_ENDimnom�#0001	�pgreg�BANKS�#0010�
ADR�#8000��"endregs=",$ ZONE_DELTA=7;???bios:FIND_ZONE�#FF00�"70START",#C7��userareaUSER=user_��	�-$,#C9�#5B20GO��,#DB00	��,#9B00	��,#2500�	��,#7FFD��,#1F��,�	��,#9B00	��,#DB00��,#25�
�JmpFrAlm 