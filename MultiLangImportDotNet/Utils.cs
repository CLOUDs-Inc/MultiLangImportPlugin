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
        public static string UNUSABLE_CHARS_STR_FOR_CASTNAME = " !\"#$%&'()*+,-./:;<=>?@[\\]^{|}~";

        public static Encoding EncodeSJIS = Encoding.GetEncoding("shift_jis");

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


        public static bool CheckNameHitUnusableSymbols(string testedString)
        {
            if(testedString == null)
            {
                return false;
            }

            bool result = testedString.Any(c => UNUSABLE_CHARS_STR_FOR_CASTNAME.Contains(c));
            return result;
        }

        public static string ChangeUnusableSymbolToUnderscore(string testedString)
        {
            if(testedString == null)
            {
                return null;
            }

            StringBuilder sb = new StringBuilder();
            foreach(var c in testedString)
            {
                sb.Append(
                    UNUSABLE_CHARS_STR_FOR_CASTNAME.Contains(c) ? '_' : c
                );
            }

            return sb.ToString();
        }

        /// <summary>
        /// ANSI(Shift-JIS)変換可否チェック
        /// </summary>
        /// <param name="testedString">変換対象文字列</param>
        /// <returns>変換可否（変換前後で文字に差異がないか）</returns>
        public static bool ANSIConvertTest(string testedString)
        {
            bool result = false;

            try
            {
                // SJIS文字に変換
                string converted = ForcelyConvertToANSI(testedString);
                // 変換前と変換後で文字列が同じなら変換成功
                if(0 == string.Compare(testedString, converted))
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

        /// <summary>
        /// C#のデフォルトUnicode文字列を強制的にShift_JISにする
        /// </summary>
        /// <param name="targetStr">変換対象文字列</param>
        /// <returns>変換後文字列、変換できない文字は'?'になる</returns>
        public static string ForcelyConvertToANSI(string targetStr)
        {
            if (string.IsNullOrEmpty(targetStr)) return targetStr;

            string sjisString;
            try
            {
                // Unicode状態でのbyte列に変換
                byte[] unicodeBytes = Encoding.Unicode.GetBytes(targetStr);
                // utf16 -> SJIS
                byte[] bytesUTF16toSJIS = Encoding.Convert(Encoding.Unicode, EncodeSJIS, unicodeBytes);
                
                // SJISエンコード文字列の取得
                sjisString = EncodeSJIS.GetString(bytesUTF16toSJIS);
            }
            catch(Exception ex)
            {
                throw ex;
            }

            return sjisString;
        }


        public static bool CorrectNameForCastName(out string correctedName, string castName)
        {
            bool result;

            try
            {
                string sjisName = ForcelyConvertToANSI(castName);

                // 変換できず"?"となった箇所は"_"に変換する
                // 使用できない記号についても"_"に変換する
                sjisName = ChangeUnusableSymbolToUnderscore(sjisName);

                // 先頭に数字がある場合"TXT_"を頭に付与する
                if (!string.IsNullOrEmpty(sjisName) && char.IsDigit(sjisName[0]))
                {
                    sjisName = "TXT_" + sjisName;
                }

                correctedName = sjisName;
                result = true;
            }
            catch
            {
                correctedName = null;
                result = false;
            }

            return result;
        }

        /// <summary>
        /// UIのグリッド表示用にキャスト名を修正する
        /// </summary>
        /// <param name="castname">修正前キャスト名</param>
        /// <returns>修正後キャスト名</returns>
        public static string CorrectCastNameForGrid(string castname)
        {
            string result = castname;
            // 使用できない記号について"_"に変換する
            foreach (char c in UNUSABLE_CHARS_STR_FOR_CASTNAME)
            {
                result = result.Replace(c, '_');
            }

            return result;
        }
    }
}
