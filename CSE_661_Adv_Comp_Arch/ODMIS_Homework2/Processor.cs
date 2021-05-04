using System;
using System.Collections.Generic;
using System.Text;

namespace ODMIS_Homework2
{
    class Processor
    {
        private SystemState mState;
        private List<Instruction> mInstructions;
        public Processor(SystemState state, List<Instruction> instructions)
        {
            mState = state;
            mInstructions = instructions;
        }
        public bool ProcessNextInstruction()
        {
            //fetch instruction, checking for end of program (via invalid program counter)
            if(mState.ProgramCounter > mInstructions.Count || mState.ProgramCounter < 0)
            {
                return false;
            }

            Instruction instruction = mInstructions[mState.ProgramCounter];

            //update PC pointer indicator naively
            mState.ProgramCounter++;

            //store args more conveniently
            int arg1 = instruction.Args[0];
            int arg2 = instruction.Args[1];
            int arg3 = instruction.Args[2];
            int arg4 = instruction.Args[3];
            int arg5 = instruction.Args[4];

            //temporart register variables to streamline code
            var reg1 = Tuple.Create<int,int>(-1, -1);
            var reg2 = Tuple.Create<int, int>(-1, -1);
            var reg3 = Tuple.Create<int, int>(-1, -1);
            var reg4 = Tuple.Create<int, int>(-1, -1);

            //update registers and memory depending on the operation selected
            switch (instruction.OpCode)
            {
                case OpCode.LOADA_M:
                    mState.Registers[arg1] = mState.Memory[arg2];
                    break;
                case OpCode.LOADA_R:
                    mState.Registers[arg1] = mState.Registers[arg2];
                    break;
                case OpCode.LOADI_I:
                    mState.Registers[arg1] = regFromArgs(arg2, arg3, false);
                    break;
                case OpCode.LOADI_D:
                    mState.Registers[arg1] = regFromArgs(arg2, arg3, true);
                    break;
                case OpCode.STORE_M:
                    mState.Memory[arg1] = mState.Memory[arg2];
                    break;
                case OpCode.STORE_R:
                    mState.Memory[arg1] = mState.Registers[arg2];
                    break;
                case OpCode.ADDA_I:
                    reg1 = mState.Registers[arg2];
                    reg2 = mState.Registers[arg3];
                    if(reg1.Item1 == 1 || reg2.Item1 == 1)
                    {
                        throw new Exception("Attempted to add a decimal value using an integer instruction");
                    }
                    mState.Registers[arg1] = regFromVal(reg1.Item2 + reg2.Item2);
                    break;
                case OpCode.ADDA_D:
                    reg1 = mState.Registers[arg2];
                    reg2 = mState.Registers[arg3];
                    if (reg1.Item1 == 0 || reg2.Item1 == 0)
                    {
                        throw new Exception("Attempted to add an integer value using a decimal instruction");
                    }
                    mState.Registers[arg1] = regFromVal(decFromRegVal(reg1.Item2) + decFromRegVal(reg2.Item2));
                    break;
                case OpCode.SUBA_I:
                    reg1 = mState.Registers[arg2];
                    reg2 = mState.Registers[arg3];
                    if (reg1.Item1 == 1 || reg2.Item1 == 1)
                    {
                        throw new Exception("Attempted to subtract a decimal value using an integer instruction");
                    }
                    mState.Registers[arg1] = regFromVal(reg1.Item2 - reg2.Item2);
                    break;
                case OpCode.SUBA_D:
                    reg1 = mState.Registers[arg2];
                    reg2 = mState.Registers[arg3];
                    if (reg1.Item1 == 0 || reg2.Item1 == 0)
                    {
                        throw new Exception("Attempted to subtract an integer value using a decimal instruction");
                    }
                    mState.Registers[arg1] = regFromVal(decFromRegVal(reg1.Item2) - decFromRegVal(reg2.Item2));
                    break;
                case OpCode.DIVA_I:
                    reg1 = mState.Registers[arg2];
                    reg2 = mState.Registers[arg3];
                    if (reg1.Item1 == 1 || reg2.Item1 == 1)
                    {
                        throw new Exception("Attempted to divide a decimal value using an integer instruction");
                    }
                    mState.Registers[arg1] = regFromVal(reg1.Item2 / reg2.Item2);
                    break;
                case OpCode.DIVA_D:
                    reg1 = mState.Registers[arg2];
                    reg2 = mState.Registers[arg3];
                    if (reg1.Item1 == 0 || reg2.Item1 == 0)
                    {
                        throw new Exception("Attempted to divide an integer value using a decimal instruction");
                    }
                    mState.Registers[arg1] = regFromVal(decFromRegVal(reg1.Item2) / decFromRegVal(reg2.Item2));
                    break;
                case OpCode.MULA_I:
                    reg1 = mState.Registers[arg2];
                    reg2 = mState.Registers[arg3];
                    if (reg1.Item1 == 1 || reg2.Item1 == 1)
                    {
                        throw new Exception("Attempted to multiply a decimal value using an integer instruction");
                    }
                    mState.Registers[arg1] = regFromVal(reg1.Item2 * reg2.Item2);
                    break;
                case OpCode.MULA_D:
                    reg1 = mState.Registers[arg2];
                    reg2 = mState.Registers[arg3];
                    if (reg1.Item1 == 0 || reg2.Item1 == 0)
                    {
                        throw new Exception("Attempted to multiply an integer value using a decimal instruction");
                    }
                    mState.Registers[arg1] = regFromVal(decFromRegVal(reg1.Item2) * decFromRegVal(reg2.Item2));
                    break;
                case OpCode.ADDI_I:
                    reg1 = mState.Registers[arg2];
                    if (reg1.Item1 == 1)
                    {
                        throw new Exception("Attempted to add a decimal value using an integer instruction");
                    }
                    mState.Registers[arg1] = regFromVal(reg1.Item2 + intFromArgs(arg3,arg4));
                    break;
                case OpCode.ADDI_D:
                    reg1 = mState.Registers[arg2];
                    if (reg1.Item1 == 0)
                    {
                        throw new Exception("Attempted to add an integer value using a decimal instruction");
                    }
                    mState.Registers[arg1] = regFromVal(decFromRegVal(reg1.Item2) + decFromArgs(arg3, arg4));
                    break;
                case OpCode.SUBI_I:
                    reg1 = mState.Registers[arg2];
                    if (reg1.Item1 == 1)
                    {
                        throw new Exception("Attempted to subtract a decimal value using an integer instruction");
                    }
                    mState.Registers[arg1] = regFromVal(reg1.Item2 - intFromArgs(arg3, arg4));
                    break;
                case OpCode.SUBI_D:
                    reg1 = mState.Registers[arg2];
                    if (reg1.Item1 == 0)
                    {
                        throw new Exception("Attempted to subtract an integer value using a decimal instruction");
                    }
                    mState.Registers[arg1] = regFromVal(decFromRegVal(reg1.Item2) - decFromArgs(arg3, arg4));
                    break;
                case OpCode.DIVI_I:
                    reg1 = mState.Registers[arg2];
                    if (reg1.Item1 == 1)
                    {
                        throw new Exception("Attempted to divide a decimal value using an integer instruction");
                    }
                    mState.Registers[arg1] = regFromVal(reg1.Item2 / intFromArgs(arg3, arg4));
                    break;
                case OpCode.DIVI_D:
                    reg1 = mState.Registers[arg2];
                    if (reg1.Item1 == 0)
                    {
                        throw new Exception("Attempted to divide an integer value using a decimal instruction");
                    }
                    mState.Registers[arg1] = regFromVal(decFromRegVal(reg1.Item2) / decFromArgs(arg3, arg4));
                    break;
                case OpCode.MULI_I:
                    reg1 = mState.Registers[arg2];
                    if (reg1.Item1 == 1)
                    {
                        throw new Exception("Attempted to multiply a decimal value using an integer instruction");
                    }
                    mState.Registers[arg1] = regFromVal(reg1.Item2 * intFromArgs(arg3, arg4));
                    break;
                case OpCode.MULI_D:
                    reg1 = mState.Registers[arg2];
                    if (reg1.Item1 == 0)
                    {
                        throw new Exception("Attempted to multiply an integer value using a decimal instruction");
                    }
                    mState.Registers[arg1] = regFromVal(decFromRegVal(reg1.Item2) * decFromArgs(arg3, arg4));
                    break;
                case OpCode.ROOT_I:
                    reg1 = mState.Registers[arg2];
                    if (reg1.Item1 == 1)
                    {
                        throw new Exception("Attempted to take the root of a decimal value using an integer instruction");
                    }
                    mState.Registers[arg1] = regFromVal((int)Math.Sqrt(reg1.Item2));
                    break;
                case OpCode.ROOT_D:
                    reg1 = mState.Registers[arg2];
                    if (reg1.Item1 == 0)
                    {
                        throw new Exception("Attempted to take the root of an integer value using a decimal instruction");
                    }
                    mState.Registers[arg1] = regFromVal((decimal)Math.Sqrt((double)decFromRegVal(reg1.Item2)));
                    break;
                case OpCode.CEIL:
                    reg1 = mState.Registers[arg2];
                    if (reg1.Item1 == 0)
                    {
                        throw new Exception("Attempted to take the ceiling of an integer value using a decimal instruction");
                    }
                    mState.Registers[arg1] = regFromVal((int)Math.Ceiling((double)decFromRegVal(reg1.Item2)));
                    break;
                case OpCode.FLOOR:
                    reg1 = mState.Registers[arg2];
                    if (reg1.Item1 == 0)
                    {
                        throw new Exception("Attempted to take the floor of an integer value using a decimal instruction");
                    }
                    mState.Registers[arg1] = regFromVal((int)Math.Floor((double)decFromRegVal(reg1.Item2)));
                    break;
                case OpCode.ROUND:
                    reg1 = mState.Registers[arg2];
                    if (reg1.Item1 == 0)
                    {
                        throw new Exception("Attempted to round an integer value using a decimal instruction");
                    }
                    mState.Registers[arg1] = regFromVal((int)Math.Round((double)decFromRegVal(reg1.Item2)));
                    break;
                case OpCode.RAND_I:
                    mState.Registers[arg1] = regFromVal(new Random().Next(0, 512));
                    break;
                case OpCode.RAND_D:
                    var rand = new Random();

                    int wholePart = rand.Next(0, 15);
                    int decimalPart = rand.Next(0, 15);
                    string randStr = $"{wholePart}.{decimalPart}";

                    mState.Registers[arg1] = regFromVal(Convert.ToDecimal(randStr));
                    break;
                case OpCode.PI:
                    mState.Registers[arg1] = regFromVal((decimal)3.14);
                    break;
                case OpCode.CLEAR_R:
                    mState.Registers[arg1] = regFromVal(0);
                    break;
                case OpCode.CLEAR_M:
                    mState.Memory[arg1] = regFromVal(0);
                    break;
                case OpCode.JUMP:
                    mState.ProgramCounter = arg1;
                    break;
                case OpCode.JUMP_LTE:
                    reg1 = mState.Registers[arg2];
                    reg2 = mState.Registers[arg3];

                    if(valFromRegister(reg1) <= valFromRegister(reg2))
                    {
                        mState.ProgramCounter = arg1;
                    }
                    break;
                case OpCode.JUMP_LT:
                    reg1 = mState.Registers[arg2];
                    reg2 = mState.Registers[arg3];

                    if (valFromRegister(reg1) < valFromRegister(reg2))
                    {
                        mState.ProgramCounter = arg1;
                    }
                    break;
                case OpCode.JUMP_GTE:
                    reg1 = mState.Registers[arg2];
                    reg2 = mState.Registers[arg3];

                    if (valFromRegister(reg1) >= valFromRegister(reg2))
                    {
                        mState.ProgramCounter = arg1;
                    }
                    break;
                case OpCode.JUMP_GT:
                    reg1 = mState.Registers[arg2];
                    reg2 = mState.Registers[arg3];

                    if (valFromRegister(reg1) > valFromRegister(reg2))
                    {
                        mState.ProgramCounter = arg1;
                    }
                    break;
                case OpCode.JUMP_EQ:
                    reg1 = mState.Registers[arg2];
                    reg2 = mState.Registers[arg3];

                    if (valFromRegister(reg1) == valFromRegister(reg2))
                    {
                        mState.ProgramCounter = arg1;
                    }
                    break;
                case OpCode.ORA_R:
                    reg1 = mState.Registers[arg2];
                    reg2 = mState.Registers[arg3];

                    mState.Registers[arg1] = regFromVal(reg1.Item2 | reg2.Item2);
                    break;
                case OpCode.ORI_I:
                    reg1 = mState.Registers[arg2];

                    mState.Registers[arg1] = regFromVal(reg1.Item2 | intFromArgs(arg3, arg4));
                    break;
                case OpCode.ANDA_R:
                    reg1 = mState.Registers[arg2];
                    reg2 = mState.Registers[arg3];

                    mState.Registers[arg1] = regFromVal(reg1.Item2 & reg2.Item2);
                    break;
                case OpCode.ANDI_I:
                    reg1 = mState.Registers[arg2];

                    mState.Registers[arg1] = regFromVal(reg1.Item2 & intFromArgs(arg3, arg4));
                    break;
                case OpCode.NOTA_R:
                    reg1 = mState.Registers[arg2];

                    mState.Registers[arg1] = regFromVal(~reg1.Item2);
                    break;
                case OpCode.NOT_I:
                    mState.Registers[arg1] = regFromVal(~intFromArgs(arg2,arg3));
                    break;
                case OpCode.TERN_LTE:
                    reg1 = mState.Registers[arg2];
                    reg2 = mState.Registers[arg3];
                    reg3 = mState.Registers[arg4];
                    reg4 = mState.Registers[arg5];

                    mState.Registers[arg1] = regFromVal(valFromRegister(reg1) <= valFromRegister(reg2) ?
                                                        valFromRegister(reg3) : valFromRegister(reg4));

                    break;
                case OpCode.TERN_LT:
                    reg1 = mState.Registers[arg2];
                    reg2 = mState.Registers[arg3];
                    reg3 = mState.Registers[arg4];
                    reg4 = mState.Registers[arg5];

                    mState.Registers[arg1] = regFromVal(valFromRegister(reg1) < valFromRegister(reg2) ?
                                                        valFromRegister(reg3) : valFromRegister(reg4));
                    break;
                case OpCode.TERN_GTE:
                    reg1 = mState.Registers[arg2];
                    reg2 = mState.Registers[arg3];
                    reg3 = mState.Registers[arg4];
                    reg4 = mState.Registers[arg5];

                    mState.Registers[arg1] = regFromVal(valFromRegister(reg1) >= valFromRegister(reg2) ?
                                                        valFromRegister(reg3) : valFromRegister(reg4));
                    break;
                case OpCode.TERN_GT:
                    reg1 = mState.Registers[arg2];
                    reg2 = mState.Registers[arg3];
                    reg3 = mState.Registers[arg4];
                    reg4 = mState.Registers[arg5];

                    mState.Registers[arg1] = regFromVal(valFromRegister(reg1) > valFromRegister(reg2) ?
                                                        valFromRegister(reg3) : valFromRegister(reg4));
                    break;
                case OpCode.TERN_EQ:
                    reg1 = mState.Registers[arg2];
                    reg2 = mState.Registers[arg3];
                    reg3 = mState.Registers[arg4];
                    reg4 = mState.Registers[arg5];

                    mState.Registers[arg1] = regFromVal(valFromRegister(reg1) == valFromRegister(reg2) ?
                                                        valFromRegister(reg3) : valFromRegister(reg4));
                    break;
                case OpCode.TIME:
                    mState.Registers[arg1] = regFromVal(DateTime.Now.Ticks % 512);
                    break;
                case OpCode.END:
                    //finish program
                    return false;
                default: throw new Exception($"Unknown OpCode given: {instruction.OpCode}");
            }

            return true;
        }

