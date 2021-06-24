using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.Windows.Forms;
using System.Data.OleDb;
using System.Collections.Generic;

namespace Filters
{
    class sepia
    {

        public Color[,] sepiaa(Color[,] cm, int r, int g, int b)
        {

            for (int i = 0; i < cm.GetLength(0); i++)
            {
                for (int j = 0; j < cm.GetLength(1); j++)
                {
                    int red = (byte)(cm[i, j].R * ((double)r / 100));
                    int green = (byte)(cm[i, j].G * ((double)g / 100));
                    int blue = (byte)(cm[i, j].B * ((double)b / 100));
                    cm[i, j] = Color.FromArgb(red, green, blue);


                }
            }
            return cm;
        }


        public Color[,] shema(Color[,] cm, int p)
        {

            for (int i = 0; i < cm.GetLength(0); i++)
            {
                for (int j = 0; j < cm.GetLength(1); j++)
                {


                    cm[i, j] = Color.FromArgb(254,130, 130, 130);
                    j += p;
                }

            }
            for (int i = 0; i < cm.GetLength(0); i++)
            {
                for (int j = 0; j < cm.GetLength(1); j++)
                {
                    cm[i, j] = Color.FromArgb(130, 130, 130);
                }
                i += p;

            }
            return cm;
        }
        public Color[,] smesh(Color[,] cm)
        {
            for (int i = 0; i < cm.GetLength(0)-10; i++)
            {
                int pi = i + 11;
                for (int j = 0; j < cm.GetLength(1)-10; j++)
                {

                    int pj = j + 11;
                    int sred = 0;
                    int sgreen = 0;
                    int sblue = 0;

                    for (int t = i + 1; t < pi; t++)
                    {
                        for (int r = j + 1; r < pj; r++)
                        {
                            int red = cm[t, r].R;
                            int green = cm[t, r].G;
                            int blue = cm[t, r].B;
                            sred += red;
                            sgreen += green;
                            sblue += blue;

                        }
                    }
                    sred /= 100;
                    sgreen /= 100;
                    sblue /= 100;

                    for (int t = i + 1; t < pi && pi <= cm.GetLength(0); t++)
                    {
                        for (int r = j + 1; r < pj && pj <= cm.GetLength(1); r++)
                        {
                            cm[t, r] = Color.FromArgb(sred, sgreen, sblue);
                        }

                    }

                    j += 10;

                }
                i += 10;
            }

            return cm;

        }

