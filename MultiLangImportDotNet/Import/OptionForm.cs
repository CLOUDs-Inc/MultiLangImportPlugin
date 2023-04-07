﻿using System;
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
        public OptionForm()
        {
            InitializeComponent();
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
    }
}
