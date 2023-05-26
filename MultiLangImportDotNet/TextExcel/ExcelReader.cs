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

using NPOI.SS.UserModel;
using NPOI.XSSF.UserModel;
using NPOI.HSSF.Util;
using NPOI.SS.Util;


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

        public ExcelReader()
        {
        }

        public bool OpenExcelNPOI(string filepath)
        {
            List<string> langNameList = new List<string>();
            List<bool> langNameANSIUnconvertableFlagList = new List<bool>();
            bool[] unusableCharLangNameFlags;
            List<string> textNameList = new List<string>();
            List<int> textNameSkipIndexList = new List<int>();
            List<bool> textNameANSIUnconvertableFlagList = new List<bool>();
            Import.TextData[,] textDataTable;


            // Multi Language Table Excelファイルパス用のファイルダイアログ展開
            this.FilePathExcel = filepath;

            //既存のExcelブックを読み込む
            IWorkbook book = WorkbookFactory.Create(filepath);
            int sheetIndex = SelectSheetNPOI(book);
            if(sheetIndex < 0)
            {
                MessageBox.Show("Sheet selection stop.");
                return false;
            }
            var sheet = book.GetSheetAt(sheetIndex);

            int rowLangIndex = 0;
            int rowStartIndex;
            int rowEndIndex = 0;

            // A列の"##"がある行を走査する
            bool tagFound = false;
            for (int rowIndex = 0; rowIndex < 100; rowIndex++)
            {
                var row = sheet.GetRow(rowIndex);
                if (row == null) { continue; }
                var cell = row.GetCell(0);
                if(cell == null) { continue; }
                var text = cell.StringCellValue;

                if (text.Trim().Equals(TAG_STRING_BASE_CELL))
                {
                    tagFound = true;
                    rowLangIndex = rowIndex;
                    break;
                }
            }
            // 何行か探して##がなかったのでエラー
            if (!tagFound)
            {
                MessageBox.Show("Language row not found in 100 rows.");
                return false;
            }

            // "##"が見つかった行を走査してどの列まで言語名で埋まっているかを確認する
            int colStart = 1;
            int colEnd = 0;
            var rowLangName = sheet.GetRow(rowLangIndex);
            for (int colIndex = colStart; colIndex < 1000; colIndex++)
            {
                colEnd = colIndex;
                var cell = rowLangName.GetCell(colIndex);
                if(cell == null)
                {
                    break;
                }
                var langName = cell.StringCellValue;
                if (string.IsNullOrWhiteSpace(langName))
                {
                    break;
                }

                // 言語名の確保
                bool ansiConvertable = Utils.ANSIConvertTest(langName);
                langNameList.Add(langName);
                langNameANSIUnconvertableFlagList.Add(!ansiConvertable);
            }

            // データ行の開始は言語名の行の次
            rowStartIndex = rowLangIndex + 1;

            tagFound = false;
            for (int rowIndex = rowStartIndex; rowIndex < int.MaxValue; rowIndex++)
            {
                rowEndIndex = rowIndex;

                // 0列目（最初の列）
                var row = sheet.GetRow(rowIndex);
                if (row == null)
                {
                    // テキストキャスト名が空白でスキップした行インデックスを記録する
                    textNameSkipIndexList.Add(rowIndex);
                    continue;
                }

                var cell = row.GetCell(0);
                if (cell == null)
                {
                    // テキストキャスト名が空白でスキップした行インデックスを記録する
                    textNameSkipIndexList.Add(rowIndex);
                    continue;
                }

                var castname = cell.StringCellValue;
                // ２回目の##を見つけた所で終了
                if (castname.Trim().Equals(TAG_STRING_BASE_CELL))
                {
                    tagFound = true;
                    break;
                }

                // テキストキャスト名を収集する
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
            }

            // 何行か探して##がなかったのでエラー
            if (!tagFound)
            {
                MessageBox.Show("Data Terminator not found in integer MAX value rows.");
                return false;
            }

            // テキストデータの行数と列数が確定したので、格納用データテーブルをnewする
            textDataTable = new Import.TextData[
                rowEndIndex - rowStartIndex - textNameSkipIndexList.Count,
                colEnd - colStart];

            // 列数が確定：言語数が確定したので、Subcast名として使えない単語が存在する言語かどうかのフラグ配列をnewする
            unusableCharLangNameFlags = new bool[colEnd - colStart];

            int targetRowIndex = 0;
            for (int rowIndex = rowStartIndex; rowIndex < rowEndIndex; rowIndex++)
            {
                if (textNameSkipIndexList.Contains(rowIndex))
                {
                    continue;
                }

                var row = sheet.GetRow(rowIndex);
                for (int colIndex = colStart; colIndex < colEnd; colIndex++)
                {
                    var dataCell = row.GetCell(colIndex);
                    if (dataCell == null)
                    {
                        continue;
                    }

                    string text = null;

                    switch (dataCell.CellType)
                    {
                        case CellType.Numeric:
                            var val = dataCell.NumericCellValue;
                            text = val.ToString();
                            break;
                        case CellType.String:
                            text = dataCell.StringCellValue;
                            break;
                    }
                    if (text != null)
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

                        var style = dataCell.CellStyle;
                        var font = style.GetFont(book);
                        var xssfFont = (font as XSSFFont);
                        byte[] rgb = { 0, 0, 0 };
                        if(xssfFont != null)
                        {
                            var xssfColor = xssfFont.GetXSSFColor();
                            if(xssfColor != null)
                            {
                                rgb = xssfColor.RGB;
                            }
                        }
                        float fontsize = (float)font.FontHeightInPoints;
                        string fontname = font.FontName;
                        fontname = fontname ?? string.Empty;
                        Color fontColor = Color.FromArgb((int)rgb[0], (int)rgb[1], (int)rgb[2]);
                        bool isBold = false; // RG14未使用
                        bool isItalic = false; // RG14未使用
                        bool isUnderline = false; // RG14未使用
                        bool isStrike = false; // RG14未使用

                        // 抽出したテキストデータをテーブルに格納する
                        textDataTable[targetRowIndex, colIndex - colStart]
                            = new Import.TextData(
                                text, fontname, fontsize, fontColor,
                                isBold, isItalic, isUnderline, isStrike, canConvToANSI
                              );
                    }
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
            return true;
        }

        /// <summary>
        /// Excelブックからシートとそのインデックスを指定する
        /// </summary>
        /// <param name="workbook">Excelブック</param>
        /// <returns>シートインデックス（-1:未選択）</returns>
        public int SelectSheetNPOI(IWorkbook workbook)
        {
            int index = -1;
            
            if(workbook.NumberOfSheets == 1)
            {
                return 0;
            }

            List<string> nameList = new List<string>();
            for(int sheetIndex = 0; sheetIndex < workbook.NumberOfSheets; sheetIndex++)
            {
                var sheet = workbook.GetSheetAt(sheetIndex);
                nameList.Add(sheet.SheetName);
            }

            string explanation = "Select a worksheet to import.";
            string windowTitle = "Select a worksheet";
            Import.SelectTextForm selectTextForm = new Import.SelectTextForm(nameList, explanation, windowTitle);
            if(DialogResult.OK == selectTextForm.ShowDialog())
            {
                index = selectTextForm.SelectedIndex;
            }
            else
            {
                index = -1;
            }
    
            return index;
        }


        /// <summary>
        /// 多言語テキストデータ定義Excelファイルの読み取り
        /// 未使用
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
                            // Sheets block
                            var worksheets = oWorkbookMultiLang.Sheets;
                            try
                            {
                                // Worksheet block
                                var sheetML = worksheets[1];
                                try
                                {
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

        public void NPOITest()
        {
            string filepath = @"C:\Users\Tsuge\Documents\npoi_test_many.xlsx";


            //既存のExcelブックを読み込む
            IWorkbook book = WorkbookFactory.Create(filepath);
            var sheet = book.GetSheetAt(0);

            for (int rowIndex = 0; rowIndex < 80; rowIndex++)
            {
                var row = sheet.GetRow(rowIndex);
                for (int colIndex = 0; colIndex < 5; colIndex++)
                {
                    var cell = row.GetCell(colIndex);

                    var str = cell.StringCellValue;
                    var style = cell.CellStyle;
                    var font = style.GetFont(book);
                    var rgb = (font as XSSFFont).GetXSSFColor().RGB;

                    int point = (int)font.FontHeightInPoints;
                    string fontname = font.FontName;

                    Console.WriteLine("cell({0},{1}): text:{2} size:{3} font:{4} color[{5},{6},{7}]", rowIndex, colIndex, str, point, fontname, rgb[0], rgb[1], rgb[2]);


                }
            }

        }
    }
}
