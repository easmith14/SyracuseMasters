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
                var instructionParser = new InstructionParser(selectedProgram);

                //create a set of controllers to handle cases differently
                var hazardControllers = new List<IHazardController>()
                {
                    new NoActionHazardController(instructionParser.Parse(false)),
                    //new StallCreatingHazardController(instructionParser.Parse(false)),
                    //new StallCreatingHazardController(instructionParser.Parse(true))
                };

                //run each controller
                foreach (var controller in hazardControllers)
                {
                    Console.WriteLine(controller.HandleHazards());
                }
            }
        }
    }
}
