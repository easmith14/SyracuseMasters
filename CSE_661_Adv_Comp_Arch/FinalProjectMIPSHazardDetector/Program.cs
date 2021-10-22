using System;
using System.Collections.Generic;

namespace FinalProjectMIPSHazardDetector
{
    class Program
    {
        static void Main(string[] args)
        {
            while (true)
            {
                //read in possible input files
                var choiceSelector = new CodeFileSelector(@"C:\Users\evana\source\repos\Syracuse_Grad\CSE_661_Adv_Comp_Arch\FinalProjectMIPSHazardDetector\CodeFiles");
                choiceSelector.RefreshFileOptions();

                //prompt user to select one file, refresh the input files, or exit program
                string selectedProgram = choiceSelector.GetUserFileSelection();

                if (selectedProgram == "")
                {
                    break;
                }

                //parse the file into Instructions
                try
                {
                    var instructionParser = new InstructionParser(selectedProgram);

                    //create a set of controllers to handle cases differently
                    var hazardControllers = new List<IHazardController>()
                    {
                        new NoActionHazardController(instructionParser.Parse(false)),
                        new StallCreatingHazardController(instructionParser.Parse(false), false),
                        new StallCreatingHazardController(instructionParser.Parse(true), true)
                    };

                    var controllerColors = new List<ConsoleColor>()
                    {
                        ConsoleColor.Blue,
                        ConsoleColor.Yellow,
                        ConsoleColor.Green
                    };

                    int i = 0;
                    //run each controller
                    foreach (var controller in hazardControllers)
                    {
                        Console.BackgroundColor = controllerColors[i++];
                        Console.ForegroundColor = ConsoleColor.Black;
                        Console.WriteLine(controller.HandleHazards());
                        Console.BackgroundColor = ConsoleColor.Black;
                        Console.ForegroundColor = ConsoleColor.White;
                    }
                }
                catch(Exception e)
                {
                    Console.BackgroundColor = ConsoleColor.Magenta;
                    Console.WriteLine(e.Message);
                    Console.BackgroundColor = ConsoleColor.Black;
                }
            }
        }
    }
}
