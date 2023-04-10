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
                // ロードデータテーブル格納
                SetDataToTable(excelReader);
            }
            else
            {
                MessageBox.Show("Excel file: read failed.");
                return;
            }


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

        private void SetDataToTable(TextExcel.ExcelReader reader)
        {
            // datagridviewをリセット
            this.dataGridViewTextMod.Rows.Clear();

            // テーブルの列数（言語数）を設定
            this.dataGridViewTextMod.ColumnCount = reader.TextTableColumn;

            // テーブルの列表題（言語名）を設定
            for(int colIndex = 0; colIndex < reader.TextTableColumn; colIndex++)
            {
                this.dataGridViewTextMod.Columns[colIndex].HeaderText = reader.LanguageNameList[colIndex];
            }
            
            for(int rowIndex = 0; rowIndex < reader.TextTableRow; rowIndex++)
            {
                int currentRowIndex = this.dataGridViewTextMod.Rows.Add();
                this.dataGridViewTextMod.Rows[currentRowIndex].HeaderCell.Value = reader.TextCastNameList[rowIndex];

                for(int colIndex = 0; colIndex < reader.TextTableColumn; colIndex++)
                {
                    var textData = reader.TextDataTable[rowIndex, colIndex];
                    var fontName = textData.FontName;
                    var fontSize = textData.FontSize;
                    FontStyle fontStyle = FontStyle.Regular;
                    if (textData.IsBold) fontStyle |= FontStyle.Bold;
                    if (textData.IsItalic) fontStyle |= FontStyle.Italic;
                    if (textData.IsUnderline) fontStyle |= FontStyle.Underline;
                    if (textData.IsStrike) fontStyle |= FontStyle.Strikeout;

                    Font textFont = new Font(fontName, fontSize, fontStyle);

                    this.dataGridViewTextMod.Rows[rowIndex].Cells[colIndex].Style.Font = textFont;
                    this.dataGridViewTextMod.Rows[rowIndex].Cells[colIndex].Value = textData.Text;

                }
            }



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
