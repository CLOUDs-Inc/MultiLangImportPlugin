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
        public const string UNUSABLE_CHARS_BY_CASTNAME = "!\"#$%&'()*+,-./:;<=>?@[\\]^{|}~";

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
                if (UNUSABLE_CHARS_BY_CASTNAME.Contains(c))
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
                    UNUSABLE_CHARS_BY_CASTNAME.Contains(c) ? '_' : c
                );
            }

            return sb.ToString();
        }
    }
}
