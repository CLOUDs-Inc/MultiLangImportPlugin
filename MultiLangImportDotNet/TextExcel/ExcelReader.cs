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
        /// 言語列ごとにテキストに使用不可文字が含まれているかのリスト
        /// </summary>
        public List<bool> LangHasTextWithUnusableCharList { get; private set; }

        /// <summary>
        /// テキストキャスト名リスト
        /// </summary>
        public List<string> TextCastNameList { get; private set; }

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
            bool[] unusableCharLangNameFlags = null;
            List<string> textNameList = new List<string>();
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
                                    int rowLang = 0;
                                    int rowStart = 0;
                                    int rowEnd = 0;
                                    var columns = sheetML.Columns;
                                    var col1 = columns[1];
                                    var col1StartFound = col1.Find("##", SearchOrder: Excel.XlSearchOrder.xlByRows);
                                    if(col1StartFound != null)
                                    {
                                        // A列の"##"がある行の後に""のある行を走査する
                                        rowLang = col1StartFound.Row;
                                        
                                        var col1EndFound = col1.Find(string.Empty, After: col1StartFound, SearchOrder: Excel.XlSearchOrder.xlByRows);
                                        if(col1EndFound != null)
                                        {
                                            rowEnd = col1EndFound.Row;
                                            Marshal.ReleaseComObject(col1EndFound);
                                        }

                                        Marshal.ReleaseComObject(col1StartFound);
                                    }

                                    Marshal.ReleaseComObject(col1);
                                    Marshal.ReleaseComObject(columns);

                                    // 行数が確認できなかった場合は、例外で処理終了
                                    if((rowLang <= 0) || (rowEnd <= rowLang))
                                    {
                                        throw new Exception();
                                    }

                                    // データ行の開始は"##"のある行（言語名行）の次
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

                                    // テキストデータの行数と列数が確定したので、格納用データテーブルをnewする
                                    textDataTable = new Import.TextData[rowEnd - rowStart, colEnd - colStart];

                                    // 列数が確定：言語数が確定したので、Subcast名として使えない単語が存在する言語かどうかのフラグ配列をnewする
                                    unusableCharLangNameFlags = new bool[colEnd - colStart];

                                    // "A1:" + 言語名でブランクが見つかった列 + テキストキャスト名でブランクが見つかった行
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
                                            castname = Utils.ChangeUnusableCharToUnderscore(castname);
                                            textNameList.Add(castname);

                                            Marshal.ReleaseComObject(castNameCell);
                                        }

                                        // 言語名の行の先頭列と末尾列が判明したので、言語名を収集する
                                        for (int colIndex = colStart; colIndex < colEnd; colIndex++)
                                        {
                                            var langNameCell = usedRange[rowLang, colIndex];
                                            string langName = langNameCell.Value as string;
                                            langName = Utils.ChangeUnusableCharToUnderscore(langName);
                                            langNameList.Add(langName);

                                            Marshal.ReleaseComObject(langNameCell);
                                        }

                                        //for (int rowIndex = 0; rowIndex < (rowEnd - rowStart - 1); rowIndex++)
                                        for (int rowIndex = rowStart; rowIndex < rowEnd; rowIndex++)
                                        {
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
                                                        bool hasUnusableChar = Utils.CheckNameHitUnusableChars(text);
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
                                                                    textDataTable[rowIndex - rowStart, colIndex - colStart]
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
                                        }

                                        // テキストデータテーブルの作成完了（Excelの読み取り処理終了）
                                        // 収集データをインターフェース用プロパティにセット
                                        this.TextDataTable = textDataTable;
                                        this.LanguageNameList = langNameList;
                                        this.TextCastNameList = textNameList;
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

        /// <summary>
        /// Cellsデータを走査してFontColorオブジェクトを生成
        /// </summary>
        /// <param name="rangeArray">必要範囲Cellデータのコピー後Object配列</param>
        /// <param name="appearanceIndex">登場順番番号</param>
        /// <param name="rowIndex">各Font色IDの先頭行インデックス</param>
        /// <returns>FontColorオブジェクト</returns>
        //private FontColor GetFontColor(object[,] rangeArray, int appearanceIndex, int rowIndex)
        //{
        //    // Cellデータの１列目のFont色ID文字列を取得
        //    string strFontColorID = (string)rangeArray[rowIndex, 1];
        //    if (string.IsNullOrWhiteSpace(strFontColorID))
        //    {
        //        return null;
        //    }

        //    strFontColorID = strFontColorID.Trim();

        //    // Font色ID毎にType数 * 4 Status = 12のStatusColorオブジェクトのリスト 
        //    var statusColorList = new List<StatusColor>();

        //    foreach (TypeID typeID in Enum.GetValues(typeof(TypeID)))
        //    {
        //        foreach (Status status in Enum.GetValues(typeof(Status)))
        //        {
        //            // TypeとStatusを指定して、CellデータからStatusColorオブジェクトを読み取る
        //            var statusColor = GetStatusColor(rangeArray, rowIndex, status, typeID);
        //            statusColorList.Add(statusColor);
        //        }
        //    }

        //    return new FontColor(strFontColorID, appearanceIndex, statusColorList);
        //}

        /// <summary>
        /// Cellsデータから指定行、指定Status, 指定TypeのStatusColorデータを取得する
        /// </summary>
        /// <param name="rangeArray">必要範囲Cellデータのコピー後Object配列</param>
        /// <param name="rowIndex">読み取り対象行インデックス</param>
        /// <param name="status">読み取り対象Status</param>
        /// <param name="typeID">読み取り対象Type</param>
        /// <returns>StatusColorオブジェクト</returns>
        //private StatusColor GetStatusColor(object[,] rangeArray, int rowIndex, Status status, TypeID typeID)
        //{
        //    // 各Statusを読み取るのに何行ずれるか
        //    int rowOffset = rowOffsetTableStatus[(int)status];

        //    // ４列目がStatus文字列
        //    string strStatus = (string)rangeArray[rowIndex + rowOffset, 4];
        //    strStatus = strStatus.Trim();

        //    StatusColor statusColor = null;

        //    if (status.ToString() == strStatus)
        //    {
        //        // 指定行、指定Status, 指定TypeのRGBデータを読み取ってRGBDataオブジェクトを生成する
        //        var rgbData = GetRGBData(rangeArray, rowIndex, status, typeID);
        //        statusColor = new StatusColor(status, rgbData);
        //    }

        //    return statusColor;
        //}

        /// <summary>
        /// Cellsデータから指定行、指定Status, 指定TypeのRGBDataデータを取得する
        /// </summary>
        /// <param name="rangeArray">必要範囲Cellデータのコピー後Object配列</param>
        /// <param name="rowIndex">>読み取り対象行インデックス</param>
        /// <param name="status">読み取り対象Status</param>
        /// <param name="typeID">読み取り対象Type</param>
        /// <returns>RGBDataオブジェクト</returns>
        //private RGBData GetRGBData(object[,] rangeArray, int rowIndex, Status status, TypeID typeID)
        //{
        //    const int COLUMN_OFFSET_COLOR = 7;       // Colorデータ列までのオフセット
        //    const int COLOR_DATA_COLS_EACH_TYPE = 6; // 各Type毎のデータ列幅

        //    // 各Statusを読み取るのに何行ずれるか
        //    int rowOffset = rowOffsetTableStatus[(int)status];
        //    // 各Typeを読み取るためには何列目か
        //    int colOffset = COLUMN_OFFSET_COLOR + COLOR_DATA_COLS_EACH_TYPE * (int)typeID;

        //    // 色R
        //    int colorR = Utility.ConvertObjTo8BitValue(rangeArray[rowIndex + rowOffset, 0 + colOffset]);
        //    // 色G
        //    int colorG = Utility.ConvertObjTo8BitValue(rangeArray[rowIndex + rowOffset, 1 + colOffset]);
        //    // 色B
        //    int colorB = Utility.ConvertObjTo8BitValue(rangeArray[rowIndex + rowOffset, 2 + colOffset]);

        //    return new RGBData(typeID, colorR, colorG, colorB);
        //}

        /// <summary>
        /// 出力スクリプトコード生成
        /// </summary>
        /// <param name="mlWordArray">Multi Languageデータ配列</param>
        /// <param name="fontColorDictionary">Font Colorデータ辞書</param>
        //private void CreateOutputCode(MLWord[] mlWordArray, OrderedDictionary fontColorDictionary)
        //{
        //    const string TEXT_COLOR_TABLE_NAME = "gTextColorArray";
        //    const string COLOR_TABLE_MACRO_NAME = "TEXT_COLOR_TABLE";

        //    const string LIST_REF_TABLE_NAME = "list_ref";
        //    const string REFERENCE_TABLE_MACRO_NAME = "REF_TABLE";

        //    // スクリプト全体出力用StringBuilder
        //    StringBuilder sbWholeScript = new StringBuilder();

        //    // 全体（ヘッダセクション）
        //    // ========================================================================
        //    sbWholeScript.AppendLine("// ----------------------------------------------------------------------------");
        //    sbWholeScript.AppendLine("// Generated by Dress Up Code (Text) Generator");
        //    sbWholeScript.AppendLine("// ----------------------------------------------------------------------------");
        //    sbWholeScript.AppendLine("##CPP-HEADER");
        //    sbWholeScript.AppendLine();


        //    // ========================================================================
        //    // Text Color Table
        //    // ========================================================================
        //    int textColorDefsCount = 0;

        //    // TextColorマクロ列挙＆参照用テーブル
        //    // =====================
        //    // マクロ列挙用Builder
        //    StringBuilder sbTextColorDefs = new StringBuilder();
        //    sbTextColorDefs.AppendLine("/* TEXT COLOR SET */");
        //    sbTextColorDefs.AppendLine();
        //    sbTextColorDefs.AppendLine("/* TEXT Color Definitions Start */");

        //    // テーブル定義用Builder
        //    StringBuilder sbTextColorTableInside = new StringBuilder();

        //    for (int i = 0; i < fontColorDictionary.Count; i++)
        //    {
        //        var fontColor = fontColorDictionary[i] as FontExcel.FontColor;

        //        foreach (var statusColor in fontColor.StatusColorList)
        //        {
        //            var strFontColorID = fontColor.FontColorID;
        //            var strStatus = statusColor.GetStatusName();
        //            var strType = statusColor.Data.GetTypeString();
        //            string macroName = $"TEXT_COLOR_{strFontColorID}_{strStatus}_{strType}_BGR";
        //            string strBGRValue = statusColor.Data.GetBGR32BitHexForm();

        //            string defMacroLineText = $"#define {macroName} ({strBGRValue})";
        //            string defTableLineText = $"    {macroName},";

        //            sbTextColorDefs.AppendLine(defMacroLineText);

        //            sbTextColorTableInside.AppendLine(defTableLineText);

        //            // マクロ数の数え上げ
        //            textColorDefsCount++;
        //        }
        //    }
        //    sbTextColorDefs.AppendLine("/* TEXT Color Definitions End */");


        //    // Font色ID マクロ列挙
        //    // ===================
        //    StringBuilder sbFontColorIDDefs = new StringBuilder();
        //    sbFontColorIDDefs.AppendLine("/* Font Color ID Definitions */");

        //    for (int i = 0; i < fontColorDictionary.Count; i++)
        //    {
        //        var fontColor = fontColorDictionary[i] as FontExcel.FontColor;

        //        string defineText = $"#define TEXT_TYPE_{fontColor.FontColorID} ({i})";
        //        sbFontColorIDDefs.AppendLine(defineText);
        //    }


        //    // テーブル変数宣言
        //    // ================
        //    StringBuilder sbVarDeclPart = new StringBuilder();
        //    sbVarDeclPart.AppendLine($"extern const unsigned int {TEXT_COLOR_TABLE_NAME}[];");
        //    sbVarDeclPart.AppendLine($"extern const int {LIST_REF_TABLE_NAME}[];");


        //    // ========================================================================
        //    // Table Length Macro
        //    // ========================================================================
        //    sbWholeScript.AppendLine($"#define {COLOR_TABLE_MACRO_NAME}_LENGTH ({textColorDefsCount})");
        //    sbWholeScript.AppendLine($"#define {REFERENCE_TABLE_MACRO_NAME}_LENGTH ({mlWordArray.Length})");
        //    sbWholeScript.AppendLine();

        //    // 全体に追加（テーブル定義）
        //    sbWholeScript.AppendLine(sbTextColorDefs.ToString());
        //    // 全体に追加（Font色ID マクロ列挙）
        //    sbWholeScript.AppendLine(sbFontColorIDDefs.ToString());
        //    // 全体に追加（テーブル変数宣言）
        //    sbWholeScript.AppendLine(sbVarDeclPart.ToString());
        //    // ================================================================================


        //    // 全体（ソースセクション）
        //    // ========================================================================
        //    sbWholeScript.AppendLine("// --------------------------------------------------------");
        //    sbWholeScript.AppendLine("##CPP-SRC");
        //    sbWholeScript.AppendLine();

        //    // テーブル定義（宣言、括弧）用Builder
        //    StringBuilder sbTextColorTableOutside = new StringBuilder();
        //    sbTextColorTableOutside.AppendLine("#ifdef __cplusplus");
        //    sbTextColorTableOutside.AppendLine("extern");
        //    sbTextColorTableOutside.AppendLine("#endif");
        //    sbTextColorTableOutside.AppendLine($"const unsigned int {TEXT_COLOR_TABLE_NAME}[{COLOR_TABLE_MACRO_NAME}_LENGTH] =");
        //    sbTextColorTableOutside.AppendLine("{");
        //    sbTextColorTableOutside.Append(sbTextColorTableInside.ToString());
        //    sbTextColorTableOutside.AppendLine("};");

        //    // 全体に追加
        //    sbWholeScript.AppendLine(sbTextColorTableOutside.ToString());



        //    // List Referenceテーブル生成
        //    // ==========================
        //    StringBuilder sbListRefTable = new StringBuilder();
        //    sbListRefTable.AppendLine("#ifdef __cplusplus");
        //    sbListRefTable.AppendLine("extern");
        //    sbListRefTable.AppendLine("#endif");
        //    sbListRefTable.AppendLine($"const int {LIST_REF_TABLE_NAME}[{REFERENCE_TABLE_MACRO_NAME}_LENGTH] = {{");

        //    for (int index = 0; index < mlWordArray.Length; index++)
        //    {
        //        string refValueText = $"    -1, /* cnum = {index} */";

        //        var mlWord = mlWordArray[index];
        //        if (mlWord != null)
        //        {
        //            // フォント色IDが定義されていることを確認する
        //            if (!string.IsNullOrWhiteSpace(mlWord.FontColorID))
        //            {
        //                // 指定するフォント色IDがFontColor定義書にあれば
        //                if (fontColorDictionary.Contains(mlWord.FontColorID))
        //                {
        //                    refValueText = $"    TEXT_TYPE_{mlWord.FontColorID}, /* cnum = {mlWord.No} */";
        //                }
        //                else
        //                {
        //                    refValueText = $"    TEXT_TYPE_NOTFOUND_ERROR, /* cnum = {mlWord.No} */";
        //                }
        //            }
        //            // FontColor定義書にない場合は、refValueTextに変更なし
        //        }

        //        sbListRefTable.AppendLine(refValueText);
        //    }

        //    sbListRefTable.AppendLine("};");

        //    // 全体に追加
        //    sbWholeScript.AppendLine(sbListRefTable.ToString());


        //    // 最終出力
        //    this.OutputCode = sbWholeScript.ToString();
        //}
    }
}
