#include "src/lib.h"
#include <iostream>
#include <string>
#include <vector>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_sinks.h>

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

namespace po = boost::program_options;
namespace fs = boost::filesystem;

int main(int argc, char *argv[])
{
    auto logger = spdlog::stdout_logger_mt("console");
    po::options_description description ("Tool for detecting duplicates in specified directories");
    description.add_options()
        ("help,h", "display this help and exit")
        ("scan_dirs,d", po::value<std::vector<std::string>>()->multitoken(), "directories for scanning")
        ("exclude_dirs,x", po::value<std::vector<std::string>>()->multitoken(), "directories for exclude scanning")
        ("depth,D", po::value<int>(), "scanning level")
        ("min_file_size,m", po::value<int>(), "minimum in bytes size of file for scanning")
        ("pattern,p", po::value<std::string>(), "matching pattern case insensitive")
        ("block_size,b", po::value<int>(), "block size in bytes that defines reading frame size")
        ("hash,H", po::value<std::string>(), "hash algorithms from list [crc32, md5]");

    po::variables_map varMap;
    try {
        po::store(po::parse_command_line(argc, argv, description), varMap);
    } catch (const std::exception &exception) {
        std::cout << description << std::endl;
        return 0;
    }
    po::notify(varMap);

    auto dirs = varMap["scan_dirs"].as<std::vector<std::string>>();
    for (const auto &d : dirs) {
        if (!fs::is_directory(d)) {
            std::cerr << d << "is not directory" << std::endl;
            continue;
        }
        fs::path path{d};
        fs::directory_iterator dirIter{path};
        while (dirIter != fs::directory_iterator{}) {
            ;
        }

        if (varMap.size() == 0 || varMap.count("help")) {
            std::cout << description << std::endl;
            return 0;
        }

        std::vector<std::string> dirs = varMap["scan_dirs"].as<std::vector<std::string>>();
        for (auto d : dirs) {
            std::cout << d << std::endl;
        }

        dirs = varMap["exclude_dirs"].as<std::vector<std::string>>();
        for (auto d : dirs) {
            std::cout << d << std::endl;
        }
    }

    return 0;
}
