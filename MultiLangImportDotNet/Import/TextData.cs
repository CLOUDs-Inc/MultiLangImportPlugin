﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace MultiLangImportDotNet.Import
{
    public class TextData
    {
        /// <summary>
        /// テキスト文字列
        /// </summary>
        public string Text { get; private set; }

        /// <summary>
        /// テキストのフォント名
        /// </summary>
        public string FontName { get; private set; }

        /// <summary>
        /// テキストのフォントサイズ
        /// </summary>
        public float FontSize { get; private set; }

        /// <summary>
        /// テキストの色
        /// </summary>
        public Color FontColor { get; private set; }

        /// <summary>
        /// テキストのBold状態
        /// </summary>
        public bool IsBold { get; private set; }

        /// <summary>
        /// テキストのItalic状態
        /// </summary>
        public bool IsItalic { get; private set; }

        /// <summary>
        /// テキストの下線状態
        /// </summary>
        public bool IsUnderline { get; private set; }

        /// <summary>
        /// テキストの取り消し線状態
        /// </summary>
        public bool IsStrike { get; private set; }

        /// <summary>
        /// ANSI(Shift-JIS)への変換可否
        /// </summary>
        public bool CanConvertToANSI { get; private set; }


        public TextData(string text, string fontName, float fontSize, Color fontColor, bool isBold, bool isItalic, bool isUnderline, bool isStrike, bool canConvToANSI)
        {
            this.Text = text;
            this.FontName = fontName;
            this.FontSize = fontSize;
            this.FontColor = fontColor;
            this.IsBold = isBold;
            this.IsItalic = isItalic;
            this.IsUnderline = isUnderline;
            this.IsStrike = isStrike;
            this.CanConvertToANSI = canConvToANSI;
        }
    }
}
