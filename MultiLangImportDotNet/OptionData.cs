using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MultiLangImportDotNet
{
    public class OptionData
    {
        /// <summary>
        /// 各チェックボックス名をキーにした辞書（値：各チェックボックスの状態）
        /// </summary>
        public Dictionary<string, bool> Flags { get; set; }

        /// <summary>
        /// チェックボックスUse subcast-nameの状態キー
        /// </summary>
        public static readonly string FLAG_USE_SUBCAST_NAME = "UseSubcastName";

        /// <summary>
        /// チェックボックスUse subcast-name when searching for castの状態キー
        /// </summary>
        public static readonly string FLAG_USE_SUBCAST_NAME_WHEN_SEARCHING_FOR_CAST = "UseSubcastNameWhenSearchingForCast";

        /// <summary>
        /// チェックボックスAdd subcast-name when creating a new castの状態キー
        /// </summary>
        public static readonly string FLAG_ADD_SUBCAST_NAME_WHEN_CREATING_A_NEW_CAST = "AddSubcastNameWhenCreatingANewCast";

        /// <summary>
        /// チェックボックスUse underscore for conjunction in subcast-nameの状態キー
        /// </summary>
        public static readonly string FLAG_USE_UNDERSCORE_FOR_CONJUNCTION_IN_SUBCAST_NAME = "FlagUseUnderscoreForConjunctionInSubcastName";

        /// <summary>
        /// キャスト名サブキャスト名接続文字列
        /// </summary>
        public string ConjunctionString { get; set; }

        /// <summary>
        /// サブキャスト指定インデックス
        /// </summary>
        public int SubcastIndex { get; set; }

        /// <summary>
        /// コンストラクタ
        /// </summary>
        public OptionData()
        {
            this.Flags = new Dictionary<string, bool>();
        }

        public void Default()
        {
            this.Flags[FLAG_USE_SUBCAST_NAME] = false;
            this.Flags[FLAG_USE_SUBCAST_NAME_WHEN_SEARCHING_FOR_CAST] = false;
            this.Flags[FLAG_ADD_SUBCAST_NAME_WHEN_CREATING_A_NEW_CAST] = true;
            this.Flags[FLAG_USE_UNDERSCORE_FOR_CONJUNCTION_IN_SUBCAST_NAME] = true;
            this.ConjunctionString = "_";
            this.SubcastIndex = -1;
        }
    }
}
