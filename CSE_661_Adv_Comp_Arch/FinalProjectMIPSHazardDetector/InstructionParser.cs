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

        public Queue<Instruction> Parse(bool useForwarding)
        {
            var rawInstructions = new List<string>(File.ReadAllLines(mProgramPath));
            var parsedInstructions = new Queue<Instruction>();

            foreach(var rawInstruction in rawInstructions)
            {
                var components = rawInstruction.Trim().Split(" ", StringSplitOptions.RemoveEmptyEntries);
                OpCode opcode;
                if (!Enum.TryParse(components[0].ToUpper(), true, out opcode) || !Enum.IsDefined(typeof(OpCode), opcode))
                {
                    throw new Exception($"Provided OpCode {components[0]} is not a recognized code.");
                }

                try
                {
                    if (opcode == OpCode.ADD || opcode == OpCode.SUB)
                    {
                        var registers = new List<Tuple<int, RegisterType>>();

                        registers.Add(Tuple.Create(Convert.ToInt32(components[1].Trim('R')), RegisterType.Written));

                        for (int i = 2; i < components.Length; i++)
                        {
                            if (components[i].Contains('R'))
                            {
                                registers.Add(Tuple.Create(Convert.ToInt32(components[i].Trim('R')), RegisterType.Read));
                            }
                        }

                        parsedInstructions.Enqueue(new Instruction(rawInstruction, opcode, registers, useForwarding));
                    }
                    if (opcode == OpCode.SW || opcode == OpCode.LW)
                    {
                        var registers = new List<Tuple<int, RegisterType>>();

                        registers.Add(Tuple.Create(Convert.ToInt32(components[1].Trim('R')), RegisterType.Written));

                        string potentialReg = components[2].Split('(')[1].Trim(')');
                        if (potentialReg.Contains('R'))
                        {
                            registers.Add(Tuple.Create(Convert.ToInt32(potentialReg.Trim('R')), RegisterType.Read));
                        }

                        parsedInstructions.Enqueue(new Instruction(rawInstruction, opcode, registers, useForwarding));
                    }
                }
                catch
                {
                    throw new Exception($"The instruction {rawInstruction} could not be properly parsed.");
                }
            }

            return parsedInstructions;
        }
    }
}
