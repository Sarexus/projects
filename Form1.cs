using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing.Imaging;
using Filters;
using System.Data.OleDb;




namespace WindowsFormsApp4
{
    public partial class Form1 : Form
    {
        public static string connectString = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=BD.accdb;";
        private OleDbConnection myConnection;

        Dictionary<Color, int> Palit = new Dictionary<Color, int>();
        Dictionary<int, Color> NewPalit = new Dictionary<int, Color>();
        Dictionary<Color, int> AllColor = new Dictionary<Color, int>();
        Dictionary<Color, Color> Vosm = new Dictionary<Color, Color>();
        int a;
        int b;
        int c;
        int a1;
        int b1;
        int colCl;
        int A1;
        int B1;
        Image picture;
        Image picture1;
        Image picture2;
        Bitmap pic3 = new Bitmap(1, 1);
        Image picture3;
        Image picture4;
        int ColR;
        int ColG;
        int ColB;
        int X1;
        int Y1;
        int width;
        int height;
        double Height;
        Color col;
        public Form1()
        {

            InitializeComponent();
            comboBox1.SelectedItem = comboBox1.Items[0];
            comboBox1.DropDownStyle = ComboBoxStyle.DropDownList;
            comboBox2.SelectedItem = comboBox2.Items[0];
            comboBox2.DropDownStyle = ComboBoxStyle.DropDownList;
            comboBox3.SelectedItem = comboBox3.Items[0];
            comboBox3.DropDownStyle = ComboBoxStyle.DropDownList;
            myConnection = new OleDbConnection(connectString);
            myConnection.Open();
            string query = "SELECT Код,R,G,B FROM Color";
            OleDbCommand command = new OleDbCommand(query, myConnection);
            OleDbDataReader reader = command.ExecuteReader();
            while (reader.Read()) 
            {
                int cod = int.Parse(reader[0].ToString());
                int R = int.Parse(reader[1].ToString());
                int G = int.Parse(reader[2].ToString());
                int B = int.Parse(reader[3].ToString());
                Color color = Color.FromArgb(R, G, B);
                if (!Palit.ContainsKey(color))
                    Palit.Add(color, cod);
            }
            reader.Close();
            pictureBox3.BackColor = Color.FromArgb(0, 0, 0);
            textBox6.Text = "0";
            textBox4.Text = "0";
            textBox5.Text = "0";
            textBox7.Text = "0";
            pictureBox2.BackColor = Color.FromArgb(254, 140, 180, 230);
            pictureBox1.BackColor = Color.FromArgb(254, 140, 180, 230);
            button12.Text = "Исходное изображение";
            this.ActiveControl = button2;
            pictureBox2.Hide();
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            label1.Text = Convert.ToString(trackBar1.Value);
        }

        private void trackBar2_Scroll(object sender, EventArgs e)
        {
            label2.Text = Convert.ToString(trackBar2.Value);
        }

