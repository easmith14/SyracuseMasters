using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinalProjectMIPSHazardDetector
{
    public class RequiredRegister
    {
        public int RegisterNumber;
        public PipelineStage NeededStage;
        public PipelineStage FreedStage;

        public RequiredRegister(int register, PipelineStage neededStage, PipelineStage freedStage)
        {
            RegisterNumber = register;
            NeededStage = neededStage;
            FreedStage = freedStage;
        }
    }
}
