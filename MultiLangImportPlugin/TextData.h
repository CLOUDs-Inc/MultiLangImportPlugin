#pragma once

class TextData {
public:
	std::string text;
	std::string fontName;
	float fontSize;
	int   colorR;
	int   colorG;
	int   colorB;
	bool  isValidData; // �ϊ��Ώۃe�L�X�g��󗓃`�F�b�N
	bool  isBold;
	bool  isItalic;
	bool  isUnderline;
	bool  isStrike;
	bool  canConvToANSI;
};
