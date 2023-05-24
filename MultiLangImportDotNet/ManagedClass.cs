using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Reflection;
using System.IO;
using System.Text;

namespace MultiLangImportDotNet
{
    public class ManagedClass
    {
        Type typeCLITextData;

        /// <summary>
        /// SDKプロジェクトファイルパス
        /// </summary>
        string projectFilePath;

        /// <summary>
        /// SDKプロジェクト名
        /// </summary>
        string projectName;

        /// <summary>
        /// SDKプロジェクト多言語使用フラグ
        /// </summary>
        bool multiLangEnabled;

        /// <summary>
        /// SDKプロジェクト言語数状況（処理前）
        /// </summary>
        public int langPageNumberPrev;

        /// <summary>
        /// アプリケーション管理データ
        /// </summary>
        ApplicationData appData;

        public ManagedClass()
        {
            // 当GUI dllパス
            string base_location = Assembly.GetExecutingAssembly().Location;
            // wrapper dllのパスを作成する
            string location = Path.GetDirectoryName(base_location) + "\\" + Properties.Resources.WRAPPER_DLL_FILENAME;

            Assembly a = Assembly.LoadFrom(location);
            // TextDataクラス情報をc++/cliラッパーdllから取得する
            this.typeCLITextData = a.GetType("CLITextData");
            Assembly asm;
            try
            {
                asm = Assembly.UnsafeLoadFrom(Path.GetDirectoryName(base_location) + "\\BouncyCastle.Crypto.dll");
                asm = Assembly.UnsafeLoadFrom(Path.GetDirectoryName(base_location) + "\\Enums.NET.dll");
                asm = Assembly.UnsafeLoadFrom(Path.GetDirectoryName(base_location) + "\\ICSharpCode.SharpZipLib.dll");
                asm = Assembly.UnsafeLoadFrom(Path.GetDirectoryName(base_location) + "\\MathNet.Numerics.dll");
                asm = Assembly.UnsafeLoadFrom(Path.GetDirectoryName(base_location) + "\\Microsoft.IO.RecyclableMemoryStream.dll");
                asm = Assembly.UnsafeLoadFrom(Path.GetDirectoryName(base_location) + "\\NPOI.dll");
                asm = Assembly.UnsafeLoadFrom(Path.GetDirectoryName(base_location) + "\\NPOI.OOXML.dll");
                asm = Assembly.UnsafeLoadFrom(Path.GetDirectoryName(base_location) + "\\NPOI.OpenXml4Net.dll");
                asm = Assembly.UnsafeLoadFrom(Path.GetDirectoryName(base_location) + "\\NPOI.OpenXmlFormats.dll");
                asm = Assembly.UnsafeLoadFrom(Path.GetDirectoryName(base_location) + "\\SixLabors.Fonts.dll");
                asm = Assembly.UnsafeLoadFrom(Path.GetDirectoryName(base_location) + "\\SixLabors.ImageSharp.dll");
                asm = Assembly.UnsafeLoadFrom(Path.GetDirectoryName(base_location) + "\\System.Buffers.dll");
                asm = Assembly.UnsafeLoadFrom(Path.GetDirectoryName(base_location) + "\\System.Memory.dll");
                asm = Assembly.UnsafeLoadFrom(Path.GetDirectoryName(base_location) + "\\System.Numerics.Vectors.dll");
                asm = Assembly.UnsafeLoadFrom(Path.GetDirectoryName(base_location) + "\\System.Runtime.CompilerServices.Unsafe.dll");
                asm = Assembly.UnsafeLoadFrom(Path.GetDirectoryName(base_location) + "\\System.Text.Encoding.CodePages.dll");
            }
            catch(Exception ex)
            {
                MessageBox.Show("LoadFrom error: " + ex.Message);
                throw ex;
            }
        }

        /// <summary>
        /// ツール処理開始
        /// </summary>
        /// <returns>true:処理完了、false:処理キャンセル</returns>
        public bool BeginProcess()
        {
            bool result = false;

            // アプリ管理データを新規化
            this.appData = new ApplicationData();
            this.appData.MultiLangEnabled = this.multiLangEnabled;
            this.appData.LangPageNumberPrev = this.langPageNumberPrev;

            // Open form
            Import.ImportForm importForm = new Import.ImportForm(this.appData);
            if(DialogResult.OK == importForm.ShowDialog())
            {
                result = true;
            }
            else
            {
                result = false;
            }

            return result;
        }

        /// <summary>
        /// プロジェクトファイルのファイルパス、名前を元に関係性ファイルの名前、パスをUIへ送る
        /// </summary>
        /// <param name="filepathObj">プロジェクトファイルパス</param>
        /// <param name="projectnameObj">プロジェクト名</param>
        public void UploadProjectInfo(object filepathObj, object projectnameObj, object multiLangEnabled, object langPageNumber)
        {
            this.projectFilePath = filepathObj as string;
            this.projectName = projectnameObj as string;
            this.multiLangEnabled = (bool)multiLangEnabled;
            this.langPageNumberPrev = (int)langPageNumber;
        }


