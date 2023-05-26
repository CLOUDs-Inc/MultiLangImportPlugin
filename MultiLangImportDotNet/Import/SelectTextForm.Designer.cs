
namespace MultiLangImportDotNet.Import
{
    partial class SelectTextForm
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
            this.panelSelectText = new System.Windows.Forms.Panel();
            this.labelExplanation = new System.Windows.Forms.Label();
            this.listBoxTexts = new System.Windows.Forms.ListBox();
            this.buttonCancel = new System.Windows.Forms.Button();
            this.buttonOK = new System.Windows.Forms.Button();
            this.panelSelectText.SuspendLayout();
            this.SuspendLayout();
            // 
            // panelSelectText
            // 
            this.panelSelectText.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panelSelectText.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panelSelectText.Controls.Add(this.labelExplanation);
            this.panelSelectText.Controls.Add(this.listBoxTexts);
            this.panelSelectText.Location = new System.Drawing.Point(12, 12);
            this.panelSelectText.Name = "panelSelectText";
            this.panelSelectText.Size = new System.Drawing.Size(229, 234);
            this.panelSelectText.TabIndex = 2;
            // 
            // labelExplanation
            // 
            this.labelExplanation.AutoSize = true;
            this.labelExplanation.Location = new System.Drawing.Point(3, 16);
            this.labelExplanation.Name = "labelExplanation";
            this.labelExplanation.Size = new System.Drawing.Size(93, 12);
            this.labelExplanation.TabIndex = 1;
            this.labelExplanation.Text = "Explain Selection";
            // 
            // listBoxTexts
            // 
            this.listBoxTexts.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.listBoxTexts.FormattingEnabled = true;
            this.listBoxTexts.ItemHeight = 12;
            this.listBoxTexts.Location = new System.Drawing.Point(3, 50);
            this.listBoxTexts.Name = "listBoxTexts";
            this.listBoxTexts.Size = new System.Drawing.Size(221, 172);
            this.listBoxTexts.TabIndex = 0;
            // 
            // buttonCancel
            // 
            this.buttonCancel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonCancel.Location = new System.Drawing.Point(247, 41);
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.Size = new System.Drawing.Size(75, 23);
            this.buttonCancel.TabIndex = 3;
            this.buttonCancel.Text = "Cancel";
            this.buttonCancel.UseVisualStyleBackColor = true;
            this.buttonCancel.Click += new System.EventHandler(this.buttonCancel_Click);
            // 
            // buttonOK
            // 
            this.buttonOK.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonOK.Location = new System.Drawing.Point(247, 12);
            this.buttonOK.Name = "buttonOK";
            this.buttonOK.Size = new System.Drawing.Size(75, 23);
            this.buttonOK.TabIndex = 4;
            this.buttonOK.Text = "OK";
            this.buttonOK.UseVisualStyleBackColor = true;
            this.buttonOK.Click += new System.EventHandler(this.buttonOK_Click);
            // 
            // SelectTextForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(334, 258);
            this.Controls.Add(this.buttonCancel);
            this.Controls.Add(this.buttonOK);
            this.Controls.Add(this.panelSelectText);
            this.Name = "SelectTextForm";
            this.Text = "SelectTextForm";
            this.Load += new System.EventHandler(this.SelectTextForm_Load);
            this.panelSelectText.ResumeLayout(false);
            this.panelSelectText.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panelSelectText;
        private System.Windows.Forms.Label labelExplanation;
        private System.Windows.Forms.ListBox listBoxTexts;
        private System.Windows.Forms.Button buttonCancel;
        private System.Windows.Forms.Button buttonOK;
    }
}