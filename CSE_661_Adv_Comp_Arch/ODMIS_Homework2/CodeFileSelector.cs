using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace ODMIS_Homework2
{
    class CodeFileSelector
    {
        private string mDirectoryPath;
        private List<string> mFileOptions;
        private const string FILE_EXT = ".ODMIS";
        public CodeFileSelector(string directoryPath)
        {
            mDirectoryPath = directoryPath;
            mFileOptions = new List<string>();
        }
        public void RefreshFileOptions()
        {
            //grab all files in the directory with the right file extension
            string[] validFiles = Directory.GetFiles(mDirectoryPath, $"*{FILE_EXT}");
            mFileOptions = new List<string>(validFiles);
        }

        public string GetUserFileSelection()
        {
            int dashCount = 57;
            Console.WriteLine(new string('-', dashCount));
            Console.WriteLine("Select the file to run:");
            Console.WriteLine(new string('-', dashCount));

            //write out all file options
            int choiceNumber = 1;
            foreach(var file in mFileOptions)
            {
                Console.WriteLine($"[{choiceNumber++}]  {Path.GetFileNameWithoutExtension(file),-30}{File.GetLastWriteTime(file), -20}");
            }

            Console.WriteLine(new string('-', dashCount) + "\n([0] to refresh, [-1] to exit)\n\n");

            string choice = "";

            while (choice == "")
            {
                Console.Write("Your Choice: ");
                string rawUserChoice = Console.ReadLine();


                int userChoice = 1;
                Int32.TryParse(rawUserChoice, out userChoice);

                if(userChoice <= mFileOptions.Count && userChoice > 0)
                {
                    choice = mFileOptions[userChoice-1];
                }
                else if(userChoice == 0)
                {
                    RefreshFileOptions();
                    Console.Clear();
                    //yes, this can cause a stack overflow. I choose to ignore this for simplicity :)
                    return GetUserFileSelection();
                }
                else if(userChoice == -1)
                {
                    return "";
                }
                else
                {
                    Console.WriteLine("Please enter a valid choice number!\n");
                }
            }

            return choice;
        }
    }
}
