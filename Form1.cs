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
            File.WriteAllText("..\\..\\solutions\\inWordoku.txt", richTextBox1.Text);
            Process process = new Process();
            process.StartInfo.UseShellExecute = false;
            process.StartInfo.WorkingDirectory = "..\\..\\solutions";
            if (checkBox1.Checked)
            { 
                process.StartInfo.FileName = "..\\..\\solutions\\SebiSolution.exe";
            }
            else
            { 
                process.StartInfo.FileName="..\\..\\solutions\\FlorinSolution.exe";  
            }
            process.StartInfo.CreateNoWindow = true;
            process.Start();
            process.WaitForExit();
            richTextBox2.Text = System.IO.File.ReadAllText("..\\..\\solutions\\outWordoku.txt");
            textBox1.Text = System.IO.File.ReadAllText("..\\..\\solutions\\timeWordoku.txt");

        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            checkBox3.Hide();
            checkBox4.Hide();
            button2.Hide();
            comboBox3.Hide();
            checkBox1.Show();
            checkBox2.Show();
            button1.Show();
            comboBox2.Show();
            richTextBox1.Text = System.IO.File.ReadAllText("..\\..\\solutions\\inWordoku.txt");
            comboBox1.SelectedIndex = 0;
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            checkBox2.Checked = !checkBox1.Checked;
            
        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            checkBox1.Checked = !checkBox2.Checked;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if(comboBox1.SelectedIndex == 0)
            {
                checkBox3.Hide();
                checkBox4.Hide();
                button2.Hide();
                comboBox3.Hide();
                checkBox1.Show();
                checkBox2.Show();
                button1.Show();
                comboBox2.Show();
                richTextBox1.Text = System.IO.File.ReadAllText("..\\..\\solutions\\inWordoku.txt");
            }
            else
            {
                checkBox1.Hide();
                checkBox2.Hide();
                button1.Hide();
                comboBox2.Hide();
                checkBox3.Show();
                checkBox4.Show();
                button2.Show();
                comboBox3.Show();
                richTextBox1.Text = System.IO.File.ReadAllText("..\\..\\solutions\\inKillerSudoku.txt");
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (!checkBox3.Checked && !checkBox4.Checked)
            {
                MessageBox.Show("Selectati o modalitate de rezolvare");
                return;
            }
            File.WriteAllText("..\\..\\solutions\\inKillerSudoku.txt", richTextBox1.Text);
            Process process = new Process();
            process.StartInfo.UseShellExecute = false;
            process.StartInfo.WorkingDirectory = "..\\..\\solutions";
            if (checkBox3.Checked)
            {
                process.StartInfo.FileName = "..\\..\\solutions\\VladSolution.exe";
            }
            else
            {
                process.StartInfo.FileName = "..\\..\\solutions\\DavidSolution.exe";
            }
            process.StartInfo.CreateNoWindow = true;
            process.Start();
            process.WaitForExit();
            richTextBox2.Text = System.IO.File.ReadAllText("..\\..\\solutions\\outKillerSudoku.txt");
            textBox1.Text = System.IO.File.ReadAllText("..\\..\\solutions\\timeKillerSudoku.txt");
        }

        private void checkBox3_CheckedChanged(object sender, EventArgs e)
        {
            checkBox4.Checked = !checkBox3.Checked;
        }

        private void checkBox4_CheckedChanged(object sender, EventArgs e)
        {
            checkBox3.Checked = !checkBox4.Checked;
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void comboBox3_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (comboBox3.SelectedIndex)
            {
                case 0:
                    richTextBox1.Text = System.IO.File.ReadAllText("..\\..\\presets\\KillerSudoku1.txt");
                    break;
                case 1:
                    richTextBox1.Text = System.IO.File.ReadAllText("..\\..\\presets\\KillerSudoku2.txt");
                    break;
                case 2:
                    richTextBox1.Text = System.IO.File.ReadAllText("..\\..\\presets\\KillerSudoku3.txt");
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    break;
            }
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            switch (comboBox2.SelectedIndex)
            {
                case 0:
                    richTextBox1.Text = System.IO.File.ReadAllText("..\\..\\presets\\Wordoku1.txt");
                    break;
                case 1:
                    richTextBox1.Text = System.IO.File.ReadAllText("..\\..\\presets\\Wordoku2.txt");
                    break;
                case 2:
                    richTextBox1.Text = System.IO.File.ReadAllText("..\\..\\presets\\Wordoku3.txt");
                    break;
                case 3:
                    richTextBox1.Text = System.IO.File.ReadAllText("..\\..\\presets\\Wordoku4.txt");
                    break;
            }
        }
    }
}
