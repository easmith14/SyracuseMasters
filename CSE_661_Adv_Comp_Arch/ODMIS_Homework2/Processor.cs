using System;
using System.Collections.Generic;
using System.Text;

namespace ODMIS_Homework2
{
    class Processor
    {
        public SystemState State { get; }
        public Processor(SystemState state)
        {
            State = state;
        }
        public void ProcessInstruction(Instruction instruction)
        {
            //update registers
            //update memory
            //update PC pointer indicator
            //print the full UI to the console and wait for user input

            throw new NotImplementedException();
        }
    }
}