        /// <summary>
        /// dll側へインポートExcelファイルフルパスを転送
        /// </summary>
        /// <returns></returns>
        public string DownloadImportExcelFilePath()
        {
            return this.appData.ImportExcelFilePath;
        }

        /// <summary>
        /// sdk側へデフォルト言語名を転送
        /// </summary>
        /// <returns></returns>
        public string DownloadDefaultLanguageName()
        {
            string resultName = string.Empty;
            if (0 <= this.appData.DefaultLanguageIndex)
            {
                resultName = this.appData.LanguageNameListInside[this.appData.DefaultLanguageIndex];
                resultName = Utils.ForcelyConvertToANSI(resultName);
            }
            return resultName;
        }

        public int DownloadSubcastNameIndex()
        {
            return this.appData.OptionData.SubcastIndex;
        }

        public int DownloadLanguageNameCount()
        {
            return this.appData.LanguageNameListModified.Count;
        }

        public string[] DownloadLanguageNameArray()
        {
            return this.appData.LanguageNameListModified.ToArray();
        }

        public int DownloadTextCastNameCount()
        {
            return this.appData.TextCastNameListInside.Count;
        }

        public string[] DownloadTextCastNameArrayLoneMod()
        {
            return this.appData.TextCastNameListLoneMod.ToArray();
        }

        public string[] DownloadSubPartNameArrayMod()
        {
            return this.appData.SubPartNameListMod.ToArray();
        }

        public string[] DownloadTextCastNameArrayConjMod()
        {
            return this.appData.TextCastNameListConjMod.ToArray();
        }

        public string DownloadSubcastConjunctionString()
        {
            return this.appData.ConjunctionStringMod;
        }

        public object[,] DownloadTextDataTable()
        {
            int rowCount = this.appData.TextDataTable.GetLength(0);
            int colCount = this.appData.TextDataTable.GetLength(1);
            //int rowCount = this.appData.TextCastNameList.Count;
            int outputColSize = this.appData.LanguageNameListModified.Count;

            object[,] dlTextDataTable = new Object[rowCount, outputColSize];
            for (int rowIndex = 0; rowIndex < rowCount; rowIndex++)
            {
                int colTgtIdx = 0;

                // デフォルト言語列に指定された列データは既に先頭に設定されているのでスキップする
                if(-1 != this.appData.DefaultLanguageIndex)
                {
                    var textData = this.appData.TextDataTable[rowIndex, this.appData.DefaultLanguageIndex];
                    if (textData != null)
                    {
                        dlTextDataTable[rowIndex, colTgtIdx] = Activator.CreateInstance(this.typeCLITextData, new object[] {
                            textData.Text,
                            textData.FontName,
                            textData.FontSize,
                            (int)textData.FontColor.R,
                            (int)textData.FontColor.G,
                            (int)textData.FontColor.B,
                            textData.IsBold,
                            textData.IsItalic,
                            textData.IsUnderline,
                            textData.IsStrike,
                            textData.CanConvertToANSI
                        });
                    }
                    colTgtIdx++;
                }

                for (int colSrcIdx = 0; colSrcIdx < colCount; colSrcIdx++)
                {
                    // サブキャストに指定された列データはスキップする
                    if (colSrcIdx == this.appData.OptionData.SubcastIndex) continue;
                    // デフォルト言語列に指定された列データは既に先頭に設定されているのでスキップする
                    if (colSrcIdx == this.appData.DefaultLanguageIndex) continue;

                    var textData = this.appData.TextDataTable[rowIndex, colSrcIdx];
                    if (textData != null)
                    {
                        dlTextDataTable[rowIndex, colTgtIdx] = Activator.CreateInstance(this.typeCLITextData, new object[] {
                            textData.Text,
                            textData.FontName,
                            textData.FontSize,
                            (int)textData.FontColor.R,
                            (int)textData.FontColor.G,
                            (int)textData.FontColor.B,
                            textData.IsBold,
                            textData.IsItalic,
                            textData.IsUnderline,
                            textData.IsStrike,
                            textData.CanConvertToANSI
                        });
                    }
                    colTgtIdx++;
                }
            }

            return dlTextDataTable;
        }

        public bool DownloadFlag(object flagName)
        {
            string keyStr = flagName as string;

            if(keyStr != null)
            {
                if (this.appData.Flags.ContainsKey(keyStr))
                {
                    return this.appData.Flags[keyStr];
                }

                if (this.appData.OptionData.Flags.ContainsKey(keyStr))
                {
                    return this.appData.OptionData.Flags[keyStr];
                }
            }

            return false;
        }
    }
}
