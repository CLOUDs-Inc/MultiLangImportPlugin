using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing;

using Excel = Microsoft.Office.Interop.Excel;
using System.Reflection;
using System.Runtime.InteropServices;

namespace MultiLangImportDotNet.TextExcel
{
    /// <summary>
    /// 多言語インポート用Excelファイル読み取りクラス
    /// </summary>
    public class ExcelReader
    {
        /// <summary>
        /// 多言語情報テーブルの左上・基点を示すタグ文字列
        /// </summary>
        public const string TAG_STRING_BASE_CELL = "##";

        /// <summary>
        /// 多言語テキストデータテーブル
        /// </summary>
        public Import.TextData[,] TextDataTable { get; private set; }

        /// <summary>
        /// 言語名リスト
        /// </summary>
        public List<string> LanguageNameList { get; private set; }

        /// <summary>
        /// 言語名ANSI変換不可フラグ（赤表示）リスト
        /// </summary>
        public List<bool> LangNameANSIUnconvertableFlagList { get; private set; }

        /// <summary>
        /// 言語列ごとにテキストに使用不可文字が含まれているかのリスト
        /// </summary>
        public List<bool> LangHasTextWithUnusableCharList { get; private set; }

        /// <summary>
        /// テキストキャスト名リスト
        /// </summary>
        public List<string> TextCastNameList { get; private set; }

        /// <summary>
        /// テキストキャスト名ANSI変換不可フラグ（赤表示）リスト
        /// </summary>
        public List<bool> TextNameANSIUnconvertableFlagList { get; private set; }

        /// <summary>
        /// インポートテキストテーブルの行数（テキストキャストの数）
        /// </summary>
        public int TextTableRow
        {
            get
            {
                if (TextCastNameList == null)
                    return 0;
                return TextCastNameList.Count;
            }
        }

        /// <summary>
        /// インポートテキストテーブルの列数（言語名の数）
        /// </summary>
        public  int TextTableColumn
        {
            get
            {
                if (LanguageNameList == null)
                    return 0;
                return LanguageNameList.Count;
            }
        }

        /// <summary>
        /// Multi Language Import Excelファイルパス
        /// </summary>
        public string FilePathExcel { get; private set; }

        /// <summary>
        /// キャスト名索引によるテキストキャストデータ辞書
        /// </summary>
        public OrderedDictionary TextCastDictionary { get; private set; }

        /// <summary>
        /// 出力スクリプト文字列
        /// </summary>
        public string OutputCode { get; private set; }

        public ExcelReader()
        {
        }

