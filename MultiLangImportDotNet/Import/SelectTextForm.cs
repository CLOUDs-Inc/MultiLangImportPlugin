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
    public partial class SelectTextForm : Form
    {
        /// <summary>
        /// 選択されたインデックス
        /// </summary>
        public int SelectedIndex { get; private set; } = -1;

        /// <summary>
        /// 扱うテキストのリスト
        /// </summary>
        private List<string> textList;

        /// <summary>
        /// 説明文
        /// </summary>
        private string explanationText;

        /// <summary>
        /// ウィンドウタイトル
        /// </summary>
        private string windowTitle;

        /// <summary>
        /// テキスト選択フォーム
        /// </summary>
        /// <param name="textList">選択用テキストリスト</param>
        /// <param name="explanation">説明文</param>
        /// <param name="windowTitle">ウィンドウタイトル</param>
        public SelectTextForm(List<string> textList, string explanation, string windowTitle)
        {
            InitializeComponent();

            this.textList = textList;
            this.explanationText = explanation;
            this.windowTitle = windowTitle;
        }

        private void SelectTextForm_Load(object sender, EventArgs e)
        {
            if (this.textList != null)
            {
                this.listBoxTexts.Items.AddRange(this.textList.ToArray());
            }
            this.labelExplanation.Text = this.explanationText;
            this.Text = this.windowTitle;
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            // 選択されているアイテムのインデックスを保持してフォームを閉じる
            this.SelectedIndex = this.listBoxTexts.SelectedIndex;
            this.DialogResult = DialogResult.OK;

            this.Close();
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
