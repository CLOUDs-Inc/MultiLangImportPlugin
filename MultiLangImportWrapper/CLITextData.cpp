#include "CLITextData.h"

CLITextData::CLITextData(System::String^ text, System::String^ fontName, float fontSize, int colorR, int colorG, int colorB, bool isBold, bool isItalic, bool isUnderline, bool isStrike)
{
	this->text = text;
	this->fontName = fontName;
	this->fontSize = fontSize;
	this->colorR = colorR;
	this->colorG = colorG;
	this->colorB = colorB;
	this->isBold = isBold;
	this->isItalic = isItalic;
	this->isUnderline = isUnderline;
	this->isStrike = isStrike;
}
