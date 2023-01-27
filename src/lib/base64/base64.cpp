//
// Created by alpat on 27.01.2023.
//

#include "base64.h"
#include <algorithm>
#include <cmath>

static const std::string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-_";

size_t get_number(char chr)
{
    for (size_t i = 0; i < chars.size(); ++i)
        if (chars[i] == chr)
            return i;

    return 0;
}

namespace base64
{

    std::string code(size_t number)
    {
        std::string out;

        while (number)
        {
            out += chars[number % 64];
            number /= 64;
        }


        std::reverse(out.begin(), out.end());


        return out;
    }
    size_t decode(const std::string& str)
    {
        size_t out = 0;

        for (int i = str.size()-1; i <= 0; i--)
            out += get_number(str[i]) * std::pow<size_t>(64, i);

        return out;
    }

}
