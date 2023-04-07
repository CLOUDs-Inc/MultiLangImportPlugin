
namespace MultiLangImportDotNet.Import
{
    partial class ImportForm
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
            this.buttonClose = new System.Windows.Forms.Button();
            this.buttonImportFile = new System.Windows.Forms.Button();
            this.labelImportFile = new System.Windows.Forms.Label();
            this.textBoxImportFile = new System.Windows.Forms.TextBox();
            this.labelImportedData = new System.Windows.Forms.Label();
            this.dataGridViewTextMod = new System.Windows.Forms.DataGridView();
            this.labelSelectedCellData = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.buttonImport = new System.Windows.Forms.Button();
            this.groupBoxApplyLangAndCast = new System.Windows.Forms.GroupBox();
            this.checkBoxInheritOnlyNewLang = new System.Windows.Forms.CheckBox();
            this.checkBoxCreateAsUnicode = new System.Windows.Forms.CheckBox();
            this.checkBoxInheritProperty = new System.Windows.Forms.CheckBox();
            this.checkBoxNotUpdate = new System.Windows.Forms.CheckBox();
            this.checkBoxAddTextCast = new System.Windows.Forms.CheckBox();
            this.checkBoxAddLangPage = new System.Windows.Forms.CheckBox();
            this.groupBoxApplyProperty = new System.Windows.Forms.GroupBox();
            this.checkBoxApplyString = new System.Windows.Forms.CheckBox();
            this.checkBoxApplyTextColor = new System.Windows.Forms.CheckBox();
            this.checkBoxApplyFontSize = new System.Windows.Forms.CheckBox();
            this.checkBoxApplyFontname = new System.Windows.Forms.CheckBox();
            this.buttonDefaultLanguage = new System.Windows.Forms.Button();
            this.buttonOption = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewTextMod)).BeginInit();
            this.groupBoxApplyLangAndCast.SuspendLayout();
            this.groupBoxApplyProperty.SuspendLayout();
            this.SuspendLayout();
            // 
            // buttonClose
            // 
            this.buttonClose.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonClose.Location = new System.Drawing.Point(671, 527);
            this.buttonClose.Name = "buttonClose";
            this.buttonClose.Size = new System.Drawing.Size(117, 37);
            this.buttonClose.TabIndex = 0;
            this.buttonClose.Text = "Close";
            this.buttonClose.UseVisualStyleBackColor = true;
            this.buttonClose.Click += new System.EventHandler(this.buttonClose_Click);
            // 
            // buttonImportFile
            // 
            this.buttonImportFile.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonImportFile.Location = new System.Drawing.Point(674, 12);
            this.buttonImportFile.Name = "buttonImportFile";
            this.buttonImportFile.Size = new System.Drawing.Size(114, 30);
            this.buttonImportFile.TabIndex = 1;
            this.buttonImportFile.Text = "Select";
            this.buttonImportFile.UseVisualStyleBackColor = true;
            this.buttonImportFile.Click += new System.EventHandler(this.buttonImportFile_Click);
            // 
            // labelImportFile
            // 
            this.labelImportFile.AutoSize = true;
            this.labelImportFile.Location = new System.Drawing.Point(12, 21);
            this.labelImportFile.Name = "labelImportFile";
            this.labelImportFile.Size = new System.Drawing.Size(62, 12);
            this.labelImportFile.TabIndex = 2;
            this.labelImportFile.Text = "Import File:";
            // 
            // textBoxImportFile
            // 
            this.textBoxImportFile.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBoxImportFile.Location = new System.Drawing.Point(80, 18);
            this.textBoxImportFile.Name = "textBoxImportFile";
            this.textBoxImportFile.ReadOnly = true;
            this.textBoxImportFile.Size = new System.Drawing.Size(588, 19);
            this.textBoxImportFile.TabIndex = 3;
            // 
            // labelImportedData
            // 
            this.labelImportedData.AutoSize = true;
            this.labelImportedData.Location = new System.Drawing.Point(12, 221);
            this.labelImportedData.Name = "labelImportedData";
            this.labelImportedData.Size = new System.Drawing.Size(79, 12);
            this.labelImportedData.TabIndex = 2;
            this.labelImportedData.Text = "Imported Data:";
            // 
            // dataGridViewTextMod
            // 
            this.dataGridViewTextMod.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.dataGridViewTextMod.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewTextMod.Location = new System.Drawing.Point(12, 236);
            this.dataGridViewTextMod.Name = "dataGridViewTextMod";
            this.dataGridViewTextMod.RowTemplate.Height = 21;
            this.dataGridViewTextMod.Size = new System.Drawing.Size(776, 228);
            this.dataGridViewTextMod.TabIndex = 5;
            // 
            // labelSelectedCellData
            // 
            this.labelSelectedCellData.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.labelSelectedCellData.AutoSize = true;
            this.labelSelectedCellData.Location = new System.Drawing.Point(12, 478);
            this.labelSelectedCellData.Name = "labelSelectedCellData";
            this.labelSelectedCellData.Size = new System.Drawing.Size(97, 12);
            this.labelSelectedCellData.TabIndex = 2;
            this.labelSelectedCellData.Text = "Selected cell data";
            // 
            // textBox1
            // 
            this.textBox1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBox1.Location = new System.Drawing.Point(12, 493);
            this.textBox1.Name = "textBox1";
            this.textBox1.ReadOnly = true;
            this.textBox1.Size = new System.Drawing.Size(776, 19);
            this.textBox1.TabIndex = 3;
            // 
            // buttonImport
            // 
            this.buttonImport.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.buttonImport.Enabled = false;
            this.buttonImport.Location = new System.Drawing.Point(12, 527);
            this.buttonImport.Name = "buttonImport";
            this.buttonImport.Size = new System.Drawing.Size(117, 37);
            this.buttonImport.TabIndex = 0;
            this.buttonImport.Text = "Import";
            this.buttonImport.UseVisualStyleBackColor = true;
            // 
            // groupBoxApplyLangAndCast
            // 
            this.groupBoxApplyLangAndCast.Controls.Add(this.checkBoxInheritOnlyNewLang);
            this.groupBoxApplyLangAndCast.Controls.Add(this.checkBoxCreateAsUnicode);
            this.groupBoxApplyLangAndCast.Controls.Add(this.checkBoxInheritProperty);
            this.groupBoxApplyLangAndCast.Controls.Add(this.checkBoxNotUpdate);
            this.groupBoxApplyLangAndCast.Controls.Add(this.checkBoxAddTextCast);
            this.groupBoxApplyLangAndCast.Controls.Add(this.checkBoxAddLangPage);
            this.groupBoxApplyLangAndCast.Location = new System.Drawing.Point(14, 43);
            this.groupBoxApplyLangAndCast.Name = "groupBoxApplyLangAndCast";
            this.groupBoxApplyLangAndCast.Size = new System.Drawing.Size(273, 165);
            this.groupBoxApplyLangAndCast.TabIndex = 6;
            this.groupBoxApplyLangAndCast.TabStop = false;
            this.groupBoxApplyLangAndCast.Text = "Apply languages and casts";
            // 
            // checkBoxInheritOnlyNewLang
            // 
            this.checkBoxInheritOnlyNewLang.AutoSize = true;
            this.checkBoxInheritOnlyNewLang.Location = new System.Drawing.Point(30, 137);
            this.checkBoxInheritOnlyNewLang.Name = "checkBoxInheritOnlyNewLang";
            this.checkBoxInheritOnlyNewLang.Size = new System.Drawing.Size(182, 16);
            this.checkBoxInheritOnlyNewLang.TabIndex = 0;
            this.checkBoxInheritOnlyNewLang.Text = "Inherit only new language page";
            this.checkBoxInheritOnlyNewLang.UseVisualStyleBackColor = true;
            // 
            // checkBoxCreateAsUnicode
            // 
            this.checkBoxCreateAsUnicode.AutoSize = true;
            this.checkBoxCreateAsUnicode.Location = new System.Drawing.Point(30, 71);
            this.checkBoxCreateAsUnicode.Name = "checkBoxCreateAsUnicode";
            this.checkBoxCreateAsUnicode.Size = new System.Drawing.Size(169, 16);
            this.checkBoxCreateAsUnicode.TabIndex = 0;
            this.checkBoxCreateAsUnicode.Text = "Create as Unicode text cast";
            this.checkBoxCreateAsUnicode.UseVisualStyleBackColor = true;
            // 
            // checkBoxInheritProperty
            // 
            this.checkBoxInheritProperty.AutoSize = true;
            this.checkBoxInheritProperty.Location = new System.Drawing.Point(15, 115);
            this.checkBoxInheritProperty.Name = "checkBoxInheritProperty";
            this.checkBoxInheritProperty.Size = new System.Drawing.Size(247, 16);
            this.checkBoxInheritProperty.TabIndex = 0;
            this.checkBoxInheritProperty.Text = "Inherit properties of the first language page";
            this.checkBoxInheritProperty.UseVisualStyleBackColor = true;
            // 
            // checkBoxNotUpdate
            // 
            this.checkBoxNotUpdate.AutoSize = true;
            this.checkBoxNotUpdate.Location = new System.Drawing.Point(15, 93);
            this.checkBoxNotUpdate.Name = "checkBoxNotUpdate";
            this.checkBoxNotUpdate.Size = new System.Drawing.Size(174, 16);
            this.checkBoxNotUpdate.TabIndex = 0;
            this.checkBoxNotUpdate.Text = "Not update existing text cast";
            this.checkBoxNotUpdate.UseVisualStyleBackColor = true;
            // 
            // checkBoxAddTextCast
            // 
            this.checkBoxAddTextCast.AutoSize = true;
            this.checkBoxAddTextCast.Location = new System.Drawing.Point(15, 49);
            this.checkBoxAddTextCast.Name = "checkBoxAddTextCast";
            this.checkBoxAddTextCast.Size = new System.Drawing.Size(170, 16);
            this.checkBoxAddTextCast.TabIndex = 0;
            this.checkBoxAddTextCast.Text = "Add if text cast is not found";
            this.checkBoxAddTextCast.UseVisualStyleBackColor = true;
            // 
            // checkBoxAddLangPage
            // 
            this.checkBoxAddLangPage.AutoSize = true;
            this.checkBoxAddLangPage.Location = new System.Drawing.Point(15, 27);
            this.checkBoxAddLangPage.Name = "checkBoxAddLangPage";
            this.checkBoxAddLangPage.Size = new System.Drawing.Size(197, 16);
            this.checkBoxAddLangPage.TabIndex = 0;
            this.checkBoxAddLangPage.Text = "Add if language page is not found";
            this.checkBoxAddLangPage.UseVisualStyleBackColor = true;
            // 
            // groupBoxApplyProperty
            // 
            this.groupBoxApplyProperty.Controls.Add(this.checkBoxApplyString);
            this.groupBoxApplyProperty.Controls.Add(this.checkBoxApplyTextColor);
            this.groupBoxApplyProperty.Controls.Add(this.checkBoxApplyFontSize);
            this.groupBoxApplyProperty.Controls.Add(this.checkBoxApplyFontname);
            this.groupBoxApplyProperty.Location = new System.Drawing.Point(324, 43);
            this.groupBoxApplyProperty.Name = "groupBoxApplyProperty";
            this.groupBoxApplyProperty.Size = new System.Drawing.Size(244, 122);
            this.groupBoxApplyProperty.TabIndex = 7;
            this.groupBoxApplyProperty.TabStop = false;
            this.groupBoxApplyProperty.Text = "Apply properties";
            // 
            // checkBoxApplyString
            // 
            this.checkBoxApplyString.AutoSize = true;
            this.checkBoxApplyString.Location = new System.Drawing.Point(15, 93);
            this.checkBoxApplyString.Name = "checkBoxApplyString";
            this.checkBoxApplyString.Size = new System.Drawing.Size(150, 16);
            this.checkBoxApplyString.TabIndex = 0;
            this.checkBoxApplyString.Text = "Apply string to text cast";
            this.checkBoxApplyString.UseVisualStyleBackColor = true;
            // 
            // checkBoxApplyTextColor
            // 
            this.checkBoxApplyTextColor.AutoSize = true;
            this.checkBoxApplyTextColor.Location = new System.Drawing.Point(15, 71);
            this.checkBoxApplyTextColor.Name = "checkBoxApplyTextColor";
            this.checkBoxApplyTextColor.Size = new System.Drawing.Size(170, 16);
            this.checkBoxApplyTextColor.TabIndex = 0;
            this.checkBoxApplyTextColor.Text = "Apply text color to text cast";
            this.checkBoxApplyTextColor.UseVisualStyleBackColor = true;
            // 
            // checkBoxApplyFontSize
            // 
            this.checkBoxApplyFontSize.AutoSize = true;
            this.checkBoxApplyFontSize.Location = new System.Drawing.Point(15, 49);
            this.checkBoxApplyFontSize.Name = "checkBoxApplyFontSize";
            this.checkBoxApplyFontSize.Size = new System.Drawing.Size(165, 16);
            this.checkBoxApplyFontSize.TabIndex = 0;
            this.checkBoxApplyFontSize.Text = "Apply font size to text cast";
            this.checkBoxApplyFontSize.UseVisualStyleBackColor = true;
            // 
            // checkBoxApplyFontname
            // 
            this.checkBoxApplyFontname.AutoSize = true;
            this.checkBoxApplyFontname.Location = new System.Drawing.Point(15, 27);
            this.checkBoxApplyFontname.Name = "checkBoxApplyFontname";
            this.checkBoxApplyFontname.Size = new System.Drawing.Size(172, 16);
            this.checkBoxApplyFontname.TabIndex = 0;
            this.checkBoxApplyFontname.Text = "Apply font name to text cast";
            this.checkBoxApplyFontname.UseVisualStyleBackColor = true;
            // 
            // buttonDefaultLanguage
            // 
            this.buttonDefaultLanguage.Enabled = false;
            this.buttonDefaultLanguage.Location = new System.Drawing.Point(324, 180);
            this.buttonDefaultLanguage.Name = "buttonDefaultLanguage";
            this.buttonDefaultLanguage.Size = new System.Drawing.Size(114, 30);
            this.buttonDefaultLanguage.TabIndex = 1;
            this.buttonDefaultLanguage.Text = "Default Language...";
            this.buttonDefaultLanguage.UseVisualStyleBackColor = true;
            this.buttonDefaultLanguage.Click += new System.EventHandler(this.buttonDefaultLanguage_Click);
            // 
            // buttonOption
            // 
            this.buttonOption.Enabled = false;
            this.buttonOption.Location = new System.Drawing.Point(454, 180);
            this.buttonOption.Name = "buttonOption";
            this.buttonOption.Size = new System.Drawing.Size(114, 30);
            this.buttonOption.TabIndex = 1;
            this.buttonOption.Text = "Options...";
            this.buttonOption.UseVisualStyleBackColor = true;
            this.buttonOption.Click += new System.EventHandler(this.buttonOption_Click);
            // 
            // ImportForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 576);
            this.Controls.Add(this.groupBoxApplyProperty);
            this.Controls.Add(this.groupBoxApplyLangAndCast);
            this.Controls.Add(this.dataGridViewTextMod);
            this.Controls.Add(this.textBox1);
            this.Controls.Add(this.textBoxImportFile);
            this.Controls.Add(this.labelSelectedCellData);
            this.Controls.Add(this.labelImportedData);
            this.Controls.Add(this.labelImportFile);
            this.Controls.Add(this.buttonOption);
            this.Controls.Add(this.buttonDefaultLanguage);
            this.Controls.Add(this.buttonImportFile);
            this.Controls.Add(this.buttonImport);
            this.Controls.Add(this.buttonClose);
            this.Name = "ImportForm";
            this.Text = "Multi-language import [PLUGIN]";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewTextMod)).EndInit();
            this.groupBoxApplyLangAndCast.ResumeLayout(false);
            this.groupBoxApplyLangAndCast.PerformLayout();
            this.groupBoxApplyProperty.ResumeLayout(false);
            this.groupBoxApplyProperty.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonClose;
        private System.Windows.Forms.Button buttonImportFile;
        private System.Windows.Forms.Label labelImportFile;
        private System.Windows.Forms.TextBox textBoxImportFile;
        private System.Windows.Forms.Label labelImportedData;
        private System.Windows.Forms.DataGridView dataGridViewTextMod;
        private System.Windows.Forms.Label labelSelectedCellData;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Button buttonImport;
        private System.Windows.Forms.GroupBox groupBoxApplyLangAndCast;
        private System.Windows.Forms.CheckBox checkBoxInheritOnlyNewLang;
        private System.Windows.Forms.CheckBox checkBoxCreateAsUnicode;
        private System.Windows.Forms.CheckBox checkBoxInheritProperty;
        private System.Windows.Forms.CheckBox checkBoxNotUpdate;
        private System.Windows.Forms.CheckBox checkBoxAddTextCast;
        private System.Windows.Forms.CheckBox checkBoxAddLangPage;
        private System.Windows.Forms.GroupBox groupBoxApplyProperty;
        private System.Windows.Forms.CheckBox checkBoxApplyString;
        private System.Windows.Forms.CheckBox checkBoxApplyTextColor;
        private System.Windows.Forms.CheckBox checkBoxApplyFontSize;
        private System.Windows.Forms.CheckBox checkBoxApplyFontname;
        private System.Windows.Forms.Button buttonDefaultLanguage;
        private System.Windows.Forms.Button buttonOption;
    }
}