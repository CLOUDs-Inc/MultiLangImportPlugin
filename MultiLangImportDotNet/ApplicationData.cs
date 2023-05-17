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
        /// SDKプロジェクト多言語使用状況
        /// </summary>
        public bool MultiLangEnabled { get; set; }

        /// <summary>
        /// SDKプロジェクト言語数状況（処理前）
        /// </summary>
        public int LangPageNumberPrev { get; set; }

        /// <summary>
        /// デフォルト設定言語インデクス
        /// </summary>
        public int DefaultLanguageIndex { get; set; } = -1;

        /// <summary>
        /// 言語名リスト
        /// </summary>
        public List<string> LanguageNameListInside { get; set; }

        /// <summary>
        /// 言語名リスト（ANSI変換済み＆サブキャスト列除去済み＆デフォルト言語先頭移動済み）
        /// </summary>
        public List<string> LanguageNameListModified
        {
            get
            {
                List<string> modList = new List<string>();
                
                // デフォルト言語はリストの先頭に移動させる
                if(this.DefaultLanguageIndex != -1)
                {
                    string name = Utils.ForcelyConvertToANSI(LanguageNameListInside[this.DefaultLanguageIndex]);
                    modList.Add(name);
                }

                for (int index = 0; index < LanguageNameListInside.Count; index++)
                {
                    if (index == this.OptionData.SubcastIndex) continue;
                    if (index == this.DefaultLanguageIndex) continue;

                    string name = Utils.ForcelyConvertToANSI(LanguageNameListInside[index]);
                    modList.Add(name);
                }
                return modList;
            }
        }

        /// <summary>
        /// デフォルト言語が設定されているか
        /// </summary>
        public bool IsSetDefaultLanguage
        {
            // 設定されている（-1以外）ならtrue
            get { return -1 != DefaultLanguageIndex; }
        }

        /// <summary>
        /// 言語毎名称使用不可文字含有フラグリスト
        /// （フラグONと同じインデックスの言語は使用不可文字を含むテキストがあるので、サブキャスト名として使用不可能）
        /// </summary>
        public List<bool> LangHasTextWithUnusableCharList { get; set; }

        /// <summary>
        /// テキストキャスト名リスト（未修正）
        /// </summary>
        public List<string> TextCastNameListInside { get; set; }

        /// <summary>
        /// サブキャスト名サブ部分リスト（未修正）
        /// </summary>
        public List<string> SubPartNameListInside
        {
            get
            {
                List<string> modList = new List<string>();
                for (int index = 0; index < TextCastNameListInside.Count; index++)
                {
                    string subname = string.Empty;
                    if(this.OptionData.SubcastIndex != -1)
                    {
                        var textData = TextDataTable[index, this.OptionData.SubcastIndex];
                        if (textData != null)
                        {
                            subname = TextDataTable[index, this.OptionData.SubcastIndex].Text;
                        }
                    }
                    modList.Add(subname);
                }
                return modList;
            }
        }

        /// <summary>
        /// サブキャスト接続文字列（未修正）
        /// </summary>
        public string ConjunctionStringInside { get; set; } = "_";

        /// <summary>
        /// テキストキャスト名リスト（サブキャスト"なし"&ANSI変換済み）
        /// </summary>
        public List<string> TextCastNameListLoneMod
        {
            get
            {
                var modList = TextCastNameListInside.Select((name) => Utils.ForcelyConvertToANSI(name)).ToList();
                return modList;
            }
        }

        /// <summary>
        /// サブキャスト名サブ部分リスト（ANSI変換済み）
        /// </summary>
        public List<string> SubPartNameListMod
        {
            get
            {
                var modList = SubPartNameListInside.Select((name) => Utils.ForcelyConvertToANSI(name)).ToList();
                return modList;
            }
        }

        /// <summary>
        /// テキストキャスト名リスト（サブキャスト加工済み＆ANSI変換済み）
        /// </summary>
        public List<string> TextCastNameListConjMod
        {
            get
            {
                bool subcastOn = 
                    this.OptionData.Flags[OptionData.FLAG_USE_SUBCAST_NAME]
                    && this.OptionData.SubcastIndex != -1;
                string conjunctionString = this.OptionData.ConjunctionString;

                List<string> modList = new List<string>();
                for (int index = 0; index < TextCastNameListInside.Count; index++)
                {
                    string castname;

                    // サブキャスト名の使用On＆サブキャスト列選択済みの場合に限り
                    if (subcastOn)
                    {
                        string combinedName = TextCastNameListInside[index];
                        var textData = TextDataTable[index, this.OptionData.SubcastIndex];
                        if (textData != null)
                        {
                            combinedName = combinedName + conjunctionString + TextDataTable[index, this.OptionData.SubcastIndex].Text;
                        }
                        castname = combinedName;
                    }
                    else
                    {
                        castname = TextCastNameListInside[index];
                    }
                    castname = Utils.ForcelyConvertToANSI(castname);
                    modList.Add(castname);
                }
                return modList;
            }
        }

        /// <summary>
        /// サブキャスト接続文字列（未修正）
        /// </summary>
        public string ConjunctionStringMod
        {
            get { return Utils.ForcelyConvertToANSI(ConjunctionStringInside); }
        }

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
                for (int index = 0; index < LanguageNameListInside.Count; index++)
                {
                    // 列をサブキャスト用に指定している場合はチェック不要
                    if (index == OptionData.SubcastIndex) continue;

                    // ページ名に１つでもANSI変換できない名前があった場合
                    if (!Utils.ANSIConvertTest(LanguageNameListInside[index]))
                    {
                        // 変換不可フラグON
                        return true;
                    }
                }

                if(TextCastNameListInside != null)
                {
                    // キャスト名に１つでもANSI変換できない名前があった場合
                    if (TextCastNameListInside.Any(name => !Utils.ANSIConvertTest(name)))
                    {
                        // 変換不可フラグON
                        return true;
                    }
                }

                // サブキャスト名としての指定があり
                if(0 <= OptionData.SubcastIndex)
                {
                    // サブキャスト名の列のデータに
                    for(int index = 0; index < TextCastNameListInside.Count; index++)
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
            this.OptionData = new OptionData();
        }
    }
}