        /// <summary>
        /// 多言語テキストデータ定義Excelファイルの読み取り
        /// </summary>
        /// <param name="filepath">Excelファイルパス</param>
        /// <returns>成否</returns>
        public bool OpenExcel(string filepath)
        {
            bool result = false;

            List<string> langNameList = new List<string>();
            List<bool> langNameANSIUnconvertableFlagList = new List<bool>();
            bool[] unusableCharLangNameFlags = null;
            List<string> textNameList = new List<string>();
            List<int> textNameSkipIndexList = new List<int>();
            List<bool> textNameANSIUnconvertableFlagList = new List<bool>();
            Import.TextData[,] textDataTable = null;

            string ML_TEXT_TABLE_SHEET_RANGE_pre = "A1:"; // Multi-lang text table 多言語テキスト対応シート使用レンジテンプレート

            //Logger logger = Logger.GetInstance();

            // Multi Language Table Excelファイルパス用のファイルダイアログ展開
            this.FilePathExcel = filepath;

            var textcastDictionary = new OrderedDictionary();

            // 各finallyブロックで、アクセスしたExcel COMオブジェクトをReleaseする必要がある
            // （Release忘れでプロセスが残り、次のExcelファイル展開時に例外発生する）ので
            // 参照するオブジェクトを１段階ずつ変数に保持しておく
            try
            {   
                // Excel Application block
                var excelApp = new Excel.Application();
                excelApp.Visible = false;
                try
                {
                    // Workbooks block
                    Excel.Workbooks oWBs = excelApp.Workbooks;
                    try
                    {
                        // Workbook block (Multi-lang text table)
                        // Multi Language Tableエクセルを展開する
                        Excel.Workbook oWorkbookMultiLang = oWBs.Open(this.FilePathExcel);
                        try
                        {
                            //logger.Log($"Multi Lang Table Opened: {this.FilePathExcel}");

                            // Sheets block
                            var worksheets = oWorkbookMultiLang.Sheets;
                            try
                            {
                                // Worksheet block
                                var sheetML = worksheets[1];
                                try
                                {
                                    //logger.Log("Multi Lang Sheet Opened.");

                                    // A列の"##"がある行を走査する
                                    int rowFirst = 0;
                                    int rowSecond = 0;
                                    int rowLang = 0;
                                    int rowStart = 0;
                                    int rowEnd = 0;
                                    var columns = sheetML.Columns;
                                    var col1 = columns[1];
                                    var col1FirstFound = col1.Find("##", SearchOrder: Excel.XlSearchOrder.xlByRows);
                                    if(col1FirstFound != null)
                                    {
                                        // A列の"##"がある最初の行をチェックする
                                        rowFirst = col1FirstFound.Row;

                                        // A列の"##"があるもう一つの行をチェックする
                                        var col1SecondFound = col1.Find("##", After: col1FirstFound, SearchOrder: Excel.XlSearchOrder.xlByRows);
                                        if (col1SecondFound != null)
                                        {
                                            rowSecond = col1SecondFound.Row;
                                            Marshal.ReleaseComObject(col1SecondFound);
                                        }

                                        Marshal.ReleaseComObject(col1FirstFound);
                                    }

                                    Marshal.ReleaseComObject(col1);
                                    Marshal.ReleaseComObject(columns);

                                    // 行数が確認できなかった場合は、例外で処理終了
                                    if(rowFirst <= 0 || rowSecond <= 0 )
                                    {
                                        throw new Exception();
                                    }

                                    if (rowFirst <= rowSecond)
                                    {
                                        rowLang = rowFirst;
                                        rowEnd = rowSecond;
                                    }
                                    else
                                    {
                                        rowLang = rowSecond;
                                        rowEnd = rowFirst;
                                    }


                                    // データ行の開始は言語名の行の次
                                    rowStart = rowLang + 1;

                                    // "##"が見つかった行を走査してどの列まで言語名で埋まっているかを確認する
                                    int colStart = 2;
                                    int colEnd = 0;
                                    string colEndLetter = string.Empty;
                                    var rows = sheetML.Rows;
                                    var rowLangName = rows[rowLang];
                                    var rowLangNameEmptyFound = rowLangName.Find(string.Empty, SearchOrder: Excel.XlSearchOrder.xlByColumns);
                                    if(rowLangNameEmptyFound != null)
                                    {
                                        colEnd = rowLangNameEmptyFound.Column;
                                        colEndLetter = Utils.GetExcelColumnName(colEnd);

                                        Marshal.ReleaseComObject(rowLangNameEmptyFound);
                                    }

                                    Marshal.ReleaseComObject(rowLangName);
                                    Marshal.ReleaseComObject(rows);

                                    if((colEnd <= 0) || (colEnd <= colStart))
                                    {
                                        throw new Exception();
                                    }

                                    // "A1:" + 言語名でブランクが見つかった列 + テキストキャスト名で"##"が見つかった行
                                    string ML_TEXT_TABLE_SHEET_RANGE =
                                        ML_TEXT_TABLE_SHEET_RANGE_pre + colEndLetter + rowEnd.ToString();

                                    Excel.Range usedRange = sheetML.Range[ML_TEXT_TABLE_SHEET_RANGE];

                                    try
                                    {
                                        // A列（テキストキャスト名）の先頭と末尾が判明したので、テキストキャスト名を収集する
                                        for (int rowIndex = rowStart; rowIndex < rowEnd; rowIndex++)
                                        {
                                            var castNameCell = usedRange[rowIndex, 1];
                                            string castname = castNameCell.Value as string;
                                            if (!string.IsNullOrWhiteSpace(castname))
                                            {
                                                bool ansiConvertable = Utils.ANSIConvertTest(castname);
                                                castname = Utils.CorrectCastNameForGrid(castname);
                                                textNameList.Add(castname);
                                                textNameANSIUnconvertableFlagList.Add(!ansiConvertable);
                                            }
                                            else
                                            {
                                                // テキストキャスト名が空白でスキップした行インデックスを記録する
                                                textNameSkipIndexList.Add(rowIndex);
                                            }

                                            Marshal.ReleaseComObject(castNameCell);
                                        }

                                        // 言語名の行の先頭列と末尾列が判明したので、言語名を収集する
                                        for (int colIndex = colStart; colIndex < colEnd; colIndex++)
                                        {
                                            var langNameCell = usedRange[rowLang, colIndex];
                                            string langName = langNameCell.Value as string;
                                            bool ansiConvertable = Utils.ANSIConvertTest(langName);
                                            //langName = Utils.ChangeUnusableCharToUnderscore(langName);
                                            langNameList.Add(langName);
                                            langNameANSIUnconvertableFlagList.Add(!ansiConvertable);

                                            Marshal.ReleaseComObject(langNameCell);
                                        }

                                        // テキストデータの行数と列数が確定したので、格納用データテーブルをnewする
                                        textDataTable = new Import.TextData[
                                            rowEnd - rowStart - textNameSkipIndexList.Count,
                                            colEnd - colStart];

                                        // 列数が確定：言語数が確定したので、Subcast名として使えない単語が存在する言語かどうかのフラグ配列をnewする
                                        unusableCharLangNameFlags = new bool[colEnd - colStart];

                                        //for (int rowIndex = 0; rowIndex < (rowEnd - rowStart - 1); rowIndex++)
                                        int targetRowIndex = 0;
                                        for (int rowIndex = rowStart; rowIndex < rowEnd; rowIndex++)
                                        {
                                            if (textNameSkipIndexList.Contains(rowIndex))
                                            {
                                                continue;
                                            }

                                            for (int colIndex = colStart; colIndex < colEnd; colIndex++)
                                            {
                                                var dataCell = usedRange[rowIndex, colIndex];
                                                try
                                                {
                                                    if (dataCell == null)
                                                    {
                                                        continue;
                                                    }

                                                    string text = dataCell.Value as string;
                                                    if(text != null)
                                                    {
                                                        // テキストにキャスト名使用不可文字含有チェック
                                                        bool hasUnusableChar = Utils.CheckNameHitUnusableSymbols(text);
                                                        // テキスト：ANSI変換可否チェック
                                                        bool canConvToANSI = Utils.ANSIConvertTest(text);

                                                        // テキストにキャスト名使用不可文字が含まれていたら
                                                        // テキストがANSI変換不可能だったら
                                                        if (hasUnusableChar || !canConvToANSI)
                                                        {
                                                            // その言語列はsubcast名として使えないとしてフラグを立てる
                                                            unusableCharLangNameFlags[colIndex - colStart] = true;
                                                        }


                                                        var dataCellFirstChar = dataCell.Characters[1, 1];
                                                        try
                                                        {
                                                            if (dataCellFirstChar != null)
                                                            {
                                                                var dataCellFont = dataCellFirstChar.Font;
                                                                try
                                                                {
                                                                    string fontname = dataCellFont.Name as string;
                                                                    fontname = (fontname == null ? string.Empty : fontname);

                                                                    float fontsize = 9f;
                                                                    if (dataCellFont.Size != null)
                                                                    {
                                                                        fontsize = (float)dataCellFont.Size;
                                                                    }

                                                                    Color fontColor = ColorTranslator.FromOle((int)dataCellFont.Color);
                                                                    bool isBold = (bool)dataCellFont.Bold;
                                                                    bool isItalic = (bool)dataCellFont.Italic;
                                                                    Excel.XlUnderlineStyle underlineStyle = (Excel.XlUnderlineStyle)dataCellFont.Underline;
                                                                    bool isUnderline = (underlineStyle != Excel.XlUnderlineStyle.xlUnderlineStyleNone);
                                                                    bool isStrike = (bool)dataCellFont.Strikethrough;

                                                                    // 抽出したテキストデータをテーブルに格納する
                                                                    textDataTable[targetRowIndex, colIndex - colStart]
                                                                        = new Import.TextData(
                                                                            text, fontname, fontsize, fontColor,
                                                                            isBold, isItalic, isUnderline, isStrike, canConvToANSI
                                                                            );
                                                                }
                                                                finally { Marshal.ReleaseComObject(dataCellFont); }

                                                            }
                                                        }
                                                        finally { Marshal.ReleaseComObject(dataCellFirstChar); }
                                                    }
                                                }
#if DEBUG
                                                catch (Exception ex)
                                                {
                                                    string msg = "Ex:" + ex.Message;
                                                    MessageBox.Show(msg);
                                                }
#endif
                                                finally { Marshal.ReleaseComObject(dataCell); }
                                            }

                                            // 次の格納行
                                            targetRowIndex++;
                                        }

                                        // テキストデータテーブルの作成完了（Excelの読み取り処理終了）
                                        // 収集データをインターフェース用プロパティにセット
                                        this.TextDataTable = textDataTable;
                                        this.LanguageNameList = langNameList;
                                        this.LangNameANSIUnconvertableFlagList = langNameANSIUnconvertableFlagList;
                                        this.TextCastNameList = textNameList;
                                        this.TextNameANSIUnconvertableFlagList = textNameANSIUnconvertableFlagList;
                                        this.LangHasTextWithUnusableCharList = unusableCharLangNameFlags.ToList();

                                        // 処理成功
                                        result = true;
                                    }
                                    finally { Marshal.ReleaseComObject(usedRange); }
                                }
                                finally
                                {
                                    Marshal.ReleaseComObject(sheetML);
                                    //logger.Log("Multi Lang Sheet Closed.");
                                }
                                // Worksheet(MultiLang) block
                            }
                            finally { Marshal.ReleaseComObject(worksheets); }
                            // Sheets block END
                        }
                        finally
                        {
                            if (oWorkbookMultiLang != null)
                            {
                                oWorkbookMultiLang.Close(false);
                            }
                            Marshal.ReleaseComObject(oWorkbookMultiLang);
                        }
                        // Workbook block (Multi-lang text table) END
                    }
                    finally
                    {
                        Marshal.ReleaseComObject(oWBs);
                    }
                    // Workbooks block END
                }
                finally
                {
                    if (excelApp != null)
                    {
                        excelApp.Quit();
                    }
                    Marshal.ReleaseComObject(excelApp);
                }
                // Excel Application block END
            }
            catch
            {
                result = false;
            }

            return result;
        }

        /// <summary>
        /// テキスト着せ替え用Excelファイル選択用ファイルダイアログの展開
        /// </summary>
        /// <param name="title">ダイアログの説明用文言</param>
        /// <returns>ファイルパス、（キャンセル時string.Empty）</returns>
        private string GetFileNameFromOpenFileDialog(string title)
        {
            string fileName = string.Empty;

            using (OpenFileDialog ofDialog = new OpenFileDialog())
            {
                ofDialog.Title = title;
                ofDialog.Filter = "xlsx files (*.xlsx)|*.xlsx";
                ofDialog.RestoreDirectory = true;

                if (ofDialog.ShowDialog() == DialogResult.OK)
                {
                    fileName = ofDialog.FileName;
                }
            }

            return fileName;
        }

        /// <summary>
        /// 各Statusで何行ずれるかのOffsetテーブル
        /// </summary>
        readonly int[] rowOffsetTableStatus = { 0, 1, 2, 3 };


    }
}
