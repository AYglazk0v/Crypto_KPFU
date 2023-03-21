#pragma once

#include "namespaces.hpp"
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <string>
#include <vector>
#include <mutex>

namespace Generator {
	
	static std::mutex mtx_;
	namespace Cypher {
		void encrypt(boost::dynamic_bitset<> MSeq_, std::string);
        std::vector<u_char> readFileBin(std::string filename);
	}
	class Register final {
		private:
			ParserSettings::Settings settings_;
			std::vector<int> polynome_;
			boost::dynamic_bitset<> digits_;
			boost::dynamic_bitset<> MSeq_;

		public:
			Register(int argc, char** argv);
			~Register() = default;
			
			Register(const Register&) = delete;
			Register(Register&&) = delete;
			Register& operator=(const Register&) = delete;
			Register& operator=(Register&&) = delete;            

		public:
			void runTask();

		private:
			void startTest();
			void readFile();
			void genDigits();
			void parsePoly();
			void generationMseq();
			void MSeq4File(std::string);

		private:
			void serialTest();
			void pokerTest();
			void corrTest();

		private:
			void crutches();

	};
} //Register