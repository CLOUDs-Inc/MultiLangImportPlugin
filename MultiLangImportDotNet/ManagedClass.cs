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
        /// <summary>
        /// テキスト着せ替え用生成コード
        /// </summary>
        string outputTableCode;

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
            string location = Assembly.GetExecutingAssembly().Location;
            location = Path.GetDirectoryName(location) + "\\" + Properties.Resources.WRAPPER_DLL_FILENAME;

            Assembly a = Assembly.LoadFrom(location);

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
            this.appData.OptionData = new OptionData()
            {
                FlagUseSubcastName = false,
                FlagUseSubcastNameWhenSearchingForCast = false,
                FlagAddSubcastNameWhenCreatingANewCast = true,
                FlagUseUnderscoreForConjunctionInSubcastName = true,
                ConjunctionString = "_",
                SubcastIndex = -1
            };

            //Logger.SetFilePath(Path.GetDirectoryName(projectFilePath) + "\\Plugin_DressUpTextCodeGen.log");

            // Open form
            Import.ImportForm importForm = new Import.ImportForm(this.appData);
            if(DialogResult.OK == importForm.ShowDialog())
            {
                MessageBox.Show("Success");
                result = true;
            }
            else
            {
                MessageBox.Show("Not yet.");
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
        /// dll側へテキスト着せ替え用生成コードを転送
        /// </summary>
        /// <returns>スクリプトキャストコード</returns>
        public string DownloadFontColorTableScriptCode()
        {
            return this.outputTableCode;
        }
    }
}
