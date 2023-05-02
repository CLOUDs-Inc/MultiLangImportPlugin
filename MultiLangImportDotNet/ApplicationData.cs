using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MultiLangImportDotNet
{
    public class ApplicationData
    {
        /// <summary>
        /// 多言語インポートExcelファイルフルパス
        /// </summary>
        public string ImportExcelFilePath { get; set; }

        /// <summary>
        /// デフォルト設定言語インデクス
        /// </summary>
        public int DefaultLanguageIndex { get; set; }

        /// <summary>
        /// 言語名リスト
        /// </summary>
        public List<string> LanguageNameList { get; set; }

        /// <summary>
        /// 言語毎名称使用不可文字含有フラグリスト
        /// （フラグONと同じインデックスの言語は使用不可文字を含むテキストがあるので、サブキャスト名として使用不可能）
        /// </summary>
        public List<bool> LangHasTextWithUnusableCharList { get; set; }

        /// <summary>
        /// テキストキャスト名リスト
        /// </summary>
        public List<string> TextCastNameList { get; set; }

        /// <summary>
        /// サブキャスト名＆接続文字付きテキストキャスト名リスト
        /// </summary>
        public List<string> CombinedTextCastNameList { get; set; }

        /// <summary>
        /// テキストデータテーブル（二次元配列）
        /// </summary>
        public Import.TextData[,] TextDataTable { get; set; }

        /// <summary>
        /// 各チェックボックス名をキーにした辞書（値：各チェックボックスの状態）
        /// </summary>
        public Dictionary<string, bool> Flags { get; set; }

        /// <summary>
        /// 名前のANSI変換不可能フラグ
        /// ページ名、キャスト名、サブキャストセルデータにANSI変換できないデータが
        /// １つでもあればフラグON
        /// </summary>
        public bool NamesANSIUnconvertableFlag
        {
            get
            {
                // ページ名に１つでもANSI変換できない名前があった場合
                for (int index = 0; index < LanguageNameList.Count; index++)
                {
                    // 列をサブキャスト用に指定している場合はチェック不要
                    if (index == OptionData.SubcastIndex) continue;

                    // ページ名に１つでもANSI変換できない名前があった場合
                    if (!Utils.ANSIConvertTest(LanguageNameList[index]))
                    {
                        // 変換不可フラグON
                        return true;
                    }
                }

                if(TextCastNameList != null)
                {
                    // キャスト名に１つでもANSI変換できない名前があった場合
                    if (TextCastNameList.Any(name => !Utils.ANSIConvertTest(name)))
                    {
                        // 変換不可フラグON
                        return true;
                    }
                }

                // サブキャスト名としての指定があり
                if(0 <= OptionData.SubcastIndex)
                {
                    // サブキャスト名の列のデータに
                    for(int index = 0; index < TextCastNameList.Count; index++)
                    {
                        // １つでもANSI変換できない名前があった場合
                        if (null != TextDataTable[index, OptionData.SubcastIndex]
                            && !TextDataTable[index, OptionData.SubcastIndex].CanConvertToANSI)
                        {
                            // 変換不可フラグON
                            return true;
                        }
                    }
                }

                // 変換不可フラグOFF
                return false;
            }
        }


        public bool TextDataANSIUnconvertableFlag
        {
            get
            {
                int rowNum = TextDataTable.GetLength(0);
                int colNum = TextDataTable.GetLength(1);

                for(int r = 0; r < rowNum; r++)
                {
                    for(int c = 0; c < colNum; c++)
                    {
                        if (null != TextDataTable[r, c]
                            && !TextDataTable[r, c].CanConvertToANSI)
                        {
                            return true;
                        }
                    }
                }

                return false;
            }
        }

        /// <summary>
        /// チェックボックスAdd if language page is not foundの状態キー
        /// </summary>
        public static readonly string FLAG_ADD_IF_LANG_PAGE_NOT_FOUND = "AddIfLangPageNotFound";

        /// <summary>
        /// チェックボックスAdd if text cast is not foundの状態キー
        /// </summary>
        public static readonly string FLAG_ADD_IF_TEXT_CAST_NOT_FOUND = "AddIfTextCastNotFound";

        /// <summary>
        /// チェックボックスCreate as Unicode text castの状態キー
        /// </summary>
        public static readonly string FLAG_CREATE_AS_UNICODE_TEXT_CAST = "CreateAsUnicodeTextCast";

        /// <summary>
        /// チェックボックスNot update existing text castの状態キー
        /// </summary>
        public static readonly string FLAG_NOT_UPDATE_EXISTING_TEXT_CAST = "NotUpdateExistingTextCast";

        /// <summary>
        /// チェックボックスInherit properties of the first language pageの状態キー
        /// </summary>
        public static readonly string FLAG_INHERIT_PROPS_OF_THE_FIRST_LANG_PAGE = "InheritPropertiesOfTheFirstLangPage";

        /// <summary>
        /// チェックボックスInherit only new language pageの状態キー
        /// </summary>
        public static readonly string FLAG_INHERIT_ONLY_NEW_LANG_PAGE = "InheritOnlyNewLangPage";

        /// <summary>
        /// チェックボックスApply font name to text castの状態キー
        /// </summary>
        public static readonly string FLAG_APPLY_FONT_NAME = "ApplyFontName";

        /// <summary>
        /// チェックボックスApply font size to text castの状態キー
        /// </summary>
        public static readonly string FLAG_APPLY_FONT_SIZE = "ApplyFontSize";

        /// <summary>
        /// チェックボックスApply text color to text castの状態キー
        /// </summary>
        public static readonly string FLAG_APPLY_TEXT_COLOR = "ApplyTextColor";

        /// <summary>
        /// チェックボックスApply string to text castの状態キー
        /// </summary>
        public static readonly string FLAG_APPLY_STRING = "ApplyString";

        /// <summary>
        /// チェックボックスLog outputの状態キー
        /// </summary>
        public static readonly string FLAG_LOG_OUTPUT = "LogOutput";

        public OptionData OptionData { get; set; }

        /// <summary>
        /// コンストラクタ
        /// </summary>
        public ApplicationData()
        {
            this.Flags = new Dictionary<string, bool>();
            this.DefaultLanguageIndex = -1;
            this.OptionData = new OptionData();
        }

        /// <summary>
        /// サブキャスト名を接続したテキストキャスト名リストを生成・保持する
        /// </summary>
        /// <returns>生成の成否</returns>
        public bool SetCombinedNameForTextCast()
        {
            if (this.LanguageNameList == null) return false;
            if (this.OptionData.SubcastIndex == -1) return false;
            if (this.TextCastNameList == null) return false;
            if (this.TextDataTable == null) return false;
            if (this.TextCastNameList.Count != TextDataTable.GetLength(0)) return false;

            List<string> combinedTextCastNameList = new List<string>();

            string conjunctionString = this.OptionData.ConjunctionString;
            for (int index = 0; index < TextCastNameList.Count; index++)
            {
                string combinedName = TextCastNameList[index];
                var textData = TextDataTable[index, this.OptionData.SubcastIndex];
                if (textData != null)
                {
                    combinedName = combinedName + conjunctionString + TextDataTable[index, this.OptionData.SubcastIndex].Text;
                }
                combinedTextCastNameList.Add(combinedName);
            }

            this.CombinedTextCastNameList = combinedTextCastNameList;

            return true;
        }
    }
}