        private void trackBar3_Scroll(object sender, EventArgs e)
        {
            label3.Text = Convert.ToString(trackBar3.Value);
        }
        private void button2_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.Cancel)
                return;
            string filename = openFileDialog1.FileName;
            string q = openFileDialog1.FileName.Replace(@"\", "\\");
            pictureBox1.Image = Image.FromFile(q);
            pictureBox2.Image = null;
            picture = null;
            picture1 = null;
            picture2 = null;
            pictureBox1.Show();
            pictureBox2.Hide();
            textBox2.Text = "";
            textBox3.Text = "";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            pictureBox2.Show();
            if (pictureBox1.Image == null)
            {
                MessageBox.Show("Отсутсвует изображение");
            }
            else
            {

                Bitmap Grafics;
                Bitmap Prom;
                A1 = a1 * 10 + a1 + 1;
                B1 = b1 * 10 + b1 + 1;
                if (picture != null)
                {
                    Grafics = new Bitmap(picture);
                }
                else
                {
                    Grafics = new Bitmap(pictureBox1.Image);
                }
                pic3.SetPixel(0, 0, Color.FromArgb(254, 140, 180, 230));
                Bitmap pic4 = new Bitmap(pic3, A1, B1);
                picture3 = (Image)pic4;
                Prom = new Bitmap(Grafics, A1, B1);
                sepia sep = new sepia();
                Color[,] colormap = new Color[Prom.Width, Prom.Height];
                for (int i = 0; i < Prom.Width; i++)
                {
                    for (int j = 0; j < Prom.Height; j++)
                    {
                        colormap[i, j] = Prom.GetPixel(i, j);
                    }
                }
                colormap = sep.shema(colormap, 10);
                colormap = sep.smesh(colormap);
                for (int i = 0; i < Prom.Width; i++)
                {
                    for (int j = 0; j < Prom.Height; j++)
                    {
                        Prom.SetPixel(i, j, colormap[i, j]);
                    }
                }
                picture1 = (Image)Prom;
                picture4 = picture1;
                pictureBox2.Image = picture3;
                pictureBox1.Hide();
                textBox2.Text = "";
                textBox3.Text = "";
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            trackBar1.Value = 100;
            trackBar2.Value = 100;
            trackBar3.Value = 100;
            comboBox1.SelectedItem = comboBox1.Items[0];
            comboBox2.SelectedItem = comboBox2.Items[0];
            comboBox3.SelectedItem = comboBox3.Items[0];
            pictureBox2.Image = null;
            label1.Text = "100";
            label2.Text = "100";
            label3.Text = "100";
            textBox2.Clear();
            textBox3.Clear();
            listBox1.Items.Clear();
            NewPalit = null;
            AllColor = null;
            Vosm = null;
            picture = null;
            picture1 = null;
            picture2 = null;
            pictureBox1.Show();
            pictureBox2.Hide();
            picture = null;
            picture1 = null;
            picture2 = null;


        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (picture1 == null)
            {
                MessageBox.Show("Отсутствует схема");
            }
            else
            {
                Bitmap Grafics = new Bitmap(pictureBox2.Image);
                Bitmap btm = new Bitmap(Grafics, width, height);
                Image pict = (Image)btm;
                saveFileDialog1.Filter = "JPeg Image|*.jpg|Bitmap Image|*.bmp|Gif Image|*.gif|Tiff Image|*.tiff|Pdf Image|*.pdf|Png Image|*.png";
                if (saveFileDialog1.ShowDialog() == DialogResult.Cancel)
                    return;
                string filename = saveFileDialog1.FileName;
                pict.Save(filename, ImageFormat.Png);
                MessageBox.Show("Файл сохранен");
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            pictureBox2.Show();
            if (pictureBox1.Image == null)
            {
                MessageBox.Show("Отсутсвует изображение");
            }
            else
            {
                sepia sep = new sepia();
                Bitmap Prom = new Bitmap(pictureBox1.Image);
                Color[,] colormap = new Color[Prom.Width, Prom.Height];
                for (int i = 0; i < Prom.Width; i++)
                {
                    for (int j = 0; j < Prom.Height; j++)
                    {
                        colormap[i, j] = Prom.GetPixel(i, j);
                    }
                }
                colormap = sep.sepiaa(colormap, trackBar1.Value, trackBar2.Value, trackBar3.Value);
                for (int i = 0; i < Prom.Width; i++)
                {
                    for (int j = 0; j < Prom.Height; j++)
                    {
                        Prom.SetPixel(i, j, colormap[i, j]);
                    }
                }
                picture = (Image)Prom;
                pictureBox2.Image = picture;
                pictureBox1.Hide();
                textBox2.Text = "";
                textBox3.Text = "";
            }
        }
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            myConnection.Close();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            pictureBox2.Show();
            if (picture1 == null)
            {
                MessageBox.Show("Примените схему");
            }
            else
            {
                sepia sep = new sepia();
                Bitmap Prom = new Bitmap(picture4);
                Color[,] colormap = new Color[Prom.Width, Prom.Height];
                for (int i = 0; i < Prom.Width; i++)
                {
                    for (int j = 0; j < Prom.Height; j++)
                    {
                        colormap[i, j] = Prom.GetPixel(i, j);
                    }
                }
                NewPalit = sep.palitra(colormap, Palit);
                colormap = sep.perecras(colormap, NewPalit);
                for (int i = 0; i < Prom.Width; i++)
                {
                    for (int j = 0; j < Prom.Height; j++)
                    {
                        Prom.SetPixel(i, j, colormap[i, j]);
                    }
                }
                picture2 =(Image)Prom;
                picture4 = picture2;
                pictureBox2.Image = picture3;
                textBox2.Text = "";
                textBox3.Text = "";
            }
        }

        private void button7_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
            int i = 0;
            foreach (Color s in Palit.Keys)
            {
                string ps = (s).ToString();
                listBox1.Items.Insert(i, ps);
                i++;
            }
        }

