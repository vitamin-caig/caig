/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/

#include "options.h"
#include "configure.h"
#include <qcolordialog.h>
#include <qmessagebox.h>
#include "zxlin.h"

void setColor(QPushButton* pBut, QColor color)
{
	pBut->setPaletteBackgroundColor(color);
	pBut->setPaletteForegroundColor(QColor((color.red() + 0x40) & 0xff, (color.green() + 0x40) & 0xff, (color.blue() + 0x40) & 0xff));
}

void OptionsDlg::setColors(unsigned* pPalette)
{
	setColor(VIDColor0, *pPalette++);
	setColor(VIDColor1, *pPalette++);
	setColor(VIDColor2, *pPalette++);
	setColor(VIDColor3, *pPalette++);
	setColor(VIDColor4, *pPalette++);
	setColor(VIDColor5, *pPalette++);
	setColor(VIDColor6, *pPalette++);
	setColor(VIDColor7, *pPalette++);
	setColor(VIDColor8, *pPalette++);
	setColor(VIDColor9, *pPalette++);
	setColor(VIDColor10, *pPalette++);
	setColor(VIDColor11, *pPalette++);
	setColor(VIDColor12, *pPalette++);
	setColor(VIDColor13, *pPalette++);
	setColor(VIDColor14, *pPalette++);
	setColor(VIDColor15, *pPalette++);
}

unsigned getColor(QPushButton* pBut)
{
QColor col = pBut->paletteBackgroundColor();

	return (unsigned)((col.red() << 16) + (col.green() << 8) + col.blue());
}

void OptionsDlg::getColors(unsigned* pPalette)
{
	*pPalette++ = getColor(VIDColor0);
	*pPalette++ = getColor(VIDColor1);
	*pPalette++ = getColor(VIDColor2);
	*pPalette++ = getColor(VIDColor3);
	*pPalette++ = getColor(VIDColor4);
	*pPalette++ = getColor(VIDColor5);
	*pPalette++ = getColor(VIDColor6);
	*pPalette++ = getColor(VIDColor7);
	*pPalette++ = getColor(VIDColor8);
	*pPalette++ = getColor(VIDColor9);
	*pPalette++ = getColor(VIDColor10);
	*pPalette++ = getColor(VIDColor11);
	*pPalette++ = getColor(VIDColor12);
	*pPalette++ = getColor(VIDColor13);
	*pPalette++ = getColor(VIDColor14);
	*pPalette++ = getColor(VIDColor15);
}


int OptionsDlg::exec()
{
    int reslt = 0;

	prepareSetup();

	Configure::pOpenFile->setFilters(QString("BetaDisk images (*.trd *.TRD);;SCL files (*.scl *.SCL)"));

    reslt = QDialog::exec();

	if (reslt == QDialog::Accepted)
	{
	//BETA
		Configure::BETAWriteProtect[0] = BETAWriteProtect0->isChecked();
		Configure::BETAWriteProtect[1] = BETAWriteProtect1->isChecked();
		Configure::BETAWriteProtect[2] = BETAWriteProtect2->isChecked();
		Configure::BETAWriteProtect[3] = BETAWriteProtect3->isChecked();
		Configure::BETAInterleave = BETAInterleave->currentItem();
		Configure::BETANoDelay = BETANoDelay->isChecked();
		Configure::BETATraps = BETATraps->isChecked();
//SND
		strncpy(Configure::SNDDevice, SNDDevice->text(), MAX_PATH_LEN);
		Configure::SNDFrequency = SNDFrequency->text().toUInt();
		Configure::SNDAYYM = SNDYM->isChecked();
		Configure::SNDAY35 = SNDAY35->isChecked();
		Configure::SNDVolAL = SNDVolAL->value();
		Configure::SNDVolAR = SNDVolAR->value();
		Configure::SNDVolBL = SNDVolBL->value();
		Configure::SNDVolBR = SNDVolBR->value();
		Configure::SNDVolCL = SNDVolCL->value();
		Configure::SNDVolCR = SNDVolCR->value();
		Configure::SNDVolSoundrv = SNDVolSoundrv->value();
		Configure::SNDVolCovDD = SNDVolCovDD->value();
		Configure::SNDVolCovFB = SNDVolCovFB->value();
		Configure::SNDVolBeepr = SNDVolBeepr->value();
//VIDEO
		Configure::VIDHWSurface = VIDHWSurface->isChecked();
		Configure::VIDAsyncBlit = VIDAsyncBlit->isChecked();
		Configure::VIDDoubleBuf = VIDDoubleBuf->isChecked();
		Configure::VIDFullScreen = VIDFullScreen->isChecked();
		Configure::VIDSkipFrames = VIDSkipFrames->value();
		getColors((unsigned*)Configure::VIDPalette);
//SYSTEM
		Configure::ULATicksPerFrame = ULATicksPerFrame->text().toUInt();
		Configure::ULATicksPerLine = ULATicksPerLine->text().toUInt();
		Configure::ULATicksBeforePaper = ULATicksBeforePaper->text().toUInt();
		Configure::ULAEvenM1 = ULAEvenM1->isChecked();
		Configure::MEMMemType = MEMMemType->currentItem();
		Configure::MEMCacheSize = MEMCacheSize->text().toUInt();
		Configure::SYSResetTo = SYSResetTo->currentItem();
		Configure::SYSExtCommands = SYSExtCommands->isChecked();

        ::ZXLin->pComputer->pULA->updateSettings();
	}
    return reslt;
}


