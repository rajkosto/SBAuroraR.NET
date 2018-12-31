using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestSBAurora
{
    class Program
    {
        static void Main(string[] args)
        {
            var manager = new SBAuroraReactive.LEDManager();
            using (manager)
            {
                var devices = manager.EnumConnectedDevices();
                Console.WriteLine($"Found {devices.Length} connected SB devices:");
                for (int i=0; i<devices.Length; i++)
                {
                    SBAuroraReactive.EnumeratedDevice currDev = devices[i];
                    Console.WriteLine($"{currDev.vid:X4}:{currDev.pid} == {currDev.friendlyName} has {currDev.totalNumLeds} LEDs");
                }
            }
        }
    }
}
