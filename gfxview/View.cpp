// View.cpp: implementation of the CView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "View.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern int iFilter;
extern int iFit;
extern int iScale;
extern int iBright;
extern DWORD dwCols[16];

CView::CView(BYTE* pData, int iBytes)
{
	m_pData = new BYTE[iBytes];
	memcpy(m_pData, pData, iBytes);
	m_iMode = m_iPhase = 0;

	m_pBitmap = new DWORD[49152 + 513];
	memset(m_pBitmap, 0, (49152 + 513) * sizeof(DWORD));

	m_biBitmap.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_biBitmap.bmiHeader.biWidth = 256;
	m_biBitmap.bmiHeader.biHeight = 192;
	m_biBitmap.bmiHeader.biPlanes = 1;
	m_biBitmap.bmiHeader.biBitCount = 32;
	m_biBitmap.bmiHeader.biCompression = BI_RGB;
	m_biBitmap.bmiHeader.biSizeImage = 49152 * sizeof(DWORD);
	m_biBitmap.bmiHeader.biXPelsPerMeter = 10000;
	m_biBitmap.bmiHeader.biYPelsPerMeter = 10000;
	m_biBitmap.bmiHeader.biClrUsed = 0;
	m_biBitmap.bmiHeader.biClrImportant = 0;

	m_pScaled = NULL;
	Invalidate();
}

void CView::Render()
{
BYTE* pSrc = m_pData;
DWORD* pDst = m_pBitmap;
int iPhs = m_iPhase;

	_asm
	{
		mov esi, pSrc
		mov edi, pDst
		add edi, (49152 - 256) * 4
		xor ebx, ebx
		mov ecx, 6144
		xor edx, edx
		mov ah, 0x80	//mask
		mov al, BYTE PTR iPhs
		and al, 1
		ror al, 1
line:
		push ebx
		push ecx
nexby:	
		test [esi + ebx], ah
		mov dl, [esi + ecx]
		jz paper
		test al, dl
		jnz paper_
ink_:	and dl, 7
		jnc geco
paper:	test al, dl
		jnz ink_
paper_:	and dl, 56
		ror dl, 3
geco:	test [esi + ecx], 64
		jz nobr
		or dl, 8
nobr:	push DWORD PTR dwCols[edx * 4]
		pop DWORD PTR [edi]
		add edi, 4
		ror ah, 1
		jnc nexby
		inc ecx
		inc ebx
		test bl, 31
		jnz nexby
		pop ecx
		pop ebx
		sub edi, 512 * 4
		inc bh
		test bh, 7
		jnz line
		add ecx, 32
		add bl, 32
		jc addok
		sub bh, 8
addok:	cmp bh, 0x18
		jc line
	}
}

void CView::Invalidate()
{
	m_biScaled.bmiHeader.biWidth = m_biScaled.bmiHeader.biHeight = 0;
}

void CView::Draw(HDC hDC, int iXDest, int iYDest)
{
int iX;
int iY;

	if (::iFit)
	{
		if (4 * iYDest >= 3 * iXDest)
		{
			iY = (iYDest - iXDest * 3 / 4) / 2;
			iYDest = iXDest * 3 / 4;
			iX = 0;
		}
		else
		{
			iX = (iXDest - iYDest * 4 / 3) / 2;
			iXDest = iYDest * 4 / 3;
			iY = 0;
		}
	}
	else
	{
		iX = (iXDest - 256 * iScale / 100) / 2;
		iY = (iYDest - 192 * iScale / 100) / 2;
		iXDest = 256 * iScale / 100;
		iYDest = 192 * iScale / 100;
	}

	if (::iFilter)
	{
		if ((iXDest != m_biScaled.bmiHeader.biWidth) || (iYDest != m_biScaled.bmiHeader.biHeight))
			_Scale(iXDest, iYDest);
		::SetDIBitsToDevice(hDC, iX, iY, iXDest, iYDest, 0, 0, 0, iYDest, m_pScaled, &m_biScaled, DIB_RGB_COLORS);
	}
	else
		::StretchDIBits(hDC, iX, iY, iXDest, iYDest, 0, 0, 256, 192, m_pBitmap, &m_biBitmap, DIB_RGB_COLORS, SRCCOPY);
}

int CView::Animate()
{
	if (! _HasAnimation()) return 0;
	m_iPhase ^= 1;
	Render();
	return 1;
}

int CView::_HasAnimation()
{
int iFlg = 0;
	for (int i = 0; i < 768; i++)
		iFlg |= m_pData[6144 + i];
	return iFlg & 128;
}


