smallunrH                        ���   �v������                maintree=RARStree=298-6*4-4+maintreebdlens=treeldlens=treeddlens=298+ldlens;rdlens=ddlens+48tabend=ddlens+48+28NEWBYTE��,�����dPPbr16��
��,dPPn16;16=prev len copies-3�LDA2����,����(dPPdupV),���,3�dPPfil	UNILDRAR��,��(theEnd),�;ᠬ HL �� �㦥�!;IX->DE��,128�NEWTREE���LDA2
��,bdlens��,19dPPtetr��,4�LDA18Bԡ,�������,dPPtetr;EXX
;PUSH DE��,19+1"�MKMAINTREE;������ �� ��� ��ॢ�	;POP DE;EXX��,298+48+28;tabsize��,ldlens;UnpOldTable	dPP0����DEHUFFMAIN���16��,dPPbr16!;<16 delta from prev codelen tabԡ,������dPPQ
dPPn16�17
��,dPPn3b;17=zerolens-3��,3��,�dPPfilG�LDA18BdPPfil��,���dPPdupV=$+1dPPdup0ԡ,0��������,dPPdup0�(dPPdupV),�	dPPQ��,�����,dPP0;EXX
;PUSH DE	��,298+1"�MKMAINTREE;������ �� ��� ��ॢ���,ddlens+49��,48+1��,tree�MKTREE;������ �� ��� ��ॢ���;EXXDEPK0�DEHUFFMAIN��
��,yBYTE�269��,NEWTREE	��,len2��
;SUB 270��,��8��,EMMTPP��,�,�	��;len��,tree�DEHUFF��,-4��,EMBBTQ��,1��,������,�	�EM_TPP	EMBBTQ��;NC	��,�,�,�GPldir��,�	��,�,�,�;OR A��,���,���;3..255�#E0��,$+3��;CALL UNILDIR�GPq;��� ���� BIT 7,DtheEnd=$+1��,0���,�;LD A,H ;!;ADD A,2;!
��,DEPK0�;LD A,(UNIpg);JP OUTME;18=zerolens-11dPPn3b��,7��,11	�dPPfilGyBYTE��,�Ԡ,����GPqlen2;261..268=>-8..-1��,���,�
��,'tlen2��,�;bits����,�;N>>bits�EM_TPP��,2��;CY	�GPldirDEHUFFMAIN��,maintreeDEHUFF���,���,NEWBYTE��,$+4;������;��������;HL���,�����,���,��'maintree&#40�6,���'maintree&#80�7,�����,DEHUFF�.;ᮧ����� ��ॢ�. �㫨 - ����� ���⪨� ��⪨!;᭠砫� ᮧ������ �� ��⪨ ���+;ᨬ����� � bitlen=1, ��⮬ 2 � �.�. �� 15;by Roman PetrovMKMAINTREE��,ldlens;�뫮 ���� tree��,���,maintreeMKTREE�����;��砫� ������,���,���;=0 �ਧ��� ��室�����;=1������,�MKTREE0�;HL=���.bitlens+1��,���,�%;ADD HL,BC;㪠�.�� ��᫥���� bitlen;OR A���,�;㪠�.�� 1� bitlen�MKTREE1��,���,��;CPDR ;BC=�᫮ ����쥢+1���,������,�(��,MKTREEY;������ ᨬ��� � ⠪�� bitlen��;�� ������ ⠪�� ᨬ�����,MKTREE0�MTREEbugMKTREE_DEEPER��;����� ������;���
��;�����
��;㧫��ԡ,���ԡ,�;㪠��⥫� ��� "0"��,���,�;���� ��� "���+0"��;����� �⮣� ������;����ᨬ ����;� �⥪
MKTREEY��4��,MKTREE_DEEPER;���� �� 㣫㡨��� �� �㦭�� �����;A=C���;��⨭���� ���ࠫ�+1	��;Q+1�	MTREEbug�(MKhl),�����;DEC BC ;����� ���ࠫ�;LD (HL),C	;INC HL;LD (HL),B ;�ନ�㥬 �������,�	MKhl=$+1	�(0),����,�����;=0 �ਧ��� ��室�������;᫥���騩 ᢮����� 㧥�;A=��� ��㡨��!;DE=���� ���� ��� ����� 㧫��	�MKTREE1EMMTPP��,��3�4��,���,���EM_TPP�
MLEN0��,���,NEWBYTE��,�	�MLEN0���	LDA2��,2LDA�9
��,LDA915
LDA18��,�LDA18B��,0�	LDA0��,���,NEWBYTE���LDA0��LDA915�8�LDA18��,���,8�LDA0-1��,����$�$+15/256<8+#F0-$��"=",$tlen2�2,0>2�2,4>2�3,8>3�4,16>4�5,32>5�6,64>6	�6,128>6	�6,192>6 