71DASM  H                        rj� �v������                �"STS*",#C6
;LD A,"0;LD (DD_NAME+7),A;XOR A;LD (DD_SEC),A
�INCDDNM��,STANDART+2ԡ,5���WINDOW�5,6�14,5,18,8,"Dis","k"+#80	;DB 11,8;DB 20;DD_NAME DB "DisName0 ","C"+W
�23,7,4,1
DD_MEND�0�09,7,17,0;START��ԡ,9DD_REINPUT��,DD_MSTART��,#70F�INPUT_W_D
;PUSH HL�(DD_LSTART),���,DD_MEND��,#71B�INPUT_W_D�(DD_LEND),�	;POP BC��;SBC HL,BC;JR C,DD_REINPUT�(DD_AREA),�;LD HL,#814;LD DE,DD_NAME;LD C,7;CALL INPUT_REWR
�RES_INPddbuf2=$+1��,DD_BUF+#200;#C200ԡ,0;v5.6�(DD_LAB_ADR),�locend=$+1��,LOCEND_BUF
LOCAL_CKL����,DD_AREA��DD_RELOCAL�WINDOW�5,7;DB 14,9,"Local",6,2�16,9,6,2
DD_AREA�0�09,11,17,1DD_LSTART�0�23,11,4,1
DD_LEND�0
DD_MODE_T
;DB 15,12;DB "MODE  "	�18,12�DD_MODE�18," ",0DDLE_R��,DD_LEND��,#B1B�INPUT_W_D;��� �� ����;LD DE,(DD_LSTART);AND A;SBC HL,DE;JR C,DDLE_R;LD HL,(DD_MEND);SBC HL,BC;JR C,DDLE_R��
DD_REMODE��,DD_MODE	�XOR_1HL��,DD_MODE_T�PRINT_T_AT�INKEY��,��#D��,DD_REMODE��,(DD_MODE)���,NO_MAK_LAB;DD_MAK_LAB�����(PR_W_JR),���,(DD_LSTART)��,0DD_LAB_ADR=$-2DD_LAB_CKLԡ,���
��,�,�,��(NEW_PC),�;=0�IPRDIS_INS	��,�,�,���,(NEW_PC)��,�����,NO_RANGE��,(DD_MSTART)���,���,NO_RANGE��,(DD_MEND)����,���,NO_RANGE��	��,�,�,���,(ddbuf2)OLDLAB_TST��,�����,NEW_LABEL����,�����,�����,���,���,���,OLDLAB_TST��
�NO_RANGE
NEW_LABEL	��,�,�,���,�ԡ,2;2 - LABEL NOT DEFINE PR;1 - LABEL DEFINE;0 - EDUP OF TABLE��ԡ,���ԡ,�������,�,�;Cf=0��,���,DD_CANCEL;CANCEL?��,#D12	�TST_PRW��	NO_RANGE��,(DD_LEND)����,���;LD (HL),A��,DD_LAB_CKL�(DD_LAB_ADR),���,PR_W-PR_W_JR-1�(PR_W_JR),���,-1�MAK_LAB_ENDNO_MAK_LAB;BC=DD_LENDREDFBL��,#C1B��,8	�INPUT_B����,REDFBL����;=DD_LEND��MAK_LAB_END��ԡ,���ԡ,���ԡ,����(DD_LSTART),���,���,(DD_MEND)�(DD_LEND),�����,���,���,LOCAL_CKLԡ,�;LOC_END_STACK�(FLEN+1),���,DD_CANCEL�(TR_CANCEL),��TEST_ROOM��,svMODE;#CA;2D73;SAVE�(SL_MODE),���,(#FFE1)�(TRSEC),�;FirstTrSec��,PUSH_BUF�(PR),�
ddbuf=$+1
��,DD_BUF�(PR_BUF_ADR),�	;XOR A�;LD (DD_SEC),A��,(locend)��,0DD_MSTART=$-2DISLOC_CKL��,���
��,DD_END����,�����,��(DD_LNEXT),������(DFB_LEN),���
��,DD_DISDD_DEF_CKL���PRINT_LW;Cf=1-NO_LAB������,SET_1_LAB��,DEFB_TXT�PRINT��,8DFB_LEN=$-1��
DFB_CKL���RES_IO;A<=(DE) INC DE���PRINT_B;Cf=0������,0DD_LNEXT=$-2����,���,DD_DB_END��,�����,",��,PR	�DFB_CKL
DD_DB_END���eol�PREOL���,EOL_TXT�PRINT�����
�TEST_EQU�DD_NEXTSEC����,(DD_LNEXT)����,���,DD_DEF_CKL�DISL_C_ENDDD_DIS;BC=LOC_START���(PR_W_JR),�DD_DIS_CKL��
�PRINT_LW����,SET_1_LAB��,9;LD (DD_R_SYM),A;LD (DD_R_SYM3),A�PR��,(PR_BUF_ADR)�(DIS_PR_ADR),��DIS_INSIDE;BC<=DIS_ADR;HL=>NEXT_ADR����eol�PREOL���,EOL_TXT�PRINT�����
�TEST_EQU�DD_NEXTSEC����,(DD_LNEXT)���,���,DD_DIS_CKLDISL_C_END���DISLOC_CKLTST_PRW�_8020��,PRINT_W�DD_CANCELDD_END	�DD_SAVE
DD_CANCEL	;LD A,32;LD (DD_R_SYM),A;LD (DD_R_SYM3),A��,ENT_TXT;ASM_BUFFER=FF80�(DIS_PR_ADR),���,SL_FILE3�(Write_CALL),�
��,CANCEL�(TR_CANCEL),���,PR_W-PR_W_JR-1�(PR_W_JR),���,'BUFFER�(PR_BUF_ADR+1),�	��,#21C5�(PR),����(PRINT+1),��CANCEL
PUT_TRSEC��,0DD_L_TRSEC=$-2�(TRSEC),��
SET_1_LAB;BC=LABEL_ADR��,(ddbuf2)S1L_CKL��,���������,�����,�����,���,���,���,S1L_CKL��,�,�ԡ,1;DEC(HL)�	TEST_EQU;BC=PC_ADR��,(ddbuf2)TEQ_CKL��,���������,�����,�����,���,���,���,TEQ_CKL����,TEQ_CKL��,�����,�����,���	ԡ,�;=1���PRINT_LW_2;!!!��,EQU_TXT�PRINT��,�	��,�,�,�����,���,�	�PRINT_B�eol�PREOL���,EOL_TXT�PRINT���	�TEQ_CKLDD_NEXTSEC�;NOP��,#C9�(DD_NEXTSEC),�;!!	��,#21C5�	�(PR),�;��� � ����,#D12�AT	�TST_PRW��,PUSH_BUF�(PR),�CCC��,(ddbuf)����,1�LD_SV_SEC�(DD_L_TRSEC),�;=TRSEC
;LD A,D�
;CP 160�;JP NC,DD_CANCEL;CALL RES_INP;!;ddbuf1=$+1��,DD_BUF+#100��;DD_BUF��,#100���,PR_BUF_ADR+1
��;=#C0XX
��,DD_SEC��,95;MAX_FILE_LEN��ء��DD_SAVE�eof��,EOF_TXT�PRINT���,(PR_BUF_ADR)����,DD_NoLSec���(DD_NEXTSEC),��DD_NEXTSEC;LAST_SEC
DD_NoLSec��,DD_NAME��,FNAME_TXT��,8�����,"CԠ,�;EXT_TXT��,(PR_BUF_ADR)��,0DD_SEC=$-1��,�	��	��	��
�(FLEN),���,PUT_TRSEC�(Write_CALL),��Write�SAVE_1_SEC��,(DD_L_TRSEC)�(TRSEC),���,(ddbuf)�(PR_BUF_ADR),�INCDDNM��,DD_NAME+7���5,����(DD_SEC),��EQU_TXT�"=$-",0DEFB_TXT�9,"DB",32,0�eolEOL_TXT�#D,#A,0��eofEOF_TXT�#D,#A,#1A,0� 