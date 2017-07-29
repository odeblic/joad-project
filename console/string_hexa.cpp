#include <iostream>
#include <iomanip>
#include <string>

void viewHexadecimal(const std::string & str, std::ostream & os)
{
    int blockSize = 0;
    int objectSize = 0;
    int nbColumnsMax = 0;
    int nbRowsMax = 0;
    int nonAsciiPolicy = 0;

    unsigned int index = 0;
    unsigned int offset = 0;

    os << "       +-------------------------------------------------+" << std::endl;

    os << "       |";
    os.flags(std::ios::right | std::ios::hex | std::ios::uppercase);

    for(index = 0x0; index <= 0xF ; ++index)
    {
        os << ' ' << index << ' ';
    }

    os << " |" << std::endl;

    os << "+------+-------------------------------------------------+------------------+" << std::endl;

    while(offset * 16 < str.size())
    {
        os << "| ";
        //os.flags(std::ios::right | std::ios::hex);
        os << std::setw(4) << std::setfill('0') << offset;
        os << " |";
        //os << std::setw(2);
        for(index = 0x0; index <= 0xF ; ++index)
        {
            if(index + offset * 16 < str.size())
            {
                os << ' ' << std::setw(2) << std::setfill('0') << (int)str[index + offset * 16];
            }
            else
            {
                os << "   ";
            }
        }
        os << " | ";
        for(index = 0x0; index <= 0xF ; ++index)
        {
            if(index + offset * 16 < str.size())
            {
                char c = (char)str[index + offset * 16];
                if(! (' ' <= c && c <= '~') )
                {
                    c = '.';
                }
                os << c;
            }
            else
            {
                os << ' ';
            }
        }
        os << " |" << std::endl;
        ++offset;
    }

    os << "+------+-------------------------------------------------+------------------+" << std::endl;
}
