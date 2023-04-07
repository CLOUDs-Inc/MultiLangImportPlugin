
namespace MultiLangImportDotNet.Import
{
    partial class OptionForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.buttonOK = new System.Windows.Forms.Button();
            this.buttonCancel = new System.Windows.Forms.Button();
            this.checkBoxUseSubcastName = new System.Windows.Forms.CheckBox();
            this.panelSubcast = new System.Windows.Forms.Panel();
            this.checkBoxUseSubcastNameSearching = new System.Windows.Forms.CheckBox();
            this.checkBoxAddSubcastNameCreating = new System.Windows.Forms.CheckBox();
            this.checkBoxUseUnderscore = new System.Windows.Forms.CheckBox();
            this.labelConjunction = new System.Windows.Forms.Label();
            this.textBoxConjunction = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.listBoxSubcastName = new System.Windows.Forms.ListBox();
            this.panelSubcast.SuspendLayout();
            this.SuspendLayout();
            // 
            // buttonOK
            // 
            this.buttonOK.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonOK.Location = new System.Drawing.Point(368, 12);
            this.buttonOK.Name = "buttonOK";
            this.buttonOK.Size = new System.Drawing.Size(75, 23);
            this.buttonOK.TabIndex = 0;
            this.buttonOK.Text = "OK";
            this.buttonOK.UseVisualStyleBackColor = true;
            // 
            // buttonCancel
            // 
            this.buttonCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonCancel.Location = new System.Drawing.Point(368, 41);
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.Size = new System.Drawing.Size(75, 23);
            this.buttonCancel.TabIndex = 1;
            this.buttonCancel.Text = "Cancel";
            this.buttonCancel.UseVisualStyleBackColor = true;
            // 
            // checkBoxUseSubcastName
            // 
            this.checkBoxUseSubcastName.AutoSize = true;
            this.checkBoxUseSubcastName.Location = new System.Drawing.Point(12, 12);
            this.checkBoxUseSubcastName.Name = "checkBoxUseSubcastName";
            this.checkBoxUseSubcastName.Size = new System.Drawing.Size(122, 16);
            this.checkBoxUseSubcastName.TabIndex = 2;
            this.checkBoxUseSubcastName.Text = "Use Subcast-name";
            this.checkBoxUseSubcastName.UseVisualStyleBackColor = true;
            this.checkBoxUseSubcastName.CheckedChanged += new System.EventHandler(this.checkBoxUseSubcastName_CheckedChanged);
            // 
            // panelSubcast
            // 
            this.panelSubcast.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panelSubcast.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelSubcast.Controls.Add(this.listBoxSubcastName);
            this.panelSubcast.Controls.Add(this.textBoxConjunction);
            this.panelSubcast.Controls.Add(this.label1);
            this.panelSubcast.Controls.Add(this.labelConjunction);
            this.panelSubcast.Controls.Add(this.checkBoxUseUnderscore);
            this.panelSubcast.Controls.Add(this.checkBoxAddSubcastNameCreating);
            this.panelSubcast.Controls.Add(this.checkBoxUseSubcastNameSearching);
            this.panelSubcast.Location = new System.Drawing.Point(12, 34);
            this.panelSubcast.Name = "panelSubcast";
            this.panelSubcast.Size = new System.Drawing.Size(350, 340);
            this.panelSubcast.TabIndex = 3;
            // 
            // checkBoxUseSubcastNameSearching
            // 
            this.checkBoxUseSubcastNameSearching.AutoSize = true;
            this.checkBoxUseSubcastNameSearching.Enabled = false;
            this.checkBoxUseSubcastNameSearching.Location = new System.Drawing.Point(14, 10);
            this.checkBoxUseSubcastNameSearching.Name = "checkBoxUseSubcastNameSearching";
            this.checkBoxUseSubcastNameSearching.Size = new System.Drawing.Size(248, 16);
            this.checkBoxUseSubcastNameSearching.TabIndex = 2;
            this.checkBoxUseSubcastNameSearching.Text = "Use subcast-name when searching for cast";
            this.checkBoxUseSubcastNameSearching.UseVisualStyleBackColor = true;
            // 
            // checkBoxAddSubcastNameCreating
            // 
            this.checkBoxAddSubcastNameCreating.AutoSize = true;
            this.checkBoxAddSubcastNameCreating.Checked = true;
            this.checkBoxAddSubcastNameCreating.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxAddSubcastNameCreating.Enabled = false;
            this.checkBoxAddSubcastNameCreating.Location = new System.Drawing.Point(14, 32);
            this.checkBoxAddSubcastNameCreating.Name = "checkBoxAddSubcastNameCreating";
            this.checkBoxAddSubcastNameCreating.Size = new System.Drawing.Size(256, 16);
            this.checkBoxAddSubcastNameCreating.TabIndex = 2;
            this.checkBoxAddSubcastNameCreating.Text = "Add subcast-name when creating a new cast";
            this.checkBoxAddSubcastNameCreating.UseVisualStyleBackColor = true;
            // 
            // checkBoxUseUnderscore
            // 
            this.checkBoxUseUnderscore.AutoSize = true;
            this.checkBoxUseUnderscore.Checked = true;
            this.checkBoxUseUnderscore.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxUseUnderscore.Enabled = false;
            this.checkBoxUseUnderscore.Location = new System.Drawing.Point(14, 54);
            this.checkBoxUseUnderscore.Name = "checkBoxUseUnderscore";
            this.checkBoxUseUnderscore.Size = new System.Drawing.Size(274, 16);
            this.checkBoxUseUnderscore.TabIndex = 2;
            this.checkBoxUseUnderscore.Text = "Use underscore for conjunction in subcast-name";
            this.checkBoxUseUnderscore.UseVisualStyleBackColor = true;
            // 
            // labelConjunction
            // 
            this.labelConjunction.AutoSize = true;
            this.labelConjunction.Location = new System.Drawing.Point(31, 79);
            this.labelConjunction.Name = "labelConjunction";
            this.labelConjunction.Size = new System.Drawing.Size(67, 12);
            this.labelConjunction.TabIndex = 3;
            this.labelConjunction.Text = "Conjunction;";
            // 
            // textBoxConjunction
            // 
            this.textBoxConjunction.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxConjunction.Location = new System.Drawing.Point(104, 76);
            this.textBoxConjunction.Name = "textBoxConjunction";
            this.textBoxConjunction.Size = new System.Drawing.Size(231, 19);
            this.textBoxConjunction.TabIndex = 4;
            this.textBoxConjunction.Text = "_";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 116);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(294, 12);
            this.label1.TabIndex = 3;
            this.label1.Text = "Column to be the Subcast-name (gray is not selectable)";
            // 
            // listBoxSubcastName
            // 
            this.listBoxSubcastName.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.listBoxSubcastName.Enabled = false;
            this.listBoxSubcastName.FormattingEnabled = true;
            this.listBoxSubcastName.ItemHeight = 12;
            this.listBoxSubcastName.Location = new System.Drawing.Point(14, 131);
            this.listBoxSubcastName.Name = "listBoxSubcastName";
            this.listBoxSubcastName.Size = new System.Drawing.Size(319, 196);
            this.listBoxSubcastName.TabIndex = 5;
            // 
            // OptionForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(455, 386);
            this.Controls.Add(this.panelSubcast);
            this.Controls.Add(this.checkBoxUseSubcastName);
            this.Controls.Add(this.buttonCancel);
            this.Controls.Add(this.buttonOK);
            this.Name = "OptionForm";
            this.Text = "Multi language import option";
            this.panelSubcast.ResumeLayout(false);
            this.panelSubcast.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonOK;
        private System.Windows.Forms.Button buttonCancel;
        private System.Windows.Forms.CheckBox checkBoxUseSubcastName;
        private System.Windows.Forms.Panel panelSubcast;
        private System.Windows.Forms.ListBox listBoxSubcastName;
        private System.Windows.Forms.TextBox textBoxConjunction;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label labelConjunction;
        private System.Windows.Forms.CheckBox checkBoxUseUnderscore;
        private System.Windows.Forms.CheckBox checkBoxAddSubcastNameCreating;
        private System.Windows.Forms.CheckBox checkBoxUseSubcastNameSearching;
    }
}