        private void button8_Click(object sender, EventArgs e)
        {

            listBox1.Items.Clear();
            int i = 0;
            foreach (int s in NewPalit.Keys)
            {
                Color r = NewPalit[s];
                string ps =(i+1).ToString()+" | "+r.ToString();
                listBox1.Items.Insert(i, ps);
                i++;
            }
        }

        private void button9_Click(object sender, EventArgs e)
        {
            if (picture1 != null)
            {
                listBox1.Items.Clear();
                sepia sep = new sepia();
                Bitmap Param = new Bitmap(pictureBox2.Image);
                Color[,] map = new Color[Param.Width, Param.Height];
                for (int i = 0; i < Param.Width; i++)
                {
                    for (int j = 0; j < Param.Height; j++)
                    {
                        map[i, j] = Param.GetPixel(i, j);
                    }
                }

                AllColor = sep.All(map);

                int y = 0;
                foreach (Color s in AllColor.Keys)
                {
                    string ps = (y + 1).ToString() + " | " + AllColor[s].ToString() + " | " + s.ToString();
                    listBox1.Items.Insert(y, ps);
                    y++;

                }
            }
        }

        private void button10_Click(object sender, EventArgs e)
        {
            if (picture1 == null || pictureBox2.Image == picture)
            {
                MessageBox.Show("Примените схему");
            }
            else 
            {
                int dip = int.Parse(textBox7.Text);
                listBox1.Items.Clear();
                Bitmap Prom = new Bitmap(picture4);
                Color[,] colormap = new Color[Prom.Width, Prom.Height];
                for (int i = 0; i < Prom.Width; i++)
                {
                    for (int j = 0; j < Prom.Height; j++)
                    {
                        colormap[i, j] = Prom.GetPixel(i, j);
                    }
                }
                sepia sep = new sepia();
                int x = int.Parse(textBox2.Text);
                int y = int.Parse(textBox3.Text);
                x = x * 10 + x - 10;
                y = y * 10 + y - 10;
                if (x < picture4.Width - 10 && y < picture4.Height)
                {
                    Vosm = sep.vosmoj(colormap, Palit, x, y, dip);

                int z = 0;
                foreach (Color s in Vosm.Keys)
                {
                    string ps = (z + 1).ToString() + "    |    " + s.ToString();
                    listBox1.Items.Insert(z, ps);
                    z++;
                }
                }
            }
        }

        private void comboBox3_SelectedIndexChanged(object sender, EventArgs e)
        {
            a = int.Parse(comboBox3.SelectedItem.ToString());
            a1 = a * c;
            colCl = a1 * b1;
            textBox1.Text = colCl.ToString();
            button1.Focus();
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            b = int.Parse(comboBox2.SelectedItem.ToString());
            b1 = b * c;
            colCl = a1 * b1;
            textBox1.Text = colCl.ToString();
            button1.Focus();
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            c = int.Parse(comboBox1.SelectedItem.ToString());
            a1 = a * c;
            b1 = b * c;
            colCl = a1 * b1;
            textBox1.Text = colCl.ToString();
            button1.Focus();
        }

        private void button11_Click(object sender, EventArgs e)
        {
            if (picture1 == null)
            {
                MessageBox.Show("Примените схему");
            }
            else if (textBox2.Text == "" || textBox3.Text == "")
            { MessageBox.Show("Не выбран цвет схемы"); }
            else
            {

                Bitmap Prom = new Bitmap(picture4);
                int x = int.Parse(textBox2.Text);
                int y = int.Parse(textBox3.Text);
                int R = int.Parse(textBox6.Text);
                int G = int.Parse(textBox4.Text);
                int B = int.Parse(textBox5.Text);
                int X = x * 10 + x - 10;
                int Y = y * 10 + y - 10;
                if (X < picture4.Width - 10 && Y < picture4.Height)
                {
                    for (int i = X - 1; i < X + 9; i++)
                    {
                        for (int j = Y - 1; j < Y + 9; j++)
                        {
                            Prom.SetPixel(i + 1, j + 1, Color.FromArgb(R, G, B));
                        }
                    }
                    picture4 = (Image)Prom;
                    pictureBox2.Image = picture3;
                }
            }
        }


