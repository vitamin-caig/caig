biosrus H                        d3�� �v������                �"STS*",#C6;STS_BIOS STALKER'1994;INPUT/PRINT_WORD/BYTE/(_D)	;INPUT_W
;HL<=YX;BC<=WORD;WORD=>BC=HL;A=C, Cf=0;INPUT_W_D
;HL<=YX;(DE)<=WORD  ,DE=WORD_ADR;WORD=>BC=HL=(WORD_ADR);A=C, Cf=0
;INPUT_HD
;HL<=YX#;DE<=TXT: 1F_LEN,#11,#2A ...,#CD	;LEN=8;IN INPUT :"11 2A ... CD";BYTE_LEN=>A ,DE=TXT
;PRINT_HD;ANALOG ^;INPUT_HLIN;...,LEN=4;IN INPUT :"112A...CD";BYTE_LEN=>A ,DE=TXT;NEW INKEY+KEY;KEY_NUM=>E;PRINT;TXT:FROM (DE)TO (0)
;HL<=YX;BC=NO MODIFY�;A=0, Cf=0;NEW INPUT;(CURSOR)=0;NEW INPUTC;(CURSOR)<=..�;KEY UP/DOWN;A<=TXT_LEN;TXT=>(BUFFER);AT
;HL<=YX;PR;A <=CHAR;FONT COMPRESSED 6*8=>6*6FILL_FF
�windows��,-1�FILL
�windows��,�	��,�,�,�����,0ԡ,����,��NL����,��7����,���,32��,�����,��8��,��STANDART;TYPE,X,Y,L,H,COLOR�5,5,9,#15,6,0WINDOW��,#A�(STAT_ZONE),����0,���,NO_STAND_W��,�+1)��,-4��,�����,STANDART��+5),���,#C9�$+5NO_STAND_W�����(aUTOSTART),����(WDR_JR),���,�;ATTRIBUTES��,�+4)��,�+2)�")))))��,�+1)��,#D8;/#58	MD_1=$-1��,�	�winatr��,�+5)����,$+4;W_ATR_2���,#07
COLOR=$-1�/T,COLOR;W_ATR2�(COLOR2),�
�windows��,#20�titl�1,���,�+3)��,WYATR;PANEL������,�;INV ATR	��,�,�,�����,�����,�����,���������,���,�+3);W_INVԡ,����$-2���W_IATR�;IFN winatrWYATR��,�+3)��;WXATRԡ,����$-2	W_IATR����,�;Cf=0��	��,WYATR;ENDIF�shad�2,���,W_CLEAR��,1	��,�+3)��ԡ,��$-2	��,�+4)ԡ,���,�;Cf=0�$-3W_CLEAR���,�+2)������#E0��,�+1);<42!��,����#18��,#40+#80;	MD_2=$-1��,���,�+3)���titl�1,���,W_PANEL��,8;W_WINDOW	;CLUPCKL���FILL�$-4��,�+4)����,�,�,�,�,��W_VERTW_PANEL�	�FILL_FF��,�+4)��,�,�,�,�,���	W_VERT����,���,�WCL_CKLԡ,#80�����FILL����,1Ԡ,�	�WCL_CKL��,�	�FILL_FF�����
��,6;D=0��,��(WINDOW_TXT),��PRINT_T_AT;W_DATA_INIT�٢,�aUTOSTART;(OPER)�;W_NOAUTOSTART�1,�����,W_PAN_DATA;W_STATIC_DATA�(START_ZONE),�	STAT_CKL��,1STAT_ZONE=$-1�#1F�(CUR_Y),���,STAT_KEYS��,STAT_ZONE��,STAT_CKL��;!�REST_ZONE��,0WINDOW_TXT=$-2�PRINT_T_AT
�STAT_CKLINKEYWAIT_FAST=$+1	WAIT=$+2��,#101WAIT_F_CKL��	��,0;IY ;CAPS_FLAG=$-1 ;0:NO 1:CAPSLOCKEXTKEY	�onint�	��,201��(-1),�;�� �� ����஫�?�2� �;im1 ����� #5C00..8, 23670/1;DI ;��� im1���,#12;KBD_SPEED�$����,$-3��_28E��,EXTKEY;KEY_END�_31E��,KEY_END��,���,#CC;(IY+1)��,�;0 ;(IY+7)�_334;A=ASCII SYM�#80	��;=1�
��,EXTKEYKEY_END����,NEW_KEY��,��0LAST_KEY=$-1�(LAST_KEY),���,NORM_KEYNEW_KEY��,#20F;A,#18;LD (WAIT_FAST),A ;LD B,2 ;? 1 �����-ᠬ�����:(	NORM_KEY�WAIT_F_CKL;WAIT_FAST=$+1��,�;1
�(WAIT),�;LD A,1 ;?;LD (WAIT_FAST),ABEEP�beeps;LD A,(COLOR);RRA;RRA;RRA
SOUND=$+1	��,#0418
;LD A,24;XOR 0;LD ($-1),A��,��(-2),��$���(-2),�����(-2),��CANCEL_TEST	�_8020����CANC1W_PAN_DATA��,�����,�	;INC HL
�(REFR),���,7��,��(START_ZONE),�������,1PANEL_Y=$-1�(CUR_Y),�W_DREFRESH	��,(ADR)�(#FFC0),�	��,#FFC2�(TABL_ADR),��0	REFR=$-2��,(CUR_Y)�(PANEL_Y),�;LD A,0	;UD8=$-1;LD (SUD8_1),A��,(PANEL_JR)��,FILER_END����,PC_CUR_PUT��,-WDR_JR+W_DREFRESH-1�(WDR_JR),���,PANEL_KEYS��,PANEL_ZONE
��,REFR+2��,#B;{STAT_END}�REST_ZONE�W_DREFRESHWDR_JR=$-1CANC1�CANCELPC_CUR_PUT��,PC_CUR_DAT��,0L_PC_CUR=$-2��,(COLOR)�PC_CURSOR��,#1601;1C01	;FL6=$-1�(PCC_SP),���,BUFFER+#C0��,(REG_PC)
PCCPCKL������,���,PC_CUR_ON��	�PCCPCKL��,STACK-2PCC_SP=$-2PC_CUR_COM;C9/0�;LD SP,STACK����(ADR),�;=REG_PC�W_DREFRESH+3;
PC_CUR_ON��,STACK-2	��,�,�,��(L_PC_CUR),���,#38�PC_CURSORPC_CUR_DAT=$-1�7,25;
REST_ZONE�(STAT_END),��(NO_REFR_JP),��(KEYTAB_ADR),��(ZONE_VAR),�
RESTORE_Z��,(ZONE_VAR)��,���,�����,ZONE_REFR	��,CUR_Y�xxx��,10+1+pgreg���,10+4+1+pgreg�ء��,ZONE_REFRԡ,�
ZONE_REFR�FIND_ZONE��,#70COLOR_CUR=$-1�PANEL_CURNO_REFR��,(START_ZONE);v5+5W_KEY�INKEYW_KEY_JP=$-2��,#C9�(PC_CUR_COM),���,�!;todo change drive if disk panel�"1"�5��,gOTO_AP��,PANEL_KEYSKEYTAB_ADR=$-2W_KSCAN��,���	��,W_KEY����,�����,�������,W_KSCAN;ZAPUSK��	�RES_INPSET_ACT_ZONE��,(ZONE_VAR)��,�
FIND_ZONE��,(FILER_END);!��,���,ZONE_DELTA;=7��,0START_ZONE=$-2FIND_Z_CKL��,��(PANEL_ZONE),�ZONE_VAR=$-2������,��FIND_Z_CKL
ADR_TO_ML��,ML_RETURN-CWB_JR-1�SET_MRMEM_TO_ADR;LD HL,(ADR);LD (MTA_ADR),HL��,MTA_RETURN-CWB_JR-1SET_MR�(CWB_JR),�
KEY_ENTER��,�+3)��,�+4)��
ENTER_SET�RES_INP;FOR SET_BREAK ???��,(PANEL_Y);FOR FINDENTER_SET2��,���,BUFFER+#BE��,���,���,���,�	;ADD A,0	;UD4=$-1��,�����,�;BC=DE=ADR MEMOR��,�;A=Y OF CURSOR��,�;Zf=0 Cf=0�gOTO_AP;LD HL,AP_BUF��,���,AP_BUF
�($+4),���,(AP_BUF)
;ADD A,L	;LD L,A;LD E,(HL)	;INC L�;LD D,(HL);EXD	�PUT_ADR
PC_TO_CUR�ENTER_SET�(REG_PC),�	AUTO_ENT��,#D�SET_AP��,1	�(-2),��INKEY��,��"1";;RET C�5��;LD HL,AP_BUF
��,(ADR)��,���,AP_BUF
�($+4),��(AP_BUF),�
;ADD A,L	;LD L,A;LD DE,(ADR);LD (HL),E	;INC L�;LD (HL),D�	SET_USER��,(STSPG);HL(STS_BANK)�BANK_PUT;BANK_PUT_0��,USER	�PUT_ADR
MEMORYSET��,1�ENTER_SET2�$+5
ENTER_ADR�ENTER_SET	��,(ADR)��,���	��,�,�,1��,(PANEL_JR)����,$+4;LIST_AD��,9	�INPUT_W��	�ADD_ADRPAGE_UP;       LD A,(PANEL_JR);       AND A;       LD A,-22	;FLP=$-1;       JR Z,$+5;       ADD A,A,A,A,A,A;       LD C,A	��,�-6)ADD_AC��,-1	��,(ADR)ADD_ADR��,�PUT_ADR�(ADR),��
PAGE_DOWN��,(NEXT_ADR)����,�����,��	�PUT_ADR
MEM_TO_PC��,(REG_PC)	�PUT_ADRRETURN_MTA;       LD HL,0;TA_ADR=$-2��,(P_BUF_ADR)�7,�����,�����,����(P_BUF_ADR),��	�PUT_ADR	KEY_LEFT��;A=0 E=FILER_END��,PAGE_UP��,�+5)�KEY_LR
KEY_RIGHT����,PAGE_DOWN��,�+6)KEY_LR
�STIR_CUR�FIND_ZONE�ZONRRRKEY_UP;E=FILER_END��,(CUR_Y)����,���,CUR_NORMSCROLL_DOWN��,-8�ADD_AC��,(PANEL_JR)��;=FILER_END��,UP_ADR��,�,���,4	DIS_SCKL������	��,�,�,��IPRDIS_INS���,(#FFC0)����,�����;?
��,UP_ADR
�DIS_SCKL	�PUT_ADRUP_ADR�(ADR),��(#FFBE),��� ;       LD DE,#D0C1;/#C841 DOWN
;D_11=$-1
;UDP2=$-2��,�-5);SZ YDOWN��,#D6;SUB N�SCROLL;LD HL,(SUD2-1)	��,�-3)���PANEL_LINE��,-1��,-3��,-2-#FFBE;!��ZONRRRCRDOWN�ENTER_SET���(TABL_ADR),�;BC=CUR_ADR��,�;=Y OF CUR�REFR_L_C2�SET_ACT_ZONE	KEY_DOWN��,(CUR_Y);       INC A;       CP 23	;FL4=$-1��-5)��,SCROLL_UP���xxx�11+1+pgreg��11+4+1+pgreg���,���,CUR_NORM��,1PANEL_ZONE=$-1����,SCROLL_UP	CUR_NORM
�STIR_CUR��,��(CUR_Y),�ZONRRR	;LD A,2;LD (WAIT_FAST),A��;ANTI_CALL�0NO_REFR_JP=$-2;
SCROLL_UP��,(#FFC2)	�(ADR),�;       LD DE,#C021;UP;D_12=$-1 ;???
;UDP1=$-2��,�-3);SCROLLZONE Y��,#C6;ADD A,N�SCROLL;LD HL,(SUD3-1)	;DEC H�	��,�-5)��,(BUFFER+#EC)NEXT_ADR=$-2�PANEL_LINE��,0TABL_ADR=$-2ԡ,���ԡ,�	��,#FFC2	��,#FFC0��,1;LD BC,46��ZONRRRSCROLL�(SC_OPR1),��(SC_OPR2),���,�-4);SCROLLZONE X;H=SCROLLZONE Y�AT
��,(POS);LD A,(PANEL_JR)	;AND A�;LD A,#1E;JR NZ,LIST_SC	;LD A,E
;ADD A,6	;LD E,A
;LD A,25;IST_SC LD (SCROLL_LEN),A���,�-1);SCROLLZONE HEIGHT 21
;SFL3=$-1
SCR_CKL_2���,���,�SC_OPR1��,#20��,���,PRODSCR��,�SC_OPR2��,8��,�PRODSCR��,7;8???
SCR_CKL_1��,�;LD BC,#1E;SCROLL_LEN=$-2��,�-2);SCROLLZONE WIDTH��,0���,���,�����,SCR_CKL_1��,#F9;F8???��,����SCR_CKL_2�	STIR_CUR��,0COLOR2=$-1
PANEL_CUR��,1
CUR_Y=$-2
PC_CURSOR;       LD BC,0;UD8_1=$-2;       ADD HL,BC�")))))��,�+1)��,#D8;/58	MD_3=$-1��,���,�+2)ԡ,����$-2�SET_ST_ADR��,#F18��,TR_STOP_A;JP INPUT_W_D
INPUT_W_D��(WORD_ADR),���,�����,���INPUT_W;BC=HL=WORD�(0),�WORD_ADR=$-2�
INPUT_B_D��,���	�INPUT_B��Ԡ,��	ML_TO_SP��,(REG_SP)��
ML_RETURN�(ML_ADR),�	;JR $+6�MLTA_RETMTA_RETURN��,P_BUFFERP_BUF_ADR=$-2
��,(ADR)���(P_BUF_ADR),�	�(ADR),�MLTA_RET��,STACK-2	��,#21C5�(PR),�MTA_R2�(CWB_JR),��CONV_W_BUF	;SOHR HL���$+2CWB_JR=$-1��,BUFFER+5Ԡ,���,�;DE=BUFFER��,1DEC_HEX=$-1���(CURSOR),�	��,DECPW�HEXP��,��PUT_2_HEXDECPW��,4;2byte only��	��,�,�,���,�����,DCPWCKL��,"0"Ԡ,���DCPWCKL;DIV_HL_C ;HL=HL/C��,#110A;DE=DE��;B=0DIV_CKL;A=OSTATOK�����,$+3;DIV_1��,�;DIV_0���,�	�DIV_CKL��,���,���,"0"��,$+4;DEC_NUM��," "��,�PUT_DECԠ,�����,�����,DCPWCKL���CONV_B_BUF;SOHR HL��,���,BUFFER+3��Ԡ,���,�;DE=BUFFER��,(DEC_HEX)���(CURSOR),���,HEXP;DECP��,2��,���,�;=0	�DECPW+2HEXP��,"#"Ԡ,�����,�
PUT_2_HEX������
�pUT_HEX��pUT_HEX�15��,#90���,#40���small�32��	lixlԠ,�����
Ԡ,�;EOL�HDUMPPR;DE=ADDR OF HEX;DUMP BYTES�AT;HL=AT YXHDPCKL��,�����	�PR2INC_DE��," "�PR�HDPCKL%CONV_HDBUF;DE=HD;HL_SOHR;C=MAIN_LEN;B=BYTE_LEN�
��,BUFFER�
CHD_B_CKL����,���PUT_2_HEX;LD (DE),A;=0=EOL����CHD_B_CKL��CHD_1F��,#1F���Ԡ,����lixl;LD (DE),A	;INC E�	;XOR A�;LD (DE),A���
��,CHD_1F�	PRINT_HB;PRINT_A;HL=COORDS��
��,BUFFER�PUT_2_HEX;A=0��,��PRINT���CONV_BUF_B��,BUFFER+2�$+5CONV_BUF_W;BUFFER_TXT TO WORD=BC��,BUFFER+4��,(BUFFER)�"#"��,HEXC_W_B
;DECC_W_B��,0��,1DCCWCKL��,�;INP_DEC�" "��,DCC_IGN�#3A����"0"��
��;STEPEN��	��,�,�,���,0��,zEROMUL_CKL��,�;UMN����,MUL_CKLzERO����,�٢,�;(SP)=WORD;HL=STEP��,�	��,�,�,���,���,�	��,�;*10
��;=WORD
DCC_IGN����,���;=0 IF A=E=FF��,DCCWCKL��,�;Cf=0�	HEXC_W_B�1,���,1��,INP_2_HEX�INP_2_HEX����,�;** (HL)
INP_2_HEX��,BYTEBUF	�INP_HEX��INP_HEX��,����"0"���10
��,C_H_T2�#DF�7�#A���#10
C_H_T2�������,0BYTEBUF=$-1��,��;INPUT VARS;LENGTH DB 0      ;IN TEXT;BUFEND DW 0      ; ...;CURSOR DB 0      ; ...;OUTPOS DW 0      ; ...;C - TXT_LEN;H - Y COORDINATE;L - X COORDINATE;NO INSERT;NEW DELETE...	INPUT_1F��,#1F�(ULINE),�INPUT���(CURSOR),�INPUTC�(OUTPOS),���,'BUFFER��
ԟ,�;=EOL
��,CWB_JRء
��,MTA_R2ACCEPT��,0OUTPOS=$-2
��,BUFFER�PRINTIPRINT=$-2
�PUT_ICUR�INKEY;GETKEY�PUT_ICUR;SOHR_DE��,��"A"�#5F�26��,���,NO_SMALL�#20C_L=$-1	NO_SMALL�downs�#A	��,$+7����(CRD_JR),����#D����,ACCEPT��
��,BUFFERCURSOR=$-2�6��,CAPS_LOCK�8
��,CRLEFT�9��,CRRIGHT	;CP #C�;JR Z,DELETE�" "��,DELETEԡ,�
CRRIGHT����,�����,pUT_POS	CRLEFT��������pUT_POS�(CURSOR),��	DELETE��������ԡ," "
ULINE=$-1	�pUT_POSSWI_RUS��,#80
��,Fruswi�xorHL
CAPS_LOCK��,C_L��,#20�xorHLSWI_DOS��,#38
��,DOS_JR�xorHLSWI_DECHEX��,DEC_HEXXOR_1HL��,1xorHL��ԡ,��
DIS_LABEL��,HHH_IGN+1;PRINT_WLAB+1��,3�xorHL
SET_REDIS��,REFR_OPER	�XOR_1HL��,ReD_TXT	�XOR_1HLSET_IND��,Ind_TXT	�XOR_1HLSET_ST_DOS��,StD_TXT	�XOR_1HL	�trfindSET_ST_FND��,StF_TXT	�XOR_1HL��userSET_ST_USE��,StU_TXT	�XOR_1HL�	�trbankSET_TR_BAN��,STEP_B_JR%;STEP_B_JR=$-1;NO_LD_AHL/ BN_NO_BANK��,BN_NO_BANK-STEP_B_JR-1��ԡ,���,TrB_TXT	�XOR_1HL�SET_TR_CALL;LD A,NO_TR_CALL-STC_JR-1;LD HL,STC_JR
;XOR (HL);LD (HL),A��,TrC_TXT	�XOR_1HLINPUT_REWR;DE=TEXT_ADR��;XY��������,BUFFER��,���,�;TXT_LEN���,������INPUT
��,BUFFER��,������;=BUFFER��PRINT�$+2;PRINT_AT_JR�AT;DE - INCPRN_CKL��,����" "��,$+2PR_SP_JR=$-1��;END_OF_LINE:0���PR	�PRN_CKL	PUT_ICUR��,(CURSOR)��,���,�HD_OPER�;/ADD A,L����,(OUTPOS)��,���,��AT��,MASK_TABL��,(JRT_POS)��,���,���,�����,�	��,(POS)��
X_CUR_CKL��,���ԡ,�����,���ԡ,�������,��7��,X_CUR_CKL�;QUICK PR 6*8,Ver 4;(C) STALKER'96;FNT 6*7(X),LEFT,COMPRESEDAT��;PERED PR, H<=Y 0..23��,�;L<=X 0..41��,�;PORTIT AF��,���;SDVIG NA +2 BITA��,������������,��(JRT_POS),���,��7�����,���,���,��#18��,#C1;#41=SCREEN
AT_MD=$-1��,�	�(POS),����NORM_PR����,���,���,�	�WRRD_OK;�室 �� PR??
��,BUFFERPR_BUF_ADR=$-2ԡ,�����,pR_B_OK��
�disdisk���(DD_NEXTSEC),��pR_B_OK�(PR_BUF_ADR),���eolPREOL��,13�PR�
�romfont�rusNPRROM_��,�;15��,���,���,-15*#300+FNT-#80��,���,#500	�INP_CHB��
YE_WR��,���	�WRRD_OK
PR2INC_DE�PR_INC_DE
PR_INC_DE��,����TAKE_SYM+3PR��;#C5,#21��,0*POS=$-2;�� ᫨誮� ������ �� PR_BUF_ADR�PBA=PR_BUF_ADR-1-POS��"PBA=",-PBA,"(<#80)"PUSH_BUF=PBA*256+#18�
�romfont��,0��,���,��rus��,�;<128���,��rus��,����,���,���,FNT-140;-5*28��,���,#500���,15�rus��,��#9C*2��,$+4	��,"-"*2�#9D*2��,$+4	��,"+"*2��,���,���,����#A0*2��,$+5	��,SETKA��,#700��#1C��,$+4��,"-"�#1D��,$+4��,"+"�ruswiFruswi=$+1�#FF�	�rusend�#F2
��,rusNET�
�rushole�#B3
��,rusHok�#DB
��,rusNET	�#DB-#B3rusHok��#20��,$+4rusNET��,"�"��,���,���,���,NPRROM_��,���,�����,#700��INP_CHB��,���,��rus�7,���,WRRD_OK;IF romfont	��,YE_WR
NO_WR��,���,WRRD_OK��,�;ENDIF�
�romfont	��,YE_WR
NO_WR��,���,WRRD_OK��,���WRRD_OK�LAST_PR�SDV_0JRT_POS=$-1�SDV_0�SDV_1�SDV_2;SDV_3��,0��,�����,�����,���,��#FC��ԡ,�����,��#F�PR_2_BYTESDV_2����,0���������#F��ԡ,�����,��#3F
PR_2_BYTE��ԡ,���
PR_1_BYTE����0,���,NORM_PR��	�INP_CHB������2,���,LAST_PR����,JRT_POS��,���
��,JRT_NEԡ,6�JRT_NE��,�INC_POS��,POS���SDV_0���#FC�SDV1QSDV_1�����#3FSDV1Q��ԡ,��PR_1_BYTE;DISPLAY "'PRINT='HDUMPPR";DISPLAY /T,PRINT,HDUMPPR 