
// =========================================================
//       從某一點到其餘各點的最短路徑
//         Dijkstra() Dijkstra演算法
//         find_Shortest() 找出Decided[]=0且Dist最小者
//         Dist(N) 從起點到各點的最短距離
//         PreNode(N) 各點最短路徑中的前一個頂點
//         Decided(N) 最短路徑是否已決定
//        作者: Chris C.S Huang            Dave Gan edited: take away unsafe code and made it an single function
//        程式語言: VC# 2008 Expression Edition
//=========================================================
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
namespace ConsoleApplication1
{
    class Program
    {
        const int NC = 100000; 
        static void Main(string[] args)
        {
            int[,] Cost = new int[,]  {{ 0, 50, 45, 10, NC, NC, },  //V0
                                       {NC,  0, 10, 15, NC, NC, },  //V1
                                       {NC, NC,  0, NC, 30, NC, },  //V2
                                       {20, NC, NC,  0, 15, NC, },  //V3
                                       {NC, 20, 35, NC,  0, NC, },  //V4
                                       {NC, NC, NC, NC,  3,  0, }}; //V5
            //                                                  //
            //                                                    //
            //                                                      //diagonal element must all be zeros


            int N = (int)Math.Sqrt(Cost.Length + 1);
            List<List<int>> matrix_pathes = new List<List<int>>();
            Console.Write("plz input start position(0-" + Convert.ToString(N - 1) + "): ");
            int Start = Convert.ToInt16(Console.ReadLine());
            int[] Dist = Dijkstra(Cost, Start, ref matrix_pathes);

            for (int i = 0; i < N; i++)
            {
                Console.Write("V{0} --> V{1}  Distance == {2}  ", Start, i, Dist[i]);
                Console.Write("path:");
                foreach (int j in matrix_pathes[i])
                    Console.Write(j + ",");
                Console.WriteLine("");
            }
            Console.WriteLine("Press Enter key to Exit"); 
            Console.Read();
        }


        public static int[] Dijkstra(int[,] Cost, int Start, ref List<List<int>> matrix_pathes) 
        {
            int N = (int)Math.Sqrt(Cost.Length + 1);
            int Nd = 0;
            int[] Dist = new int[N];
            int[] PreNode = new int[N];
            int[] Decided = new int[N];

            for (int i = 0; i < N; i++)
            {
                Dist[i] = Cost[Start, i]; 
                PreNode[i] = Start;       
                Decided[i] = 0;
            }
            Decided[Start] = 1;


            while (true)
            {
                int lowest = NC;
                for (int j = 0; j < N; j++)
                {
                    if (Decided[j] == 0 && Dist[j] < lowest)
                    {
                        lowest = Dist[j];
                        Nd = j;
                    }
                }
                if (Decided[Nd] == 1)
                    break;

                Decided[Nd] = 1;
                for (int w = 0; w < N; w++)
                {
                    if (Decided[w] == 0 && Dist[w] > (Dist[Nd] + Cost[Nd, w])) 
                    {
                        Dist[w] = Dist[Nd] + Cost[Nd, w]; 
                        PreNode[w] = Nd; 
                    }
                }
            }

            for (int Nd_ = 0; Nd_ < N; Nd_++)
            {
                List<int> track = new List<int>();
                int i = PreNode[Nd_];

                track.Add(Nd_);
                while (i != Start)
                {
                    track.Add(i); 
                    i = PreNode[i];
                }
                track.Add(i);
                matrix_pathes.Add(track);
            }
            return Dist;
        }
    }
}