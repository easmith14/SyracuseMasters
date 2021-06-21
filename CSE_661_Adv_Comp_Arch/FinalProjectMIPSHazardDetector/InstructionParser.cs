using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace FinalProjectMIPSHazardDetector
{
    class InstructionParser
    {
        private string mProgramPath;

        public InstructionParser(string programPath)
        {
            mProgramPath = programPath;
        }

        public Queue<Instruction> Parse()
        {
            var rawInstructions = new List<string>(File.ReadAllLines(mProgramPath));
            var parsedInstructions = new Queue<Instruction>();

            //TODO: actually parse
            //parse into instruction object
            //reserved register set
            //opcode

            parsedInstructions.Enqueue(new Instruction("ADD R1, R2, 2", OpCode.ADD, new Dictionary<int, RegisterType>() 
            { 
                { 1, RegisterType.Written },
                { 2, RegisterType.Read }
            }, false));
            parsedInstructions.Enqueue(new Instruction("SUB R3, R4, 4", OpCode.SUB, new Dictionary<int, RegisterType>()
            {
                { 3, RegisterType.Written },
                { 4, RegisterType.Read }
            }, false));
            parsedInstructions.Enqueue(new Instruction("TES R3, R4, 4", OpCode.SUB, new Dictionary<int, RegisterType>()
            {
                { 1, RegisterType.Written },
                { 4, RegisterType.Read }
            }, false));

            return parsedInstructions;
        }
    }
}
