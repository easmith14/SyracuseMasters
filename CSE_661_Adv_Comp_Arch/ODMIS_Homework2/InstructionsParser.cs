using System;
using System.Collections.Generic;
using System.Text;

namespace ODMIS_Homework2
{
    class InstructionsParser
    {
        private Dictionary<string, int> mLabels;
        private List<string> mRawInstructions;
        public InstructionsParser(Dictionary<string, int> labels, List<string> rawInstructions)
        {
            mLabels = labels;
            mRawInstructions = rawInstructions;
        }

        public List<Instruction> ParseAll()
        {
            var parsedInstructions = new List<Instruction>();

            foreach (var instruction in mRawInstructions)
            {
                parsedInstructions.Add(parseInstruction(instruction));
            }

            return parsedInstructions;
        }

        private Instruction parseInstruction(string rawInstruction)
        {
            throw new NotImplementedException();
        }
    }
}