void CView::_Scale(int iXTo, int iYTo)
{
	if (m_pScaled) delete[] m_pScaled;

	m_pScaled = new DWORD[iXTo * iYTo];

	m_biScaled.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_biScaled.bmiHeader.biWidth = iXTo;
	m_biScaled.bmiHeader.biHeight = iYTo;
	m_biScaled.bmiHeader.biPlanes = 1;
	m_biScaled.bmiHeader.biBitCount = 32;
	m_biScaled.bmiHeader.biCompression = BI_RGB;
	m_biScaled.bmiHeader.biSizeImage = iXTo * iYTo * sizeof(DWORD);
	m_biScaled.bmiHeader.biXPelsPerMeter = 10000;
	m_biScaled.bmiHeader.biYPelsPerMeter = 10000;
	m_biScaled.bmiHeader.biClrUsed = 0;
	m_biScaled.bmiHeader.biClrImportant = 0;

	int stepx = 0x100000 / iXTo;
	int stepy = 0xc0000 / iYTo;
	if (stepx * iXTo != 0x100000) stepx++;
	if (stepy * iYTo != 0xc0000) stepy++;
	int iX = 0, iY = 0;
	DWORD* pFrom = NULL;
	DWORD* pTo = m_pScaled;
	for (int y = 0; y < iYTo; y++)
	{
		pFrom = m_pBitmap + ((iY & 0xff000) >> 4);
		iX = 0;
		for (int x = 0; x < iXTo; x++)
		{
			int xt = iX >> 12;
			DWORD lu = pFrom[xt];
			DWORD ru = pFrom[xt + 1];
			DWORD ld = pFrom[xt + 0x100];
			DWORD rd = pFrom[xt + 0x101];
			if (xt == 0xff) ru = lu, rd = ld;
			if ((iY >> 12) == 0xbf) ld = lu, rd = ru;

			DWORD col = 0;
			for (int i = 0; i < 3; i++)
			{
				BYTE l = BYTE((lu & 0xff) + ((int(ld & 0xff) - (lu & 0xff)) * (iY & 0xfff) >> 12));
				BYTE r = BYTE((ru & 0xff) + ((int(rd & 0xff) - (ru & 0xff)) * (iY & 0xfff) >> 12));
				col |= (l + ((int(r) - l) * (iX & 0xfff) >> 12)) << (i * 8);
				lu >>= 8;
				ru >>= 8;
				ld >>= 8;
				rd >>= 8;
			}
			*pTo++ = col;
			iX += stepx;
		}
		iY += stepy;
	}
}

void CView::Invert()
{
DWORD* pDat = (DWORD*)m_pData;
	for (int i = 0; i < 1536; i++)
		pDat[i] = ~pDat[i];
}


void CView::Save(const char* szFileName)
{
HANDLE hFile = CreateFile(szFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
							FILE_FLAG_SEQUENTIAL_SCAN, NULL);
BITMAPFILEHEADER bfh;
DWORD tmp = 0;

	memset(&bfh, 0, sizeof(bfh));
	bfh.bfType = 0x4d42;
	bfh.bfOffBits = sizeof(bfh) + sizeof(m_biBitmap);
	bfh.bfSize = bfh.bfOffBits + 49152 * 4;

	WriteFile(hFile, &bfh, sizeof(bfh), &tmp, NULL);
	WriteFile(hFile, &m_biBitmap, sizeof(m_biBitmap), &tmp, NULL);
	WriteFile(hFile, m_pBitmap, 49152 * 4, &tmp, NULL);
	CloseHandle(hFile);
}

//-----------------

CScrView::CScrView(BYTE* pData) : CView(pData, 6912)
{
	CView::Render();
}

int CScrView::Animate()
{
	if (! _HasAnimation()) return 0;
	m_iPhase ^= 1;
	m_iMode ? Render() : CView::Render();
	return 1;
}


void CScrView::NextMode()
{
	if (! m_iMode)
	{
		m_iMode = 1;
		Render();
	}
}

void CScrView::PrewMode()
{
	if (m_iMode)
	{
		m_iMode = 0;
		CView::Render();
	}
}

void CScrView::Render()
{
BYTE* pSrc = m_pData;
DWORD* pDst = m_pBitmap;
int iPhs = m_iPhase;

	_asm
	{
		mov esi, pSrc
		mov edi, pDst
		add edi, (49152 - 256) * 4
		xor ebx, ebx
		mov ecx, 6144
		xor edx, edx
		mov ah, 0x80	//mask
		mov al, BYTE PTR iPhs
		and al, 1
		ror al, 1
line:
		push ecx
nexby:	
		test [esi + ebx], ah
		mov dl, [esi + ecx]
		jz paper
		test al, dl
		jnz paper_
ink_:	and dl, 7
		jnc geco
paper:	test al, dl
		jnz ink_
paper_:	and dl, 56
		ror dl, 3
geco:	test [esi + ecx], 64
		jz nobr
		or dl, 8
nobr:	push DWORD PTR dwCols[edx * 4]
		pop DWORD PTR [edi]
		add edi, 4
		ror ah, 1
		jnc nexby
		inc ecx
		inc ebx
		test bl, 31
		jnz nexby
		pop ecx
		sub edi, 512 * 4
		test bl, bl
		jnz line
		add ecx, 32
		cmp bh, 0x18
		jc line
	}
}


//-------------------

CDblView::CDblView(BYTE* pData) : CView(pData, 13824)
{
	Render();
}

