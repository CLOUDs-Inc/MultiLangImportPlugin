using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MultiLangImportDotNet.Import
{
    public partial class SelectLangForm : Form
    {
        /// <summary>
        /// 選択された言語インデックス
        /// </summary>
        public int SelectedLanguageIndex { get; private set; }

        /// <summary>
        /// サブキャスト扱い列インデックス
        /// </summary>
        private int subcastIndex;

        /// <summary>
        /// 扱う言語名のリスト
        /// </summary>
        private List<string> langNameList;


        /// <summary>
        /// デフォルト言語選択フォーム
        /// </summary>
        /// <param name="langNameList">取り扱い言語名リスト</param>
        /// <param name="selectedIndex">選択済み言語インデックス</param>
        /// <param name="subcastIndex">サブキャスト扱い列インデックス</param>
        public SelectLangForm(List<string> langNameList, int selectedIndex, int subcastIndex)
        {
            InitializeComponent();

            this.langNameList = langNameList;
            this.SelectedLanguageIndex = (selectedIndex < 0 || langNameList.Count <= selectedIndex)
                ? -1
                : selectedIndex;
            this.subcastIndex = (subcastIndex < 0 || langNameList.Count <= subcastIndex)
                ? -1
                : subcastIndex;
        }

        private void SelectLangForm_Load(object sender, EventArgs e)
        {
            if (this.langNameList == null) return;

            this.listBoxLanguages.Items.AddRange(this.langNameList.ToArray());

            if(0 <= this.SelectedLanguageIndex && this.SelectedLanguageIndex < this.listBoxLanguages.Items.Count)
            {
                this.listBoxLanguages.SelectedIndex = this.SelectedLanguageIndex;
            }
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            // サブキャスト扱いの言語を選択した場合はキャンセル処理と同等とする
            if(this.listBoxLanguages.SelectedIndex != this.subcastIndex)
            {
                // 選択されている言語のインデクスを保持して、フォームを閉じる
                this.SelectedLanguageIndex = this.listBoxLanguages.SelectedIndex;
                this.DialogResult = DialogResult.OK;
            }

            this.Close();
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
