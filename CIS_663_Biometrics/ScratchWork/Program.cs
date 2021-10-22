using System;
using System.Collections.Generic;

namespace ScratchWork
{
    class Program
    {
        static List<List<int>> inputArray = new List<List<int>>()
            {
                new List<int>(){0,0,0,0,0,0,0,1,1,1},
                new List<int>(){0,0,3,3,3,3,3,2,1,1},
                new List<int>(){0,0,3,3,4,4,4,4,4,4},
                new List<int>(){0,0,3,3,3,3,4,4,4,4},
                new List<int>(){0,0,0,1,1,3,4,4,4,4},
                new List<int>(){0,0,0,0,0,4,4,4,1,0},
                new List<int>(){5,5,0,0,0,4,4,4,0,0},
                new List<int>(){5,5,0,0,0,4,4,4,0,0},
                new List<int>(){5,5,0,0,0,0,5,5,0,0},
                new List<int>(){5,5,0,0,0,0,5,5,0,0}
            };

        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");

            List<List<int>> outputArray = new List<List<int>>()
            {
                new List<int>(){0,0,0,0,0,0,0,0,0,0},
                new List<int>(){0,0,0,0,0,0,0,0,0,0},
                new List<int>(){0,0,0,0,0,0,0,0,0,0},
                new List<int>(){0,0,0,0,0,0,0,0,0,0},
                new List<int>(){0,0,0,0,0,0,0,0,0,0},
                new List<int>(){0,0,0,0,0,0,0,0,0,0},
                new List<int>(){0,0,0,0,0,0,0,0,0,0},
                new List<int>(){0,0,0,0,0,0,0,0,0,0},
                new List<int>(){0,0,0,0,0,0,0,0,0,0},
                new List<int>(){0,0,0,0,0,0,0,0,0,0}
            };

            for (int i=0; i<10; i++)
            {
                for(int j=0; j<10; j++)
                {
                    outputArray[i][j] = sumForCoordinates(i, j);
                }
            }

            Console.WriteLine("".PadLeft(40,'-'));
            outputArray.ForEach(row =>
            {
                row.ForEach(entry => Console.Write($"{entry}|".PadLeft(4)));
                Console.WriteLine("\n" + "".PadLeft(40, '-'));
            });

            outputArray.ForEach(row =>
            {
                row.ForEach(entry => Console.Write($"{entry},"));
                Console.WriteLine();
            });

            Console.ReadLine();
        }

        private static int sumForCoordinates(int x, int y)
        {
            int sum = 0;
            for(int i=0; i<=x; i++)
            {
                for(int j=0; j<=y; j++)
                {
                    sum += inputArray[i][j];
                }
            }

            return sum;
        }
    }
}