void CDblView::Render()
{
BYTE* pSrc = m_pData;
DWORD* pDst = m_pBitmap;
int iPhs = m_iPhase;

	_asm
	{
		mov esi, pSrc
		mov edi, pDst
		add edi, (49152 - 256) * 4
		xor ebx, ebx
		mov ecx, 6144
		xor edx, edx
		push edi
		mov ah, 0x80	//mask
		mov al, BYTE PTR iPhs
		and al, 1
		ror al, 1
		call render
		pop edi
		xor ebx, ebx
		mov ecx, 6144
		add esi, 6912
		call render
	}
	return;

	_asm
	{
render:
line:
		push ebx
		push ecx
nexby:	test [esi + ebx], ah
		mov dl,[esi + ecx]
		jz paper
		test al, dl
		jnz paper_
ink_:	and dl, 7
		jnc geco
paper:	test al, dl
		jnz ink_
paper_:	and dl, 56
		ror dl, 3
geco:	test [esi + ecx], 64
		jz nobr
		or dl, 8
nobr:	cmp esi, pSrc
		jz move
		push ax
		mov al, BYTE PTR dwCols[edx * 4]
		add al, BYTE PTR [edi]
		rcr al, 1
		mov BYTE PTR [edi], al

		mov al, BYTE PTR dwCols[edx * 4 + 1]
		add al, BYTE PTR [edi + 1]
		rcr al, 1
		mov BYTE PTR [edi + 1], al

		mov al, BYTE PTR dwCols[edx * 4 + 2]
		add al, BYTE PTR [edi + 2]
		rcr al, 1
		mov BYTE PTR [edi + 2], al

		pop ax
		jmp short mova

move:	push DWORD PTR dwCols[edx * 4]
		pop DWORD PTR [edi]
mova:	add edi, 4
		ror ah, 1
		jnc nexby
		inc ecx
		inc ebx
		test bl, 31
		jnz nexby
		pop ecx
		pop ebx
		sub edi, 512 * 4
		inc bh
		test bh, 7
		jnz line
		add ecx, 32
		add bl, 32
		jc addok
		sub bh, 8
addok:	cmp bh, 0x18
		jc line
		ret
	}
}

void CDblView::Invert()
{
	CView::Invert();
DWORD* pDat = (DWORD*)(m_pData + 6912);
	for (int i = 0; i < 1536; i++)
		pDat[i] = ~pDat[i];
}

int CDblView::_HasAnimation()
{
int iFlg = 0;
	for (int i = 0; i < 768; i++)
		iFlg |= m_pData[6144 + i] | m_pData[6912 + 6144 + i];
	return iFlg & 128;
}

//--------------

CTriView::CTriView(BYTE* pData) : CView(pData, 18432)
{
	Render();
}

void CTriView::Render()
{
BYTE* pSrc = m_pData;
DWORD* pDst = m_pBitmap;

	memset(m_pBitmap, 0, 4 * 49152);
	_asm
	{
		mov esi, pSrc
		mov edi, pDst
		add edi, (49152 - 256) * 4
		xor ebx, ebx
		mov ecx, 2
		xor edx, edx
		mov ah, 0x80	//mask
		push edi
		call line
		pop edi
		add ecx, ecx
		add esi, 6144
		xor ebx, ebx
		push edi
		call line
		pop edi
		mov ecx, 1
		add esi, 6144
		xor ebx, ebx
		call line

		mov ecx, 49152
		lea esi, dwCols
		mov edi, pDst
decod:	mov eax, [edi]
		or eax, iBright
		mov eax, [esi + eax * 4]
		mov [edi], eax
		add edi, 4
		loop decod
	}
	return;

	_asm
	{
line:
		push ebx
nexby:	test [esi + ebx], ah
		jz nodot
		or DWORD PTR [edi], ecx
nodot:	add edi, 4
		ror ah, 1
		jnc nexby
		inc ebx
		test bl, 31
		jnz nexby
		pop ebx
		sub edi, 512 * 4
		inc bh
		test bh, 7
		jnz line
		add bl, 32
		jc addok
		sub bh, 8
addok:	cmp bh, 0x18
		jc line
		ret
	}
}

int CTriView::Animate()
{
	return 0;
}

void CTriView::Invert()
{
DWORD* pDat = (DWORD*)m_pData;
	for (int i = 0; i < 1536 * 3; i++)
		pDat[i] = ~pDat[i];
}

int CTriView::_HasAnimation()
{
	return 0;
}

//---------------

CFontView::CFontView(BYTE* pData) : CView(pData, 6912)
{
	for (int i = 0; i < 2048; i++)
		m_pData[4096 + (i >> 3) + 256 * (i & 7)] = m_pData[i];
	memset(m_pData + 2048, 0, 2048);
	memset(m_pData + 6144, 7 + 64, 768);
	Render();
}

int CFontView::Animate()
{
	return 0;
}

int CFontView::_HasAnimation()
{
	return 0;
}

//--------------------------------

C8colView::C8colView(BYTE* pData) : CView(pData, 6144 * 3)
{
	_Depack(pData);
	Render();
}

