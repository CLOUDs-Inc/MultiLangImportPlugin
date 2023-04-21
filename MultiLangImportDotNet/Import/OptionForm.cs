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
    public partial class OptionForm : Form
    {
        private ApplicationData appData;

        public OptionForm(ApplicationData appData)
        {
            InitializeComponent();

            this.appData = appData;
        }


        private void SetOptionFormSettingToAppData(OptionData optionData)
        {
            optionData.Flags[OptionData.FLAG_USE_SUBCAST_NAME] = this.checkBoxUseSubcastName.Checked;
            optionData.Flags[OptionData.FLAG_USE_SUBCAST_NAME_WHEN_SEARCHING_FOR_CAST] = this.checkBoxUseSubcastNameSearching.Checked;
            optionData.Flags[OptionData.FLAG_ADD_SUBCAST_NAME_WHEN_CREATING_A_NEW_CAST] = this.checkBoxAddSubcastNameCreating.Checked;
            optionData.Flags[OptionData.FLAG_USE_UNDERSCORE_FOR_CONJUNCTION_IN_SUBCAST_NAME] = this.checkBoxUseUnderscore.Checked;
            optionData.ConjunctionString = this.textBoxConjunction.Text.Trim();

            // 使用不可言語を選択している場合は、選択を解除(index:-1)とする
            optionData.SubcastIndex = appData.LangHasTextWithUnusableCharList[this.listBoxSubcastName.SelectedIndex]
                ? -1
                : optionData.SubcastIndex = this.listBoxSubcastName.SelectedIndex;
        }

        private void checkBoxUseSubcastName_CheckedChanged(object sender, EventArgs e)
        {
            var checkbox = sender as CheckBox;
            if (checkbox == null) return;

            // 有効化と無効化のチェック
            if (checkbox.Checked)
            {
                // 有効化された場合、他のUIをEnableにする
                this.checkBoxUseSubcastNameSearching.Enabled = true;
                this.checkBoxAddSubcastNameCreating.Enabled = true;
                this.checkBoxUseUnderscore.Enabled = true;

                // アンダースコアを使うかどうかチェック状態で接続用文字列用UIの使用可否を切り替える
                // ↑でアンダースコアを使う、としているなら接続文字のUIは不要
                // ↑でアンダースコアを使わない、としているなら接続文字UIが必要
                this.labelConjunction.Enabled =
                    this.textBoxConjunction.Enabled = !(this.checkBoxUseUnderscore.Checked);

                this.listBoxSubcastName.Enabled = true;
            }
            else
            {
                // 無効化された場合、他のUIをDisableにする
                this.checkBoxUseSubcastNameSearching.Enabled = false;
                this.checkBoxAddSubcastNameCreating.Enabled = false;
                this.checkBoxUseUnderscore.Enabled = false;
                this.labelConjunction.Enabled = false;
                this.textBoxConjunction.Enabled = false;
                this.listBoxSubcastName.Enabled = false;
            }
        }

        private void buttonOK_Click(object sender, EventArgs e)
        {
            SetOptionFormSettingToAppData(this.appData.OptionData);
            this.DialogResult = DialogResult.OK;
            this.Close();
        }

        private void buttonCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void OptionForm_Load(object sender, EventArgs e)
        {
            var optionData = this.appData.OptionData;
            this.checkBoxUseSubcastName.Checked = optionData.Flags[OptionData.FLAG_USE_SUBCAST_NAME];
            this.checkBoxUseSubcastNameSearching.Checked = optionData.Flags[OptionData.FLAG_USE_SUBCAST_NAME_WHEN_SEARCHING_FOR_CAST];
            this.checkBoxAddSubcastNameCreating.Checked = optionData.Flags[OptionData.FLAG_ADD_SUBCAST_NAME_WHEN_CREATING_A_NEW_CAST];
            this.checkBoxUseUnderscore.Checked = optionData.Flags[OptionData.FLAG_USE_UNDERSCORE_FOR_CONJUNCTION_IN_SUBCAST_NAME];
            this.textBoxConjunction.Text = optionData.ConjunctionString;

            this.listBoxSubcastName.Items.AddRange(this.appData.LanguageNameList.ToArray());
            this.listBoxSubcastName.SelectedIndex = optionData.SubcastIndex;
        }

        private void checkBoxUseUnderscore_CheckedChanged(object sender, EventArgs e)
        {
            var checkbox = sender as CheckBox;
            if (checkbox == null) return;

            // 接続文字に"_"を使うかどうか
            if (checkbox.Checked)
            {
                // 使うならば、接続文字のテキストボックスは不要
                this.textBoxConjunction.Enabled = false;
                this.labelConjunction.Enabled = false;
            }
            else
            {
                if (this.checkBoxUseSubcastName.Checked)
                {
                    // 使わないなら、接続文字を指定するのでテキストボックスを有効化
                    this.textBoxConjunction.Enabled = true;
                    this.labelConjunction.Enabled = true;
                }
            }
        }

        private void listBoxSubcastName_DrawItem(object sender, DrawItemEventArgs e)
        {
            var listBox = sender as ListBox;

            // 背景描画指示
            e.DrawBackground();
            // 描画アイテムのインデックス
            int index = e.Index;

            // インデックスチェック
            if (index < 0 || this.appData.LangHasTextWithUnusableCharList.Count <= index) return;

            // 使用不可能フラグ
            bool langUnusable = this.appData.LangHasTextWithUnusableCharList[index];

            Color bgColor = SystemColors.Window;
            Color fgColor = SystemColors.WindowText;
            // サブキャストとして使用可能な言語か確認する
            if (langUnusable)
            {
                // 使用不可の時
                // 選択状態に限らずグレー化（グレーを選択した場合はOKボタンの際にインデクス指定解除処理を行う）
                bgColor = Color.DarkGray;
                fgColor = Color.Silver;
            }
            // アイテムの選択状態を確認する
            else if ((e.State & DrawItemState.Selected) == DrawItemState.Selected)
            {
                // 選択されている時
                bgColor = SystemColors.Highlight;
                fgColor = SystemColors.HighlightText;
            }
            else
            {
                // 選択されていない時
                // 色はすでに指定済み
            }
            

            // ListBoxアイテムの背景色を設定
            using (SolidBrush brush = new SolidBrush(bgColor))
            {
                e.Graphics.FillRectangle(brush, e.Bounds);
            }

            // ListBoxアイテムの文字色を設定
            using (SolidBrush brush = new SolidBrush(fgColor))
            {
                e.Graphics.DrawString(listBox.Items[index].ToString(), e.Font, brush, e.Bounds);
            }

            e.DrawFocusRectangle();
        }
    }
}