        public Dictionary<int, Color> palitra(Color[,] cm, Dictionary<Color, int> Palit)
        {
            Dictionary<int, Color> NewPalit = new Dictionary<int, Color>();
            Dictionary<Color, Color> Promeg = new Dictionary<Color, Color>();
            int ind = 0;
            for (int i = 0; i < cm.GetLength(0) - 10; i++)
            {   
                for (int j = 0; j < cm.GetLength(1) - 10; j++)
                {

                        ind++;
                        int R = cm[i + 1, j + 1].R;
                        int G = cm[i + 1, j + 1].G;
                        int B = cm[i + 1, j + 1].B;

                        Color con = cm[i + 1, j + 1];
                        string sred = null;
                        string M1 = null;
                        string M2 = null;
                        string M = null;
                        string sred1 = null;
                        // string M4 = null;
                        Promeg.Clear();
                        foreach (Color s in Palit.Keys)
                        {
                            if (R - 25 <= s.R && s.R <= R + 25 && G - 25 <= s.G && s.G <= G + 25 && B - 25 <= s.B && s.B <= B + 25)
                            {       
                                    Promeg.Add(s,cm[i + 1, j + 1]);
                            }
                        }
                        /* if (M != null)
                           {
                               if (M == "R")
                               {
                                   if (R > G)
                                   {
                                       M4 = "Max";
                                   }
                                   else
                                   {
                                       M4 = "Min";
                                   }
                               }
                               else if (M == "G")
                               {
                                   if (G > R)
                                   {
                                       M4 = "Max";
                                   }
                                   else
                                   {
                                       M4 = "Min";
                                   }
                               }
                               else if (M == "B")
                               {
                                   if (B > G)
                                   {
                                       M4 = "Max";
                                   }
                                   else
                                   {
                                       M4 = "Min";
                                   }
                               }

                           }*/

                        if (R == G)
                        {
                            M1 = "R";
                            M2 = "G";
                            M = "B";
                        }
                        else if (R == B)
                        {
                            M1 = "R";
                            M2 = "B";
                            M = "G";
                        }
                        else if (G == B)
                        {
                            M1 = "G";
                            M2 = "B";
                            M = "R";
                        }
                        if (M == null)
                        {
                            int big = R; 
                            sred = "R";
                            if (big < G)
                            {
                                sred = "G";
                                big = G;
                            }
                            if (big < B)
                            {
                                sred = "B";
                                big = B;
                            }
                        int small = R;
                        sred1 = "R";
                        if (small > G)
                        {
                            sred1 = "G";
                            small = G;
                        }
                        if (small < B)
                        {
                            sred1 = "B";
                            small = B;
                        }

                    }

                    if (sred != null)

                    {

                        int min = 25;
                        if (sred == "R")
                        {
                            foreach (Color s in Promeg.Keys)
                            {
                                
                                    int R2 = R - s.R;
                                    if (min > Math.Abs(R2))
                                    {
                                        min = R2;
                                        con = s;
                                    }
                                    else if (min == Math.Abs(R2))
                                    {
                                        if (min >= R2)
                                        {
                                            min = R2;
                                            con = s;
                                        }

                                    }
                               
                            }
                        }
                        else if (sred == "G")
                        {
                            foreach (Color s in Promeg.Keys)
                            {
                                    int G2 = G - s.G;
                                    if (min > Math.Abs(G2))
                                    {
                                        min = G2;
                                        con = s;
                                    }
                                    else if (min == Math.Abs(G2))
                                    {
                                        if (min >= G2)
                                        {
                                            min = G2;
                                            con = s;
                                        }

                                    }
                            }
                        }
                        else if (sred == "B")
                        {
                            foreach (Color s in Promeg.Keys)
                            {
                                    int B2 = B - s.B;
                                    if (min > Math.Abs(B2))
                                    {
                                        min = B2;
                                        con = s;
                                    }
                                    else if (min == Math.Abs(B2))
                                    {
                                        if (min >= B2)
                                        {
                                            min = B2;
                                            con = s;
                                        }

                                    }
                            }
                        }
                    }
                    else if (M != null)
                    {
                        if (M1 == "R" && M2 == "G")
                        {
                            int min = 40;
                            foreach (Color s in Promeg.Keys)
                            {
                                int R2 = s.R - s.G;
                                if (min > R2)
                                {
                                    min = R2;
                                    con = s;
                                }
                                if (min == R2)
                                {
                                    if (B <= s.B)
                                    {
                                        min = R2;
                                        con = s;
                                    }
                                }
                            }
                        }
                        else if (M1 == "R" && M2 == "B")
                        {
                            int min = 40;
                            foreach (Color s in Promeg.Keys)
                            {
                                int R2 = s.R - s.B;
                                if (min > R2)
                                {
                                    min = R2;
                                    con = s;
                                }
                                if (min == R2)
                                {
                                    if (G <= s.G)
                                    {
                                        min = R2;
                                        con = s;
                                    }
                                }
                            }
                        }
                        else if (M1 == "G" && M2 == "B")
                        {
                            int min = 40;
                            foreach (Color s in Promeg.Keys)
                            {
                                int R2 = s.G - s.B;
                                if (min > R2)
                                {
                                    min = R2;
                                    con = s;
                                }
                                if (min == R2)
                                {
                                    if (R <= s.R)
                                    {
                                        min = R2;
                                        con = s;
                                    }
                                }
                            }
                        }

                    }
                    if (!NewPalit.ContainsKey(ind))
                   { NewPalit[ind] = con; }
                        j += 10;
                    }
                    i += 10;
                }
           
               return NewPalit;
            }


            public Color[,] perecras(Color[,] cm, Dictionary<int, Color> Palit)
            {
                int ind = 1;
                for (int i = 0; i < cm.GetLength(0)-10; i++)
                {
                    int pi = i + 11;
                    for (int j = 0; j < cm.GetLength(1)-10; j++)
                    {
                        
                        int pj = j + 11;
                        for (int t = i + 1; t < pi; t++)
                        {
                            for (int r = j + 1; r < pj; r++)
                            {
                                cm[t, r] = Palit[ind];    
                            }

                        }
                       
                        j += 10;
                    ind += 1;
                    }
                    i += 10;

                }
                return cm;
            }

            public Dictionary<Color, int> All(Color[,] cm)
            {
                Dictionary<Color, int> AllColor = new Dictionary<Color, int>();
                for (int i = 0; i < cm.GetLength(0); i++)
                {
                    int pi = i + 11;
                    if (i > cm.GetLength(0) - 10)
                    { break; }
                    for (int j = 0; j < cm.GetLength(1); j++)
                    {
                        if (j > cm.GetLength(1) - 10)
                        { break; }
                        if (!AllColor.ContainsKey(cm[i + 1, j + 1]))
                        {
                            AllColor.Add(cm[i + 1, j + 1], 1);
                        }
                        else
                        {
                            AllColor[cm[i + 1, j + 1]] += 1;
                        }
                        j += 10;
                    }
                    i += 10;
                }
                return AllColor;
            }

            public Dictionary<Color, Color> vosmoj(Color[,] cm, Dictionary<Color, int> Palit, int x, int y, int dip)
            {
                Dictionary<Color, Color> Promeg = new Dictionary<Color, Color>();
                for (int i = x - 1; i < x; i++)
                {
                    for (int j = y - 1; j < y; j++)
                    {

                        int R = cm[i + 1, j + 1].R;
                        int G = cm[i + 1, j + 1].G;
                        int B = cm[i + 1, j + 1].B;
                        foreach (Color s in Palit.Keys)
                        {
                            if (R - dip <= s.R && s.R <= R + dip && G - dip <= s.G && s.G <= G + dip && B - dip <= s.B && s.B <= B + dip)
                            {
                                Promeg.Add(s, cm[i + 1, j + 1]);
                            }
                        }
                    }
                }
                return Promeg;
            }

        }
    } 

