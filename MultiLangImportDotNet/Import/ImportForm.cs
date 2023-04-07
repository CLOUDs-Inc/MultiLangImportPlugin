using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace MultiLangImportDotNet.Import
{
    public partial class ImportForm : Form
    {
        public ImportForm()
        {
            InitializeComponent();
        }

        private void buttonClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void buttonImportFile_Click(object sender, EventArgs e)
        {
            // ファイルパス取得
            string filename = GetFileNameFromOpenFileDialog();
            if(string.Empty == filename)
            {
                return;
            }

            // ファイル存在チェック
            if (!File.Exists(filename))
            {
                MessageBox.Show("File not exists.");
                return;
            }

            // xlsxファイルロード
            var excelReader = new TextExcel.ExcelReader();
            if (excelReader.OpenExcel(filename))
            {

            }
            else
            {
                MessageBox.Show("Excel file: read failed.");
                return;
            }

            // ロードデータテーブル格納
            SetDataToTable(null);

            // ファイルパスを表示
            this.textBoxImportFile.Text = filename;
        }



        private string GetFileNameFromOpenFileDialog()
        {
            string filename = string.Empty;

            using (OpenFileDialog ofDialog = new OpenFileDialog())
            {
                ofDialog.Title = "Select Excel file for import multi-language text";
                ofDialog.Filter = "xlsx files (*.xlsx)|*.xlsx";
                ofDialog.RestoreDirectory = true;

                if(DialogResult.OK == ofDialog.ShowDialog())
                {
                    filename = ofDialog.FileName;
                }

                return filename;
            }
        }

        private bool LoadXLSX(string filepath)
        {
            bool result = false;



            return result;
        }

        private void SetDataToTable(object data)
        {

        }

        private void buttonOption_Click(object sender, EventArgs e)
        {

        }

        private void buttonDefaultLanguage_Click(object sender, EventArgs e)
        {
            var langForm = new SelectLangForm();
            if (DialogResult.OK == langForm.ShowDialog(this))
            {


            }
        }
    }
}
