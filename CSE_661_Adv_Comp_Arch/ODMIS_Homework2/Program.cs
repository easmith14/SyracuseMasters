using System;
using System.Collections.Generic;
using System.IO;

namespace ODMIS_Homework2
{
    class Program
    {
        static void Main(string[] args)
        {
            while (true)
            {
                //read in possible input files
                var choiceSelector = new CodeFileSelector(@"C:\Users\evana\source\repos\Syracuse_Grad\CSE_661_Adv_Comp_Arch\Homework2");
                choiceSelector.RefreshFileOptions();

                //prompt user to select one file, refresh the input files, or exit program
                string instructionFile = choiceSelector.GetUserFileSelection();

                if(instructionFile == "")
                {
                    break;
                }

                //load selected file and parse labels
                var rawInstructions = new List<string>(File.ReadAllLines(instructionFile));

                var labelParser = new LabelParser(rawInstructions);
                
                List<string> cleanedInstructions;
                Dictionary<string, int> labels;

                labelParser.Parse(out cleanedInstructions, out labels);

                //parse list of cleaned instructions into list of instruction objects
                var instructionParser = new InstructionsParser(labels, cleanedInstructions);
                var parsedInstructions = new List<Instruction>();

                try
                {
                    parsedInstructions = instructionParser.ParseAll();
                }
                catch (Exception e)
                {
                    Console.WriteLine($"Compilation Failure!\nExeption: '{e.Message}'");
                }

                //if all instructions are valid, initialize registers
                //16 regs + PC, 16 memory blocks of 4 words each
                var systemState = new SystemState(registerCount:16, memoryEntryCount:16);
                var processor = new Processor(systemState);

                string instructionPrompt = "[Enter] to run next line, or [Escape] to return to program selection: ";
                var options = new List<ConsoleKey>() { ConsoleKey.Enter, ConsoleKey.Escape };
                var userInput = getUserKeyConstrained(instructionPrompt, options);

                foreach (var instruction in parsedInstructions)
                {                    
                    if(userInput == ConsoleKey.Enter)
                    {
                        //execute instruction
                        processor.ProcessInstruction(instruction);
                    }
                    else
                    {
                        break;
                    }

                    //get user input - continue or exit
                    userInput = getUserKeyConstrained(instructionPrompt, options);
                }

                //when instructions run out, loop back to possible input options
                Console.Clear();
            }
        }

        private static ConsoleKey getUserKeyConstrained(string prompt, List<ConsoleKey> options)
        {
            Console.WriteLine(prompt);

            var userInput = Console.ReadKey().Key;

            while (!options.Contains(userInput))
            {
                userInput = Console.ReadKey().Key;
            }

            return userInput;
        }
    }
}
