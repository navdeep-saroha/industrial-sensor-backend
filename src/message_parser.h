#pragma once

#include <string>
#include "point_processing.h"
Point3D parse_point(const std::string& line);

std::vector<std::string> extract_line(std::string &buffer);