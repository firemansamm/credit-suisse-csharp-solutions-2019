using System;
using System.Linq;
using Mono.Cecil;
using Mono.Cecil.Cil;

namespace ctor_injector
{
    class Program
    {
        private const string HostTypeName = "Initialiser";
        private const string HostMethodName = "Run";

        static void Main(string[] args)
        {
            if (args.Length < 1)
            {
                Console.WriteLine("usage: ctor-injector <.dll>");
                return;
            }
            var path = args[0];
            Console.WriteLine("path: {0}", path);

            Console.WriteLine("opening assembly...");
            using (var asm = ModuleDefinition.ReadModule(path, new ReaderParameters { ReadWrite = true })) { 

                Console.WriteLine("generating definitions...");
                var mctor = new MethodDefinition(
                    ".cctor",
                    MethodAttributes.Static |
                    MethodAttributes.SpecialName |
                    MethodAttributes.RTSpecialName,
                    asm.ImportReference(typeof(void))
                );
                Console.WriteLine("generated OK.");

                Console.WriteLine("looking for host method ({0}.{1})...", HostTypeName, HostMethodName);
                try
                {
                    var hostType = asm.Types.First(x => x.Name == HostTypeName);
                    var hostMethod = hostType.Methods.First(x => x.Name == HostMethodName);

                    Console.WriteLine("got host. creating call...");
                    var proc = mctor.Body.GetILProcessor();
                    proc.Append(proc.Create(OpCodes.Call, hostMethod));
                    proc.Append(proc.Create(OpCodes.Ret));

                    Console.WriteLine("created hook. injecting!");

                    var moduleType = asm.Types.First(x => x.Name == "<Module>");
                    moduleType.Methods.Add(mctor);

                    Console.WriteLine("done injecting in IL. rewriting file.");

                    asm.Write();
                }
                catch (Exception e)
                {
                    Console.WriteLine("there was a problem. the error was:");
                    Console.WriteLine(e.Message);
                    return;
                }


                Console.WriteLine("done.");
            }
        }
    }
}