        private void textBox5_KeyPress(object sender, KeyPressEventArgs e)
        {
            char number = e.KeyChar;

            if (!Char.IsDigit(number) && number != 8)
            {
                e.Handled = true;
            }
        }

        private void textBox4_KeyPress(object sender, KeyPressEventArgs e)
        {
            char number = e.KeyChar;

            if (!Char.IsDigit(number) && number != 8)
            {
                e.Handled = true;
            }
        }

        private void textBox6_KeyPress(object sender, KeyPressEventArgs e)
        {
            char number = e.KeyChar;

            if (!Char.IsDigit(number) && number != 8)
            {
                e.Handled = true;
            }

        }

        private void textBox7_KeyPress(object sender, KeyPressEventArgs e)
        {
            char number = e.KeyChar;

            if (!Char.IsDigit(number) && number != 8)
            {
                e.Handled = true;
            }
        }

        private void textBox6_TextChanged(object sender, EventArgs e)
        {
            if (textBox6.Text != "")
            { ColR = int.Parse(textBox6.Text); }
        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {
            if (textBox4.Text != "")
            { ColG = int.Parse(textBox4.Text); }
        }

        private void textBox5_TextChanged(object sender, EventArgs e)
        {
            
            if (textBox5.Text != "")
            { ColB = int.Parse(textBox5.Text); }
        }

        private void textBox6_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                button11.Focus();
            }
        }

        private void textBox4_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                button11.Focus();
            }
        }

        private void textBox5_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                button11.Focus();
            }
        }

        private void textBox6_Validated(object sender, EventArgs e)
        {
            if (textBox6.Text == "")
            { textBox6.Text = "0"; }
            if (int.Parse(textBox6.Text) > 255)
            { textBox6.Text = "255"; }
            pictureBox3.BackColor = Color.FromArgb(ColR, ColG, ColB);
        }

        private void textBox4_Validated(object sender, EventArgs e)
        {
            if (textBox4.Text == "")
            { textBox4.Text = "0"; }
            if (int.Parse(textBox4.Text) > 255)
            { textBox4.Text = "255"; }
            pictureBox3.BackColor = Color.FromArgb(ColR, ColG, ColB);
        }

        private void textBox5_Validated(object sender, EventArgs e)
        {
            if (textBox5.Text == "")
            { textBox5.Text = "0"; }
            if (int.Parse(textBox5.Text) > 255)
            { textBox5.Text = "255"; }
            pictureBox3.BackColor = Color.FromArgb(ColR, ColG, ColB);
        }

        private void textBox2_KeyPress(object sender, KeyPressEventArgs e)
        {
            char number = e.KeyChar;

            if (!Char.IsDigit(number) && number != 8)
            {
                e.Handled = true;
            }
        }

        private void textBox3_KeyPress(object sender, KeyPressEventArgs e)
        {
            char number = e.KeyChar;

            if (!Char.IsDigit(number) && number != 8)
            {
                e.Handled = true;
            }
        }

        private void textBox2_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                button10.Focus();
            }
        }

        private void textBox3_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                button10.Focus();
            }
        }

        private void textBox7_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                button10.Focus();
            }
        }

        private void textBox7_Validated(object sender, EventArgs e)
        {
            if (textBox7.Text == "")
            { textBox7.Text = "0"; }
            if (int.Parse(textBox7.Text) > 255)
            { textBox7.Text = "255"; }
        }

        private void pictureBox2_Paint(object sender, PaintEventArgs e)
        {
            if (picture1 != null && pictureBox2.Image != picture)
            {
                    double Wit = (double)pictureBox2.Width;
                    double Heig = (double)pictureBox2.Height;
                    if (picture4.Width < picture4.Height)
                    {
                        Height = Heig / (double)picture4.Height;
                        width = (int)(picture4.Width * Height);
                        height = (int)(picture4.Height * Height);
                        X1 = (int)((Wit - width) / 2.00);
                        Y1 = 0;
                        pictureBox2.Image = picture3;
                        e.Graphics.DrawImage(picture4, X1, Y1, width, height);
                    }
                    else if (picture4.Width == picture4.Height)
                    {

                        Height = Heig / (double)picture4.Height;
                        width = (int)(picture4.Width * Height) - 100;
                        height = (int)(picture4.Height * Height) - 100;
                        X1 = (int)((Wit - width) / 2.00);
                        Y1 = (int)((Heig - height) / 2.00);
                        pictureBox2.Image = picture3;
                        e.Graphics.DrawImage(picture4, X1, Y1, width, height);

                    }
                    else
                    {
                        Height = Wit / (double)picture4.Width;
                        int width = (int)(picture4.Width * Height);
                        int height = (int)(picture4.Height * Height);
                        X1 = 0;
                        Y1 = (int)((Heig - height) / 2.00);
                        pictureBox2.Image = picture3;
                        e.Graphics.DrawImage(picture4, X1, Y1, width, height);
                    }
                
            }
        }

        private void button12_Click(object sender, EventArgs e)
        {
            if (pictureBox1.Image == null)
            {
                MessageBox.Show("Отсутствует изображение");
            }
            else
            {   if(button12.Text == "Исходное изображение")
                { 
                pictureBox1.Show();
                pictureBox2.Hide();
                button12.Text = "Конечное изображение";
                }
                else if(button12.Text == "Конечное изображение")
                {
                    pictureBox1.Hide();
                    pictureBox2.Show();
                    button12.Text = "Исходное изображение";
                }
            }
        }

        private void pictureBox2_MouseDown(object sender, MouseEventArgs e)
        {
            int x = e.X - X1;
            int y = e.Y - Y1;
            int x1 = x / (int)Height;
            int y1 = y / (int)Height;
            int x2 = x1 / 10 + 1;
            int y2 = y1 / 10 + 1;
            textBox2.Text = x2.ToString();
            textBox3.Text = y2.ToString();
            if (textBox2.Text != "" && textBox3.Text != "" && pictureBox2.Image == picture3 && picture4 != null)
            {
                Bitmap par = new Bitmap(picture4);
                textBox2.Text = x2.ToString();
                textBox3.Text = y2.ToString();
                x = x2 * 10 + x2 - 10;
                y = y2 * 10 + y2 - 10;
                if (x < picture4.Width - 10 && y < picture4.Height)
                {
                    col = par.GetPixel(x + 1, y + 1);
                    textBox6.Text = col.R.ToString();
                    textBox4.Text = col.G.ToString();
                    textBox5.Text = col.B.ToString();
                    pictureBox3.BackColor = col;
                }

            }
            }

        private void textBox2_Validated(object sender, EventArgs e)
        {
            if (textBox2.Text != "" && textBox3.Text != "" && pictureBox2.Image == picture3 && picture4 != null)
            {
                Bitmap par = new Bitmap(picture4);
                int x = int.Parse(textBox2.Text);
                int y = int.Parse(textBox3.Text);
                x = x * 10 + x - 10;
                y = y * 10 + y - 10;
                if (x < picture4.Width - 10 && y < picture4.Height)
                {
                    col = par.GetPixel(x + 1, y + 1);
                    textBox6.Text = col.R.ToString();
                    textBox4.Text = col.G.ToString();
                    textBox5.Text = col.B.ToString();
                    pictureBox3.BackColor = col;
                }
            }
        }

        private void textBox3_Validated(object sender, EventArgs e)
        {
            if (textBox2.Text != "" && textBox3.Text != "" && pictureBox2.Image == picture3 && picture4 != null)
            {
                Bitmap par = new Bitmap(picture4);
                int x = int.Parse(textBox2.Text);
                int y = int.Parse(textBox3.Text);
                x = x * 10 + x - 10;
                y = y * 10 + y - 10;
                if (x < picture4.Width - 10 && y < picture4.Height)
                {
                    col = par.GetPixel(x + 1, y + 1);
                    textBox6.Text = col.R.ToString();
                    textBox4.Text = col.G.ToString();
                    textBox5.Text = col.B.ToString();
                    pictureBox3.BackColor = col;
                }
            }
        }
    }
}