void C8colView::Render()
{
BYTE* pSrc = m_pData;
DWORD* pDst = m_pBitmap;

	memset(m_pBitmap, 0, 4 * 49152);
	_asm
	{
		mov esi, pSrc
		mov edi, pDst
		add edi, (49152 - 256) * 4
		mov ecx, 2
		xor ebx, ebx
		mov ah, 0x80
		push edi
		call render
		pop edi
		add ecx, ecx
		add esi, ebx
		xor ebx, ebx
		push edi
		call render
		pop edi
		mov ecx, 1
		add esi, ebx
		xor ebx, ebx
		call render

		mov ecx, 49152
		lea esi, dwCols
		mov edi, pDst
decod:	mov eax, [edi]
		or eax, iBright
		mov eax, [esi + eax * 4]
		mov [edi], eax
		add edi, 4
		loop decod
	}
	return;

	_asm
	{
render:
		test [esi + ebx], ah
		jz nopix
		or DWORD PTR [edi], ecx
nopix:	add edi, 4
		ror ah, 1
		jnc render
		inc ebx
		test bl, 31
		jnz render
		sub edi, 512 * 4
		cmp ebx, 6144
		jc render
		ret
	}
}


void C8colView::_Depack(BYTE* pData)
{
BYTE dwPalette[8];
BYTE* pDat = m_pData;
BYTE lx[4];
	_asm
	{
        mov esi, pData
        mov bx, 0x180
		mov edi, pDat
		xor eax, eax
		lea edx, dwPalette
dep:
        call dep3
		jz juzn
		call oldcl
		jmp short colqq

juzn:
        mov ecx, 8		// zero, copy all colors
col80:	mov ax, [esi]
		mov [edi], al
		mov [edi + 6144], ah
		mov al, [esi + 2]
		mov [edi + 12288], al
		add edi, 32		// next line
        add esi, 3
        loop col80
colqq:					
		inc edi
        mov eax, edi
		sub eax, pDat
		test eax, 0x1f
		jnz okbyt
		sub edi, 32
		jnz juzz
okbyt:	sub edi, 256
		dec ah
juzz:	cmp ah, 24
		jc dep
	}
	return;

	_asm
	{
chl:	mov bl, [esi]
		inc esi
		rcl bl, 1
		ret

oldcl:
		dec al
		jz colold
		xor ecx, ecx
		mov cl, al
		mov lx, al
deptab:	call dep3
		dec cl
		mov [edx + ecx], al
		jnz deptab
colold:
		mov al, lx
		mov ecx, 64	//####
		cmp al, 4
		jnc col450
		dec al
		jz col1
		dec al
		jz col2
col3:
		mov al, 0x80
		call depcol0
		jz col3n1
		sal bl, 1
		jnz noch1
		call chl
noch1:
		rcl al, 1
		dec al
col3n1:	call putcol
		loop col3
		ret

col2:	mov al, 0x80
		call depcol0
		call putcol
		loop col2
		ret

col450:
		jz col4
		rcr al, 1
		jc col5
col6:
		mov al, 0x40
		call depcol0
		cmp al, 2
		jc col6n1
		dec al
		sal bl, 1
		jnz noch2
		call chl
noch2:	
		rcl al, 1
col6n1:
		call putcol
		loop col6
		ret

col5:
		mov al, 0x40
		call depcol0
		cmp al, 3
		jc col5n1
		sal bl, 1
		jnz noch3
		call chl
noch3:	rcl al, 1
		sub al, 3
col5n1:	call putcol
		loop col5
		ret

col4:	mov al, 0x40
		call depcol0
		call putcol
		loop col4
		ret

col1:
		mov al, [edx]	// old color from palete
		xor ah, ah
		rcr al, 1
		jnc noR
		not ah
noR:	xor cx, cx
		rcr al, 1
		jnc noG
		not ch
noG:	rcr al, 1
		jnc noB
		not cl
noB:	
		mov al, 8
filzz:	mov [edi + 6144], ah
		mov [edi + 12288], cl
		mov [edi], ch
		add edi, 32
		dec al
		jnz filzz
		ret

putcol:
		xor ah, ah
		mov al, [edx + eax]
		rcr al, 1
		rcl BYTE PTR [edi + 12288], 1
		rcr al, 1
		rcl BYTE PTR [edi], 1
		rcr al, 1
		rcl BYTE PTR [edi + 6144], 1
		rol bh, 1
		jnc noaa
		add edi, 32
noaa:	ret

dep3:	mov al, 0x20
depcol0:
		sal bl, 1
		jnz noch4
		call chl
noch4:	adc al, al
		jnc depcol0
		ret
}
}

int C8colView::Animate()
{
	return 0;
}

void C8colView::Invert()
{
DWORD* pDat = (DWORD*)m_pData;
	for (int i = 0; i < 1536 * 3; i++)
		pDat[i] = ~pDat[i];
}

int C8colView::_HasAnimation()
{
	return 0;
}

//--------------------------------

CLCView::CLCView(BYTE* pData) : CView(pData, 6912)
{
	_Depack(pData);
	Render();
}

