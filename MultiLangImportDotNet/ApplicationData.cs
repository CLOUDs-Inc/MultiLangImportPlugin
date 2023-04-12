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
        /// デフォルト設定言語インデクス
        /// </summary>
        public int DefaultLanguageIndex { get; set; }

        /// <summary>
        /// 言語名リスト
        /// </summary>
        public List<string> LanguageNameList { get; set; }

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
        /// チェックボックスAdd if language page is not foundの状態
        /// </summary>
        public bool FlagAddIfLangPageNotFound { get; set; }

        /// <summary>
        /// チェックボックスAdd if text cast is not foundの状態
        /// </summary>
        public bool FlagAddIfTextCastNotFound { get; set; }

        /// <summary>
        /// チェックボックスCreate as Unicode text castの状態
        /// </summary>
        public bool FlagCreateAsUnicodeTextCast { get; set; }

        /// <summary>
        /// チェックボックスNot update existing text castの状態
        /// </summary>
        public bool FlagNotUpdateExistingTextCast { get; set; }

        /// <summary>
        /// チェックボックスInherit properties of the first language pageの状態
        /// </summary>
        public bool FlagInheritPropertiesOfTheFirstLangPage { get; set; }

        /// <summary>
        /// チェックボックスInherit only new language pageの状態
        /// </summary>
        public bool FlagInheritOnlyNewLangPage { get; set; }

        /// <summary>
        /// チェックボックスApply font name to text castの状態
        /// </summary>
        public bool FlagApplyFontName { get; set; }

        /// <summary>
        /// チェックボックスApply font size to text castの状態
        /// </summary>
        public bool FlagApplyFontSize { get; set; }

        /// <summary>
        /// チェックボックスApply text color to text castの状態
        /// </summary>
        public bool FlagApplyTextColor { get; set; }

        /// <summary>
        /// チェックボックスApply string to text castの状態
        /// </summary>
        public bool FlagApplyString { get; set; }


        public OptionData OptionData { get; set; }

    }
}
