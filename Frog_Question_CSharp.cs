using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Frog_Question_CSharp
{
    class Program
    {
        static void Main(string[] args)
        {
            int[] t = new int[] { 1, 1, 1, 0, 2, 2, 2 };
            int k = 1;
            while (!Jump(t))
            {
                Console.Write(k++ + " ");
                print(t);
            }
        }

        static bool Jump(int[] t)
        {
            if (t[0] + t[1] + t[2] == 6 && t[4] + t[5] + t[6] == 3 && t[3] == 0) 
            {
                return true;
            }
            else
            {
                for (int i = 0; i < 7; i++)
                {
                    if (i <= 4 && t[i] == 1 && t[i + 1] == 2 && t[i + 2] == 0)
                    {
                        change(ref t[i], ref t[i + 2]);
                        return false;
                    }
                }

                for (int i = 0; i < 7; i++)
                {
                    if (i <= 4 && t[i] == 0 && t[i + 1] == 1 && t[i + 2] == 2)
                    {
                        change(ref t[i], ref t[i + 2]);
                        return false;
                    }
                }

                //Traffic Block State:  in this state, the next step will and will only have "1122" situation, and "1122" situation will always be "1122"

                for (int i = 0; i < 7; i++)
                {
                    if (
                        (i <= 5 && t[i] == 1 && t[i + 1] == 0)
                        &&
                        (
                            (i < 1 || i > 4)
                            ||
                            (t[i - 1] != t[i + 2])
                        )
                        )
                    {
                        change(ref t[i], ref t[i + 1]);
                        return false;
                    }
                }

                for (int i = 0; i < 7; i++)
                {
                    if (
                        (i <= 5 && t[i] == 0 && t[i + 1] == 2)
                        &&
                        (
                            (i < 1 || i > 4)
                            ||
                            (t[i - 1] != t[i + 2])
                        )
                        )
                    {
                        change(ref t[i], ref t[i + 1]);
                        return false;
                    }
                }

                Console.WriteLine("error"); 
                Console.Read();
                return false;
            }
        }
        static void print(int[] a)
        {
            int i;
            for (i = 0; i <= 6; i++)
            {
                Console.Write(a[i]);
            }
            Console.WriteLine("");
        }

        static void change(ref int n, ref int m)
        {
            int term;
            term = n; n = m; m = term;
        }
    }
}
