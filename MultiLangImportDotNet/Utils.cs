using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MultiLangImportDotNet
{
    public class Utils
    {
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
    }
}
