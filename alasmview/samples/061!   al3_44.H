al3_44  H                        �=(� �v������                �"Al5*",#C6disp�oneprm1�ent1error04�error0ent�fndEstr��,(a_place)ent1�(a_exe),��org3equ
�6,�+#26)��,error04equ1�oneprm1��,�	equ2��,0
�selLBpgHԡ,���ԡ,�	�nxtstr1org	�calcule��,error04����,(a_exe)��,���,(a_place)��,��5,�+#34)��,��#40	��,_org1�5,�+#34);ࠧ��.����.� ���_org1�(lastorg),��(a_place),����(a_exe),��nxtsm19��,nxtstr1;org3 �� ����,�.�.ORG ⥯��� �� ����� shift	;LD L,0;LD L,(IX+#2B);JR Z,_org2�",��,error04	�calcule��,error04��,�����,error04
_org2��,���+#32);mask on page��+#2B),�;⥪.���.ORGorg3��,(postadr)	�postpgnԡ,#47��
��,�+#2B)ԡ,�������,(a_place)��,���,(a_exe)����,���,���,���ԡ,���ԡ,���;LD A,(a_place+1)ԡ,��(place+2),����rstpst�(postadr),�	�nxtstr1	runinasm	�oneprm1�jphl	�nxtstr1	assemble�vertxt��,illegal
�7,�+#2E)
��,�+#0D)
��+#24),�
��,labEND
�selLBpgH�(symbadr),���
��+#2B),��(compile),��(macrflg),��(alabel+2),�;LD (HL),A ;for SYMBOL	;INC HLԡ,�����,$-2��	��,$-5��(postadr),��(ae1+1),��(pocksiz),��(n_str),��(a_sp+1),���1��+#34),�;����� ������.� ��� � RUN,ࠧ��.MAIN��,#80�(a_place),��(a_exe),��(lastorg),���,(MacPgBeg)�(macradr),�	�text_pg�entclr��+1),5�asmi1assem1��,(a_exe)
��+#2F),��verbrk��,asm1	�intrupt	a_sp��,0�p_ovf�mprent�" Post",0�l_o1l_ovf�mprent�" Symbols",0	l_o1�mpr�" overflow!",0�a_spasm1�(error+1),���,���,�����,nxtstr;��ப� - �������,���,��vMacIfnerN��,nxtstr�32
��,error0��,nerN;�訡�� :N ��᪠�������"@
��,a_plusas4��,�����,���,�;C=B-(DE-HL)��,�
��,a_buff��
��+#26),���,��;��ப� � ����Ԡ,���,a_buff-1as1��as2��,�����,as1����,nxtstr1�16��,as1�";��,nxtstr1	�"@	��,kva3;errorer if compile=0��,���,���,anallbl;compile=1:as1��,0��,a_tbl-#80��,���,���,���,����(as42+1),���0��,jpinhl;�� ����� �� if: ELSE,IF0,IFN,ENDIF����(as41+1),���,(compile)	asmora����,nxtstr1;LD A,183;LD (asmora),A��,��(adsbc+1),�	as41��,0����,jpinhl;1��&��,a_sympl;2 ��⠢��� ����� �����������,pushpop;3 push/pop��*��,rollz;4 rlc,rrc,sla,sra,sli,srl,rl,rr����,djnzjr;5 djnz,jr����,incdec;6 inc,dec����,accum;7 sub,and,xor,or,cp����,calljp;8 call,jp����,bits;9 bit,res,set����,adsbc;#A adc,sbcerror03�error02
a_plus�"-
��,nxtstr;CP "!;JR Z,a_wow�"+��,error02��,"-Ԡ,�a_plQ���as4a_wow;LD A,175;LD (asmora),A;JR a_plQbits��	�calcule��,error02��,�����,error02��,��7����,error02�����ס��,string+1ԡ,���,��",;JR NZ,error02	��,rollzerror02�error0jp1��,��#A1;(HL)��,error02��,jp2	;DEC A�;JR Z,error02	;DEC A��2�2��,error02����#DD	�putbyte
jp2��,#E9	�putbyte
�nxtParamcalljp�nxtsym��,error02�#80	��,_ld23	�ext_reg��,jp1�fnd3NT��,error02��,���ס�_ld24
_ld23��,�_ld24�5,�+#26)
�4,�+#26)�_ld22add�nxtsym��,error02�#F5��,add3��,0�#E2��,add1��,#DD�#E4��,add1��,#FD����,error02add1�p_prfx�fnd3NT��,�	�ext_reg��,error02
��,error0�#20��,add2��,�����,error02��,#20add2�9	�putbyte
�nxtParamadsbc��,0;(DE)�nxtsym��,error01�#F5
;A	��,adsb1	�#E2
;HL��,error01�fnd3NT��,error01	�ext_reg��,error01�7,���,error01�#4A��,���,��#AF��������,#ED	�putbyte��	�putbyte
�nxtParamadd3��,string+2ԡ,#C6��ԡ,#80adsb1�nxtsym�",��,error01accum�nxtsym��,error01�#80
��,accumN��,6	�ext_reg��,error01
��,c_ixy1ס��,��_ld16	accumN����,�acN1��	�putbyte
�5,�+#26)	�one_prm��,�	�putbyte
�nxtParamincdec�nxtsym��,error01	�ext_reg	��,inde1��,error0;*** inc af!ס;bc,de,hl,ix,iy,sp... and af!incde1�ppop2error01�error0inde1����,#30��,error01��,c_ixy1;(ix),(iy)���ס���incde1	rolixy���p_prfx��,#CB�p_prfx�ixyA	�putbyte����,��6�ci2	c_ixy1���p_prfx����,���ci1�putbyte�ixyAci2�putbyte
�nxtParam	ixyA��,��#A3	��;(IX)��	��;(IY)�val��,error01��,��")��,error01�vldrel��error3��,3�errorvldrel��,�;RLCA�;RRCA�
;ADC A,H;SUB L��,#80��,���,$+3������,��;��ࠡ�◨� djnz � jrdjnzjr�nxtsym��,error01�3,���,a_djnz;djnz�#80��,a_djnz;jr label	�ext_reg
��,error0��,error0;nz,nc,z,c�5,��nxtsym�",��,error01��,�
�a_djnz+2a_djnz��,���	�putbyte
�4,�+#26)	�one_prm����,(a_exe)	���,���,�	��
��+#2F),����vldrel��,error3
�PutbNxt;CALL putbyte;JP nxtParam
;�������rollz�nxtsym��,error07	�ext_reg��,error07;b0=1&��,rolixy;b2=1 ���� �� #FE - IX,IY�7,���,error07ס��,���,#CB�p_prfx��,�PutbNxt�putbyte
�nxtParamfnd3NT�nxtsym��,error07�",��,error07nxtsym��;�ய�᪠�� #FF, ⠡��樨,nxtsm1��,�;�� ��室� Z - �ய����� ��ப���
��,nxtsym�����16
��,nxtsym�";�pushpop�nxtsym��,error07	�#E6;SP;JR Z,error07��,ext_reg��,error07ס
ppop2��,����p_prfx��,�	�putbyte��
�nxtParamerror07�error0a_sympl��,�������,putbyte������,�a_symp1�putbytefndEnxt�fndEstr	�nxtstr1putbyte��,(a_exe)���(a_exe),���,(a_place)���(a_place),����curcpgԡ,��/;�������� �� HL �㦭� ��࠭��� ��� �������樨curcpg����,�	�;#80..��,ccp1�;#40..#7F��,ccp3;����5,�+#34);�� ORG � ���?��,ccp3��,#A�error;1+1ccp1�
��,�+#2B)��,ccp2;#C0..��,(pgsyst)�6,�ccp2�ONPAGEccp3���;1
curpgkv����,�;*** ���. {}���,ccp1���;2jpinhl��,�����,���,�֡nxtstre��+1),ALSTR-1;#17nxtstr1�6,�+#34)nxtstr	�text_pg��,(n_str)���(n_str),���,�nstr1�0��,pr_astr��,(curstr)	�n_strHL�(curstr),�asmit��,assem1	�pr_astr����,�����,deincld;end of assembly
�7,�+#2E)
�7,�+#34)�mprent�" Symbols:",0��,(symbadr)	�prnumHL�mpr�" Post:",0��,(postadr)	�prnumHL�mpr�" Macro:",0��,(macradr)	�prnumHL	�verdebu��,ae1��,(lastorg)�(#FEFE),��(#FEE4),���,(symbadr)���(STSlabAD),���,�+#1D);!!!��+#32);!!!�(STSlabPG),�;!!!;posting...!;� post'� ����� ���� ��� ��⮪&;���������� � maklab, disp, ent, org@;shift, pg � ��.����� ���ᮢ �������� �१ "�������" (OR #40)A;����訥 ���� �����।�⢥��� (�筥�,� ��������� ����-� &#BF)ae1��,0ae2��,��#C0����,$+4����,��(ae1+1),��verbrk��,intrupt��,���,(postadr);end of post����,���,text_pg��,�	�postpgn��,����6,���,pst4;�� �����������,pst1��,�;page���(p_pg+3),�pst1����,pst2��,�;phase=a_place-a_exe����,����(phase+1),�pst2����,pst3��,�;place���(place+2),�pst3����,ae2c��,����(alabel+2),�ae2c�rstpst�ae2	pst4��,����(alabel+1),���,����(place+1),��rstpst�(ae1+1),�p_pg��+#2B),0��"alabel��,0;���� ��⪨ � ⠡����(ladr+1),�
�selLBpgH��,��#C0�#80
��,prndef����,�����,���,(place+1)���3,���,pst6	��,�;**�	�curcpg;**��,�	��,�;**��#DD��,pst5�#ED��,pst5�#FD��,$+3pst5����	pst6��,��1,�;㬭��/���
��,prncnt�7,���,$+5��,���,0�0,���,pst7������,0��,���,���	pst7�5,���,pst8;jr�4,� ��,ptwrd;dw, ��� ���室� - dbpst8�curcpg;***��,���,0��
��,�,�,��7,���,$+3���4,���,pst9;�� dw, ld(), djnz��
phase��,0��,�!place��,0;a_place �� �� ������������,��0,���,$+4;+/- ��⪠	��,�,�,���	pst9��,���,��5,��
��,vldrel��,�����,$+5��,pwrshrtԡ,��ae1#ptwrd��;*** ⥯��� �த� ࠡ�⠥��curcpg��,���,�ԡ,�������curcpg���,���,�ԡ,��ae1
pwrshrt��
��,wrshrt�prpstecntcnt�" Can't count:",0wrshrt�" Wrong short:",0	prncnt��
��,cntcnt�prpste	prndef����,ndef	prpste������
��,�+#2D)���prent	ladr��,0
�selLBpgH��,��63��,���,0��,���,�	;DEC DE�5�clnm;������⠥� ��� ��⪨���ONPAGE���������;onceanallbl	;LD C,A��,��"}��	��,obqz��
��,error0;0=䫠� �������樨compile=$+1��,0��	��,as1�obqz�srclbl��,anl1�6,���,domacroanl1;once	;LD B,0;INC B;DEC B;JP NZ,nxtstr1 ;as1
�6,�+#26)
��,error0��,anl3��	�makelbl	anl5��,��"=��,equ1;LD A,(DE)�":";��-style ��⪨��,$+3��
�6,�+#26)�as2	anl4��,��"=��,6	��,error�equ14anl3�(equ2+1),�;��������� ��⪠ 㦥 �ᯮ�짮�������7,�	;�᫨ ��।����� - ������
��,anl4;�63��,(a_exe)��
�selLBpgH��ԡ,���ԡ,���ԡ,��anl5makelbl��,(symbadr);l	;OR HY�����,(slLY-1)��,�
;LD B,LY��,���	��,l_ovfmlb1�selLBpgH;f�	��,l_ovf	;AND #C0;LD (mlb2+1),A��,�ԡ,������$-4��ԡ,�;0 ����� ��ॢ���ԡ,�����,(a_exe)ԡ,���ԡ,���ԡ,�atoptre��,0	;l�f2l	�0	��,�	�63mlb2�0		��,�
;l	���,�;l
�selLBpgHԡ,�;f��ԡ,���,���	;l�����(equ2+1),�;l����
;l��,��63	��,ppdm3��,��(#C000),�����,#FFppdm3�(symbadr),�;lpopde���;���� ��⪨;C - �� �������srclbl�(lbnadr+1),���,#400����sl3�����,�����
srcl2��,��"0��,sl2�":��,sl3�"@��,sl2�"{��,sl3	sl2��,�
;LD HY,A��,��5�(slLY),�
;LD LY,A	��,-1	;l��,�
�selLBpgH
;5335 ࠧ	��,#C0�sl4��,�����,���,�sllbex��,�����,sl5;curpgms LD B,0	��;page��,selLBpgH1�#C0��,���,�	;AND A�;JR Z,sl5�#3F	;CP HY�����,sl6sl7������;15000 ࠧ�sl4
selLBpgH1��,��#C0��,�;LD (curpgms+1),A
�sUlLBpgH��,���
��,sllbexsl5����,��63;OR C����,��(atoptre+1),����,(lbnadr+1)�sl6����
;LD C,HY��,0��,�	slLY=$+1��,0
;LD B,LY!lbnadr��,0	;adress of label namesl8����,�ء��,sl9���sl8sl9������,sl7��,���f2l������f2l��,��63sle�0��,��;>HL => label page	selLBpgH��,��#C0	sUlLBpgH;13000 ࠧ�(sle+1),�������,pgsymb4��,���,���,������EXRAM;? or maybe ONPAGE? !!!������,��6,��7,��	error0��
error��,0��	�pr_astr�mprsym�":���prnumA�mprsym�#B3;�	�text_pg��,(curstr)	�set2err	�str2txt�err2	�nxtstreofltx	��,#C040	�str2txt
�?alasm48��,ALSYM-18+.string�;��祬� ��-ࠧ����?��,ALSYM-17+.string
��,string
ofxt1��,����prsym��+1)�ofxt1����err2��,string	err1��,�������,��prsymi���err1set2err���vertxt��,$+5����������
��,�+#0F)�����(T_STR),��getbyte
��,�+#2D)�����curpgkv;1��,���;*** ���. {}����exram��;4	c_kva1�0c_skobk��,")	�c_mem+2;����� ᫮�� �� �����c_mem��,"}
��,�+#26)��,(rez+1)��������,(c_kva1)��	�calcule����(c_kva1),�����٢,��(rez+1),���
��+#26),���,�ء;}��,�����������#7D;}
��+#3C),���,c_do	�getbyte����	�getbyte��,�����,��c_dolab_inf����,��"@���"{���
��+#3C),��srclbl��,0��,li1��,#C9;RET	�(sl2),�#�srcl2;�஢�ઠ ��⪮�ࠢ��쭮��;� �筥�,�ய�� �������,#7C;LD A,H	�(sl2),�	;DEC HL��,-1�li2li1���7,���,li2���6,���,li2����	li2�c_domacpg��,�+#16)expgsav�(expg+1),�	expg��,0	exra_k���exram���symbpgk��,�+#1D)�exra_k;1:���.���<@kva3��,(compile)��
��,error0�nxtstr1;as1;1domacro
�selLBpgH��,�����,���,��(adrmcr+1),���,0	domIF������,��#E2;was IF
��,domIF��	�McShft��,(m_shft)�������,(macrflg)����,dm2;not in macro
��,m_buffdm1��,�����,dm2���������dm1dm2	�McShft�(m_shft),��
��,�+#24)��,���+#16);macropg	��,$+5��(inczapg),���,�����,(curstr)����,(ptrmstr)��	��,#F2�����,#E2;IF���$-1��adrmcr��,0�(curstr),�
��,�+#16)&��+#24),�;�������� ��࠭��� ����ᮢ
��,m_buff�(ptrmstr),����nxtsym��,�;ln2Ehl��������,�����ء	��,$-3���ԡ,�	�str2txt	�nulEstH��,���,string-1
��,m_buff��,32��ء	��,$-2�!dm3��,�;㤠��� �஡���, ","->1*��;(��஗� - � m_buff ��ࠬ���� ��१ 1)�";��,dm4�0,���,dm6���dm6dm4�"""��,$+3���",��,dm5�0,���,dm6��,1�dm6dm5;CP #20;JR NZ,dm6
;BIT 0,B;JR Z,dm6+2dm6Ԡ,�������,dm3���(macrflg),�	�nxtstr1ifn��,1�if+1if���(if1+1),���,compile��,�������,nxtstr1����	�calcule��
��,error0��,�����,���,if1��if1��,0��ԡ,�	��,#E2���	�nxtstr1;2verifc�fndEstr������,��#E2������,#E	��,error��,compile��,����else�verifcԡ,1��,nxtstr1ԡ,�����,nxtstr1ԡ,�	�nxtstr1endif�verifc��,ei1����,nxtstr1ei1��	�nxtstr1local	�fndEstr	;LD B,0locIF;INC B	;POP HL	;LD A,L;CP #E2 ;was IF;JR Z,locIF
;PUSH HL��,(symbadr)��	��,#F0���;LD L,#E2 ;IF
;PUSH HL;DJNZ $-1	;POP HL	�nxtstr1endl	�fndEstr	;LD B,0enlIF;INC B����,�;CP #E2 ;was IF;JR Z,enlIF�#F0��,#E
;PUSH HL	��,error�
;POP HL����(saloc+1),�;symbadr
;PUSH BC��,labTAB;FF80el1����,���,��crl0��������,el1��	��,el1�	;POP BC;LD L,#E2 ;IF
;PUSH HL;DJNZ $-1	;POP HL	�nxtstr1;���४�� ��������corloc������crl0
�selLBpgH��,�����,���,���;HL=���. ��� ᫥� ��⪨��,crl3;����㘪�
;PUSH HL
saloc��,0��,���,�	;POP HL)��,crl2;NC-��⪠ �� � �����쭮� ��������
�selLBpgH��,����640��,crl2;NC - ��⪠ ��� ���� ��� �� ��।�����������,���,0��,�
�selLBpgH��,��64;��䨪� ������쭮� ��⪨��
��,corloc	crl2��,�
�selLBpgHԡ,���ԡ,�;� �। ��� ⥪㙥�������-��,�
;HL=DE=���� 㪠��⥫� ���� ᫥� ��⪨��,��crl0	crl3��,�
�selLBpgHԡ,0��ԡ,0�#macrflg�0;0=notusing macro,1=,-1=6macradr�0;���� ������ ᢮������� ���� � macro page*ptrmstr�0;���� 㪠��⥫� � ���� ��ப�macropg��,�+#16)�ONPAGE;� IF ��� MACRO+;�᫨ MACRO,��४��뢠�� ��ப� � MACRO pgvMacIf��,(macrflg)��
��,ver_if����,m_param��,(curstr)��,���,�;0
��,m_buff�����Ԡ,�	�macropg������,(macradr)����(macradr),���vM1����,������";���#9B;ENDM��,vM1��,��fndEstr;�஢���� �� ���������(macrflg),�ԡ,����(macradr),���٢,��nulEstH��,string+#40
nulEstr����,��#20��,nulEstr��ԡ,0�ver_if��,(compile)��
��,nxtsym����,"A�;�뤠�� ��ப� ᨬ����� �� ";1 for :S"m_str��,��#20��,mp5�#F0��,mp5��,���ms1�m_gets����,mnxtsym����,mnxtsymԠ,����msnxts�ms1;1:use macrom_param��,(compile)��
��,ver_if����,�mp0����,�
�McSym;":��,mp1����,mp0�mp1��
��,ver_if	�str2txt
��,string
��,a_buff��Ԡ,�����
�bc40ldir��,64��ԡ,32�$-3��,a_buff+#41	�nulEstr��
��,stringmnxtsym��,�����,mpe��
�McSym;":��,mp3mp4Ԡ,���	�mnxtsym;⥪� ᨬ���cursym�m_gets����,mnxtsym�mp4;�� ������ ��ப� ��ࠬ��஢begprm��
��,m_buff�(ptrmstr),���	�McShft���(m_shft),��	�mnxtsymmpe�cnv2str
��,a_buff��,���,���,��ver_ifmn3��	�mnxtsym;�� ᫥� ᨬ���mnxts�msnxts	�mnxtsymmp3��,����"R
��,begprm�"C
��,cursym�"N	��,mnxts	�"S	��,m_str�	�McShft�"P��,mnxpar��"0��,mp5�10	��,m_nummp5����,McSym;":�mp4mnxpar	�McShft��,(m_shft)���(m_shft),���,-1�;��ࠬ��� �� ������m_num��;?
��,m_buff	�McShftm_shft=$+1��,0�����,mn2��,�mn1��,�����,mn2������,mn1����,mn1mn2��,����2��,mn3;1=ࠧ����⥫�?Ԡ,����mn2	m_gets����,(ptrmstr)��,����1����,",�	msnxts����,(ptrmstr)��,�����,$+3���(ptrmstr),����;kmacro��,(macrflg)����,#C��,kmaer0;def MACRO in MACRO�nxtsym
��,error0��,��"@
��,error0�"{
��,error0�srclbl��,#Ckmaer0��,error��,#40	�makelbl��,(equ2+1)
�selLBpgH��,(macradr)ԡ,���ԡ,���,�	�macropg��,1ԡ,����(macradr),��(macrflg),�	��,#F2���	�nxtstr1endm3;�)�᫨ �� macro,� compile=1:skip,=0:error(skip!)-;�)�᫨ use macro,� �⥪ IF ��४��뢠�����";�)�᫨ ��।.macro,� �� �뢠��?	�fndEstr��,(macrflg)��
��,endmQ
;LD A,#C;JP Z,error��,0
endmIF������,��#E2;was IF in macro��,endmIF�#F2��,#E	��,error���(ptrmstr),�����
��+#24),���,�0��+#16);��ࠢ����� �� ��������� ����ᮢ���,0�(curstr),�	��,em1���
��,em1-2��,���,�	��,�;0�	;LD B,A
��,m_buff��,�
ԡ,�;D=0������ԡ,��$-4��,-1em1�(macrflg),�	�McShft�����(m_shft),����,���,#E2;IF���$-1��endmQ�nxtstr1srclbnm�srclbl���6,�������;� ��� 㦥 � ��� ������� :));�, ����, �ਢ� ! :(    ���, 4.4.2��2display���nxtsym	��,dino1�"/	��,dino1����,��#F4;L	��,dino1�����dnnxtdino1�pr_astr���mpr�"  ",0dnnxt�nxtsym��,nxtstrD�"/
��,dspopt�"""��,dsplnum��,prsymi�(pun34+1),�	�puttxt��,putbyte�(pun34+1),�����,nxtsym��,nxtstrD�dsn1dsplnum�(prT1+1),���	�calcule
��,error0��dsprdx�prnumHL��,prnumHL�(dsprdx+1),��(prT2+1),���	dsn2��,�dsn1�",	��,dnnxt	�fnEstr1nxtstrD�nxtstr1	dspopt����,��#F3;H	��,pnHLh	��,dspo1�#F1;D��,prHLdec	��,dspo1�"T
��,prTasm	��,dspo2�#F5;A��,prdh
��,error0dspo1�(prT2+1),�dspo2�(dsprdx+1),����dsn2	prTasm��	prT1��,0��,�����,���,����prsymi�$-5�mpr�"=",0��prT2�prnumHL 