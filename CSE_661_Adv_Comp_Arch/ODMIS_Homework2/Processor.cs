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

            //update registers
            //update memory

            switch (instruction.OpCode)
            {
                case OpCode.LOADA_M:
                    break;
                case OpCode.LOADA_R:
                    break;
                case OpCode.LOADI_I:
                    break;
                case OpCode.LOADI_D:
                    break;
                case OpCode.STORE_M:
                    break;
                case OpCode.STORE_R:
                    break;
                case OpCode.ADDA_I:
                    break;
                case OpCode.SUBA_I:
                    break;
                case OpCode.SUBA_D:
                    break;
                case OpCode.DIVA_I:
                    break;
                case OpCode.DIVA_D:
                    break;
                case OpCode.MULA_I:
                    break;
                case OpCode.MULA_D:
                    break;
                case OpCode.ADDI_I:
                    break;
                case OpCode.ADDI_D:
                    break;
                case OpCode.SUBI_I:
                    break;
                case OpCode.SUBI_D:
                    break;
                case OpCode.DIVI_I:
                    break;
                case OpCode.DIVI_D:
                    break;
                case OpCode.MULI_I:
                    break;
                case OpCode.MULI_D:
                    break;
                case OpCode.ROOT_I:
                    break;
                case OpCode.ROOT_D:
                    break;
                case OpCode.CEIL:
                    break;
                case OpCode.FLOOR:
                    break;
                case OpCode.ROUND:
                    break;
                case OpCode.RAND_I:
                    break;
                case OpCode.RAND_D:
                    break;
                case OpCode.PI:
                    break;
                case OpCode.CLEAR_R:
                    break;
                case OpCode.CLEAR_M:
                    break;
                case OpCode.JUMP:
                    break;
                case OpCode.JUMP_LTE:
                    break;
                case OpCode.JUMP_LT:
                    break;
                case OpCode.JUMP_GTE:
                    break;
                case OpCode.JUMP_GT:
                    break;
                case OpCode.JUMP_EQ:
                    break;
                case OpCode.ORA_R:
                    break;
                case OpCode.ORI_I:
                    break;
                case OpCode.ANDA_R:
                    break;
                case OpCode.ANDI_I:
                    break;
                case OpCode.NOTA_R:
                    break;
                case OpCode.NOT_I:
                    break;
                case OpCode.TERN_LTE:
                    break;
                case OpCode.TERN_LT:
                    break;
                case OpCode.TERN_GTE:
                    break;
                case OpCode.TERN_GT:
                    break;
                case OpCode.TERN_EQ:
                    break;
                case OpCode.TIME:
                    break;
                case OpCode.ADDA_D:
                    break;
                case OpCode.END:
                    //finish program
                    return false;
                default: throw new Exception($"Unknown OpCode given: {instruction.OpCode}");
            }

            return true;
        }

        //todo: add scrollability here
        public void PrintSystemState(int firstInstructionToShow = 0)
        {
            const int TOTAL_VISIBLE_INSTR = 16;
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
    }
}
