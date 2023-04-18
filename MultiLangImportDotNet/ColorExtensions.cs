using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace MultiLangImportDotNet
{
    static class ColorExtensions
    {
        public static string ToHexRGBString(this Color color)
        {
            string colorStr = string.Format("{0:X2}{1:X2}{2:X2}", color.R, color.G, color.B);
            return colorStr;
        }
    }
}
