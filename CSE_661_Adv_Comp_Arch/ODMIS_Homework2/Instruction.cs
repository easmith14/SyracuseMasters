using System;
using System.Collections.Generic;
using System.Text;

namespace ODMIS_Homework2
{
    class Instruction
    {
        public string RawInstruction { get; set; }
        public string OpCode { get; set; }
        public int Arg1 { get; set; }
        public int Arg2 { get; set; }
        public int Arg3 { get; set; }
        public int Arg4 { get; set; }
        public int Arg5 { get; set; }

        public Instruction(string rawInstruction, string opCode)
        {
            RawInstruction = rawInstruction;
            OpCode = opCode;
        }
    }
}
