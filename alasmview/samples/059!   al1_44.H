al1_44  H                        �=� �v������                �"Al5*",#C6mainerr�pr_astr�mprent�" Bad MAIN",0�a_spmain������,�����,nxtstr1*�6,�+#34);��� 1 ����� 㦥 ᪮�������?��,mainerr���,(#5D19);drv��	�incnmpg;LD A,(IX+#24);CALL ONPAGE	��,#C03F�incl1include���,(#5D19);drv��	�incnmpg�pr_astr;# ⥪ ��� ���
��,�+#24)�ONinc;��� pg=label��,(curstr)incl1����,T_NAME+9incl2����,�����	��,incl2
��,�+#24)	��,#D4����incl3
��,�+#0A);LD (IX+#24),A�ONinc��,�+#2D)��+#24),�	�pr_astr;1asmi1��,#C040�(curstr),����(#C030),�ס�asmitillasp�illegalilla_sp�a_spincl3
��,�+#0A)�ONinc	�vertxt;???	��,incl4;NZ=error
��,#C000
�cpfnmhl��;㦥 ����㦥�
��,param��
�frmfnme	�svchngs��
��,fname
�bc9ldir�6,�+#2E);???interrupted?
��,wdskopincl4�6,�+#2E)�openfl�6,�+#2E);��諨 䠩�?��wdskop�mprent�" Wrong disk operation.",0	�illa_sp	;1:asmitdeincld��,�	�#D4	��,illasp
��+#0A),�
��+#24),�	��,param	��,fnamedin1������,�ԡ,�ԟ,�������,�	�fname+9��,din1���(curstr),����,#5D19�����;(IX+#17)��,cngdrv�incl3	�nxtstr1;1+wrtputtxt����,�	;AND A�����;ᤢ���� DB�����"""	;RET Z�	��,pu34pun34�putbyte�puttxt	pu34�����,��"""
��,pun34���defb
�5,�+#26)dbnxt�nxtsymdbZer0��,error0�"""	��,dbnum��,�������
��,dbZer0��ء��	��,$+6����1��,�����,�&��,dbnum;"a" ��� """,0 � ��� "O"+#80�puttxt����,nxtstr1�nxtsym��,nxtstr1�db1dbnum���val
��,error0��,�	�putbyte��,�db1�",	��,dbnxtfnEnxt�fnEstr1	�nxtstr1defd�5,�+#26)ddnxt�nxtsym
��,dbZer0�"#��,$+3��
dblng��,0	dblng1���vh12
��,dblng2������,����vh12
��,error0����	�putbyte����,1�dblng1	dblng2��
��,error0��,��",	��,ddnxt�fnEnxtldrnnme��,#C041	��,#C03E��,#3Fԡ,���ԡ,1��ԡ,����,�
��,noname	�bc9ldir��,#21��,15��
yesno�mpr�" (Y/N)?",0
yn1�inkey�#DF�"Y���"N���5���yn1work	�copynme��,illegal�extH	�svchngs
�6,�+#2E)���ldcat��w_param��,(0)��	��,work6���clrscr��,#80��work1��,���	��,work2��	��,work3�3,���,��3,�;LD A,(IY+8)�"H	��,work2�crdD	��,work3��
;PUSH IY����	�pr8syms����	;POP IYwork2��,16��,���	��,work1
work3��,�����,NoAlFil	��,prstr	�SelName����,8��,(catadr)�work5
work4��,�
work5��,���,���	��,work4��,��"H	��,work4��	��,work4��,ALSTR-3�(y),���,fext��,9�work6�prevpgopenfl�sfmsg;���� 䠩���;caterr��;JR Z,ldtx1 ;found;CALL mprent;DB " New file.",0;CALL ldrnnme;CALL frmfnmeDE	;JR of1	ldtx1�65
��,wrongf��,���,5	��,#C000�TRDOS���vertxt
��,wrongf	��;�� ��襭 � 䠩��!!ldtx2�(T_OPT),�;only for merge�mprent�" Loaded Ok to ",0�pgnam�jumbitof1�6,�+#2E)�
frmfnmeDE
��,T_NAMEfrmfnme��,fnamebc9ldir��,9��wrongf
�parprent�" Wrong file",0�$;��ॢ���� ����� ����� � ���न����;5crdD��,�;1crdA����,-11
ccrd1��,���,���,11	�ALSYM-1
��,ccrdQ��,���,��ALLST	��,ccrd1�(y),�	ccrdQ���SelName��SN2��,�	SN1��,��crdA�BigCury;s�inkey����,��crdA
�BigCury���5;break���;JR Z,BigCurs�#14;ss/sp, ss/ent��;JR Z,BigCurs
�8;left�	��,SNlft
��;right	��,SNrgt
��;enter��,SNenter��;up��,SNup
��;down���,SN1
SNdwn��,�������,SN1SNd1;CALL BigCurs�SN2SNlft;CALL BigCurs	;LD A,H	;AND A�;JR Z,SelName��,��ALLST��,SelName�SN2SNrgt;CALL BigCurs��,�	��,ALLST����,SN2��,����SN2	SNup��,��1��,0�SN2	;AND A�;JP Z,SN1	;DEC A�
;JR SNd1	;BigCurs�(y),�BigCuryBigCurln=$+1��,8�CurLat��+1)����,$-7�SNenter;CALL BigCurs��;NZ?�copynme	��,param�getdrv��	��,cnam1	��,�;drv	���cnam2������,��cngdrv;1+1cnam1��,paramcnam2�(w_param+1),�	��,fname��,8	�cnvname����,��;for incb��cnvname��,"?cn1��,�����,cn4���".��,cn4��,"?�"*��,cn2Ԡ,�����,32�cn1cn2��,�����,cn3�".���;*a=error��cn3��,�����cn4��,�Ԡ,����$-2�intrup1�6,�+#2E)intrupt��,break�prentdefs	�calcule
��,error0��
��,stringds1��,��",��,ds2��	�calcule��
��,jpcer0��,�ԟ,����ds1ds2�fnEstr1��,�����,$+4ԟ,���
;LD LY,C��,��(dsLY),���ds3��,string��,�����,nxtstr1��ds4��,��putbyte;����� HL����,�	dsLY=$+1�0	;CP LY���,ds4�����ds3defw�5,�+#26)
�4,�+#26)dw1�valjpcer0��,error0��,���	�putbyte����,�	�putbyte��,��",��,dw1�fnEnxtcursor
�0,�+#3A)
��,CurLat�CurRusincpxy��+1)
�?alasm48�6,�+1)�����,�+1)�ALSYM���/entclr��,�;���室�� �� ᫥� ��� � ������� ��,�ALSTR-3;#15 ;�᫨ ����, �஫����� ��࠭��,ec1�scrup0��ec1����+1),0	�clrlineclrscr	��,#4001	��,#1800��,���,�ԡ,����,767
��,�+#3E)ԡ,��
��,ALLINE�drwlin�(y),��mpr���prstrjphl֡	parprent���(param+9),�
��,param	�prent�	mprent���prent֡prent�entclr;n=#D Enter;n<#D Tab n	;n=#E at$;n=#F ����⠥� ��᫮ �� ����� +2+1prstr��,��������#D	��,prtab	��,prent�#E��,prat�#F	��,prnum�prsymi�prstrprtab��,��mprsym�32�$-4�prstrprnum��+1)��,�����,���,����prnumA���pra1prat��,���+1),�����,�ԣ,�pra1���prstrim��,#ED	�putbyte	�oneprm1��,���
��,error0��,��#03
��,error0��,#46����,im1��,#56����,im1��,#5Eim1��,�	�putbyte	�nxtstr1rst�oneprm1��,���rster0��,error0��,��#38��
��,rster0�#C7	�putbyte
�nxtParam	KEYDRBEG;���������inkey0������
ik0�kscan��,ik2;no key��,���+#06)��,ik3;��㣠� ���������+#08)0��,ik0;1       ;����প� ��। ��⮯���஬����)��+#08),#01;᪮���� ����ண� �/�����
��,�+#07)�ik5;POP3)ik2�kscan;������ 横� �������� ���������,ik2ik3��+#06),���,15;(IX+#1E) ;kbd wait
��+#08),���,skey
�1,�+#05)��,$+5	��,SSkey��,���,�
�2,�+#05)��,ik4;no cs�#20��,ik4�#30��,5��,ik4;break��,��#20�#40��,ik4��,���,ksdigs-"0"��,���,�ik4��+#07),�ik5�������=;᪠����� ������, �� ��室�: L-䫠��, E-scancode, NZ - key�	;2+3lamekscan;HALT���
��,23672ء	��,$-1���,�ԡ,�
;PUSH BC��,%11000001��,-2ks2��,���,(-2)��,5ks3���,���,ks7��,���;CS?��,ks4�2,�;CS - L.2�ks6ks4�#24;SS?��,ks5�1,�;SS - L.1�2,�;ext? (D=#24)��,ks6ks5�0,���,ksex�0,�;key pressed��,�;E=scanks6��,�ks7���ks3����,ks2	�QUOkbd�0,�	;--- BY EVG��,QKBD;--- BY EVG���,���1��,0ksex��+#05),�	;POP BC�;single keyskey�#F,"ZXCV�"ASDFG�"QWERT�"12345�"09876�"POIUY
�#A,"LKJH�" ",#F,"MNB;SS+keySSkey�#0F,":`?/";CsZXCV�"~|\{}"
; ASDFG�#01,#0D,#04,"<>"; QWERT�"!@#$%"
; 12345�"_)('&"
; 09876�#22,";",#10,"]["; POIUY�#14,"=+-^";EnLKJH�#14,#0F,".,*";SpsMNBksdigs�#6;Cs+0 backspace�#7;1    tab�#11;2    insert space�#2;3    page up�#3;4    page down�#8;5    left�#C;6    down�#B;7    up�#9;8    right�#E;9    delete;fastkey DB 2,3,#B,#C�"KEYDRV SIZE=",$-KEYDRBEG;��ப� �����;HL-⮪���input��,ALSTR-2;#16�(y),�	�clrline�prnxtx�(inp7+1),�
��,cmd_bf
�2,�+#37)��,">inp2�prnxtxinp3��,��;LD (inpSYM),A��Ԡ,�inp1�CurLatcompatch=$+1�inkey���CurLat���#14;alter���,inp4��,�	�.cmd_bf��,inp1;��ப� �� �������,#14�inp11inp4�#A;enter���,inp5	�1,�+#37)	��,inp10	�2,�+#37)	��,inp10��,�+1)�#29��,inp1�2	��,inp10;SET 2,(IX+#37)��,#F6;"�";LD (DE),A	;INC DE
;JR inp2inp5�5;break��	��,inp10�#F;cs/ss���,inp6��,�	�.cmd_bf��,inp1;��ப� �� ������inp10inp6�6;cs/0��,inp9�9��,inpNRGT�inpNRGT�32��,inp1��,���,�+1)�2��,inp8;⮪�� ������ inp7��,0;���� ���� ��������5,���,��"@��,inp1;�� �㪢�	shk2�7,���,inp1ء	��,swedoshk1���5,���,shk2�shk1 swedo�(tkn_adr),�;⮪�� ������
�1,�+#37)�pr_tkn��,�Ԡ,�����,inp3��Ԡ,��inp10pr_tkn���6,����5,���,32
��,prnxtx��,��"@
��,prcode�"[	��,ptkn1�prsymi�pr_tkn ptkn1�1,�+#37);⮪�� ������⠭����+1)�"prcode��,�;��������� ��� ᨬ������+1)��,(T_SCRYX+1);X��,���,'string��,��prnumA�mprsym�">����,��	inp8�#29��,inp1��,�Ԡ,��#F6;"�"��,$+6�2,�+#37)���inp2inp9�Ԡ,���,�	�.cmd_bf��,inp1��,�+1)����	��,inp12��,2inp12��+1)��,#20�prsym��,�+1)��	��,inp12����,�
�#F6;"�"��,inp3
�2,�+#37)�inp3inp10��,(cmd_bf)	��,inp11�1��inp11ԣ,ALSTR-2;#16	�clrline;4extH��,fext��,��"?��ԡ,"H�;7;HL=(catadr)ldcat��,�+#10);��࠭�� ��⠫����ONPAGE��,(catadr);��� ������,(#5D19)��+#17)��;㦥 ����㦥�
��+#17),���,5catdir��,0��,9�TRDOS;CATALOGUEcat	�copynme��,illegal�ldcat��	��,�,���mprent�"Title:",0��	��,#08F5��,���	�prdsknm�mprent�"Files:",0�����4,���,��4,�����;LD A,(IY-#11) ;#8E4;SUB (IY-1) ;#8F4�prnumAcat1�mprsym�32��,�+1)����,$+6�ALSTR-3;#15��,cat1�mpr�"Deleted:",0����,�;LD A,(IY-1) ;#8F4�prnumA�entclr��
cat2��,�����,cat5����,cat4
�cpfnmhl��,cat4���prname�2,�������,�;LD A,(IY+5)�prnumA��+1)����,���
��,�,�,�;LD H,(IY+4);LD L,(IY+3)	�prnumHL����,�+1)��	��,cat3_��,2��+1),�cat3_;LD BC,-8;ADD HL,BC
cat4��,16��,��cat2;1prdsknm��,11��,��#7F���prsymiס�����$-10�cat5��,�+1)��
��,entclr�mprent�"Free:",0����,#8E5��,���,�����,���,�	�prnumHL;3prname	�pr8syms�mprsym�".��,��prnxtx��+1)�;5pr8syms��,8��,����prnxtx�$-5;8�svall����,�sa1�ONPAGE�vertxt��,sa2��,(param)�"!	��,$+5���,(T_OPT)��;JR Z,sa2��	��,svtxt����sa2�corrEpg��,sa1�curflsave��,���,��"!	��,$+4��"+��,$+3���getdrv��,illegal
��,cngdrv��,�����,illegal��,��"!	��,$+4��"+	��,svall�vertxt��,illegalsvtxt��,(T_OPT)�(svtop+1),�;???��,(T_SIZE)��,64��,�����,#C000;⠪ � �뫮	�delfile��	;POP IY����;filelen�prevpg��,(catadr)��,#8E4��,���,���,���,svt1��dirful�mprent�" Dir full",0�svt1��,�����,���,���,���,���,���,�	�frmfnme��,�ԡ,���ԡ,���
;PUSH IY��;filelenԡ,���ԡ,���������,�ԡ,�������,#8E1��,(catadr)��,���,�����,�٢,�ԡ,���ԡ,���ԡ,0����,�������������,���ԡ,�����,���,0ԡ,���,svt2�mprent�" Disk full",0��svt3svt2���prevpg����-�(T_OPT),�;�⮡� �� ��᪥ �� � ��.䫠�����,6	��,#C000�TRDOS;1svtop��,0;var�(T_OPT),�;��� �뫮svt3�����prevpg��,(#5CF4)ԡ,���ԡ,���,(catadr)��,6�catdir���prevpg�pnmt
�6,�+#2E)�mpr�"saved Ok",0���(T_OPT),�;notchanged�
ex�nxtsym
��,drror0��,��fnd3NT
��,drror0��,���,�	�#E1;DE��,ex5�#A2;(SP)��,ex1	�#E3;AF
��,drror0��,�
�#D3;AF'
��,drror0ex7��,8;EXA�ex4ex1��,�;LD B,#E3 ;EX (SP),HL	��,#E3DD	�#E4;IX��,ex2	�#E5;IY��,ex6��,#FDex2�p_prfxex3��,�ex4�putbyte
�nxtParamexa�fndEstr���ex7exd�fndEstr��	��,#E2�ex5��,#EB;EX DE,HL��,�ex6�#E2;HL��,ex3drror0�error0name�vertxt��,illegal��,(param)��
��,pnmifv�cnam1��,illegal�extH;LD DE,#C000�frmfnmeDE�pnmifvpage��,���,���pgvfil��,�+#0D)��,pg2�taknum��,illegal��,�����,$+3����,illegal��pg2��+#32)�ONPAGE
��,�+#2D)�vertxt��,setcurt���entclr��,��prnumA���mprent�" No file. Create",0�yesno�2,���,"N��,pg3��,"Y
��+#0D),�	�ldrnnmepg3�prsymi	�pgcurtx�pnmifvsetcurt��+#0D),�pnmifv�vertxt��pnmt�entclr�pgnamprevpg��,�+#18)�ONPAGEpgcurtx��,�+#0D)ONPAGE��,�+#2D)
��+#18),�
��+#2D),�exram�EXRAM;3ONinc$;446:INCLUDE � ����� �����⢮�����+#16);macropg ;���� �ࠢ������ �� ��࠭���...��,ONPAGEinczapg=$+1��,0	�ONPAGE;4cpfnmhl��,���,9	��,fnamecf1��,��"?��,cf2ء��,cf3cf2�����cf1cf3��,��verdebu��,�+#21);��࠭�� ��������ONPAGE��,(#DB00)��	��,#73ED��,��info�mprent�" ALASM vAlVer;DB " - STALL Edition"�#D�" System pg",7,"-",#F�pgsyst�#D," Macro pg",8,"-",#F�pgmacr�#D," Symbols pg",6,"-",#F�pgsymb�0��,pgsymb2��,"+�prsnum�mpr�#D," Post symbols pg -",#F�pgpost�0��,pgpost1��,"#�prsnum�mpr�#D," Pocket text pg",2,"-",#F	�pgpocke�#D," Debugger",8,"-",#F	�pgdebug�0	�verdebu	��,empt_��,$+5	��,nemp_�prstr��,#B7;OR Ajumb2�(jmbf),�����,�inflp�ONPAGE���vertxt	��,jumb3	�prcurpg�prnam��,(T_OPT)����,"+
��,prsymijmbf��
��,jumbit	��,jumb3	��+1),17��,(#C030)����,ofltxsr	��,jumb3�prnumA�mpr�" errors",0jumb3��	�corrEpg	��,inflpcurfl�mprent�" Current file:",0�pgvfiljumb��,��"+	��,jumb1����,vertxt��,illegal�jumbit�curfljumb1����,�����,illegal
��,175;xa�jumb21;���� ��� E 1-� ����-�,�� ������� ��������� ���
corrEpg����
��,�+#32)�����,corrEpg���prcurpg�entclrprcpg1��,�+#2D)�prnumAempt_�" emptynemp_�#D," Memory:",0prsnum�(psn1),���,3	psn2��,������mprsym�",����,��prnumA��psn1���psn2�in�nxtsym
��,error0	�ext_reg
��,error0�7,�
��,error0��,��fnd3NT
��,error0�#D0��,in2��,#40��,��6
��,error0in1���������,#EDputAE�putbyte��	�putbyte
�nxtParamin2�"(��,ouNZer0��,��7��,ouNZer0
�5,�+#26)�val
��,error0��,��")��,ouNZer0��,�����,#DB�putAEout�nxtsym�#D0��,out1�"(��,ouNZer0
�5,�+#26)
�3,�+#26)�val
��,error0��,��")��,ouNZer0�fnd3NT�#F5ouNZer0��,error0��,�����,#D3�putAEout1�fnd3NT
��,ouZer0�"0��,out2��,6�out3out2�ext_reg
��,error0�7,���,ouNZer0�6ouZer0��,error0out3��,#41�in1svchngs
�6,�+#2E)�vertxt����,(T_OPT)�����pnmt�mprent�" Save changes",0�yesno�3,�;break��,intrup1�prsymi����svtxtptxname��,ALSTR-2;#16�(y),�	�clrlinepgnam�prcurPGprnam��+1)
��,#C000�prnameINSOVRprcurPG��,�+#2D)���EXRAM���prnumA;free � ࠧ��� ��ଠ��prpock����,#F*256+ALSTR-2�(y),���,(T_SIZE)	��,#3FC0����,�	�prnumHL
�?alasm48��,(T_OPT)����,"+��,$+4��,32�prnxtx���,(pocksiz)��,���,��63��,�����,prp2��+1)	�prnumHL����,"-��,prp1��,"|����,prp1��,32prp1�prnxtxprp2;᭮��?��?alasm48��+1),ALSYM-INSIZE-2��,(T_OPT)����,"+��,$+4��,32�prnxtx���prsnq��
�?alasm48��,���+2)��,���(y),���,(T_STR)	�str2txt��,noMundO��������,a_buff1�hlstringbc40ldirprsnq��,(T_STR)
��,-#C040��,�
�?alasm48��+1),ALSYM-INSIZE-12-2���+1),ALSYM-INSIZE-12�	�prnumHL�mprsym�"/��,(T_SIZE)	�prnumHLfndhot����ء����,$-4��,�����,���,���	��,param�mm_comm�"aASSEMBLE'�"bBAN�"cCATALOGUE
�"dDEBUG'	�ovlhlp	�"hHELP'�
�"ySYMBOL�"rRUN�"gMERGE"
�"mMOVE"�"sSAVE�"qQUIT�"nNAME
�"pPAGE"�"wWORK	�"vDRIVE�"eEDIT	�"tCOUNT	�"iINFO'�"jJUMB
�"oIMPORT
�"xEXPORT
�"fCONFIGmm_hot�"'",-1�"c�cat	�ovlhlp�"h�help��"y	�symbols�"r�run�"a
�assemble�"n�name�"d�debug�"p"�page�"w�work�"s�save�"e�edit�"q�quit�"g"�merge�"m"�movedisk�"t�count�"i�info�"v�drive�"j�jumb�"b�ban�"o�import�"x�export�"f�config	�illegal�	movedisk��
;PUSH IY;LD IY,#5C3A;LD (IY),#FF�(movdiSP),���,#7000;ACE=big basic��,���,�
��,#5C00	��,#400	��,�,���;LD HL,(23730);LD (movRAMT),HL;LD BC,#6FFF;CALL 7863��,(#5D19)��,1	�#3D13�	�movdiPP;DI;movRAMT=$+1;LD BC,#5FFF;CALL 7863	��,�,��movdiSP=$+1��,0�	;POP IY���movdiPP;LD (#5D1C),SP';LD HL,5803 ;����, �⮡� (#5D11+1)=13����,5806;�� DOS6.05 ���� ZF=1����,�;-2�(#5D15),�;NO MSG�(#5D1F),�;NO LDIR?�15663runovl����,����(rovl1+1),��ruov��;caterr��;notfnd/skip	�ovlCRC��ԡ,���ԡ,��ruov�ovl_pg	�ovlCRC��;LD DE,#400 ;???;JR NZ,cfg1
rovl1��,0��cfg1���mprent�" Load overlay",0�yesno�#05��,intrupt�prsymi�"Y"��	��,cfgnm�sfmsg1��;caterr��;notfnd��,���,#05��,(confadr)�TRDOS��	�pgcurtx�ruovovlCRC��,(confadr)��,�����,���������,ovlall-2	��,�,�,�ovlCRC0��,������,���,�����,�������,�����,ovlCRC0����,����cfgnm�"ol"AlFnm�"C"drive�getDRA��,illegal��,illegal	cngdrv����,#01�TRDOS���(#5D19),�;23833���#C8��,���,#5C��,��#1B��,$+4ԡ,#83���getdrv��,���������,����":��,gd1getDRA��,������"A�4��verbrk
�6,�+#05)
�6,�+#05)����,-2��,(-2)�����,#7F��,(-2)���	;XOR A�;RETgd1���pockpg��,�+#36)�ONPAGE;��⠢��� �� ��ଠ��inspock��,(T_SIZE)��,64��,���,(pocksiz)��,��#80�(pocksiz+1),��#3F��,�����,ed2��,��6,���,ed2�(T_OPT),�����,��(T_SIZE),���,���,�����,��#C0��,���,��#C0��,�����,(T_STR)��,�ip1��,�������,�ԟ,���,���,ip1����,���,���,��#C0��,�ip2�����pockpg��,���	�pgcurtx��Ԡ,���,��#C0����,ip2�ed1;����⪠ ��ଠ��clear��,0�(pocksiz),��ed2 