void OptionsDlg::SNDVolAL_valueChanged(int val)
{
    VolAL->setNum(val);
    SNDVol->setCurrentItem(0);
}


void OptionsDlg::SNDVolAR_valueChanged(int val)
{
    VolAR->setNum(val);
    SNDVol->setCurrentItem(0);
}


void OptionsDlg::SNDVolBL_valueChanged(int val)
{
    VolBL->setNum(val);
    SNDVol->setCurrentItem(0);
}


void OptionsDlg::SNDVolBR_valueChanged(int val)
{
    VolBR->setNum(val);
    SNDVol->setCurrentItem(0);
}



void OptionsDlg::SNDVolCL_valueChanged(int val)
{
    VolCL->setNum(val);
    SNDVol->setCurrentItem(0);
}


void OptionsDlg::SNDVolCR_valueChanged(int val)
{
    VolCR->setNum(val);
    SNDVol->setCurrentItem(0);
}



void OptionsDlg::SNDVolSoundrv_valueChanged(int val)
{
    VolSD->setNum(val);
}


void OptionsDlg::SNDVolCovDD_valueChanged(int val)
{
    VolCovDD->setNum(val);
}


void OptionsDlg::SNDVolCovFB_valueChanged(int val)
{
    VolCovFB->setNum(val);
}



void OptionsDlg::SNDVolBeepr_valueChanged(int val)
{
    VolBeepr->setNum(val);
}


void OptionsDlg::SNDVol_activated(int mode)
{
    unsigned values[5][6] = {{90, 10,  50, 50,  10, 90}, //ABC
                             {90, 10,  10, 90,  50, 50}, //ACB
                             {50, 50,  90, 10,  10, 90}, //BAC
                             {10, 90,  90, 10,  50, 50}, //BCA
                             {100, 100,  100, 100,  100, 100}}; //mono

    if (! mode) return;
    mode--;
    SNDVolAL->setValue(values[mode][0]);
    SNDVolAR->setValue(values[mode][1]);
    SNDVolBL->setValue(values[mode][2]);
    SNDVolBR->setValue(values[mode][3]);
    SNDVolCL->setValue(values[mode][4]);
    SNDVolCR->setValue(values[mode][5]);
}





void OptionsDlg::changeColor(QPushButton* sender)
{
QColor col = QColorDialog::getColor(sender->paletteBackgroundColor(), this, "Select color");

	if (col.isValid())
	{
		setColor(sender, col);
		VIDPalettes->setCurrentItem(0);
	}
}

void OptionsDlg::VIDColor0_clicked()
{
	changeColor(VIDColor0);
}

void OptionsDlg::VIDColor1_clicked()
{
	changeColor(VIDColor1);
}

void OptionsDlg::VIDColor2_clicked()
{
	changeColor(VIDColor2);
}

void OptionsDlg::VIDColor3_clicked()
{
	changeColor(VIDColor3);
}

void OptionsDlg::VIDColor4_clicked()
{
	changeColor(VIDColor4);
}

void OptionsDlg::VIDColor5_clicked()
{
	changeColor(VIDColor5);
}

void OptionsDlg::VIDColor6_clicked()
{
	changeColor(VIDColor6);
}

void OptionsDlg::VIDColor7_clicked()
{
	changeColor(VIDColor7);
}

void OptionsDlg::VIDColor8_clicked()
{
	changeColor(VIDColor8);
}

void OptionsDlg::VIDColor9_clicked()
{
	changeColor(VIDColor9);
}

void OptionsDlg::VIDColor10_clicked()
{
	changeColor(VIDColor10);
}

void OptionsDlg::VIDColor11_clicked()
{
	changeColor(VIDColor11);
}

void OptionsDlg::VIDColor12_clicked()
{
	changeColor(VIDColor12);
}

void OptionsDlg::VIDColor13_clicked()
{
	changeColor(VIDColor13);
}

void OptionsDlg::VIDColor14_clicked()
{
	changeColor(VIDColor14);
}

void OptionsDlg::VIDColor15_clicked()
{
	changeColor(VIDColor15);
}





void OptionsDlg::Eject0_clicked()
{
	::ZXLin->pComputer->pBetaDisk->freeDisk(0);
    BETAImages0->setText(Configure::BETAImages[0]);
}


void OptionsDlg::Eject1_clicked()
{
	::ZXLin->pComputer->pBetaDisk->freeDisk(1);
    BETAImages1->setText(Configure::BETAImages[1]);
}


void OptionsDlg::Eject2_clicked()
{
	::ZXLin->pComputer->pBetaDisk->freeDisk(2);
    BETAImages2->setText(Configure::BETAImages[2]);
}


void OptionsDlg::Eject3_clicked()
{
	::ZXLin->pComputer->pBetaDisk->freeDisk(3);
    BETAImages3->setText(Configure::BETAImages[3]);
}


