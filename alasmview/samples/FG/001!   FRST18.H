FRST18  H                        �?�� �v������                0;BUILD: 00215 OF FIRESTARTER GIFT 18 (16.03.05)#;....FIRESTARTER GIFT 18 MINI GAME�"MACROSES",12
DEBUG=YESSLOWMEM=#6000SLOW_HIGH=#8000FASTMEM=#BE00UPMEM=#C000START=#8000_aDrBlD=#C04D_pAgEdB=#0A
+HEADER�
BUILDNO�GET_SLOWSCR,6912GET_SLOWSPRIT,1280GET_FASTFNT_ADR,1792GET_FASTSM_SPRIT,320GET_UPPERMUSIC,5011GET_FASTFIN_SCR,6912GET_FASTSPR,480GET_FASTIZWTABL,256�SPR+�"F18SPR"	�IZWTABL+�"PRYGTABL"�SCR+�"LOGIC1"	�FIN_SCR+�"fin_cut"�SPRIT+�"LOGICSPR"	�FNT_ADR+�"6X6FONT"
�SM_SPRIT+�"LOGICSM"	�MUSIC,6+�"4game1"	�#D400,6+�"MANUCHAO"�START�INIT
KEYPRES�
BORDER0��,18��	_AGAIN��
_GAMLUP����,#17�RAMP�LEVEL_INIT�MAINLP����,#17�RAMP�TV_OFF��������,_GUDBOY�RESTORE_LEVELFILL#4000,6144,0��,GAMOVER	�MES_PRN	�FADE_IN
KEYPRES�	�FADE_OU�_AGAIN_GUDBOY��,19+19��,(_LWSW1+2)��,��(_LWSW1+2),���,(_LWSW2+2)��,��(_LWSW2+2),���,LEVELNU����	�_GAMLUPFILL#4000,6144,0�FINAL_CUT
LEVELNU�1WIN1�14,15,"�஢���: #"WIN1_1�"00",13GAMOVER�15,15,"�ந�ࠫ...",13X_CRD�0Y_CRD�0	LEV_BUFF�19RESTORE_LEVEL��,19��,LEV_BUFF��,���,���STORE_LEVEL��,19��,���,�
LD_HL_DE��,LEV_BUFF��LEVEL_INIT��,0�(CURCOORDS),���,18�(MOVES),�FILL#5800,768,0FILL#4000,6144,0��,(LEVELNU)
��,WIN1_1	�PRN_HEX��,WIN1	�MES_PRN	�FADE_IN
KEYPRES�	�FADE_OUCOPYSCR,#C000,6912_LWSW1��,LEVEL_LWSW2��,LEVEL+19�STORE_LEVEL�PRINT_BIG�PRINT_SMALL�TV_ON�MAINLP��,%00101000�CURSOR_PRINT��,(BANKM)�%00000010�RAMP��,%00101000�CURSOR_PRINT��,(BANKM)�%00000010�RAMP�KEYZ��,%00100000�CURSOR_PRINT��,(BANKM)�%00000010�RAMP��,%00100000�CURSOR_PRINT��,(BANKM)�%00000010�RAMP���,(BANKM)�%00001010�RAMP�CHECK_SCORE��,19������,(MOVES)��,�������;       LD A,#7F;       IN A,(254);       RRA;       RET NC�MAINLPTEMP�0TEMP1�0	MOVES�18PRN_HEX��,�
;A-NUMBER��#F0	;HL-PLACE�����_PUT��,��#F�_PUT�_PUT�#A	��,_PTNM��,7_PTNM��,48ԡ,����KEYZ��,(TEMP1)��,���,#F7	��,(254)�(TEMP1),�����,_KZ�4,���,ANTICLOCKWISE_KZ��,(TEMP)��,���,#EF	��,(254)
�(TEMP),������0,���,CLOCKWISE�1,�
��,CUR_UP�2,���,CUR_DOWN�3,���,CUR_RIGHT�4,���,CUR_LEFT�TV_OFF��,#5820
��,#5ADF��,11�	LOPP1����,32�LOPP����,127
��,#0020��,����,0��,������,���,127��,����,0��,������,����LOPP����LOPP1
��,#595F��,32�	LOPP2����,0�LOPP2��,16�
��,#5980
��,#599F��LOPP3��,�����,�����LOPP3��,8��,63�
��,#598FLOPP4��,��9�5���LOPP4�TV_ON��,22528��,0��������,767�_FROM��,#C000
��,16384	��,6144���,8��
��,#598FLOOP4��,���,9��5���LOOP4��,16�
��,#598F
��,#5990��,127LOOP3��,�����,�����LOOP3
��,#595F
��,#59A0��,11�	LOOP1����,32�LOOP����,127
��,#0020��,���PUT��,������,���,127
��,#0020��,���PUT��,������,����LOOP����LOOP1_FROM1��,#C000+6144
��,#5800��,768��PUT����_FROM2��,#C000-16384��,����,�������,��CUR_UP��,(CURCOORDS)��������,2��	��,_CUJP��_CUJP���(CURCOORDS),��	CUR_DOWN��,(CURCOORDS)��,2������	��,_CDJP��_CDJP���(CURCOORDS),��	CUR_LEFT��,(CURCOORDS)���������(CURCOORDS),��
CUR_RIGHT��,(CURCOORDS)��,2������;LD A,1��	��,_CRJP����_CRJP���(CURCOORDS),��ANTICLOCKWISE��,(MOVES)���(MOVES),���,%00100000�CURSOR_PRINT��,(BANKM)�%00000010�RAMP��,%00100000�CURSOR_PRINT��,(BANKM)�%00000010�RAMP��,ANTICLOCK_TABLE�(_ACSW+1),���,(CURCOORDS)_ACSW��,(ANTICLOCK_TABLE)��,���
��,_NEXT1��,���
��,_NEXT1��,(_ACSW+1)������,�����,���.�(_ACWSW1+1),�;������ ���� ������⮩ ⠡���,�����,���1�(_ACWSW2+1),�;������ ���� ��楤��� ��������,�����,���.�(_ACWSW3+1),�;������ ���� ��ଠ�쭮� ⠡��(_ACWSW4+1),��(_ACWSW7+1),��(_ACWSW9+1),��(_ACWSW0+1),���,�����,���)�(_ACWSW5+1),�;������ ���� ��� �����(_ACWSW6+1),��(_ACWSW8+1),��PRINT_ACW_NEXT1��,(_ACSW+1)�10����(_ACSW+1),��_ACSW
PRINT_ACW_ACWSW3��,0��,0�PRINT_CLEAR_STAR_ACWSW5��,0�SCR_TO_BUFF
_ACWSW2�0_ACWSW1��,0��,1�PRINT_CLEAR_STAR���,(BANKM)�%00001010�RAMP_ACWSW6��,0�BUFF_TO_SCR_ACWSW7��,0��,0�PRINT_CLEAR_STAR_ACWSW4��,0��,1�PRINT_CLEAR_STAR��,(BANKM)�%00001010�RAMP_ACWSW8��,0�BUFF_TO_SCR_ACWSW9��,0��,0�PRINT_CLEAR_STAR_ACWSW0��,0��,1�PRINT_CLEAR_STAR��,(BANKM)�%00001010�RAMP�
CLOCKWISE��,(MOVES)���(MOVES),���,%00100000�CURSOR_PRINT��,(BANKM)�%00000010�RAMP��,%00100000�CURSOR_PRINT��,(BANKM)�%00000010�RAMP��,CLOCK_TABLE�(_CSW+1),���,(CURCOORDS)_CSW��,(CLOCK_TABLE)��,�����,_NEXT11��,�����,_NEXT11��,(_CSW+1)������,�����,���-�(_CWSW1+1),�;������ ���� ������⮩ ⠡���,�����,���0�(_CWSW2+1),�;������ ���� ��楤��� ��������,�����,���-�(_CWSW3+1),�;������ ���� ��ଠ�쭮� ⠡��(_CWSW4+1),��(_CWSW7+1),��(_CWSW9+1),��(_CWSW0+1),���,�����,���(�(_CWSW5+1),�;������ ���� ��� �����(_CWSW6+1),��(_CWSW8+1),�
�PRINT_CW_NEXT11��,(_CSW+1)�10����(_CSW+1),��_CSW	PRINT_CW_CWSW3��,0��,0�PRINT_CLEAR_STAR_CWSW5��,0�SCR_TO_BUFF_CWSW1��,0��,1�PRINT_CLEAR_STAR���,(BANKM)�%00001010�RAMP	_CWSW2�0_CWSW6��,0�BUFF_TO_SCR_CWSW7��,0��,0�PRINT_CLEAR_STAR_CWSW4��,0��,1�PRINT_CLEAR_STAR��,(BANKM)�%00001010�RAMP_CWSW8��,0�BUFF_TO_SCR_CWSW9��,0��,0�PRINT_CLEAR_STAR_CWSW0��,0��,1�PRINT_CLEAR_STAR��,(BANKM)�%00001010�RAMP�SCR_TO_BUFF	;����� ������ � HLADR��,BUFF;����� ������� � DE��,64	;PO YMK2�����12����������,��7��,VV2��,���,#20��,���,VV2��,��8��,�VV2�MK2�BUFF_TO_SCR	;DE=ADRESS APRAJTA��,BUFF;HL=ADRESS EKRANA��,64	;PO YMK1�����12����������,��7��,VV1��,���,#20��,���,VV1��,��8��,�VV1�MK1�CURSOR_PRINT�GET_CUR_ADDR��,4;IN A=COLORLP2��,4LP1ԡ,����LP1��,32-4��,������LP2GET_CUR_ADDR��,���,CURSOR_TABLE�(_GTSW+1),���,(CURCOORDS)_GTSW��,(CURSOR_TABLE)��,�����,_NEXTAD��,�����,_NEXTAD��,(_GTSW+1)������,�����,�
LD_HL_DE��,��_NEXTAD��,(_GTSW+1)���������(_GTSW+1),��_GTSWCHECK_SCORE��,19����,�_CHJP�(_CHSW1+2),��(_CHSW2+2),���,�_CHSW1��,�+0)��,�_CHSW2��,�+0)��
��,_NXTCH��	_NXTCH������,����_CHJP
PRINT_BIG���(_SWPR+2),���,BIG_TABLE��,19_PRBLP��,�����,����PRINT_BIG_CELL��,(_SWPR+2)���(_SWPR+2),��_PRBLP�PRINT_SMALL���(_SWPR1+2),���,SMALL_TABLE��,19
_PSLP��,�����,����PRINT_SMALL_CELL��,(_SWPR1+2)���(_SWPR1+2),��_PSLP�PRINT_SMALL_CELL��������,0_SWPR1��,�+0)�48��,���
��,MULT32��,SM_SPRIT��,����SM_SPROUT�����MULT32��,5_LPPR2��,��_LPPR2�PRINT_CLEAR_STAR��,6*_PCSLP��,�	;HL - ⠡��� ���ᮢ � �������(_SWPR+2),�;C - 0-CLEAR��;    1-PRINT��,�����,�����,���
��,_PCSJP�CLEAR_BIG_CELL
�_PCSJP+3_PCSJP�PRINT_BIG_CELL�_PCSLP�PRINT_BIG_CELL��������,0_SWPR��,�+0)�48��,�����,MULT128	��,SPRIT��,����SPROUT�����CLEAR_BIG_CELL����	�SPROUT1�����MULT128��,7_LPPR1��,��_LPPR1�SPROUT	;HL=ADRESS APRAJTA	;DE=ADRESS EKRANA��,32	;PO YMK����	�4;PO X��,���,����������������,���,�����Ԡ,��������������,��7��,VV��,���,#20��,���,VV��,��8��,�VV�MK�SPROUT1	;HL=ADRESS APRAJTA	;DE=ADRESS EKRANA��,32	;PO YMK3������	�4;PO XԠ,������������,��7��,VV3��,���,#20��,���,VV3��,��8��,�VV3�MK3�
SM_SPROUT	;HL=ADRESS APRAJTA	;DE=ADRESS EKRANA��,16	;PO YMK9��������������,��7��,VV9��,���,#20��,���,VV9��,��8��,�VV9�MK9�CW_9	��,�+4)	��,�+5)
��,�+10)
��,�+14)
��,�+13)	��,�+8)	��+5),�
��+10),�
��+14),�
��+13),�	��+8),�	��+4),��CW_4	��,�+0)	��,�+1)	��,�+5)	��,�+9)	��,�+8)	��,�+3)	��+1),�	��+5),�	��+9),�	��+8),�	��+3),�	��+0),��CW_5	��,�+1)	��,�+2)	��,�+6)
��,�+10)	��,�+9)	��,�+4)	��+2),�	��+6),�
��+10),�	��+9),�	��+4),�	��+1),��CW_8	��,�+3)	��,�+4)	��,�+9)
��,�+13)
��,�+12)	��,�+7)	��+4),�	��+9),�
��+13),�
��+12),�	��+7),�	��+3),��CW_10	��,�+5)	��,�+6)
��,�+11)
��,�+15)
��,�+14)	��,�+9)	��+6),�
��+11),�
��+15),�
��+14),�	��+9),�	��+5),��CW_13	��,�+8)	��,�+9)
��,�+14)
��,�+17)
��,�+16)
��,�+12)	��+9),�
��+14),�
��+17),�
��+16),�
��+12),�	��+8),��CW_14	��,�+9)
��,�+10)
��,�+15)
��,�+18)
��,�+17)
��,�+13)
��+10),�
��+15),�
��+18),�
��+17),�
��+13),�	��+9),��ACW_9	��,�+4)	��,�+5)
��,�+10)
��,�+14)
��,�+13)	��,�+8)	��+8),�	��+4),�	��+5),�
��+10),�
��+14),�
��+13),��ACW_4	��,�+0)	��,�+1)	��,�+5)	��,�+9)	��,�+8)	��,�+3)	��+3),�	��+0),�	��+1),�	��+5),�	��+9),�	��+8),��ACW_5	��,�+1)	��,�+2)	��,�+6)
��,�+10)	��,�+9)	��,�+4)	��+4),�	��+1),�	��+2),�	��+6),�
��+10),�	��+9),��ACW_8	��,�+3)	��,�+4)	��,�+9)
��,�+13)
��,�+12)	��,�+7)	��+7),�	��+3),�	��+4),�	��+9),�
��+13),�
��+12),��ACW_10	��,�+5)	��,�+6)
��,�+11)
��,�+15)
��,�+14)	��,�+9)	��+9),�	��+5),�	��+6),�
��+11),�
��+15),�
��+14),��ACW_13	��,�+8)	��,�+9)
��,�+14)
��,�+17)
��,�+16)
��,�+12)
��+12),�	��+8),�	��+9),�
��+14),�
��+17),�
��+16),��ACW_14	��,�+9)
��,�+10)
��,�+15)
��,�+18)
��,�+17)
��,�+13)
��+13),�	��+9),�
��+10),�
��+15),�
��+18),�
��+17),��MES_PRN��,(X_CRD);MESSAGE PRINT��	;IN:    DE-TEXT ADDRES��,��(X_CRD),�����,��(Y_CRD),�_LOOP����,��13	��,_PRNT�32��,_JPR��,32_JPR��	�SYM_PRN���_LOOP_PRNT���(X_CRD),��SYM_PRN�����,���,0��,���,���,���,FNT_ADR-256��,�����
�(_SW2),�CHECK��,(X_CRD)��,���,���,���,���,���,���,���,���,���,���,���,���,���,-1��,8CHPL1����
��,CHPL1��,���,���,����(SL1+1),��(SL2+1),�;       LD (SL3+1),AADDRZ��,��������#40���#F8����,���,��%00111000������,�_SW2�����
�(_SW1),���,6
SCRL��,�����,%11111100��,�SL1��,0�8	��,_NZER��,��_ZERO
_NZER��,���,45
�(_SW1),���,�SCRL1�����SCRL1��SL2��,0SCRL2�ݡ�SCRL2��
_ZERO��,���,255����,���,�����ԡ,�_SW1������,��7	��,LAMER��,��#E0��,�	��,LAMER��,��8��,�LAMER��������,SCRL�����,(X_CRD)�41	��,_NEXT��_NEXT�(X_CRD),��
FADE_IN��_FADIN��	�(254),�	��,#5800	��,#5801��,767��������ԡ,�������8
��,_FADIN�FADE_OU��,7	_FADIN1��	�(254),�	��,#5800	��,#5801��,767��������ԡ,�������255��,_FADIN1�INIT��,6	�RAMPAGE�MUSIC��,#17�RAMP	��,#BE00��,���,���	_IM2ԡ,�����,_IM2��ԡ,��2�!COPYSTR_IM,#BFBF,END_IM-STR_IM�RAMPAGE��,���,(BANKM)�%11111000��RAMP��,#7FFD�(BANKM),���,��BANKM�#10;#5B5CSTR_IM�#BFBF���,�,�,�,�,����,�	��,�,�,���,(BANKM)�(_IMSW+1),���,6	�RAMPAGE�#C005_IMSW��,0000	�RAMPAGE	��,�,�,����,���,�,�,�,�,����	END_IM=$
FINAL_CUT�"F18_FNLC",11CODE_END=$
BIG_TABLEDEFW_SCRADRH5,2*8DEFW_SCRADRH9,2*8DEFW_SCRADRH13,2*8DEFW_SCRADRH3,6*8DEFW_SCRADRH7,6*8DEFW_SCRADRH11,6*8DEFW_SCRADRH15,6*8DEFW_SCRADRH1,10*8DEFW_SCRADRH5,10*8DEFW_SCRADRH9,10*8DEFW_SCRADRH13,10*8DEFW_SCRADRH17,10*8DEFW_SCRADRH3,14*8DEFW_SCRADRH7,14*8DEFW_SCRADRH11,14*8DEFW_SCRADRH15,14*8DEFW_SCRADRH5,18*8DEFW_SCRADRH9,18*8DEFW_SCRADRH13,18*8SMALL_TABLEDEFW_SCRADRH24,0*8DEFW_SCRADRH26,0*8DEFW_SCRADRH28,0*8DEFW_SCRADRH23,2*8DEFW_SCRADRH25,2*8DEFW_SCRADRH27,2*8DEFW_SCRADRH29,2*8DEFW_SCRADRH22,4*8DEFW_SCRADRH24,4*8DEFW_SCRADRH26,4*8DEFW_SCRADRH28,4*8DEFW_SCRADRH30,4*8DEFW_SCRADRH23,6*8DEFW_SCRADRH25,6*8DEFW_SCRADRH27,6*8DEFW_SCRADRH29,6*8DEFW_SCRADRH24,8*8DEFW_SCRADRH26,8*8DEFW_SCRADRH28,8*8	S4_TABLE�0DEFW_SCRADRH5,2*8�1DEFW_SCRADRH9,2*8�3DEFW_SCRADRH3,6*8�5DEFW_SCRADRH11,6*8�8DEFW_SCRADRH5,10*8�9DEFW_SCRADRH9,10*8	D4_TABLE�0DEFW_SCRADRH7,2*8�3DEFW_SCRADRH3,4*8�1DEFW_SCRADRH11,4*8�8DEFW_SCRADRH3,8*8�5DEFW_SCRADRH11,8*8�9DEFW_SCRADRH7,10*8	S5_TABLE�1DEFW_SCRADRH9,2*8�2DEFW_SCRADRH13,2*8�4DEFW_SCRADRH7,6*8�6DEFW_SCRADRH15,6*8�9DEFW_SCRADRH9,10*8�10DEFW_SCRADRH13,10*8	D5_TABLE�1DEFW_SCRADRH11,2*8�4DEFW_SCRADRH7,4*8�2DEFW_SCRADRH15,4*8�9DEFW_SCRADRH7,8*8�6DEFW_SCRADRH15,8*8�10DEFW_SCRADRH11,10*8	S8_TABLE�3DEFW_SCRADRH3,6*8�4DEFW_SCRADRH7,6*8�7DEFW_SCRADRH1,10*8�9DEFW_SCRADRH9,10*8�12DEFW_SCRADRH3,14*8�13DEFW_SCRADRH7,14*8	D8_TABLE�3DEFW_SCRADRH5,6*8�7DEFW_SCRADRH1,8*8�4DEFW_SCRADRH9,8*8�12DEFW_SCRADRH1,12*8�9DEFW_SCRADRH9,12*8�13DEFW_SCRADRH5,14*8	S9_TABLE�4DEFW_SCRADRH7,6*8�5DEFW_SCRADRH11,6*8�8DEFW_SCRADRH5,10*8�10DEFW_SCRADRH13,10*8�13DEFW_SCRADRH7,14*8�14DEFW_SCRADRH11,14*8	D9_TABLE�4DEFW_SCRADRH9,6*8�8DEFW_SCRADRH5,8*8�5DEFW_SCRADRH13,8*8�13DEFW_SCRADRH5,12*8�10DEFW_SCRADRH13,12*8�14DEFW_SCRADRH9,14*8
S10_TABLE�5DEFW_SCRADRH11,6*8�6DEFW_SCRADRH15,6*8�9DEFW_SCRADRH9,10*8�11DEFW_SCRADRH17,10*8�14DEFW_SCRADRH11,14*8�15DEFW_SCRADRH15,14*8
D10_TABLE�5DEFW_SCRADRH13,6*8�9DEFW_SCRADRH9,8*8�6DEFW_SCRADRH17,8*8�14DEFW_SCRADRH9,12*8�11DEFW_SCRADRH17,12*8�15DEFW_SCRADRH13,14*8
S13_TABLE�8DEFW_SCRADRH5,10*8�9DEFW_SCRADRH9,10*8�12DEFW_SCRADRH3,14*8�14DEFW_SCRADRH11,14*8�16DEFW_SCRADRH5,18*8�17DEFW_SCRADRH9,18*8
D13_TABLE�8DEFW_SCRADRH7,10*8�12DEFW_SCRADRH3,12*8�9DEFW_SCRADRH11,12*8�16DEFW_SCRADRH3,16*8�14DEFW_SCRADRH11,16*8�17DEFW_SCRADRH7,18*8
S14_TABLE�9DEFW_SCRADRH9,10*8�10DEFW_SCRADRH13,10*8�13DEFW_SCRADRH7,14*8�15DEFW_SCRADRH15,14*8�17DEFW_SCRADRH9,18*8�18DEFW_SCRADRH13,18*8
D14_TABLE�9DEFW_SCRADRH11,10*8�13DEFW_SCRADRH7,12*8�10DEFW_SCRADRH15,12*8�17DEFW_SCRADRH7,16*8�15DEFW_SCRADRH15,16*8�18DEFW_SCRADRH11,18*8CURSOR_TABLE�0,0DEFW_ATTRADRH7,6�1,0DEFW_ATTRADRH11,6�0,1DEFW_ATTRADRH5,10�1,1DEFW_ATTRADRH9,10�2,1DEFW_ATTRADRH13,10�0,2DEFW_ATTRADRH7,14�1,2DEFW_ATTRADRH11,14ANTICLOCK_TABLE�0,0
�D4_TABLE�ACW_4
�S4_TABLEDEFW_SCRADRH3,4*8�1,0
�D5_TABLE�ACW_5
�S5_TABLEDEFW_SCRADRH7,4*8�0,1
�D8_TABLE�ACW_8
�S8_TABLEDEFW_SCRADRH1,8*8�1,1
�D9_TABLE�ACW_9
�S9_TABLEDEFW_SCRADRH5,8*8�2,1�D10_TABLE�ACW_10�S10_TABLEDEFW_SCRADRH9,8*8�0,2�D13_TABLE�ACW_13�S13_TABLEDEFW_SCRADRH3,12*8�1,2�D14_TABLE�ACW_14�S14_TABLEDEFW_SCRADRH7,12*8CLOCK_TABLE�0,0
�D4_TABLE�CW_4
�S4_TABLEDEFW_SCRADRH3,4*8�1,0
�D5_TABLE�CW_5
�S5_TABLEDEFW_SCRADRH7,4*8�0,1
�D8_TABLE�CW_8
�S8_TABLEDEFW_SCRADRH1,8*8�1,1
�D9_TABLE�CW_9
�S9_TABLEDEFW_SCRADRH5,8*8�2,1�D10_TABLE�CW_10�S10_TABLEDEFW_SCRADRH9,8*8�0,2�D13_TABLE�CW_13�S13_TABLEDEFW_SCRADRH3,12*8�1,2�D14_TABLE�CW_14�S14_TABLEDEFW_SCRADRH7,12*8
CURCOORDS�0BUFF�768LEVEL�"000"�"0010"	�"00000"�"0000"�"000"�"000"�"0000"	�"00100"�"0000"�"000";2�"111"�"1111"	�"11111"�"1313"�"111"�"111"�"1111"	�"13131"�"1111"�"111";3�"252"�"2222"	�"22225"�"5222"�"222"�"222"�"2222"	�"52525"�"2222"�"222";4�"444"�"4314"	�"44444"�"4144"�"444"�"444"�"4114"	�"44344"�"4444"�"444";5�"226"�"2222"	�"26222"�"2222"�"226"�"262"�"2222"	�"22622"�"2222"�"262";6�"666"�"6666"	�"64666"�"4666"�"646"�"666"�"6666"	�"64446"�"6666"�"666";7�"656"�"6556"	�"55555"�"5555"�"555"�"555"�"5665"	�"56565"�"5555"�"555";8�"042"�"4444"	�"44444"�"4434"�"444"�"444"�"4444"	�"42034"�"4444"�"444";9�"655"�"7555"	�"55566"�"5555"�"555"�"555"�"6556"	�"55755"�"5555"�"565";10�"383"�"3933"	�"33333"�"3337"�"633"�"383"�"3333"	�"33733"�"9336"�"333";11�"202"�"2022"	�"22202"�"2220"�"022"�"202"�"2222"	�"02020"�"2222"�"202";12�"553"�"5535"	�"35555"�"5535"�"553"�"555"�"3553"	�"55355"�"3553"�"555";13�"866"�"6668"	�"66666"�"7668"�"668"�"686"�"6666"	�"86768"�"6666"�"686";14�"444"�"6446"	�"46664"�"6446"�"444"�"444"�"4664"	�"46664"�"4664"�"444";15�"611"�"6666"	�"61661"�"6666"�"611"�"616"�"1661"	�"66666"�"1661"�"616";16�"000"�"0202"	�"00020"�"0222"�"000"�"000"�"0220"	�"02020"�"0220"�"000";17�"979"�"9979"	�"97997"�"9999"�"799"�"999"�"9999"	�"77777"�"9999"�"999";18�"899"�"9998"	�"89898"�"9989"�"988"�"898"�"8998"	�"99999"�"8998"�"898"DATA_END=$PROG_END=$
MEM_INFO�"PRIKOL",13�START 