void CLCView::_Depack(BYTE* pData)
{
BYTE* pDat = m_pData;
BYTE hx = 0;
BYTE lx = 0;
BYTE off = 0;

	memset(pDat + 6144, 7 + 64, 768);
	_asm
	{
		mov esi, pData
		mov edi, pDat
		xor edx, edx	//de'de
		xor ecx, ecx	//bc+other
		xor ebx, ebx	//hl'
		xor eax, eax

		cmp DWORD PTR [esi], 0x504d434c
		jz nodepc
		mov dh, [esi + 2]		//to
		mov al, [esi + 0x60]	//counter
		mov hx, al
		mov al, [esi + 0x91]
		mov off, al
		add esi, 0x9a	//depacker exists
		jmp short dlc1_
nodepc:
		mov al, [esi + 7]
		add al, 8
		add esi, eax
		mov dh, [esi]
		mov al, dh
		mov off, al
		and dh, 3
		shl dh, 3
		or dh, 0x40

		xor al, 0x40+0x18
		and al, 0xfc
		mov hx, al
		inc esi

dlc1_:
		rol edx, 16

dlc1:	mov al, [esi]
        inc esi
        mov lx, 0xff
dlc2:	

		pushf
		rol edx, 16
		popf

		jnz dlc10		//jump in first time, then pass
		mov ch, 1
dlc3:
		lahf
		rol eax, 16
		sahf

		sal dh, 1
		inc dh
		dec dh
		jnz s6
		mov dh, [esi]
		inc esi
		stc
		rcl dh, 1
s6:		dec ch
		jnz dlc7
		jc dlc1

		inc ch

dlc4:
		mov cl, 01010110b
		mov al, 0xfe
dlc5:	
		sal dh, 1
		inc dh
		dec dh
		jnz s6_
		mov dh, [esi]
		inc esi
		rcl dh, 1
s6_:	rcl al, 1
		sal cl, 1
		inc cl
		dec cl
		jz dlc6
		jc dlc5
		ror al, 1
		jnc dlc5
		sub al, 8
dlc6:
		add al, 9
		dec ch
		jnz dlc3

		cmp al, 0-8+1
		jnz s4_
		mov al, [esi]
		inc esi
s4_:		
		adc al, 0xff
		mov lx, al
		jc dlc4
reter:
	}
	return;

	_asm
	{
//---------

dlc7:	mov al, [esi]
		inc esi

		pushf
		rol edx, 16
		popf

		mov bl, al

		lahf
		rol eax, 16
		sahf

		mov bh, al

		add bx, dx

		cmp al, 0xff-2
		jnc dlc8
		dec lx

dlc8:
		mov al, bh		//hl'
		cmp al, hx
		jnc dlc13
		xor al, bl
		and al, 0xf8
		xor al, bl
		mov ch, al
		xor al, bl
		xor al, bh
		rol al, 2
		mov cl, al
dlc9:

		lahf
		rol eax, 16
		sahf

		mov al, [edi + ecx - 0x4000]
dlc10:

		lahf
		rol eax, 16
		sahf

		mov al, dh	//de'
		cmp al, hx
		jnc dlc14
		xor al, dl
		and al, 0xf8
		xor al, dl
		mov ch, al
		xor al, dl
		xor al, dh
		rol al, 2
		mov cl, al

dlc11:	

		lahf
		rol eax, 16

		and ecx, 0x1fff
		cmp ch, 0x1b
		jnc reter
		mov [edi + ecx], al
		inc dx
		sahf

		jnc s4		///
		dec bx
		dec bx
s4:		inc bx
					//exa

		lahf
		rol eax, 16
		sahf

		inc lx
		jnz dlc8
		jz dlc2		

dlc13:
		stc
dlc14:
		pushf
		push ax
		add al, off
		mov ch, al
		pop ax
		popf
		mov cl, dl
		jnc dlc11
		mov cl, bl
		jc dlc9
	}
}
		
//------------------

CBitView::CBitView(BYTE* pData) : CView(pData, 6912)
{
	m_pSrc = new BYTE[16384];
	memcpy(m_pSrc, pData, 16384);
	_Depack(0);
	Render();
}

void CBitView::_Depack(DWORD iSprite)
{
	memset(m_pData, 0, 6144);
	memset(m_pData + 6144, 7 + 64, 768);

BYTE* pDat = m_pData;
BYTE* pSrc = m_pSrc;

	_asm
	{
		mov esi, pSrc
		mov edi, pDat
		xor edx, edx
		mov eax, iSprite
		mov cx, [esi + eax * 4 + 8]
		cmp cl, 33
		jnc neshow
		cmp ch, 25
		jnc neshow
		mov ax, [esi + eax * 4 + 10]
		mov bh, ah
		and ax, 0x3fff
		add esi, eax
	
depall:
		push dx
		push cx
depline:		
		xor bl, bl		//diff
		xor al, al		//data
		mov ah, [esi]	//mask
		inc esi

depc1:	rcr ah, 1
		jnc oldi
		mov bl, [esi]
		inc esi
oldi:
		xor al, bl
		mov [edi + edx], al
		inc dh
		test dh, 7
		jnz depc1
		sub dh, 8
		test bh, 128
		jz noattr
		push dx
		and dh, 0x18
		ror dh, 3
		or dh, 0x18
		mov al, [esi]
		inc esi
		mov [edi + edx], al
		pop dx
noattr:
		inc dl
		dec cl
		jnz depline
		pop cx
		pop dx
		add dl, 32
		jnc noaddh
		add dh, 8
noaddh:	dec ch
		jnz depall
neshow:
	}
}

