using System;
using System.Collections.Generic;
using System.Text;

namespace ODMIS_Homework2
{
    class Instruction
    {
        public string RawInstruction { get; set; }
        public OpCode OpCode { get; set; }
        public List<int> Args { get; set; }

        public Instruction(string rawInstruction, OpCode opCode)
        {
            RawInstruction = rawInstruction;
            OpCode = opCode;
            Args = new List<int>() { 0, 0, 0, 0, 0 };
        }
    }
}
