//
// Created by alpat on 27.01.2023.
//
#pragma once
#include <string>

namespace base64
{
    std::string code(size_t number);
    size_t decode(const std::string& str);
};
