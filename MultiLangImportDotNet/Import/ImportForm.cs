﻿using System;
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
        ApplicationData appData;

        /// <summary>
        /// テキスト修飾情報表示ラベルの右上のx座標
        /// </summary>
        int labelTextModTopRightX = -1;

        public ImportForm(ApplicationData appData)
        {
            InitializeComponent();

            this.appData = appData;
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
            if (!excelReader.OpenExcel(filename))
            {
                MessageBox.Show("Excel file: read failed.");
                return;
            }

            // ロードデータテーブル格納
            SetDataToTable(excelReader);

            // Excel読み取りを行ったデータを管理クラスに移す
            SetApplicationDataToManageClass(appData, excelReader);


            // デフォルト言語指定、サブキャスト機能、インポート機能を有効に
            this.buttonDefaultLanguage.Enabled = true;
            this.buttonOption.Enabled = true;
            this.buttonImport.Enabled = true;


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

        /// <summary>
        /// Excelリーダーで取得したうちの必須データを管理クラスに渡す
        /// </summary>
        /// <param name="appData">アプリケーション管理データクラス</param>
        /// <param name="reader">Excelリーダーオブジェクト</param>
        private void SetApplicationDataToManageClass(ApplicationData appData, TextExcel.ExcelReader reader)
        {
            appData.DefaultLanguageIndex = -1;
            appData.LanguageNameList = reader.LanguageNameList;
            appData.TextCastNameList = reader.TextCastNameList;
            appData.TextDataTable = reader.TextDataTable;
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
                this.dataGridViewTextMod.Columns[colIndex].SortMode = DataGridViewColumnSortMode.NotSortable;
                this.dataGridViewTextMod.Columns[colIndex].HeaderText = reader.LanguageNameList[colIndex];
            }
            
            for(int rowIndex = 0; rowIndex < reader.TextTableRow; rowIndex++)
            {
                int currentRowIndex = this.dataGridViewTextMod.Rows.Add();
                this.dataGridViewTextMod.Rows[currentRowIndex].HeaderCell.Value = reader.TextCastNameList[rowIndex];

                for(int colIndex = 0; colIndex < reader.TextTableColumn; colIndex++)
                {
                    var textData = reader.TextDataTable[rowIndex, colIndex];
                    this.dataGridViewTextMod.Rows[rowIndex].Cells[colIndex].Value = textData.Text;
                }
            }
        }

        /// <summary>
        /// テキストデータの情報をテーブル下の表示欄に表示する
        /// </summary>
        /// <param name="textData"></param>
        private void SetSelectedTextData(TextData textData)
        {
            SetTextDataDisplayTextBox(textData);
            SetTextDataDisplayLabel(textData);
        }

        private void SetTextDataDisplayTextBox(TextData textData)
        {
            var fontSizeTextBox = this.textBoxTextModification.Font.Size;

            FontStyle fontStyle = FontStyle.Regular;
            if (textData.IsBold) fontStyle |= FontStyle.Bold;
            if (textData.IsItalic) fontStyle |= FontStyle.Italic;
            if (textData.IsUnderline) fontStyle |= FontStyle.Underline;
            if (textData.IsStrike) fontStyle |= FontStyle.Strikeout;

            Font textFont = new Font(textData.FontName, fontSizeTextBox, fontStyle);
            this.textBoxTextModification.Font = textFont;
            this.textBoxTextModification.ForeColor = textData.FontColor;
            this.textBoxTextModification.Text = textData.Text;
        }

        /// <summary>
        /// フォント情報表示ラベルにテキストデータを表示する
        /// </summary>
        /// <param name="textData">テキストデータ</param>
        private void SetTextDataDisplayLabel(TextData textData)
        {
            if (textData == null) return;

            StringBuilder sb = new StringBuilder();

            // フォント名文字列の作成
            string fontNameStr = "Font: " + (string.IsNullOrWhiteSpace(textData.FontName) ? "--" : textData.FontName);
            sb.Append(fontNameStr);

            // フォントサイズ文字列の作成
            float fontSize = textData.FontSize;
            if (0.0 < fontSize)
            {
                string sizeFormat = ((fontSize % 1f) != 0f)
                        ? ", Size: {0:F1} pt"
                        : ", Size: {0:F0} pt";

                string fontSizeStr = string.Format(sizeFormat, fontSize);
                sb.Append(fontSizeStr);
            }

            // フォント色文字列の作成
            string colorStr = ", Color: " + ColorTranslator.ToHtml(textData.FontColor);
            sb.Append(colorStr);

            // フォント情報表示ラベルにセット
            this.labelTextModification.Text = sb.ToString();

            // ラベル幅に応じて、ラベルのx座標を調節
            var oldLocation = this.labelTextModification.Location;
            int newX = this.labelTextModTopRightX - this.labelTextModification.Size.Width;
            Point newLocation = new Point(newX, oldLocation.Y);
            this.labelTextModification.Location = newLocation;
        }

        /// <summary>
        /// テキストテーブルの言語デフォルトを表示し直す
        /// </summary>
        /// <param name="appData">アプリ管理データクラス</param>
        private void SetDefaultLanguage(ApplicationData appData)
        {
            // テーブルの列表題（言語名）を設定
            for (int langIndex = 0; langIndex < appData.LanguageNameList.Count; langIndex++)
            {
                string defaultAppend = (langIndex == appData.DefaultLanguageIndex ? " (DEFAULT)" : string.Empty);
                this.dataGridViewTextMod.Columns[langIndex].HeaderText = appData.LanguageNameList[langIndex] + defaultAppend;
            }
        }


        private void SetImportFormSettingToAppData(ApplicationData appData)
        {
            appData.FlagAddIfLangPageNotFound = this.checkBoxAddLangPage.Checked;
            appData.FlagAddIfTextCastNotFound = this.checkBoxAddTextCast.Checked;
            appData.FlagCreateAsUnicodeTextCast = this.checkBoxCreateAsUnicode.Checked;
            appData.FlagNotUpdateExistingTextCast = this.checkBoxNotUpdate.Checked;
            appData.FlagInheritPropertiesOfTheFirstLangPage = this.checkBoxInheritProperty.Checked;
            appData.FlagInheritOnlyNewLangPage = this.checkBoxInheritOnlyNewLang.Checked;

            appData.FlagApplyFontName = this.checkBoxApplyFontname.Checked;
            appData.FlagApplyFontSize = this.checkBoxApplyFontSize.Checked;
            appData.FlagApplyTextColor = this.checkBoxApplyTextColor.Checked;
            appData.FlagApplyString = this.checkBoxApplyString.Checked;
        }


        private int GetLabelTextModTopRightXPosition()
        {
            var targetLabel = this.labelTextModification;
            return targetLabel.Location.X + targetLabel.Size.Width; ;
        }

        private void buttonOption_Click(object sender, EventArgs e)
        {
            var optionForm = new OptionForm(this.appData);
            if(DialogResult.OK != optionForm.ShowDialog(this))
            {
                return;
            }



        }

        private void buttonDefaultLanguage_Click(object sender, EventArgs e)
        {
            // デフォルト言語選択フォームを展開する
            var langForm = new SelectLangForm(this.appData.LanguageNameList, this.appData.DefaultLanguageIndex);
            if (DialogResult.OK != langForm.ShowDialog(this))
            {
                return;
            }

            // 選択されたインデクスを保持する
            this.appData.DefaultLanguageIndex = langForm.SelectedLanguageIndex;

            // テキストテーブルのデフォルト言語の表示更新
            SetDefaultLanguage(this.appData);
        }

        private void buttonImport_Click(object sender, EventArgs e)
        {
            // フォームのチェックボックス設定をアプリ管理データにセットする
            SetImportFormSettingToAppData(this.appData);

            // フォーム呼び出し元に通知OK
            this.DialogResult = DialogResult.OK;
        }

        private void dataGridViewTextMod_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            // クリックされたセルの行と列を取得
            int rowIndex = e.RowIndex;
            int colIndex = e.ColumnIndex;

            // 文字データ以外のセルのクリックは無視
            if(rowIndex < 0 || 
               appData.TextCastNameList.Count <= rowIndex ||
               colIndex < 0 ||
               appData.LanguageNameList.Count <= colIndex)
            {
                return;
            }

            var textData = this.appData.TextDataTable[rowIndex, colIndex];

            //textData
            SetSelectedTextData(textData);
        }

        private void ImportForm_Load(object sender, EventArgs e)
        {
            // テキスト修飾情報表示用ラベルの右上のx座標を取得しておく
            this.labelTextModTopRightX = GetLabelTextModTopRightXPosition();
        }

        private void ImportForm_Resize(object sender, EventArgs e)
        {
            // テキスト修飾情報表示用ラベルの右上のx座標を取得しておく
            this.labelTextModTopRightX = GetLabelTextModTopRightXPosition();
        }

        private void checkBoxAddTextCast_CheckedChanged(object sender, EventArgs e)
        {
            // "Add if text cast is not found"のチェックONの時だけ
            // "Create as unicode ..."を活性状態にする
            this.checkBoxCreateAsUnicode.Enabled = this.checkBoxAddTextCast.Checked;
        }

        private void checkBoxInheritProperty_CheckedChanged(object sender, EventArgs e)
        {
            // "Inherit properties ..."のチェックONの時だけ
            // "Inherit only new ..."を活性状態にする
            this.checkBoxInheritOnlyNewLang.Enabled = this.checkBoxInheritProperty.Checked;
        }
    }
}
