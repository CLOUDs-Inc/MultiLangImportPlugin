using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MultiLangImportDotNet
{
    public class OptionData
    {
        public bool FlagUseSubcastName { get; set; }


        public bool FlagUseSubcastNameWhenSearchingForCast { get; set; }


        public bool FlagAddSubcastNameWhenCreatingANewCast { get; set; }


        public bool FlagUseUnderscoreForConjunctionInSubcastName { get; set; }


        public string ConjunctionString { get; set; }


        public int SubcastIndex { get; set; }
    }
}
