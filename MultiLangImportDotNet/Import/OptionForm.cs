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
            optionData.SubcastIndex = this.listBoxSubcastName.SelectedIndex;
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
    }
}
