﻿//BSD 2-Clause License

//Copyright(c) 2018, Stan Sakl
//All rights reserved.

//Redistribution and use in source and binary forms, with or without
//modification, are permitted provided that the following conditions are met:

//* Redistributions of source code must retain the above copyright notice, this
//  list of conditions and the following disclaimer.

//* Redistributions in binary form must reproduce the above copyright notice,
//  this list of conditions and the following disclaimer in the documentation
//  and/or other materials provided with the distribution.

//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//DISCLAIMED.IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
//FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
//CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
//OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

using System;
using System.Collections.Generic;
using System.IO;

namespace kwic_csharp
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Running kwic_csharp");

            if (args.Length == 1)
            {
                string fileName = args[0];
                string output = "";

                try
                {
                    IEnumerable<string> lines = File.ReadLines(fileName);
                    foreach(string line in lines)
                    {
                        string[] words = line.Split(' ');
                        Array.Sort(words);

                        foreach(string word in words)
                        {
                            if(word.EndsWith("\n"))
                            {
                                word.TrimEnd('\n');
                            }
                            output += word;
                            output += " ";
                        }

                        output += "\n";

                        Console.WriteLine(output);                       
                    }
                }
                catch(Exception e)
                {
                    Console.WriteLine(e.Message);
                }

            }

            else
            {
                ShowFileArgumentError();
            }

            Console.WriteLine("Press any key to continue...");
            Console.ReadKey();
        }

        private static void ShowFileArgumentError()
        {
            Console.WriteLine("A file name is required!");
        }
    }
}
