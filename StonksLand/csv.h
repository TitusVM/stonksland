#pragma once

#include <istream>
#include <string>
#include <vector>

#include <QFile>

std::vector<std::vector<std::string>> readCSV(QFile &file);
