/*! \file
 *
 * \brief Basic output and printing functionality (source)
 * \author Benjamin Pritchard (ben@bennyp.org)
 */ 


#include "pulsar/output/Output.hpp"


namespace pulsar{

// global function
bool color_enabled(void) noexcept;


namespace detail {

void print_output_(std::ostream & out, OutputType type, const std::string & str)
{
    if(color_enabled())
    {
        std::string st = str;
        if(st.size() == 0)
            return;

        // strip out the last newline character. Makes it look ugly
        bool newline = (st.back() == '\n');
        if(newline)
            st = st.substr(0, st.size()-1);

        switch(type)
        {
            case OutputType::Success:
                out << "\033[32m" << st << "\033[0m";
                break;
            case OutputType::Changed:
                out << "\033[91m" << st << "\033[0m";
                break;
            case OutputType::Debug:
                out << "\033[35m" << st << "\033[0m";
                break;
            case OutputType::Warning:
                out << "\033[33m" << st << "\033[0m";
                break;
            case OutputType::Error:
                out << "\033[37;41m" << st << "\033[0m";
                break;
            default:
                out << st;
                break;

        }
        if(newline)
            out << "\n";
    }
    else
        out << str;
}

}

} // close namespace pulsar
