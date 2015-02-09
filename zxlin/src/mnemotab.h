/***************************************************************************
                          mnemotab.h  -  description
                             -------------------
    begin                : ��� ��� 26 2005
    copyright            : (C) 2005 by vitaly
    email                : vitamin_caig@mail.ru
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#define _iw  9
#define _ib  10
#define _shrt 27
#define _ld 0x89
#define _zr16 0x8A
#define _zr8 0x8B
#define _cb 0x8C
#define _zjr 0x8D
#define _hl 0x8E
#define _zr81 0x8F
#define _zop 0x90
#define _zf 0x91
#define _zr16a 0x92
#define _zr8_ 0x9D
#define _zr81_ 0x9E

BYTE Disasm::mnemotab[] = {
/*
   2,0xED,0xFF,0xFF,0xFF, // call unreal api
   'u','a','p','i',0,
*/
   // fix bug out (c),a => out (0C),a
   2, 0xED, 0x40, 0xFF, 0xC7, // in r8,(c)
   'i','n',' ',_zr8,',','(','c',')',0,
   2, 0xED, 0x41, 0xFF, 0xC7, // out (c),r8
   'o','u','t',' ','(','c',')',',',_zr8,0,


   1,0xCB,0xFF, // all cb-opcodes
   _cb,0,
   1, 0x00, 0xFF, // nop
   'n','o','p',0,
   1, 0x08, 0xFF, // ex af,af'
   'e','x',' ','a','f',',','a','f','\'',0,
   1,0x02, 0xFF, // ld (bc),a
   _ld, '(','b','c',')',',','a',0,
   1,0x12, 0xFF, // ld (de),a
   _ld, '(','d','e',')',',','a',0,
   1,0x0A, 0xFF, // ld a,(bc)
   _ld, 'a',',','(','b','c',')',0,
   1,0x1A, 0xFF, // ld a,(de)
   _ld, 'a',',','(','d','e',')',0,
   1,0x03,0xCF, // inc r16
   'i','n','c',' ',_zr16,0,
   1,0x0B,0xCF, // dec r16
   'd','e','c',' ',_zr16,0,
   1,0x04,0xC7, // inc r8
   'i','n','c',' ', _zr8,0,
   1, 0x05, 0xC7, // dec r8
   'd','e','c',' ', _zr8,0,
   1, 0x07, 0xFF, // rlca
   'r','l','c','a',0,
   1, 0x17, 0xFF, // rla
   'r','l','a',0,
   1, 0x27, 0xFF, // daa
   'd','a','a',0,
   1, 0x37, 0xFF, // scf
   's','c','f',0,
   1, 0x0F, 0xFF, // rrca
   'r','r','c','a',0,
   1, 0x1F, 0xFF, // rra
   'r','r','a',0,
   1, 0x2F, 0xFF, // cpl
   'c','p','l',0,
   1, 0x3F, 0xFF, // ccf
   'c','c','f',0,
   1, 0x00, 0xC7, // relative jumps
   _zjr, _shrt, 0,
   1, 0x09, 0xCF, // add hl, r16
   'a','d','d',' ',_hl,',',_zr16,0,
   1, 0x32, 0xFF, // ld (nnnn),a
   _ld,'(',_iw,')',',','a',0,
   1, 0x3A, 0xFF, // ld a,(nnnn)
   _ld,'a',',','(',_iw,')',0,
   1, 0x22, 0xFF, // ld (nnnn),hl
   _ld,'(',_iw,')',',',_hl,0,
   1, 0x2A, 0xFF, // ld hl,(nnnn)
   _ld,_hl,',','(',_iw,')',0,
   1, 0x76, 0xFF, // halt
   'h','a','l','t',0,
   1, 0x40, 0xC0, // ld r8,r8
   _ld, _zr8_, ',', _zr81_, 0,
   1, 0x80, 0xC0, // op r8
   _zop, ' ', _zr81, 0,
   1, 0xC0, 0xC7, // ret cc
   'r','e','t',' ',_zf,0,
   1, 0xC2, 0xC7, // jp cc, nnnn
   'j','p',' ',_zf,',',_iw,0,
   1, 0xC4, 0xC7, // call cc, nnnn
   'c','a','l','l',' ',_zf,',',_iw,0,
   1, 0xC6, 0xC7, // op immb
   _zop, ' ', _ib, 0,
   1, 0xC1, 0xCF, // pop r16a
   'p','o','p',' ',_zr16a,0,
   1, 0xC5, 0xCF, // push r16a

   'p','u','s','h',' ',_zr16a,0,
   1, 0xC3, 0xFF, // jp nnnn
   'j','p', ' ', _iw,0,
   1, 0xD3, 0xFF, // out (nn),a
   'o','u','t',' ','(',_ib,')',',','a',0,
   1, 0xE3, 0xFF, // ex (sp),hl
   'e','x',' ','(','s','p',')',',',_hl,0,
   1, 0xF3, 0xFF, // di
   'd','i',0,
   1, 0xC9, 0xFF, // ret
   'r','e','t',0,
   1, 0xD9, 0xFF, // exx
   'e','x','x',0,
   1, 0xE9, 0xFF, // jp (hl)
   'j','p',' ','(',_hl,')',0,
   1, 0xF9, 0xFF, // ld sp, hl
   _ld, 's','p',',',_hl,0,
   1, 0xDB, 0xFF, // in a,(nn)
   'i','n',' ','a',',','(',_ib,')',0,
   1, 0xEB, 0xFF,  // ex de,hl  - no 'ex de,ix' !
   'e','x',' ','d','e',',','h','l',0,
   1, 0xFB, 0xFF, // ei
   'e','i',0,
   1, 0xCD, 0xFF, // call nnnn
   'c','a','l','l',' ',_iw,0,
   1, 0xC7, 0xFF, // rst 0
   'r','s','t',' ','0',0,
   1, 0xCF, 0xFF, // rst 8
   'r','s','t',' ','8',0,
   1, 0xD7, 0xFF, // rst 10
   'r','s','t',' ','1','0',0,
   1, 0xDF, 0xFF, // rst 18
   'r','s','t',' ','1','8',0,
   1, 0xE7, 0xFF, // rst 20
   'r','s','t',' ','2','0',0,
   1, 0xEF, 0xFF, // rst 28
   'r','s','t',' ','2','8',0,
   1, 0xF7, 0xFF, // rst 30
   'r','s','t',' ','3','0',0,
   1, 0xFF, 0xFF, // rst 38
   'r','s','t',' ','3','8',0,


   // ED opcodes
   2, 0xED, 0x70, 0xFF, 0xFF, // in (c)
   'i','n',' ','(','c',')',0,
   2, 0xED, 0x71, 0xFF, 0xFF, // out (c),0
   'o','u','t',' ','(','c',')',',','0',0,
