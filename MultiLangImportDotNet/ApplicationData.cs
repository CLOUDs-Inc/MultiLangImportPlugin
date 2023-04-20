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
        /// サブキャスト名指定インデクス
        /// </summary>
        public int SubcastNameIndex { get; set; }

        /// <summary>
        /// テキストキャスト名リスト
        /// </summary>
        public List<string> TextCastNameList { get; set; }

        /// <summary>
        /// テキストデータテーブル（二次元配列）
        /// </summary>
        public Import.TextData[,] TextDataTable { get; set; }

        /// <summary>
        /// 各チェックボックス名をキーにした辞書（値：各チェックボックスの状態）
        /// </summary>
        public Dictionary<string, bool> Flags { get; set; }

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
        }
    }
}