        public void PrintSystemState(int firstInstructionToShow = 0)
        {
            const int lineSp = -4;
            const int indSp = 1;
            const int instrSp = -23;
            const int parsedSp = -31;
            const int columnSp = -20;
            const int regAddSp = 4;
            const int regValSp = -11;
            const int memHeaderSp = 35;

            //print the full UI to the console
            Console.Clear();

            //print the instructions and registers
            Console.WriteLine($"|{"Line",lineSp}|{"",indSp}|{"Instruction",instrSp}" +
                $"|{"Parsed Instruction",parsedSp}|{$"PC: {formatIntToBinWord(mState.ProgramCounter, 4)}",columnSp}{"Add",regAddSp}|{"Reg Val",regValSp}|");

            for (int i=0; i<mState.Registers.Count; i++)
            {
                string ind = mState.ProgramCounter-1 == i ? ">" : "";
                int instructionIndex = i + firstInstructionToShow;

                string binInstr = "";
                string rawInstr = "";

                if (instructionIndex < mInstructions.Count)
                {
                    Instruction instr = mInstructions[instructionIndex];
                    rawInstr = instr.RawInstruction;

                    binInstr = $"{formatIntToBinWord((int)instr.OpCode, 6)}";
                    foreach (var arg in instr.Args)
                    {
                        binInstr += $" {formatIntToBinWord(arg, 4)}";
                    }
                }

                string regAddr = $"[{i}]";
                string binReg = formatRegToBin(mState.Registers[i]);

                Console.WriteLine($"|{instructionIndex + 1,lineSp}|{ind,indSp}|{rawInstr,instrSp}" +
                    $"|{binInstr,parsedSp}|{"",columnSp}{regAddr,regAddSp}|{binReg,regValSp}|");
            }

            //print the memory, chunked
            Console.WriteLine($"\n{"** Memory **", memHeaderSp}");
            Console.WriteLine($"{"Add",regAddSp}|{"Mem Val 1",regValSp}|{"Mem Val 2",regValSp}|{"Mem Val 3",regValSp}|{"Mem Val 4",regValSp}|");

            if(mState.Memory.Count % 4 != 0)
            {
                throw new Exception("Memory must be in units of 4");
            }

            for(int i=0; i<mState.Memory.Count; i += 4)
            {
                string memAddr = $"[{i}]";
                string memReg = formatRegToBin(mState.Memory[i]);

                Console.WriteLine($"{memAddr,regAddSp}" +
                    $"|{formatRegToBin(mState.Memory[i]),regValSp}" +
                    $"|{formatRegToBin(mState.Memory[i+1]),regValSp}" +
                    $"|{formatRegToBin(mState.Memory[i+2]),regValSp}" +
                    $"|{formatRegToBin(mState.Memory[i+3]),regValSp}|");
            }

            Console.WriteLine(new string('_', Console.WindowWidth));
        }

