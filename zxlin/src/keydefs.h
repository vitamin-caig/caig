/***************************************************************************
 *   Copyright (C) 2006 by vitaly   *
 *   vitamin@vitamin   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

struct KeyDef
{
    int value;
    char name[16];
};

const KeyDef PCKeys[] = {
//ESC F1 F2 F3 F4 F5 F6 F7 F8 F9 F10 F11 F12
    {SDLK_ESCAPE, "ESC"}, {SDLK_F1, "F1"}, {SDLK_F2, "F2"}, {SDLK_F3, "F3"}, {SDLK_F4, "F4"},
    {SDLK_F5, "F5"}, {SDLK_F6, "F6"}, {SDLK_F7, "F7"}, {SDLK_F8, "F8"}, {SDLK_F9, "F9"},
    {SDLK_F10, "F10"}, {SDLK_F11, "F11"}, {SDLK_F12, "F12"},
//TIL 1 2 3 4 5 6 7 8 9 0 MINUS PLUS BACKSL BACK  PRSCR SCLOCK PAUSE NUMLOCK GRDIV GRMUL GRSUB
    {SDLK_BACKQUOTE, "TIL"}, {SDLK_1, "1"}, {SDLK_2, "2"}, {SDLK_3, "3"}, {SDLK_4, "4"},
    {SDLK_5, "5"}, {SDLK_6, "6"}, {SDLK_7, "7"}, {SDLK_8, "8"}, {SDLK_9, "9"}, {SDLK_0, "0"},
    {SDLK_MINUS, "MINUS"}, {SDLK_EQUALS, "PLUS"}, {SDLK_BACKSLASH, "BACKSL"},
    {SDLK_BACKSPACE, "BACK"}, {SDLK_PRINT, "PRSCR"}, {SDLK_SCROLLOCK, "SCLOCK"},
    {SDLK_PAUSE, "PAUSE"}, {SDLK_NUMLOCK, "NUMLOCK"}, {SDLK_KP_DIVIDE, "GRDIV"},
    {SDLK_KP_MULTIPLY, "GRMUL"}, {SDLK_KP_MINUS, "GRSUB"},
//TAB Q W E R T Y U I O P LB RB INS HOME PGUP N7 N8 N9 GRADD
    {SDLK_TAB, "TAB"}, {SDLK_q, "Q"}, {SDLK_w, "W"}, {SDLK_e, "E"}, {SDLK_r, "R"},
    {SDLK_t, "T"}, {SDLK_y, "Y"}, {SDLK_u, "U"}, {SDLK_i, "I"}, {SDLK_o, "O"}, {SDLK_p, "P"},
    {SDLK_LEFTBRACKET, "LB"}, {SDLK_RIGHTBRACKET, "RB"}, {SDLK_INSERT, "INS"},
    {SDLK_HOME, "HOME"}, {SDLK_PAGEUP, "PGUP"}, {SDLK_KP7, "N7"}, {SDLK_KP8, "N8"},
    {SDLK_KP9, "N9"}, {SDLK_KP_PLUS, "GRADD"},
//CAPS A S D F G H J K L COL QUOTE ENTER DEL END PGDN N4 N5 N6
    {SDLK_CAPSLOCK, "CAPS"}, {SDLK_a, "A"}, {SDLK_s, "S"}, {SDLK_d, "D"}, {SDLK_f, "F"},              {SDLK_g, "G"},  {SDLK_h, "H"},  {SDLK_j, "J"},
    {SDLK_k, "K"}, {SDLK_l, "L"}, {SDLK_SEMICOLON, "COL"}, {SDLK_QUOTE, "QUOTE"},
    {SDLK_RETURN, "ENTER"}, {SDLK_DELETE, "DEL"}, {SDLK_END, "END"}, {SDLK_PAGEDOWN, "PGDN"},
    {SDLK_KP4, "N4"}, {SDLK_KP5, "N5"}, {SDLK_KP6, "N6"},
//LSHIFT Z X C V B N M COMMA POINT SLASH RSHIFT UP N1 N2 N3 GRENTER
    {SDLK_LSHIFT, "LSHIFT"}, {SDLK_z, "Z"}, {SDLK_x, "X"}, {SDLK_c, "C"}, {SDLK_v, "V"},
    {SDLK_b, "B"}, {SDLK_n, "N"}, {SDLK_m, "M"}, {SDLK_COMMA, "COMMA"},
    {SDLK_PERIOD, "POINT"}, {SDLK_SLASH, "SLASH"}, {SDLK_RSHIFT, "RSHIFT"}, {SDLK_UP, "UP"},
    {SDLK_KP1, "N1"}, {SDLK_KP2, "N2"}, {SDLK_KP3, "N3"}, {SDLK_KP_ENTER, "GRENTER"},
//LCONTROL LWIN LALT SPACE RALT RWIN RCONTROL LEFT DOWN RIGHT N0 NP
    {SDLK_LCTRL, "LCONTROL"}, {SDLK_LSUPER, "LWIN"}, {SDLK_LALT, "LALT"},
    {SDLK_SPACE, "SPACE"}, {SDLK_RALT, "RALT"}, {SDLK_RSUPER, "RWIN"},
    {SDLK_RCTRL, "RCONTROL"}, {SDLK_LEFT, "LEFT"}, {SDLK_DOWN, "DOWN"}, {SDLK_RIGHT, "RIGHT"},
    {SDLK_KP0, "N0"}, {SDLK_KP_PERIOD, "NP"},
//groupped
    {-SDLK_LCTRL, "CONTROL"}, {-SDLK_LALT, "ALT"}, {-SDLK_LSUPER, "WIN"},
    {-SDLK_LSHIFT, "SHIFT"},
    {-1, ""}
};

/****************
ZX_KEYS:
 1  2  3  4  5  6  7  8  9  0
 Q  W  E  R  T  Y  U  I  O  P
 A  S  D  F  G  H  J  K  L ENT
CAP Z  X  C  V  B  N  M SYM SPC
KLEFT, KRIGHT, KUP, KDOWN, KFIRE
*****************************/

const KeyDef ZXKeys[] = {
    {ZX_1, "1"}, {ZX_2, "2"}, {ZX_3, "3"}, {ZX_4, "4"}, {ZX_5, "5"},
    {ZX_6, "6"}, {ZX_7, "7"}, {ZX_8, "8"}, {ZX_9, "9"}, {ZX_0, "0"},
    {ZX_Q, "Q"}, {ZX_W, "W"}, {ZX_E, "E"}, {ZX_R, "R"}, {ZX_T, "T"},
    {ZX_Y, "Y"}, {ZX_U, "U"}, {ZX_I, "I"}, {ZX_O, "O"}, {ZX_P, "P"},
    {ZX_A, "A"}, {ZX_S, "S"}, {ZX_D, "D"}, {ZX_F, "F"}, {ZX_G, "G"},
    {ZX_H, "H"}, {ZX_J, "J"}, {ZX_K, "K"}, {ZX_L, "L"}, {ZX_EN, "ENT"},
    {ZX_CS, "CAP"}, {ZX_Z, "Z"}, {ZX_X, "X"}, {ZX_C, "C"}, {ZX_V, "V"},
    {ZX_B, "B"}, {ZX_N, "N"}, {ZX_M, "M"}, {ZX_SS, "SYM"}, {ZX_SP, "SPC"},
    {ZX_KLEFT, "KLEFT"}, {ZX_KRIGHT, "KRIGHT"}, {ZX_KUP, "KUP"}, {ZX_KDOWN, "KDOWN"},
    {ZX_KFIRE, "KFIRE"},
    {-1, ""}
};
