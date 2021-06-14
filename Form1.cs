using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

namespace ProiectSudoku
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            
            if (!checkBox1.Checked && !checkBox2.Checked)
            {
                MessageBox.Show("Selectati o modalitate de rezolvare");
                return;
            }
            if (checkBox1.Checked)
            {
                File.WriteAllText("..\\..\\solutions\\inf.txt",richTextBox1.Text);
                Process.Start("..\\..\\solutions\\FlorinSolution.exe");
                richTextBox2.Text = System.IO.File.ReadAllText("..\\..\\solutions\\outf.txt");
            }
            else
            {
                File.WriteAllText("..\\..\\solutions\\inf.txt", richTextBox1.Text);
                Process process = new Process();
                process.StartInfo.UseShellExecute = false;
                process.StartInfo.WorkingDirectory = "..\\..\\solutions";
                process.StartInfo.FileName="..\\..\\solutions\\FlorinSolution.exe";
                process.StartInfo.CreateNoWindow = false;
                process.Start();
                process.WaitForExit();
                richTextBox2.Text = System.IO.File.ReadAllText("..\\..\\solutions\\outf.txt");
            }
            
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            richTextBox1.Text = System.IO.File.ReadAllText("..\\..\\solutions\\inf.txt");
            checkBox1.Checked = true;
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            checkBox2.Checked = !checkBox1.Checked;
            
        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            checkBox1.Checked = !checkBox2.Checked;
        }
    }
}
