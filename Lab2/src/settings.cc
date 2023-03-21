#include "../inc/namespaces.hpp"

namespace ParserSettings {
	namespace po = boost::program_options;

	Settings::Settings(int argc, char** argv) {
		try {
			po::options_description desc("Settings");
			desc.add_options()
			("help,h", "Help screen")
			("L", po::value<size_t>(&L_)->default_value(4), "Register size")
			("poly", po::value<std::string>(&poly_)->default_value("x4+x1+1"), "Polynom for feedback function")
			("N", po::value<int>(&N_)->default_value(-1), "Result size")
			("file", po::value<std::string>(&keyFile_)->default_value(""), "File to store key")
			("task", po::value<int>(&task_)->default_value(1), "Number task")
			("serialK", po::value<int>(&serialK_)->default_value(2), "Serial Test K")
			("serialAlpha",po::value<double>(&serialAlpha_)->default_value(0), "Serial Test alpha")
			("pokerAlpha", po::value<double>(&pokerAlpha_)->default_value(0), "Poker Test alpha");
	
			po::variables_map vm;
			po::store(po::parse_command_line(argc, argv, desc), vm);

			if (vm.count("help")) {
				std::cout << desc << '\n';
			}

		} catch (const po::error& e) {
			std::cerr << e.what() << std::endl;
			exit(EXIT_FAILURE);
		}
	}
} //ParseSettings
