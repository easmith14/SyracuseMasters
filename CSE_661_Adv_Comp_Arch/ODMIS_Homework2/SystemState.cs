using System.Collections.Generic;

namespace ODMIS_Homework2
{
    class SystemState
    {
        public HashSet<int> Registers { get; set; }
        public HashSet<int> Memory { get; set; }
        public int ProgramCounter { get; set; }

        public SystemState(int registerCount, int memoryEntryCount)
        {
            ProgramCounter = 0;
            Registers = new HashSet<int>();
            Memory = new HashSet<int>();

            for(int i=0; i<registerCount; i++)
            {
                Registers.Add(0);
            }

            for (int i = 0; i < memoryEntryCount; i++)
            {
                Memory.Add(0);
            }
        }
    }
}