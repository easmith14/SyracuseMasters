using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Assignment4
{
    class Program
    {
        static void Main(string[] args)
        {
            string dataLocation = @"C:\Users\evana\Downloads\iris.data";

            //read in file and parse
            List<string> rawLines = File.ReadLines(dataLocation).ToList();
            List<Entry> entries = new List<Entry>();

            int id = 0;
            foreach(var line in rawLines)
            {
                string[] columns = line.Split(',');
                entries.Add(new Entry(columns, id++));
            }

            //for each element, calculate all other pairs for each distance and save shortest
            var distanceCalculations = new Dictionary<DistanceTypes, Dictionary<Tuple<Entry, Entry>, double>>()
            {
                { DistanceTypes.Euclidean, new Dictionary<Tuple<Entry, Entry>, double>() },
                { DistanceTypes.Manhattan, new Dictionary<Tuple<Entry, Entry>, double>() },
                { DistanceTypes.CosineSimilarity, new Dictionary<Tuple<Entry, Entry>, double>() }
            };

            for (int i=0; i<entries.Count; i++)
            {
                for (int j = 1; j < entries.Count; j++)
                {
                    //don't find distance between the same value
                    if(entries[i].ID != entries[j].ID)
                    {
                        foreach(var distanceCalculation in distanceCalculations)
                        {
                            double distance = 0;
                            DistanceTypes type = distanceCalculation.Key;
                            var closestPairs = distanceCalculation.Value;

                            switch (type)
                            {
                                case DistanceTypes.Euclidean: distance = computeEuclideanDistance(entries[i], entries[j]); break;
                                case DistanceTypes.Manhattan: distance = computeManhattanDistance(entries[i], entries[j]); break;
                                case DistanceTypes.CosineSimilarity: distance = computeCosineSimularity(entries[i], entries[j]); break;
                                default: throw new Exception("Unknown distance type!");
                            }

                            //if 3 shorter distances do not exist already, record/overwrite
                            double maxValue = closestPairs.Count > 0 ? closestPairs.Values.Max() : 0;

                            var potentialKey = Tuple.Create(entries[i], entries[j]);
                            var mirroredPotentialKey = Tuple.Create(entries[j], entries[i]);

                            if (!closestPairs.ContainsKey(potentialKey) && !closestPairs.ContainsKey(mirroredPotentialKey))
                            {
                                if (closestPairs.Count < 3)
                                {
                                    closestPairs.Add(Tuple.Create(entries[i], entries[j]), distance);
                                }
                                else if (distance < maxValue)
                                {
                                    var maxKey = closestPairs.Where(x => x.Value == maxValue).First().Key;
                                    closestPairs.Remove(maxKey);
                                    closestPairs.Add(Tuple.Create(entries[i], entries[j]), distance);
                                }
                            }
                            
                        }
                    }
                }
            }

            //output the discovered shortest distance pairs
            foreach(var computation in distanceCalculations)
            {
                Console.WriteLine($"Closest Pairs By {computation.Key}");
                
                foreach(var pair in computation.Value)
                {
                    Console.WriteLine($"\t[{pair.Value}]: {{{pair.Key.Item1}}} - {{{pair.Key.Item2}}}");
                }
            }

            Console.ReadLine();
        }

        static private double computeEuclideanDistance(Entry element1, Entry element2)
        {
            double sumOfSquareDifference = 0;
            for(int i=0; i<element1.Values.Count; i++)
            {
                double difference = element1.Values.ElementAt(i) - element2.Values.ElementAt(i);
                sumOfSquareDifference += Math.Pow(difference, 2);
            }

            return Math.Sqrt(sumOfSquareDifference);
        }

        static private double computeManhattanDistance(Entry element1, Entry element2)
        {
            double sumOfAbsoluteValueOfDifference = 0;
            for (int i = 0; i < element1.Values.Count; i++)
            {
                sumOfAbsoluteValueOfDifference += Math.Abs(element1.Values.ElementAt(i) - element2.Values.ElementAt(i));
            }

            return sumOfAbsoluteValueOfDifference;
        }

        static private double computeCosineSimularity(Entry element1, Entry element2)
        {
            double dotProduct = element1.Values.Zip(element2.Values, (d1, d2) => d1 * d2).Sum();
            double magnitudeOf1 = Math.Sqrt(element1.Values.Sum(x => x * x));
            double magnitudeOf2 = Math.Sqrt(element2.Values.Sum(x => x * x));
            double magnitudeProduct = magnitudeOf1 * magnitudeOf2;

            return dotProduct / magnitudeOf2;
        }

        private class Entry
        {
            public List<double> Values;
            public string Type;
            public int ID;

            public Entry(string[] columns, int id)
            {
                Values = new List<double>();
                int lastIndex = columns.Length - 1;
                for (int i=0; i<lastIndex; i++)
                {
                    Values.Add(Convert.ToDouble(columns[i]));
                }

                Type = columns[lastIndex];
                ID = id;
            }

            public override string ToString()
            {
                string valuesString = "";
                foreach(double value in Values)
                {
                    valuesString += $"{value}, ";
                }
                return $"{valuesString} [{Type}-{ID}]";
            }
        }

        private enum DistanceTypes
        {
            Euclidean, Manhattan, CosineSimilarity
        }
    }
}
