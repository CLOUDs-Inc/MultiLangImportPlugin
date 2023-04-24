using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace MultiLangImportDotNet
{
    public class Utils
    {
        /// <summary>
        /// キャスト名に使用できない文字
        /// </summary>
        public static string UNUSABLE_CHARS_STR_BY_CASTNAME = " !\"#$%&'()*+,-./:;<=>?@[\\]^{|}~";

        public static char[] UNUSABLE_CHARS_BY_CASTNAME = UNUSABLE_CHARS_STR_BY_CASTNAME.ToCharArray();

        /// <summary>
        /// Excel列番号の文字列変換(1->"A", 26->"Z", 27->"AA", 28->"AB"...)
        /// </summary>
        /// <param name="columnNumber">列番号（１～）</param>
        /// <returns>Excel列名アルファベット文字列</returns>
        public static string GetExcelColumnName(int columnNumber)
        {
            string columnName = string.Empty;

            while(columnNumber > 0)
            {
                int module = (columnNumber - 1) % 26;
                columnName = Convert.ToChar('A' + module) + columnName;
                columnNumber = (columnNumber - module) / 26;
            }

            return columnName;
        }


        public static bool CheckNameHitUnusableChars(string testedString)
        {
            if(testedString == null)
            {
                return false;
            }

            foreach(var c in testedString)
            {
                if (UNUSABLE_CHARS_STR_BY_CASTNAME.Contains(c))
                {
                    return true;
                }
            }

            return false;
        }

        public static string ChangeUnusableCharToUnderscore(string testedString)
        {
            if(testedString == null)
            {
                return null;
            }

            StringBuilder sb = new StringBuilder();
            foreach(var c in testedString)
            {
                sb.Append(
                    UNUSABLE_CHARS_STR_BY_CASTNAME.Contains(c) ? '_' : c
                );
            }

            return sb.ToString();
        }

        /// <summary>
        /// ANSI(Shift-JIS)変換可否チェック
        /// </summary>
        /// <param name="testedString">変換対象文字列</param>
        /// <returns>変換可否</returns>
        public static bool ANSIConvertTest(string testedString)
        {
            bool result = false;
            try
            {
                byte[] unicodeBytes = Encoding.Unicode.GetBytes(testedString);
                Encoding encodeSJIS = Encoding.GetEncoding("shift_jis");

                // utf16 -> SJIS
                byte[] bytesUTF16toSJIS = Encoding.Convert(Encoding.Unicode, encodeSJIS, unicodeBytes);

                string targetString = encodeSJIS.GetString(bytesUTF16toSJIS);

                // 変換前と変換後で'?'の数が同じなら変換成功
                int qCountOfTested = testedString.Count((c) => c == '?');
                int qCountOfTarget = targetString.Count((c) => c == '?');
                if (qCountOfTested == qCountOfTarget)
                {
                    result = true;
                }
            }
            catch (Exception ex)
            {
                string errMsg = ex.Message;
            }

            return result;
        }

        public static string CorrectCastName(string castName)
        {
            string result = castName;
            if (string.IsNullOrEmpty(result)) return result;

            try
            {
                byte[] unicodeBytes = Encoding.Unicode.GetBytes(result);
                Encoding encodeSJIS = Encoding.GetEncoding("shift_jis");

                // utf16 -> SJIS
                byte[] bytesUTF16toSJIS = Encoding.Convert(Encoding.Unicode, encodeSJIS, unicodeBytes);

                string targetString = encodeSJIS.GetString(bytesUTF16toSJIS);
                // 変換できず"?"となった箇所は"_"に変換する
                // 使用できない記号についても"_"に変換する
                foreach(char c in UNUSABLE_CHARS_STR_BY_CASTNAME)
                {
                    result = result.Replace(c, '_');
                }
            }
            catch
            {
                result = "CorrectError";
            }

            // 先頭に数字がある場合"TXT_"を頭に付与する
            if(char.IsDigit(result[0]))
            {
                result = "TXT_" + result;
            }
            return result;
        }



    }
}
