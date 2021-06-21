using System;
using System.Collections.Generic;
using System.Text;

namespace FinalProjectMIPSHazardDetector
{
    public class NoForwardingHazardController : IHazardController
    {
        private Queue<Instruction> mInputInstructions;
        public NoForwardingHazardController(Queue<Instruction> inputInstructions)
        {
            mInputInstructions = inputInstructions;
        }

        public string HandleHazards()
        {
            var activeInstructions = new Queue<Instruction>();
            bool allInstructionsProcessed = false;
            string outputInstructions = "";

            //iterate over instructions and clock cycles
            while (!allInstructionsProcessed)
            {
                //initialize tracking variables
                var reservedRegisters = new List<int>();
                var conflictRegisters = new List<int>();
                bool isAnInstructionAtDecode = false;

                //increment current instructions' pipeline stage
                foreach (var instruction in activeInstructions)
                {
                    PipelineStage nextStage = instruction.CurrentStage + 1;

                    //check to see if there are any required registers that are reserved
                    foreach (var register in instruction.RegistersRequired)
                    {
                        //look for conflicts within the registers
                        if (reservedRegisters.Contains(register.Key))
                        {
                            conflictRegisters.Add(register.Key);
                            instruction.IsStalled = true;
                        }
                        else
                        {
                            reservedRegisters.Add(register.Key);
                            instruction.CurrentStage = nextStage;
                            instruction.IsStalled = false;
                        }
                    }

                    if (!instruction.IsStalled)
                    {
                        if (instruction.CurrentStage == PipelineStage.D)
                        {
                            isAnInstructionAtDecode = true;
                        }
                        if (instruction.CurrentStage == PipelineStage.Complete)
                        {
                            activeInstructions.Dequeue();
                        }
                    }
                }

                //attempt to add a new instruction
                if (isAnInstructionAtDecode || activeInstructions.Count == 0)
                {
                    //add an instruction if possible, else end the analysis
                    if (mInputInstructions.Count > 0)
                    {
                        activeInstructions.Enqueue(mInputInstructions.Dequeue());
                    }
                    else
                    {
                        allInstructionsProcessed = true;
                    }
                }

                //we have incremented the clock cycle and noted all the conflicts
                //now we generate the output
            }

            return outputInstructions;
        }

    }
}
