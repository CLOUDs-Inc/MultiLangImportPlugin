#pragma once

ref class CLITextData {
public:
	System::String^ text;
	System::String^ fontName;
	float fontSize;
	int colorR;
	int colorG;
	int colorB;
	bool isBold;
	bool isItalic;
	bool isUnderline;
	bool isStrike;
	bool canConvToANSI;

	CLITextData(
		System::String^ text,
		System::String^ fontName,
		float fontSize,
		int colorR, int colorG, int colorB,
		bool isBold, bool isItalic, bool isUnderline, bool isStrike,
		bool canConvToANSI);
};