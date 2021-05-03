using System;
using System.Collections.Generic;
using System.Text;

namespace ODMIS_Homework2
{
    class LabelParser
    {
        private List<string> mRawInstructions;

        public LabelParser(List<string> rawInstructions)
        {
            mRawInstructions = rawInstructions;
        }

        public void Parse(out List<string> instructions, out Dictionary<string, int> labels)
        {
            instructions = new List<string>();
            labels = new Dictionary<string, int>();

            //find all labels and store their location in the instruction set
            for(int i=0; i<mRawInstructions.Count; i++)
            {
                var parts = mRawInstructions[i].Split(':');

                //if there is a label, log it and store non-label part as instruction
                if(parts.Length == 2)
                {
                    if (labels.ContainsKey(parts[0]))
                    {
                        throw new ArgumentException($"The label {parts[0]} is repeated!");
                    }
                    labels.Add(parts[0], i);
                    instructions.Add(parts[1].Trim());
                }
                else if(parts.Length == 1)
                {
                    instructions.Add(parts[0].Trim());
                }
                else
                {
                    throw new Exception("Too many labels exist at this row!");
                }
            }
        }
    }
}