void CBitView::NextMode()
{
	if (m_iMode < m_pSrc[3] - 1)
	{
		_Depack(++m_iMode);
		Render();
	}
}

void CBitView::PrewMode()
{
	if (m_iMode > 0)
	{
		_Depack(--m_iMode);
		Render();
	}
}

//-----------------

CChunkView::CChunkView(BYTE* pData) : CView(pData, 6912)
{
	m_pSrc = new BYTE[1536];
	memcpy(m_pSrc, pData, 1536);
	_Depack(m_pSrc);
	Render();
}

void CChunkView::NextMode()
{
	if (! m_iMode)
	{
		m_iMode = 1;
		_Rot();
		_Depack(m_pSrc);
		Render();
	}
}

void CChunkView::PrewMode()
{
	if (m_iMode)
	{
		m_iMode = 0;
		_Rot();
		_Depack(m_pSrc);
		Render();
	}
}

void CChunkView::_Rot()
{
BYTE* pByt = m_pSrc;

	_asm
	{
		mov esi, pByt
		mov ecx, 1536
rota:	ror BYTE PTR [esi], 4
		inc esi
		loop rota
	}
}

void CChunkView::_Depack(BYTE* pData)
{
static const BYTE bChunk[1024] = {
	0,0,0,0,8,0,0,0, 8,0,2,0,8,0,10,0, 10,0,10,0,10,4,10,0, 10,4,10,1,10,4,10,5,
	10,5,10,5,10,5,11,5, 14,5,11,5,15,5,11,5, 15,5,15,5,15,7,15,5, 15,7,15,13,15,15,15,15,

	128,0,0,0,136,0,0,0, 136,0,2,0,136,0,10,0, 138,0,10,0,138,4,10,0, 138,4,10,1,138,4,10,5,
	138,5,10,5,138,5,11,5, 142,5,11,5,143,5,11,5, 143,5,15,5,143,7,15,5, 143,7,15,13,143,15,15,15,

	128,0,32,0,136,0,32,0, 136,0,34,0,136,0,42,0, 138,0,42,0,138,4,42,0, 138,4,42,1,138,4,42,5,
	138,5,42,5,138,5,43,5, 142,5,43,5,143,5,43,5, 143,5,47,5,143,7,47,5, 143,7,47,13,143,15,47,15,

	128,0,160,0,136,0,160,0, 136,0,162,0,136,0,170,0, 138,0,170,0,138,4,170,0, 138,4,170,1,138,4,170,5,
	138,5,170,5,138,5,171,5, 142,5,171,5,143,5,171,5, 143,5,175,5,143,7,175,5, 143,7,175,13,143,15,175,15,

	160,0,160,0,168,0,160,0, 168,0,162,0,168,0,170,0, 170,0,170,0,170,4,170,0, 170,4,170,1,170,4,170,5,
	170,5,170,5,170,5,171,5, 174,5,171,5,175,5,171,5, 175,5,175,5,175,7,175,5, 175,7,175,13,175,15,175,15,

	160,64,160,0,168,64,160,0, 168,64,162,0,168,64,170,0, 170,64,170,0,170,68,170,0, 170,68,170,1,170,68,170,5,
	170,69,170,5,170,69,171,5, 174,69,171,5,175,69,171,5, 175,69,175,5,175,71,175,5, 175,71,175,13,175,79,175,15,

	160,64,160,16,168,64,160,16, 168,64,162,16,168,64,170,16, 170,64,170,16,170,68,170,16, 170,68,170,17,170,68,170,21,
	170,69,170,21,170,69,171,21, 174,69,171,21,175,69,171,21, 175,69,175,21,175,71,175,21, 175,71,175,29,175,79,175,31,

	160,64,160,80,168,64,160,80, 168,64,162,80,168,64,170,80, 170,64,170,80,170,68,170,80, 170,68,170,81,170,68,170,85,
	170,69,170,85,170,69,171,85, 174,69,171,85,175,69,171,85, 175,69,175,85,175,71,175,85, 175,71,175,93,175,79,175,95,

	160,80,160,80,168,80,160,80, 168,80,162,80,168,80,170,80, 170,80,170,80,170,84,170,80, 170,84,170,81,170,84,170,85,
	170,85,170,85,170,85,171,85, 174,85,171,85,175,85,171,85, 175,85,175,85,175,87,175,85, 175,87,175,93,175,95,175,95,

	160,80,176,80,168,80,176,80, 168,80,178,80,168,80,186,80, 170,80,186,80,170,84,186,80, 170,84,186,81,170,84,186,85,
	170,85,186,85,170,85,187,85, 174,85,187,85,175,85,187,85, 175,85,191,85,175,87,191,85, 175,87,191,93,175,95,191,95,
	
	224,80,176,80,232,80,176,80, 232,80,178,80,232,80,186,80, 234,80,186,80,234,84,186,80, 234,84,186,81,234,84,186,85,
	234,85,186,85,234,85,187,85, 238,85,187,85,239,85,187,85, 239,85,191,85,239,87,191,85, 239,87,191,93,239,95,191,95,

	240,80,176,80,248,80,176,80, 248,80,178,80,248,80,186,80, 250,80,186,80,250,84,186,80, 250,84,186,81,250,84,186,85,
	250,85,186,85,250,85,187,85, 254,85,187,85,255,85,187,85, 255,85,191,85,255,87,191,85, 255,87,191,93,255,95,191,95,

	240,80,240,80,248,80,240,80, 248,80,242,80,248,80,250,80, 250,80,250,80,250,84,250,80, 250,84,250,81,250,84,250,85,
	250,85,250,85,250,85,251,85, 254,85,251,85,255,85,251,85, 255,85,255,85,255,87,255,85, 255,87,255,93,255,95,255,95,

	240,112,240,80,248,112,240,80, 248,112,242,80,248,112,250,80, 250,112,250,80,250,116,250,80, 250,116,250,81,250,116,250,85,
	250,117,250,85,250,117,251,85, 254,117,251,85,255,117,251,85, 255,117,255,85,255,119,255,85, 255,119,255,93,255,127,255,95,

	240,112,240,208,248,112,240,208, 248,112,242,208,248,112,250,208, 250,112,250,208,250,116,250,208, 250,116,250,209,250,116,250,213,
	250,117,250,213,250,117,251,213, 254,117,251,213,255,117,251,213, 255,117,255,213,255,119,255,213, 255,119,255,221,255,127,255,223,

	240,240,240,240,248,240,240,240, 248,240,242,240,248,240,250,240, 250,240,250,240,250,244,250,240, 250,244,250,241,250,244,250,245,
	250,245,250,245,250,245,251,245, 254,245,251,245,255,245,251,245, 255,245,255,245,255,247,255,245, 255,247,255,253,255,255,255,255
};
 
BYTE* pDst = m_pData;

	_asm
	{
		mov esi, pData
		mov edi, pDst
		xor ebx, ebx	//from
		xor ecx, ecx	//to
		xor edx, edx	//palette

line1:	mov dl, [esi + ebx]
//		ror dl, 4
		mov eax, DWORD PTR bChunk[edx * 4]
		mov [edi + ecx], al
		mov [edi + ecx + 256], ah
		ror eax, 16
		mov [edi + ecx + 512], al
		mov [edi + ecx + 768], ah

		mov dl, [esi + ebx + 32]
//		ror dl, 4
		mov eax, DWORD PTR bChunk[edx * 4]
		mov [edi + ecx + 1024], al
		mov [edi + ecx + 1280], ah
		ror eax, 16
		mov [edi + ecx + 1536], al
		mov [edi + ecx + 1792], ah

		inc ecx
		inc ebx
		test ecx, 31
		jnz line1
		add ebx, 32
		test cl, cl
		jnz line1
		add ecx, 7 * 256
		cmp ebx, 1536
		jc line1
	}
	memset(m_pData + 6144, 7 + 64, 768);
}

