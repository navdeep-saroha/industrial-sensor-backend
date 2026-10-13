#include "message_parser.h"

#include <vector>
#include <sstream>
#include <stdexcept>

double parse_double(const std::string& text){
    std::size_t pos = 0;
    double value = 0;

    try
    {
        value = std::stod(text, &pos);
    }
    catch(const std::exception& e)
    {
        throw std::invalid_argument("parse_point: '" + text + "' is not a number");
    }

    if(pos != text.size()){
        throw std::invalid_argument("parse_point: unexpected characters in '" + text + "'");
    }
    return value;
    
}

Point3D parse_point(const std::string& line){
    std::istringstream stream(line);
    std::string part;
    std::vector<std::string> parts;

    while(std::getline(stream, part, ',')){
        parts.push_back(part);
    }

    if (parts.size() != 3){
        throw std::invalid_argument("Not valid input. Expected 3 got:" + std::to_string(parts.size()));
    }

    return {parse_double(parts[0]), parse_double(parts[1]), parse_double(parts[2])};
}

std::vector<std::string> extract_line(std::string& buffer){
    std::vector<std::string> lines;
    std::size_t newline_pos = buffer.find("\n");

    while(newline_pos!=std::string::npos){
        lines.push_back(buffer.substr(0,newline_pos));
        buffer.erase(0, newline_pos+1);
        newline_pos = buffer.find("\n");
    }
    return lines;
}