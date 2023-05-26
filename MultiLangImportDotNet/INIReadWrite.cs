using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace MultiLangImportDotNet
{
    public class INIReadWrite
    {
        [DllImport("kernel32.dll", EntryPoint = "GetPrivateProfileString", CharSet = CharSet.Unicode, SetLastError = true)]
        static extern uint GetPrivateProfileString(string lpAppName, string lpKeyName, string lpDefault, StringBuilder lpReturnedString, uint nSize, string lpFileName);

        [DllImport("kernel32.dll", EntryPoint = "WritePrivateProfileString", CharSet = CharSet.Unicode, SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool WritePrivateProfileString(string lpAppName, string lpKeyName, string lpString, string lpFileName);



        private const int CAPACITY_SIZE = 16;

        private string filepath;

        public INIReadWrite(string filepath)
        {
            this.filepath = filepath;
        }

        public string ReadString(string key)
        {
            string val = string.Empty;

            StringBuilder sb = new StringBuilder(CAPACITY_SIZE);
            uint ret = GetPrivateProfileString("MLImp", key, string.Empty, sb, Convert.ToUInt32(sb.Capacity), filepath);
            if (0 < ret)
            {
                val = sb.ToString();
            }

            return val;
        }

        public bool ReadBool(string key)
        {
            bool val = false;

            StringBuilder sb = new StringBuilder(CAPACITY_SIZE);
            uint ret = GetPrivateProfileString("MLImp", key, "none", sb, Convert.ToUInt32(sb.Capacity), filepath);
            if (0 < ret)
            {
                string text = sb.ToString();
                if ("On" == text)
                {
                    val = true;
                }
            }

            return val;
        }

        public void WriteString(string key, string text)
        {
            bool ret = WritePrivateProfileString("MLImp", key, text, filepath);
        }

        public void WriteBool(string key, bool check)
        {
            string text = check ? "On" : "Off";
            bool ret = WritePrivateProfileString("MLImp", key, text, filepath);
        }
    }
}
