70START H                        n�  �v������                �"STS*",#C6;START MODULE;STALKER'96�#FF00	TEST_RES��,���,(INS_BANK)����,������5,���,TEST_RES
;#20 +#38��,#38
�TEST_RESMD_TABL�AT_MD,MD_D�MD_1,MD_2,MD_3#;DW MD_4,MD_5,MD_6,MD_7,MD_8,MD_9�MD_10,MD_11;MD_12�MD_13,MD_14
�disdisk�ddbuf2+1,locend+1�MD_Tln=$-MD_TABL/2user_=$�START��,RESTORE_VARS�(START_JP),�	�oldres��,(RES_ADR)��,OLD_RES��,RES_LEN����,TEST_RES�RES_SET;BC=0�(INS_BANK),���,#18
�RESIDENT;TEST_RET;HL=0�#D7�(STSPG_0),��(INS_BANK),��#17��,STS_in_Pg7
;SUB #10;JR NZ,$+10;LD (KEY_48K),A;LD A,#CA ;JP Z,...!;LD (MD_RES_COM),A ;48K MODE ON;RES_ADR>#C0;XOR A;LD (MD_8_BANK),A��,#10
�BANK_PUT��,#C4�(MD_SCR_COM),�;LD A,#18;LD (MD_LD_COM),A
��,MD_Tln��,MD_TABL	MDPutCKL��,�����,�����,��#80Ԡ,�
�MDPutCKL	�MD_CONTSTS_in_Pg7��,#40	��,#C000	��,#1B00�MD_CONT	�splash�WINDOW�5,#4F�16,9,"STS ",v1,v2,v3�rus�"ru",W+"s"��"ex",W+"t"��8,11,"Monitor-Debugger�" 48-"�mega�"512","K"+W��"1024","K"+W��9,13,"Alone Coder�" (4912)75139","0"+W�15,12,"STS ",14,2	INS_BANK	�"sts",0��,#B0BMD_CKL	��,#D934	MD_D=$-1	��,�,�,���,���,��#3F
��,MD_CKL;XOR A��,(-2)��#1F��,MD_CKL-3�	��,#79��(jP_OUT_COM),�;128K	��,(QUIT_SP)	�(REG_SP),��CANCEL	�splash	INS_BANK	�"sts",0	MD_D=$-1�MDE��"INITEND=",$ 