//   2, 0xED, 0x40, 0xFF, 0xC7, // in r8,(c)
//   'i','n',' ',_zr8,',','(','c',')',0,
//   2, 0xED, 0x41, 0xFF, 0xC7, // out (c),r8
//   'o','u','t',' ','(','c',')',',',_zr8,0,
   2, 0xED, 0x42, 0xFF, 0xCF, // sbc hl,r16
   's','b','c',' ','h','l',',',_zr16,0,
   2, 0xED, 0x4A, 0xFF, 0xCF, // adc hl,r16
   'a','d','c',' ','h','l',',',_zr16,0,
   2, 0xED, 0x43, 0xFF, 0xCF, // ld (nnnn), r16
   _ld, '(',_iw,')',',',_zr16, 0,
   2, 0xED, 0x4B, 0xFF, 0xCF, // ld r16, (nnnn)
   _ld, _zr16, ',', '(',_iw,')', 0,
   2, 0xED, 0x44, 0xFF, 0xC7, // neg
   'n','e','g',0,
   2, 0xED, 0x45, 0xFF, 0xCF, // retn
   'r','e','t','n',0,
   2, 0xED, 0x4D, 0xFF, 0xCF, // reti
   'r','e','t','i',0,
   2, 0xED, 0x46, 0xFF, 0xDF, // im 0
   'i','m',' ','0',0,
   2, 0xED, 0x56, 0xFF, 0xDF, // im 1
   'i','m',' ','1',0,
   2, 0xED, 0x5E, 0xFF, 0xDF, // im 2
   'i','m',' ','2',0,
   2, 0xED, 0x4E, 0xFF, 0xDF, // im 0/1
   'i','m',' ','0','/','1',0,
   2, 0xED, 0x47, 0xFF, 0xFF, // ld i,a
   _ld, 'i',',','a',0,
   2, 0xED, 0x57, 0xFF, 0xFF, // ld a,i
   _ld, 'a',',','i',0,
   2, 0xED, 0x67, 0xFF, 0xFF, // rrd
   'r','r','d',0,
   2, 0xED, 0x4F, 0xFF, 0xFF, // ld r,a
   _ld, 'r',',','a',0,
   2, 0xED, 0x5F, 0xFF, 0xFF, // ld a,r
   _ld, 'a',',','r',0,
   2, 0xED, 0x6F, 0xFF, 0xFF, // rld
   'r','l','d',0,

   2, 0xED, 0xA0, 0xFF, 0xFF, // ldi
   'l','d','i',0,
   2, 0xED, 0xA1, 0xFF, 0xFF, // cpi
   'c','p','i',0,
   2, 0xED, 0xA2, 0xFF, 0xFF, // ini
   'i','n','i',0,
   2, 0xED, 0xA3, 0xFF, 0xFF, // outi
   'o','u','t','i',0,
   2, 0xED, 0xA8, 0xFF, 0xFF, // ldd
   'l','d','d',0,
   2, 0xED, 0xA9, 0xFF, 0xFF, // cpd
   'c','p','d',0,
   2, 0xED, 0xAA, 0xFF, 0xFF, // ind
   'i','n','d',0,
   2, 0xED, 0xAB, 0xFF, 0xFF, // outd
   'o','u','t','d',0,

   2, 0xED, 0xB0, 0xFF, 0xFF, // ldir
   'l','d','i','r',0,
   2, 0xED, 0xB1, 0xFF, 0xFF, // cpir
   'c','p','i','r',0,
   2, 0xED, 0xB2, 0xFF, 0xFF, // inir
   'i','n','i','r',0,
   2, 0xED, 0xB3, 0xFF, 0xFF, // otir
   'o','t','i','r',0,
   2, 0xED, 0xB8, 0xFF, 0xFF, // lddr
   'l','d','d','r',0,
   2, 0xED, 0xB9, 0xFF, 0xFF, // cpdr
   'c','p','d','r',0,
   2, 0xED, 0xBA, 0xFF, 0xFF, // indr
   'i','n','d','r',0,
   2, 0xED, 0xBB, 0xFF, 0xFF, // otdr
   'o','t','d','r',0,

   2, 0xED, 0x00, 0xFF, 0x00, // all others 'ED'
   'n','o','p','*',0,

   // place immediates after all - 'ld a,b' is not 'ld a,0B'
   1, 0x01, 0xCF, // ld r16,imm16
   _ld, _zr16, ',', _iw, 0,
   1, 0x06, 0xC7, // ld r8, imm8
   _ld, _zr8, ',', _ib, 0,

   0 // end
};
