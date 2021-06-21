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

            //TODO: actually parse

            try
            {
                foreach(var rawInstruction in rawInstructions)
                {
                    var components = rawInstruction.Trim().Split(" ", StringSplitOptions.RemoveEmptyEntries);
                    OpCode opcode;
                    if (!Enum.TryParse(components[0], true, out opcode) || !Enum.IsDefined(typeof(OpCode), opcode))
                    {
                        throw new Exception($"Provided OpCode {components[0]} is not a recognized code.");
                    }

                    if(opcode == OpCode.ADD || opcode == OpCode.SUB)
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
                    if (opcode == OpCode.SVW || opcode == OpCode.LDW)
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
            }
            catch (Exception e)
            {
                throw;
            }

            //parse into instruction object
            //reserved register set
            //opcode

            //parsedInstructions.Enqueue(new Instruction("ADD R1, R2, 2", OpCode.ADD, new Dictionary<int, RegisterType>() 
            //{ 
            //    { 1, RegisterType.Written },
            //    { 2, RegisterType.Read }
            //}, useForwarding));
            //parsedInstructions.Enqueue(new Instruction("SUB R1, R2, 4", OpCode.SUB, new Dictionary<int, RegisterType>()
            //{
            //    { 1, RegisterType.Written },
            //    { 2, RegisterType.Read }
            //}, useForwarding));

            return parsedInstructions;
        }
    }
}
