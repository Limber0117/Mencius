// Copyright 2019 Lukas Joswiak, Justin Johnson, Jack Khuu.

#include <fstream>
#include <iostream>

#include "Utilities.hpp"

const int kMaxConfigLineLength = 255;

std::vector<std::tuple<std::string, std::string>> Utilities::ReadConfig(
    const std::string &config_path) {
  // Read list of host names and ports from config file.
  std::vector<std::tuple<std::string, std::string>> server_addresses;

  std::ifstream config_file(config_path);
  if (!config_file) {
    std::cerr << "cannot open config file" << std::endl;
    return {};
  }

  char buf[kMaxConfigLineLength];
  while (config_file) {
    config_file.getline(buf, kMaxConfigLineLength);
    std::string line(buf);
    if (config_file) {
      int pos = line.find_first_of(' ');
      auto host = line.substr(0, pos);
      auto port = line.substr(pos + 1);
      server_addresses.push_back(std::make_tuple(host.c_str(), port.c_str()));
    }
  }

  return server_addresses;
}
