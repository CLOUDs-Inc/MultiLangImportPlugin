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
            // デフォルト言語指定をリセット
            appData.DefaultLanguageIndex = -1;
            appData.LanguageNameList = reader.LanguageNameList;
            appData.LangHasTextWithUnusableCharList = reader.LangHasTextWithUnusableCharList;
            appData.TextCastNameList = reader.TextCastNameList;
            appData.TextDataTable = reader.TextDataTable;
            // サブキャスト列指定をリセット
            appData.SubcastNameIndex = -1;
            appData.OptionData.SubcastIndex = -1;
        }

        private void SetDataToTable(TextExcel.ExcelReader reader)
        {
            // datagridviewをリセット
            this.dataGridViewTextMod.Columns.Clear();
            this.dataGridViewTextMod.Rows.Clear();

            // テーブルの列数（言語数）を設定
            this.dataGridViewTextMod.ColumnCount = reader.TextTableColumn;

            // テーブルの列表題（言語名）を設定
            for(int colIndex = 0; colIndex < reader.TextTableColumn; colIndex++)
            {
                this.dataGridViewTextMod.Columns[colIndex].SortMode = DataGridViewColumnSortMode.NotSortable;
                this.dataGridViewTextMod.Columns[colIndex].HeaderText = reader.LanguageNameList[colIndex];
                if (reader.LangNameANSIUnconvertableFlagList[colIndex])
                {
                    this.dataGridViewTextMod.Columns[colIndex].HeaderCell.Style.ForeColor = Color.Red;
                }
            }
            
            for(int rowIndex = 0; rowIndex < reader.TextTableRow; rowIndex++)
            {
                int currentRowIndex = this.dataGridViewTextMod.Rows.Add();
                this.dataGridViewTextMod.Rows[currentRowIndex].HeaderCell.Value = reader.TextCastNameList[rowIndex];
                if (reader.TextNameANSIUnconvertableFlagList[rowIndex])
                {
                    this.dataGridViewTextMod.Rows[currentRowIndex].HeaderCell.Style.ForeColor = Color.Red;
                }

                for(int colIndex = 0; colIndex < reader.TextTableColumn; colIndex++)
                {
                    var textData = reader.TextDataTable[rowIndex, colIndex];
                    if(textData != null)
                    {
                        this.dataGridViewTextMod.Rows[rowIndex].Cells[colIndex].Value = textData.Text;
                        if (!textData.CanConvertToANSI)
                        {
                            // ANSI(shift_jis)変換出来ないテキストは赤色表示
                            this.dataGridViewTextMod.Rows[rowIndex].Cells[colIndex].Style.ForeColor = Color.Red;
                        }
                    }
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
            this.textBoxTextModification.BackColor = SystemColors.Control;
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
            string colorStr = ", Color: #" + textData.FontColor.ToHexRGBString();
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
                this.dataGridViewTextMod.Columns[langIndex].HeaderText = GetTargetColumnHeaderText(langIndex);
            }
        }


        private void SetImportFormSettingToAppData(ApplicationData appData)
        {
            appData.ImportExcelFilePath = this.textBoxImportFile.Text;

            appData.Flags[ApplicationData.FLAG_ADD_IF_LANG_PAGE_NOT_FOUND] = this.checkBoxAddLangPage.Checked;
            appData.Flags[ApplicationData.FLAG_ADD_IF_TEXT_CAST_NOT_FOUND] = this.checkBoxAddTextCast.Checked;
            appData.Flags[ApplicationData.FLAG_CREATE_AS_UNICODE_TEXT_CAST] = this.checkBoxCreateAsUnicode.Checked;
            appData.Flags[ApplicationData.FLAG_NOT_UPDATE_EXISTING_TEXT_CAST] = this.checkBoxNotUpdate.Checked;
            appData.Flags[ApplicationData.FLAG_INHERIT_PROPS_OF_THE_FIRST_LANG_PAGE] = this.checkBoxInheritProperty.Checked;
            appData.Flags[ApplicationData.FLAG_INHERIT_ONLY_NEW_LANG_PAGE] = this.checkBoxInheritOnlyNewLang.Checked;

            appData.Flags[ApplicationData.FLAG_APPLY_FONT_NAME] = this.checkBoxApplyFontname.Checked;
            appData.Flags[ApplicationData.FLAG_APPLY_FONT_SIZE] = this.checkBoxApplyFontSize.Checked;
            appData.Flags[ApplicationData.FLAG_APPLY_TEXT_COLOR] = this.checkBoxApplyTextColor.Checked;
            appData.Flags[ApplicationData.FLAG_APPLY_STRING] = this.checkBoxApplyString.Checked;
            appData.Flags[ApplicationData.FLAG_LOG_OUTPUT] = this.checkBoxLogOutput.Checked;
        }


        private void SetEnableUIAfterExcelImport()
        {
            // デフォルト言語指定機能、サブキャスト機能、インポート機能を有効に
            this.buttonDefaultLanguage.Enabled = true;
            this.buttonOption.Enabled = true;
            this.buttonImport.Enabled = true;
            // Apply propertiesを有効に
            this.checkBoxApplyFontname.Enabled = true;
            this.checkBoxApplyFontSize.Enabled = true;
            this.checkBoxApplyTextColor.Enabled = true;
        }


        private int GetLabelTextModTopRightXPosition()
        {
            var targetLabel = this.labelTextModification;
            return targetLabel.Location.X + targetLabel.Size.Width; ;
        }


        private string GetTargetColumnHeaderText(int colIndex)
        {
            string headerText;

            if(colIndex == this.appData.DefaultLanguageIndex)
            {
                headerText = this.appData.LanguageNameList[colIndex] + " (DEFAULT)";
            }
            else if(this.appData.OptionData.Flags[OptionData.FLAG_USE_SUBCAST_NAME] &&
                (colIndex == this.appData.OptionData.SubcastIndex))
            {
                headerText = string.Format("Subcast({0})", this.appData.LanguageNameList[colIndex]);
            }
            else
            {
                headerText = this.appData.LanguageNameList[colIndex];
            }

            return headerText;
        }


        private void PaintSubcastInfoToSelectedColumn(int targetColIndex)
        {
            // 列ごとにセルの修飾変更を行う
            for(int colIndex = 0; colIndex < this.dataGridViewTextMod.Columns.Count; colIndex++)
            {
                // ターゲット列は黄色、それ以外の列はデフォルト色
                Color headerCellColor = (colIndex == targetColIndex) ? Color.Yellow : this.dataGridViewTextMod.DefaultCellStyle.BackColor;
                Color cellColor = (colIndex == targetColIndex) ? Color.LightGoldenrodYellow : this.dataGridViewTextMod.DefaultCellStyle.BackColor;

                // ターゲット列のヘッダテキストは、"Subcast(言語名)"
                string headerText = GetTargetColumnHeaderText(colIndex);

                // 列ヘッダの色を変更する
                this.dataGridViewTextMod.Columns[colIndex].HeaderCell.Style.BackColor = headerCellColor;
                // 列ヘッダのテキストを変更する
                this.dataGridViewTextMod.Columns[colIndex].HeaderText = headerText;

                // 列ヘッダ以外のセルの修飾変更を行う
                for(int rowIndex = 0; rowIndex < this.dataGridViewTextMod.Rows.Count; rowIndex++)
                {
                    // 各行のセルの色を変更する
                    this.dataGridViewTextMod[colIndex, rowIndex].Style.BackColor = cellColor;
                }
            }
        }

        private void buttonClose_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void buttonImportFile_Click(object sender, EventArgs e)
        {
            // ファイルパス取得
            string filename = GetFileNameFromOpenFileDialog();
            if (string.Empty == filename)
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

            // デフォルト言語指定機能、サブキャスト機能、インポート機能を有効に
            SetEnableUIAfterExcelImport();

            // ファイルパスを表示
            this.textBoxImportFile.Text = filename;
        }

        private void buttonOption_Click(object sender, EventArgs e)
        {
            var optionForm = new OptionForm(this.appData);
            if(DialogResult.OK != optionForm.ShowDialog(this))
            {
                return;
            }

            if (this.appData.OptionData.Flags[OptionData.FLAG_USE_SUBCAST_NAME])
            {
                // デフォルト言語とサブキャスト名選択が被った場合、デフォルト設定を解除する
                if(this.appData.OptionData.SubcastIndex == this.appData.DefaultLanguageIndex)
                {
                    this.appData.DefaultLanguageIndex = -1;
                }

                // テーブル表示をサブキャスト名選択状態に変更する
                PaintSubcastInfoToSelectedColumn(this.appData.OptionData.SubcastIndex);
            }
            else
            {
                // サブキャスト名設定を解除した状態でテーブルを表示する
                PaintSubcastInfoToSelectedColumn(-1);
            }

        }

        private void buttonDefaultLanguage_Click(object sender, EventArgs e)
        {
            // デフォルト言語選択フォームを展開する
            var langForm = new SelectLangForm(this.appData.LanguageNameList, this.appData.DefaultLanguageIndex, this.appData.OptionData.SubcastIndex);
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
            // 言語ページ、キャスト名はANSI指定
            // ページ名候補（列タイトル）、キャスト名（行タイトル）、サブキャストセルデータにANSI変換できないフラグが１つでも
            // あれば、ユーザに確認し、アンダーラインへの変換を許可できなければ、処理中止
            bool ansiUnconvertableFlag = appData.NamesANSIUnconvertableFlag;
            if (ansiUnconvertableFlag)
            {
                if (MessageBox.Show(this, Properties.Resources.WARN_NAME_CONTAINS_NOT_ANSI, "Question", MessageBoxButtons.OKCancel)
                    != DialogResult.OK)
                {
                    return;
                }
            }

            // 「テキストキャストをUnicode作る」チェックを付けていない（ANSIで作る）時、
            // ANSIにコンバート出来ないテキストが１つでもあれば、ユーザに確認し、Unicodeでの作成に転向したくなければ処理中止
            bool flagCreateAsUnicode = this.checkBoxCreateAsUnicode.Checked;
            bool hasUnconvertableTextFlag = appData.TextDataANSIUnconvertableFlag;
            if((!flagCreateAsUnicode) && hasUnconvertableTextFlag)
            {
                if (MessageBox.Show(this, Properties.Resources.WARN_TEXTCAST_CONTAINS_NOT_ANSI, "Question", MessageBoxButtons.OKCancel)
                    != DialogResult.OK)
                {
                    return;
                }
            }

            // フォームのチェックボックス設定をアプリ管理データにセットする
            SetImportFormSettingToAppData(this.appData);

            // フォーム呼び出し元に通知OK
            this.DialogResult = DialogResult.OK;

            this.Close();
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
