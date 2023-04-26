#pragma once

class TextData {
public:
	std::string text;
	std::string fontName;
	float fontSize;
	int   colorR;
	int   colorG;
	int   colorB;
	bool  isValidData; // 変換対象テキスト非空欄チェック
	bool  isBold;
	bool  isItalic;
	bool  isUnderline;
	bool  isStrike;
	bool  canConvToANSI;
};
