
using System;

public class HelloCsharp
{
    private void TestArgs(string []args)
    {
        Console.WriteLine("The number of arguments: {0}", args.Length);
        for(int i = 0; i < args.Length; i ++)
        {
            Console.WriteLine("Argv[{0}] = {1}", i, args[i]);
        }

        Console.WriteLine("foreach output:");
        foreach(string s in args)
        {
            Console.WriteLine(s);
        }
    }

    public static void Main(string [] args)
    {
        Console.WriteLine("Hello, world!");
        HelloCsharp instance = new HelloCsharp();
        instance.TestArgs(args);
    }

}