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
                
                List<string> cleanedInstructions;
                Dictionary<string, int> labels;

                //parse list of cleaned instructions into list of instruction objects
                var parsedInstructions = new List<Instruction>();

                try
                {
                    //load selected file and parse labels
                    var rawInstructions = new List<string>(File.ReadAllLines(instructionFile));

                    var labelParser = new LabelParser(rawInstructions);
                    labelParser.Parse(out cleanedInstructions, out labels);

                    var instructionParser = new InstructionsParser(labels, cleanedInstructions);
                    parsedInstructions = instructionParser.ParseAll();
                }
                catch (Exception e)
                {
                    Console.WriteLine($"Compilation Failure!\nExeption: '{e.Message}'");
                    continue;
                }

                //if all instructions are valid, initialize registers
                //16 regs + PC, 16 memory blocks of 4 words each
                var systemState = new SystemState(registerCount:16, memoryEntryCount:16);
                var processor = new Processor(systemState, parsedInstructions);

                string instructionPrompt = "[Enter] run next line | [Escape] return to program selection | [Up/Down] scroll program instructions: ";
                var options = new List<ConsoleKey>() { ConsoleKey.Enter, ConsoleKey.Escape, ConsoleKey.UpArrow, ConsoleKey.DownArrow };

                //display program for user to decide if it's what they want to run
                processor.PrintSystemState();
                var userInput = getUserKeyConstrained(instructionPrompt, options);


                bool programRunning = true;
                int firstInstructionToShow = 0;

                while (programRunning)
                {
                    try
                    {
                        if (userInput == ConsoleKey.Enter)
                        {
                            //execute instruction
                            programRunning = processor.ProcessNextInstruction();
                            processor.PrintSystemState(firstInstructionToShow);
                        }
                        else if(userInput == ConsoleKey.UpArrow)
                        {
                            firstInstructionToShow = Math.Max(firstInstructionToShow - 3, 0);
                            processor.PrintSystemState(firstInstructionToShow);
                        }
                        else if (userInput == ConsoleKey.DownArrow)
                        {
                            firstInstructionToShow = Math.Min(firstInstructionToShow + 3, parsedInstructions.Count - 6);
                            processor.PrintSystemState(firstInstructionToShow);
                        }
                        else
                        {
                            break;
                        }

                        //get user input - continue or exit
                        userInput = getUserKeyConstrained(instructionPrompt, options);
                    }
                    catch (Exception e)
                    {
                        Console.WriteLine($"Runtime Exception: {e.Message}");
                        break;
                    }
                    
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
