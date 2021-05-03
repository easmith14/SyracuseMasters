using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ODMIS_Homework2
{
    class InstructionsParser
    {
        Dictionary<OpCode, List<int>> mOpCodeExpansionLookup = new Dictionary<OpCode, List<int>>()
        {
            {OpCode.LOADA_M,    new List<int>(){1} },
            {OpCode.LOADA_R,    new List<int>(){1} },
            {OpCode.LOADI_I,    new List<int>(){1,2} },
            {OpCode.LOADI_D,    new List<int>(){1,2} },
            {OpCode.STORE_M,    new List<int>(){1,1} },
            {OpCode.STORE_R,    new List<int>(){1,1} },
            {OpCode.ADDA_I,     new List<int>(){1,1,1} },
            {OpCode.ADDA_D,     new List<int>(){1,1,1} },
            {OpCode.SUBA_I,     new List<int>(){1,1,1} },
            {OpCode.SUBA_D,     new List<int>(){1,1,1} },
            {OpCode.DIVA_I,     new List<int>(){1,1,1} },
            {OpCode.DIVA_D,     new List<int>(){1,1,1} },
            {OpCode.MULA_I,     new List<int>(){1,1,1} },
            {OpCode.MULA_D,     new List<int>(){1,1,1} },
            {OpCode.ADDI_I,     new List<int>(){1,1,2} },
            {OpCode.ADDI_D,     new List<int>(){1,1,2} },
            {OpCode.SUBI_I,     new List<int>(){1,1,2} },
            {OpCode.SUBI_D,     new List<int>(){1,1,2} },
            {OpCode.DIVI_I,     new List<int>(){1,1,2} },
            {OpCode.DIVI_D,     new List<int>(){1,1,2} },
            {OpCode.MULI_I,     new List<int>(){1,1,2} },
            {OpCode.MULI_D,     new List<int>(){1,1,2} },
            {OpCode.ROOT_I,     new List<int>(){1,1,1} },
            {OpCode.ROOT_D,     new List<int>(){1,1,1} },
            {OpCode.CEIL,       new List<int>(){1,1,1} },
            {OpCode.FLOOR,      new List<int>(){1,1,1} },
            {OpCode.ROUND,      new List<int>(){1,1,1} },
            {OpCode.RAND_I,     new List<int>(){1} },
            {OpCode.RAND_D,     new List<int>(){1} },
            {OpCode.PI,         new List<int>(){1} },
            {OpCode.CLEAR_R,    new List<int>(){1} },
            {OpCode.CLEAR_M,    new List<int>(){1} },
            {OpCode.JUMP,       new List<int>(){1} },
            {OpCode.JUMP_LTE,   new List<int>(){1,1,1} },
            {OpCode.JUMP_LT,    new List<int>(){1,1,1} },
            {OpCode.JUMP_GTE,   new List<int>(){1,1,1} },
            {OpCode.JUMP_GT,    new List<int>(){1,1,1} },
            {OpCode.JUMP_EQ,    new List<int>(){1,1,1} },
            {OpCode.ORA_R,        new List<int>(){1,1,1} },
            {OpCode.ORI_I,        new List<int>(){1,1,2} },
            {OpCode.ANDA_R,       new List<int>(){1,1,1} },
            {OpCode.ANDI_I,       new List<int>(){1,1,2} },
            {OpCode.NOTA_R,       new List<int>(){1,1,1} },
            {OpCode.NOT_I,       new List<int>(){1,1,2} },
            {OpCode.TERN_LTE,   new List<int>(){1,1,1,1,1} },
            {OpCode.TERN_LT,    new List<int>(){1,1,1,1,1} },
            {OpCode.TERN_GTE,   new List<int>(){1,1,1,1,1} },
            {OpCode.TERN_GT,    new List<int>(){1,1,1,1,1} },
            {OpCode.TERN_EQ,    new List<int>(){1,1,1,1,1} },
            {OpCode.TIME,       new List<int>(){1} },
            {OpCode.END,  new List<int>(){} }
        };
        Dictionary<int, HashSet<OpCode>> mOpCodeValidationLookup = new Dictionary<int, HashSet<OpCode>>()
        {
            {1,  new HashSet<OpCode>()
                {
                    OpCode.LOADA_M, OpCode.LOADA_R, OpCode.RAND_I,  OpCode.RAND_D,
                    OpCode.PI,      OpCode.CLEAR_R, OpCode.CLEAR_M, OpCode.JUMP,
                    OpCode.TIME
                } 
            },
            {2, new HashSet<OpCode>()
                {
                    OpCode.LOADI_I, OpCode.LOADI_D, OpCode.STORE_M, OpCode.STORE_R
                }
            },
            {3, new HashSet<OpCode>()
                {
                OpCode.ADDA_I,  OpCode.ADDA_D,  OpCode.SUBA_I,  OpCode.SUBA_D,
                OpCode.DIVA_I,  OpCode.DIVA_D,  OpCode.MULA_I,  OpCode.MULA_D,
                OpCode.ROOT_I,  OpCode.ROOT_D,  OpCode.CEIL,    OpCode.FLOOR,
                OpCode.ROUND,   OpCode.JUMP_LTE,OpCode.JUMP_LT, OpCode.JUMP_GTE,
                OpCode.JUMP_GT, OpCode.JUMP_EQ, OpCode.ORA_R,     OpCode.ANDA_R,
                OpCode.NOTA_R
                }
            },
            {4, new HashSet<OpCode>()
                {
                OpCode.ADDI_I,  OpCode.ADDI_D,  OpCode.SUBI_I,  OpCode.SUBI_D,
                OpCode.DIVI_I,  OpCode.DIVI_D,  OpCode.MULI_I,  OpCode.MULI_D,
                OpCode.ORI_I,     OpCode.ANDI_I,    OpCode.NOT_I
                }
            },
            {5, new HashSet<OpCode>()
                {
                OpCode.TERN_LTE,OpCode.TERN_LT, OpCode.TERN_GTE,OpCode.TERN_GT,
                OpCode.TERN_EQ
                }
            }
        };
        private const int MAX_ARGUMENT_VALUE = 15;

        private Dictionary<string, int> mLabels;
        private List<string> mRawInstructions;

        public InstructionsParser(Dictionary<string, int> labels, List<string> rawInstructions)
        {
            mLabels = labels;
            mRawInstructions = rawInstructions;
        }

        public List<Instruction> ParseAll()
        {
            var parsedInstructions = new List<Instruction>();

            foreach (var instruction in mRawInstructions)
            {
                parsedInstructions.Add(parseInstruction(instruction));
            }

            return parsedInstructions;
        }

        private Instruction parseInstruction(string rawInstruction)
        {
            //parse first part to an opcode enum
            //if doesn't match one, throw compiler exception

            var components = rawInstruction.Trim().Split(" ", StringSplitOptions.RemoveEmptyEntries);
            OpCode opcode;
            if(!Enum.TryParse(components[0], true, out opcode) || !Enum.IsDefined(typeof(OpCode), opcode))
            {
                throw new Exception($"Provided OpCode {components[0]} is not a recognized code.");
            }

            var parsedInstruction = new Instruction(rawInstruction, opcode);

            //expand values into the proper number of arg slots
            var expansionKey = mOpCodeExpansionLookup[opcode];

            //validate that the instruction has the proper number of arguments
            if(expansionKey.Count != components.Length - 1)
            {
                throw new ArgumentException($"An incorrect number of arguments, {components.Length} " +
                    $"supplied for opcode {opcode} (expects {expansionKey.Count})");
            }

            int argNum = 0;
            for(int i=1; i<components.Length; i++)
            {
                int expandedComponentSize = expansionKey[i - 1];
                if(expandedComponentSize == 1)
                {
                    parsedInstruction.Args[argNum++] = Convert.ToInt32(components[i]);
                }
                else if(expandedComponentSize == 2)
                {
                    //if int, expand to binary and split into two arguments
                    if(opcode.ToString().EndsWith('I'))
                    {
                        int rawValue = Convert.ToInt32(components[i]);

                        string binRepresentation = Convert.ToString(rawValue, 2);

                        //if int is an overflow, throw compiler error
                        if(binRepresentation.Length > 8)
                        {
                            throw new OverflowException($"Value {rawValue} supplied overflows the possible representable int");
                        }
                        else
                        {
                            //expand to add leading zeros
                            while(binRepresentation.Length < 8)
                            {
                                binRepresentation = "0" + binRepresentation;
                            }

                            parsedInstruction.Args[argNum++] = Convert.ToInt32(binRepresentation.Substring(0, 4), 2);
                            parsedInstruction.Args[argNum++] = Convert.ToInt32(binRepresentation.Substring(4, 4), 2);
                        }
                        
                    }
                    //if decimal, put whole number in one argument and fractional part in the other argument
                    else if (opcode.ToString().EndsWith('D'))
                    {
                        decimal rawValue = Convert.ToDecimal(components[i]);
                        int wholePart = (int)rawValue;

                        if (wholePart > 7)
                        {
                            throw new OverflowException($"Value {rawValue} supplied overflows the possible representable int component");
                        }

                        decimal potentialFractionalPart = rawValue - wholePart;
                        int fractionalPart = 0;

                        //if fraction starts with 1, we can take 2 digits
                        if((int) (fractionalPart * 10) == 1)
                        {
                            fractionalPart = (int)(fractionalPart * 100);

                            //we round to our nearest approximation of the decimal value
                            if (fractionalPart > 15)
                            {
                                fractionalPart = 15;
                            }
                        }
                        //else take just first digit
                        else
                        {
                            fractionalPart = (int)(potentialFractionalPart * 10);
                        }

                        parsedInstruction.Args[argNum++] = wholePart;
                        parsedInstruction.Args[argNum++] = fractionalPart;
                    }
                }
            }

            //double check that argument counts line up
            if(argNum != expansionKey.Sum())
            {
                throw new ArgumentException($"An incorrect number of expanded arguments, {argNum - 1} " +
                    $"supplied for opcode {opcode} (expects {expansionKey.Sum()})");
            }

            return parsedInstruction;
        }
    }
}