void OptionsDlg::BETAImages0_clicked()
{
	loadFile(0);
}


void OptionsDlg::BETAImages1_clicked()
{
	loadFile(1);
}


void OptionsDlg::BETAImages2_clicked()
{
	loadFile(2);
}


void OptionsDlg::BETAImages3_clicked()
{
	loadFile(3);
}


void OptionsDlg::loadFile(unsigned drv)
{
QPushButton* butts[4] = {BETAImages0, BETAImages1, BETAImages2, BETAImages3};

	if (Configure::pOpenFile->exec() == QDialog::Accepted)
	{
		if (! ::ZXLin->pComputer->pBetaDisk->freeDisk(drv));	//success freeing
		{
			if (Configure::pOpenFile->selectedFilter() == "*.scl *.SCL")
				::ZXLin->pComputer->pBetaDisk->openSCL(Configure::pOpenFile->selectedFile(), drv);
			else
				::ZXLin->pComputer->pBetaDisk->openTRD(Configure::pOpenFile->selectedFile(), drv);
            butts[drv]->setText(Configure::BETAImages[drv]);
		}
	}
}


void OptionsDlg::buttonReload_clicked()
{
	if (Configure::loadIni("zxlin.ini"))
		QMessageBox::warning(this, QString("Error"), QString("Cannot read zxlin.ini"), QMessageBox::Ok, QMessageBox::NoButton);
	else
		prepareSetup();
}


void OptionsDlg::buttonSave_clicked()
{
	if (Configure::saveIni())
		QMessageBox::warning(this, QString("Error"), QString("Cannot write zxlin.ini"), QMessageBox::Ok, QMessageBox::NoButton);

}


void OptionsDlg::prepareSetup()
{
    QString str;
    //BETA
    BETAWriteProtect0->setChecked(Configure::BETAWriteProtect[0]);
    BETAWriteProtect1->setChecked(Configure::BETAWriteProtect[1]);
    BETAWriteProtect2->setChecked(Configure::BETAWriteProtect[2]);
    BETAWriteProtect3->setChecked(Configure::BETAWriteProtect[3]);
    BETAImages0->setText(Configure::BETAImages[0]);
    BETAImages1->setText(Configure::BETAImages[1]);
    BETAImages2->setText(Configure::BETAImages[2]);
    BETAImages3->setText(Configure::BETAImages[3]);
    BETAInterleave->setCurrentItem(Configure::BETAInterleave);
    BETANoDelay->setChecked(Configure::BETANoDelay);
    BETATraps->setChecked(Configure::BETATraps);
    //SOUND
    SNDDevice->setText(Configure::SNDDevice);
    str.setNum(Configure::SNDFrequency);
    SNDFrequency->setText(str);
    SNDAY->setChecked(! Configure::SNDAYYM);
    SNDYM->setChecked(Configure::SNDAYYM);
    SNDAY35->setChecked(Configure::SNDAY35);
    SNDVolAL->setValue(Configure::SNDVolAL);
    SNDVolAR->setValue(Configure::SNDVolAR);
    SNDVolBL->setValue(Configure::SNDVolBL);
    SNDVolBR->setValue(Configure::SNDVolBR);
    SNDVolCL->setValue(Configure::SNDVolCL);
    SNDVolCR->setValue(Configure::SNDVolCR);
    SNDVolSoundrv->setValue(Configure::SNDVolSoundrv);
    SNDVolCovDD->setValue(Configure::SNDVolCovDD);
    SNDVolCovFB->setValue(Configure::SNDVolCovFB);
    SNDVolBeepr->setValue(Configure::SNDVolBeepr);
    //Video
    VIDHWSurface->setChecked(Configure::VIDHWSurface);
    VIDAsyncBlit->setChecked(Configure::VIDAsyncBlit);
    VIDDoubleBuf->setChecked(Configure::VIDDoubleBuf);
    VIDFullScreen->setChecked(Configure::VIDFullScreen);
    VIDSkipFrames->setValue(Configure::VIDSkipFrames);
    setColors((unsigned*)Configure::VIDPalette);

    VIDPalettes->clear();
    VIDPalettes->insertItem("User defined");
    for (int i = 0; i < 8; i++)
        if (*Configure::VIDPaletteNames[i])
            VIDPalettes->insertItem(Configure::VIDPaletteNames[i]);
        else
            break;

	str.setNum(Configure::ULATicksPerFrame);
	ULATicksPerFrame->setText(str);
	str.setNum(Configure::ULATicksPerLine);
	ULATicksPerLine->setText(str);
	str.setNum(Configure::ULATicksBeforePaper);
	ULATicksBeforePaper->setText(str);
	ULAEvenM1->setChecked(Configure::ULAEvenM1);
	MEMMemType->setCurrentItem(Configure::MEMMemType);
	str.setNum(Configure::MEMCacheSize);
	MEMCacheSize->setText(str);
	SYSResetTo->setCurrentItem(Configure::SYSResetTo);
	SYSExtCommands->setChecked(Configure::SYSExtCommands);
}