int CChunkView::_HasAnimation()
{
	return 0;
}


//---------

CChunkUnpView::CChunkUnpView(BYTE* pData) : CChunkView(pData)
{
	for (int i = 0; i < 1536; i++)
		m_pSrc[i] = ((pData[i * 2] & 15) << 4) | (pData[i * 2 + 1] & 15);

	_Depack(m_pSrc);
	Render();
}

//-----------

CMCView::CMCView(BYTE* pData) : CView(pData, 12288)
{
	Render();
}

void CMCView::Render()
{
//static const DWORD* dwCols = dwPalette;
BYTE* pSrc = m_pData;
DWORD* pDst = m_pBitmap;
int iPhs = m_iPhase;

	_asm
	{
		mov esi, pSrc
		mov edi, pDst
		add edi, (49152 - 256) * 4
		xor ebx, ebx
		mov ecx, 6144
		xor edx, edx
		mov ah, 0x80	//mask
		mov al, BYTE PTR iPhs
		and al, 1
		ror al, 1
line:
nexby:	
		test [esi + ebx], ah
		mov dl, [esi + ecx]
		jz paper
		test al, dl
		jnz paper_
ink_:	and dl, 7
		jnc geco
paper:	test al, dl
		jnz ink_
paper_:	and dl, 56
		ror dl, 3
geco:	test [esi + ecx], 64
		jz nobr
		or dl, 8
nobr:	push DWORD PTR dwCols[edx * 4]
		pop DWORD PTR [edi]
		add edi, 4
		ror ah, 1
		jnc nexby
		inc ecx
		inc ebx
		test bl, 31
		jnz nexby
		sub edi, 512 * 4
		cmp bh, 0x18
		jc line
	}
}

int CMCView::_HasAnimation()
{
int iFlg = 0;
	for (int i = 0; i < 6144; i++)
		iFlg |= m_pData[6144 + i];
	return iFlg & 128;
}

//-----------

CMCXView::CMCXView(BYTE* pData) : CView(pData, 24576)
{
	Render();
}

