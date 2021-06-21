using System;
using System.Collections.Generic;
using System.Text;

namespace FinalProjectMIPSHazardDetector
{
    public class Instruction
    {
        public OpCode OpCode { get; set; }
        public string InstructionString { get; set; }
        public List<RequiredRegister> RegistersRequired { get; set; }
        public PipelineStage CurrentStage { get; set; }
        public bool IsStalled { get; set; }
        public List<int> ConflictRegisters { get; set; }
        public List<PipelineStage> ConflictStages { get; set; }
        public int ClockCycleOffset { get; set; }
        public string PipelineStagesUsed = "";
        public Instruction(string instructionString, OpCode opCode, List<Tuple<int, RegisterType>> registersRequired, bool isForwarding)
        {
            InstructionString = instructionString;
            OpCode = opCode;
            RegistersRequired = makeRequiredRegisterMapping(registersRequired, isForwarding);
            CurrentStage = PipelineStage.None;
            IsStalled = false;
            ConflictRegisters = new List<int>();
            ConflictStages = new List<PipelineStage>();
        }

        public void RecordStage()
        {
            if (IsStalled)
            {
                PipelineStagesUsed += $" S";
            }
            else
            {
                PipelineStagesUsed += $" {CurrentStage.ToString()}";
            }
        }

        private List<RequiredRegister> makeRequiredRegisterMapping(List<Tuple<int, RegisterType>> registers, bool isForwarding)
        {
            var requiredRegisters = new List<RequiredRegister>();

            foreach(var register in registers)
            {
                if (isForwarding)
                {
                    switch (OpCode)
                    {
                        case OpCode.ADD:
                        case OpCode.SUB:
                            if (register.Item2 == RegisterType.Read)
                            {
                                var entry = new RequiredRegister(register.Item1, PipelineStage.D, PipelineStage.M);
                                requiredRegisters.Add(entry);
                            }
                            else
                            {
                                var entry = new RequiredRegister(register.Item1, PipelineStage.D, PipelineStage.M);
                                requiredRegisters.Add(entry);
                            }
                            break;
                        case OpCode.LDW:
                        case OpCode.SVW:
                            if (register.Item2 == RegisterType.Read)
                            {
                                var entry = new RequiredRegister(register.Item1, PipelineStage.D, PipelineStage.M);
                                requiredRegisters.Add(entry);
                            }
                            else
                            {
                                var entry = new RequiredRegister(register.Item1, PipelineStage.D, PipelineStage.W);
                                requiredRegisters.Add(entry);
                            }
                            break;
                    }
                }
                else
                {
                    if (register.Item2 == RegisterType.Read)
                    {
                        var entry = new RequiredRegister(register.Item1, PipelineStage.D, PipelineStage.M);
                        requiredRegisters.Add(entry);
                    }
                    else
                    {
                        var entry = new RequiredRegister(register.Item1, PipelineStage.D, PipelineStage.Complete);
                        requiredRegisters.Add(entry);
                    }
                }
            }

            return requiredRegisters;
        }
    }
}
