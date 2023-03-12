#include "../inc/namespaces.hpp"

namespace Generator {

	void Register::parsePoly() {
		const std::string tmp = settings_.getPoly();
		polynome_.reserve(std::count_if(tmp.begin(), tmp.end(), [](char c){return c == '+';}) + 1);
		std::vector<std::string> splt;
		boost::split(splt, settings_.getPoly(), "+x");
		std::for_each(splt.begin(), splt.end(), [this](const std::string& s){ if (s != "") polynome_.push_back(std::stoi(s)); });
	}

	void Register::genDigits() {
		for (size_t i = 0, end = settings_.getL(); i != end; ++i) {
			digits_[i] = std::rand() % 2;
		}
	}

	void Register::readFile() {
		std::ifstream f(settings_.getKeyFile(), std::ifstream::in);
		if (f.is_open())
		{
			std::string s, tmp;
			while (std::getline(f,tmp)) {
				s += tmp;
			}
			digits_.reserve(s.size());
			std::for_each(s.rbegin(), s.rend(), [this](char c){digits_.push_back(c == '1');});
			f.close();
		} else {
			throw std::runtime_error("Could not open the file");
		}
	}

	Register::Register(int argc, char** argv) : settings_(argc,argv) {
		try {
			if (settings_.getKeyFile() != "") {
				readFile();
				settings_.setL(digits_.size());
			} else {
				digits_.reserve(settings_.getL());

			}
		} catch (const std::exception& e) {
			std::cerr << e.what();
			std::exit(EXIT_FAILURE);
		}
	}
}