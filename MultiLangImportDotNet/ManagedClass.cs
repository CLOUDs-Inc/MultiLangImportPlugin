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
        /// アプリケーション管理データ
        /// </summary>
        ApplicationData appData;

        public ManagedClass()
        {
            // 当GUI dllパス
            string location = Assembly.GetExecutingAssembly().Location;
            // wrapper dllのパスを作成する
            location = Path.GetDirectoryName(location) + "\\" + Properties.Resources.WRAPPER_DLL_FILENAME;

            Assembly a = Assembly.LoadFrom(location);
            // TextDataクラス情報をc++/cliラッパーdllから取得する
            this.typeCLITextData = a.GetType("CLITextData");

            // 設定ファイルパスと配置フォルダ
            //this.localToolFolder = Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData) + "\\" + Properties.Resources.TOOL_NAME;
            //this.settingFilePath = this.localToolFolder + "\\" + Properties.Resources.SETTING_FILE;
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
            this.appData.OptionData = new OptionData();
            // オプションデータのデフォルト設定を行う
            this.appData.OptionData.Default();

            //Logger.SetFilePath(Path.GetDirectoryName(projectFilePath) + "\\Plugin_DressUpTextCodeGen.log");

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
        public void UploadProjectInfo(object filepathObj, object projectnameObj)
        {
            this.projectFilePath = filepathObj as string;
            this.projectName = projectnameObj as string;
        }

        /// <summary>
        /// dll側へテーブルのスクリプトキャスト名を転送
        /// </summary>
        /// <returns>スクリプト名</returns>
        public string DownloadFontColorTableScriptName()
        {
            return "";
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
        /// dll側へデフォルト言語インデックスを転送
        /// </summary>
        /// <returns></returns>
        public int DownloadDefaultLanguageIndex()
        {
            return this.appData.DefaultLanguageIndex;
        }

        public int DownloadSubcastNameIndex()
        {
            return this.appData.OptionData.SubcastIndex;
        }

        public int DownloadLanguageNameCount()
        {
            return this.appData.LanguageNameList.Count;
        }

        public string[] DownloadLanguageNameArray()
        {
            return this.appData.LanguageNameList.ToArray();
        }

        public int DownloadTextCastNameCount()
        {
            return this.appData.TextCastNameList.Count;
        }

        public string[] DownloadTextCastNameArray()
        {
            return this.appData.TextCastNameList.ToArray();
        }

        public string DownloadSubcastConjunctionString()
        {
            return this.appData.OptionData.ConjunctionString;
        }

        public object[,] DownloadTextDataTable()
        {
            int rowCount = this.appData.TextCastNameList.Count;
            int colCount = this.appData.LanguageNameList.Count;

            object[,] dlTextDataTable = new Object[rowCount,colCount];
            for (int rowIndex = 0; rowIndex < rowCount; rowIndex++)
            {
                for (int colIndex = 0; colIndex < colCount; colIndex++)
                {
                    var textData = this.appData.TextDataTable[rowIndex, colIndex];

                    dlTextDataTable[rowIndex, colIndex] = Activator.CreateInstance(this.typeCLITextData, new object[] {
                            textData.Text,
                            textData.FontName,
                            textData.FontSize,
                            (int)textData.FontColor.R,
                            (int)textData.FontColor.G,
                            (int)textData.FontColor.B,
                            textData.IsBold,
                            textData.IsItalic,
                            textData.IsUnderline,
                            textData.IsStrike
                        });
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