        private string formatIntToBinWord(int val, int word)
        {
            return Convert.ToString(val, 2).PadLeft(word, '0');
        }

        private string formatRegToBin(Tuple<int,int> register)
        {
            string binVal = Convert.ToString(register.Item1, 2);
            string binRegVal = Convert.ToString(register.Item2, 2).PadLeft(8, '0');

            return $"{binVal} {binRegVal.Substring(0, 4)} {binRegVal.Substring(4,4)}";
        }

        private decimal valFromRegister(Tuple<int, int> register)
        {
            if(register.Item1 == 0)
            {
                return (decimal)register.Item2;
            }
            else
            {
                return decFromRegVal(register.Item2);
            }
        }

        private int intFromArgs(int arg1, int arg2)
        {
            return (arg1 * 16) + arg2;
        }

        private decimal decFromArgs(int arg1, int arg2)
        {
            string repVal = $"{arg1}.{arg2}";
            return Convert.ToDecimal(repVal);
        }

        private decimal decFromRegVal(int val)
        {
            string binWord = formatIntToBinWord(val, 8);
            int arg1 = Convert.ToInt32(binWord.Substring(0, 4));
            int arg2 = Convert.ToInt32(binWord.Substring(4, 4));
            return decFromArgs(arg1, arg2);
        }

        private Tuple<int,int> regFromArgs(int arg1, int arg2, bool isDecimal)
        {
            if (isDecimal)
            {
                return Tuple.Create(1, intFromArgs(arg1, arg2));
            }
            else
            {
                return Tuple.Create(0, intFromArgs(arg1, arg2));
            }
        }

        private Tuple<int, int> regFromVal(int val)
        {
            return Tuple.Create(0, val);
        }

        private Tuple<int, int> regFromVal(decimal val)
        {
            int wholePart = (int)val;

            decimal potentialFractionalPart = val - wholePart;
            int fractionalPart = 0;

            //if fraction starts with 1, we can take 2 digits
            if ((int)(fractionalPart * 10) == 1)
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

            return Tuple.Create(1, intFromArgs(wholePart, fractionalPart));
        }
    }
}
