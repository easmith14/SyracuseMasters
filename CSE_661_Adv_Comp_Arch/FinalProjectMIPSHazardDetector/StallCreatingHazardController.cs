using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace FinalProjectMIPSHazardDetector
{
    public class StallCreatingHazardController : IHazardController
    {
        private Queue<Instruction> mInputInstructions;
        private bool mIsForwarding;
        public StallCreatingHazardController(Queue<Instruction> inputInstructions, bool isForwarding)
        {
            if (inputInstructions.Count == 0)
            {
                throw new Exception("Code must be at least one instruction");
            }
            mInputInstructions = inputInstructions;
            mIsForwarding = isForwarding;
        }

        public string HandleHazards()
        {
            var activeInstructions = new Queue<Instruction>();
            var processedInstructions = new Queue<Instruction>();
            activeInstructions.Enqueue(mInputInstructions.Dequeue());

            string outputInstructions = "";
            int clockCycle = 1;

            //iterate over instructions and clock cycles
            while (activeInstructions.Count != processedInstructions.Count)
            {
                //initialize tracking variables
                var reservedRegisters = new List<int>();
                bool isAnInstructionAtDecode = false;

                //increment current instructions' pipeline stage
                foreach (var instruction in activeInstructions)
                {
                    if (instruction.CurrentStage != PipelineStage.Complete)
                    {
                        PipelineStage nextStage = instruction.CurrentStage + 1;
                        instruction.IsStalled = false;

                        List<int> newReservedRegisters = new List<int>();
                        //check to see if there are any required registers that are reserved
                        foreach (var register in instruction.RegistersRequired)
                        {
                            //should this register be reserved?
                            if (register.NeededStage <= nextStage && register.FreedStage > nextStage)
                            {
                                //look for conflicts within the registers
                                if (reservedRegisters.Contains(register.RegisterNumber))
                                {
                                    instruction.ConflictRegisters.Add(register.RegisterNumber);
                                    instruction.ConflictStages.Add(instruction.CurrentStage);
                                    instruction.IsStalled = true;
                                }
                                else
                                {
                                    newReservedRegisters.Add(register.RegisterNumber);
                                }
                            }
                        }

                        reservedRegisters.AddRange(newReservedRegisters);

                        if (!instruction.IsStalled)
                        {
                            instruction.CurrentStage = nextStage;
                        }

                        if (instruction.CurrentStage == PipelineStage.D)
                        {
                            isAnInstructionAtDecode = true;
                        }

                        if (instruction.CurrentStage == PipelineStage.Complete)
                        {
                            processedInstructions.Enqueue(instruction);
                        }
                        else
                        {
                            instruction.RecordStage();
                        }
                    }
                }

                //attempt to add a new instruction
                if (isAnInstructionAtDecode)
                {
                    //add an instruction if possible, else end the analysis
                    if (mInputInstructions.Count > 0)
                    {
                        var nextInstruction = mInputInstructions.Dequeue();
                        nextInstruction.ClockCycleOffset = clockCycle;
                        activeInstructions.Enqueue(nextInstruction);
                    }
                }

                clockCycle++;
            }

            //format the output appropriately
            string title = mIsForwarding ? "With Forwarding Unit" : "Without Forwarding Unit";
            outputInstructions += $"\n{new string('*', 50)}\n{title}:\n{new string('*', 50)}\n";

            foreach (var instruction in processedInstructions)
            {
                outputInstructions += $"{instruction.InstructionString, 15} | ";

                for (int i = 0; i < instruction.ClockCycleOffset; i++)
                {
                    outputInstructions += " ";
                }
                outputInstructions += instruction.PipelineStagesUsed;

                outputInstructions += "\n";
            }

            return outputInstructions;
        }

    }
}
