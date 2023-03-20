#include "../inc/namespaces.hpp"
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include <set>
#include <stack>
#include <thread>
#include <fstream>

namespace Generator {

	void Register::parsePoly() {
		const std::string tmp = settings_.getPoly();
		polynome_.reserve(std::count_if(tmp.begin(), tmp.end(), [](char c){return c == '+';}) + 1);
		std::vector<std::string> splt;
		boost::split(splt, settings_.getPoly(), "+x");
		std::for_each(splt.begin(), splt.end(), [this](const std::string& s){ if (s != "") polynome_.push_back(std::stoi(s)); });
		polynome_.pop_back();
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
			digits_ = boost::dynamic_bitset<>(s);
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
				genDigits();
			}
		} catch (const std::exception& e) {
			std::cerr << e.what();
			std::exit(EXIT_FAILURE);
		}
	}

	void Register::generationMseq() {
		std::set<boost::dynamic_bitset<>> findContain;
		std::stack<bool> s;
		int ret_xor;
		
		s.push(digits_[0]);
		while (findContain.count(digits_) == 0) {
			findContain.insert(digits_);
			bool ret_xor = 0;
			for (auto c : polynome_){
				ret_xor ^= digits_[c - 1];
			}
			digits_ >> 1;
			digits_[digits_.size() - 1] = ret_xor;
			s.push(digits_[0]);
		}
		
		while (!s.empty()) {
			MSeq_.push_back(s.top());
			s.pop();
		}
	}

	void Register::runTask() {
		int curr_status = settings_.getStatusTask();
		switch (curr_status) {
			case 1:
			{
				std::cout << MSeq_;
			}
				break;
			case 2:
			{
				std::thread t1(corrTest, this);
				std::thread t2(serialTest, this);
				std::thread t3(pokerTest, this);
				t1.join();
				t2.join();
				t3.join();
			}
				break;
			case 3: {

			}
				break;
			case 4:
			{

			}
				break;
			case 5:
			{

			}
				break;
			case 6:
			{

			}
			break;
		}
	}
}