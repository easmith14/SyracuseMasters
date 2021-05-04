using System;
using System.Collections.Generic;

namespace ODMIS_Homework2
{
    class SystemState
    {
        public Dictionary<int, Tuple<int, int>> Registers { get; set; }
        public Dictionary<int, Tuple<int, int>> Memory { get; set; }
        public int ProgramCounter { get; set; }

        public SystemState(int registerCount, int memoryEntryCount)
        {
            ProgramCounter = 0;
            Registers = new Dictionary<int, Tuple<int, int>>();
            Memory = new Dictionary<int, Tuple<int, int>>();

            for(int i=0; i<registerCount; i++)
            {
                Registers.Add(i, Tuple.Create(0, 0));
            }

            for (int i = 0; i < memoryEntryCount; i++)
            {
                Memory.Add(i, Tuple.Create(0, 0));
            }
        }
    }
}