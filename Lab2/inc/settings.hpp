#pragma once

#include <boost/program_options.hpp>
namespace ParserSettings {
	class Settings final {
		private:
			size_t L_;
			int 		N_, serialK_;
			double 		serialAlpha_, pokerAlpha_;
			std::string poly_, keyFile_;
			int 		task_;

		public:
			Settings(int argc, char** argv);
			Settings(const Settings& other) = delete;
			Settings& operator=(const Settings& rhs) = delete;
			Settings(Settings&& other) = delete;
			Settings& operator=(Settings&& rhs) = delete;
			~Settings() = default;

		public:
			size_t getL() const				{ return L_; }
			int getN() const				{ return N_; }
			int getStatusTask() const		{ return task_; }
			int getSerialK() const			{ return serialK_; }
			double getSerialAlpha() const	{ return serialAlpha_; }
			double getPokerAlpha() const	{ return pokerAlpha_; }
			std::string getPoly() const		{ return poly_;}
			std::string getKeyFile() const	{ return keyFile_;}

			void setL(size_t newL)				{ L_ = newL; }
	};
} //ParserSettings