void CMCXView::Render()
{
BYTE* pSrc = m_pData;
DWORD* pDst = m_pBitmap;
int iPhs = m_iPhase;

	_asm
	{
		mov esi, pSrc
		mov edi, pDst
		add edi, (49152 - 256) * 4
		xor ebx, ebx
		mov ecx, 6144
		xor edx, edx
		push edi
		mov ah, 0x80	//mask
		mov al, BYTE PTR iPhs
		and al, 1
		ror al, 1
		call render
		pop edi
		xor ebx, ebx
		mov ecx, 6144
		add esi, 12288
		call render
	}
	return;

	_asm
	{
render:
line:
nexby:	test [esi + ebx], ah
		mov dl,[esi + ecx]
		jz paper
		test al, dl
		jnz paper_
ink_:	and dl, 7
		jnc geco
paper:	test al, dl
		jnz ink_
paper_:	and dl, 56
		ror dl, 3
geco:	test [esi + ecx], 64
		jz nobr
		or dl, 8
nobr:	cmp esi, pSrc
		jz move
		push ax
		mov al, BYTE PTR dwCols[edx * 4]
		add al, BYTE PTR [edi]
		rcr al, 1
		mov BYTE PTR [edi], al

		mov al, BYTE PTR dwCols[edx * 4 + 1]
		add al, BYTE PTR [edi + 1]
		rcr al, 1
		mov BYTE PTR [edi + 1], al

		mov al, BYTE PTR dwCols[edx * 4 + 2]
		add al, BYTE PTR [edi + 2]
		rcr al, 1
		mov BYTE PTR [edi + 2], al

		pop ax
		jmp short mova

move:	push DWORD PTR dwCols[edx * 4]
		pop DWORD PTR [edi]
mova:	add edi, 4
		ror ah, 1
		jnc nexby
		inc ecx
		inc ebx
		test bl, 31
		jnz nexby
		sub edi, 512 * 4
		cmp bh, 0x18
		jc line
		ret
	}
}

void CMCXView::Invert()
{
	CView::Invert();
DWORD* pDat = (DWORD*)(m_pData + 12288);
	for (int i = 0; i < 1536; i++)
		pDat[i] = ~pDat[i];
}

int CMCXView::_HasAnimation()
{
int iFlg = 0;
	for (int i = 0; i < 6144; i++)
		iFlg |= m_pData[6144 + i] | m_pData[12288 + 6144 + i];
	return iFlg & 128;
}

//------------------
// db quantity
// db w,h,plc_size
//	...
// ds 4
// data

CSpriteView::CSpriteView(BYTE* pData) : CDblView(pData)
{
	m_pSrc = new BYTE[16384];
	memcpy(m_pSrc, pData, 16384);
	_Depack(0);
	Render();
}

void CSpriteView::_Depack(DWORD iSprite)
{
BYTE* pDat1 = m_pData;
BYTE* pDat2 = m_pData + 6912;
BYTE* pAtr1 = pDat1 + 6144;
BYTE* pAtr2 = pDat2 + 6144;

BYTE wid = m_pSrc[1];
BYTE hei = m_pSrc[2];
BYTE size = m_pSrc[3];
BYTE* pSrc = m_pSrc + 5 + 3 * *m_pSrc;
BYTE* pInfo = m_pSrc + 4;
		
	while (iSprite--)
	{
		pSrc += wid * hei * size;
		wid = *pInfo++;
		hei = *pInfo++;
		size = *pInfo++;
	}

	memset(pDat1, 0, 6144);
	memset(pAtr1, 7 + 64, 768);
	memset(pDat2, size > 9 ? 255 : 0, 6144);
	memset(pAtr2, 7 + 64, 768);

	if (size & 1)	//attrs
	{
		for (int y = 0; y < hei; y++)
		{
			for (int x = 0; x < wid; x++)
				pAtr1[x] = pAtr2[x] = *pSrc++;
			pAtr1 += 32;
			pAtr2 += 32;
		}
	}

	for (int y = 0; y < hei; y++)
	{
		for (int i = 0; i < 8; i++)
			for (int x = 0; x < wid; x++)
			{
				if (size > 9)	//mask
				{
					pDat1[x + (i << 8)] &= *pSrc;
					pDat2[x + (i << 8)] &= *pSrc++;
				}

				pDat1[x + (i << 8)] |= *pSrc;
				pDat2[x + (i << 8)] |= *pSrc++;
			}
		pDat1 += 32;
		pDat2 += 32;
		if (! ((pDat1 - m_pData) & 0xff))
		{
			pDat1 += 2048 - 256;
			pDat2 += 2048 - 256;
		}
	}
}

void CSpriteView::NextMode()
{
	if (m_iMode < *m_pSrc - 1)
	{
		_Depack(++m_iMode);
		Render();
	}
}

void CSpriteView::PrewMode()
{
	if (m_iMode > 0)
	{
		_Depack(--m_iMode);
		Render();
	}
}

int CSpriteView::_HasAnimation()
{
int iFlg = 0;
	for (int i = 0; i < 768; i++)
		iFlg |= m_pData[6144 + i] | m_pData[6912 + 6144 + i];
	return iFlg & 128;
}

