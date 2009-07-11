/*
#################################################################################
#				Konkord 														#
#			Version 0.0.2009.04.19												#
#	This program was created for learning words									#
#	 		from different languages.											#
#																				#
#    Copyright(C) 2009 Sławomir Domagała										#
#																				#
#    This program is free software: you can redistribute it and/or modify		#
#    it under the terms of the GNU General Public License as published by		#
#    the Free Software Foundation, either version 3 of the License, or			#
#    (at your option) any later version.										#
#																				#
#    This program is distributed in the hope that it will be useful,			#
#    but WITHOUT ANY WARRANTY; without even the implied warranty of				#
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the				#
#    GNU General Public License for more details.								#
#																				#
#    You should have received a copy of the GNU General Public License			#
#    along with this program.  If not, see <http://www.gnu.org/licenses/>		#
#																				#
#    E-mail: godlark@gmail.com													#
#################################################################################		
*/
#ifndef RegisterOfErrors_hpp
#define REgisterOfErrors_hpp

#include <string>
#include <vector>

using namespace std;
typedef unsigned short int USI;

class Error//and Warnings
{
	private:
		USI kindOfError;
		string nameOfFunction;
		USI numberOfLine;
		string filename;
	public:
		static const USI QUANTITY_OF_ERRORS = 9;
		static string *DescriptionOfErrors;
		static const USI OTHER_ERROR = 0;
		static const USI ERROR_SAVE_FILE = 1;
		static const USI ERROR_READ_FILE = 2;
		static const USI ERROR_OPEN_FILE = 3;
		static const USI OUTPASS_ABOVE_SPACE_OF_ARRAY = 4;
		static const USI OUTPASS_MAX_SIZE_OF_ARRAY = 5;
		static const USI BAD_ARGUMENT = 6;
		static const USI IGNORED_LINE_IN_FILE = 7; // warning
		static const USI BOOST__REGEX_ERROR = 8;
		//przy dodaniu kolejnych błędów i ostrzeżeń trzeba zmienić funkcję "isWarning()"
		Error(USI _kindOfError, string _nameOfFunction, USI _numberOfLine, string _filename)
		{
			kindOfError = _kindOfError;
			nameOfFunction = _nameOfFunction;
			numberOfLine = _numberOfLine;
			filename =_filename;
		}
		string getDescription() const
		{
			return DescriptionOfErrors[kindOfError];
		}
		USI getKindOfError() const
		{
			return kindOfError;
		}
		string getNameOfFunction() const
		{
			return nameOfFunction;
		}
		USI getNumberOfLine() const
		{
			return numberOfLine;
		}
		string getFilname() const
		{
			return filename;
		}
		static void setDescriptionOfErrors()
		{
			DescriptionOfErrors = new string[QUANTITY_OF_ERRORS];
			DescriptionOfErrors[0] = "OTHER_ERROR";
			DescriptionOfErrors[1] = "ERROR_SAVE_FILE";
			DescriptionOfErrors[2] = "ERROR_READ_FILE";
			DescriptionOfErrors[3] = "ERROR_OPEN_FILE";
			DescriptionOfErrors[4] = "OUTPASS_ABOVE_SPACE_OF_ARRAY";
			DescriptionOfErrors[5] = "OUTPASS_MAX_SIZE_OF_ARRAY";
			DescriptionOfErrors[6] = "BAD_ARGUMENT";
			DescriptionOfErrors[7] = "IGNORED_LINE_IN_FILE";
			DescriptionOfErrors[8] = "BOOST::REGEX_ERROR";
		}
		static Error newError(USI _kindOfError, string _nameOfFunction, USI _numberOfLine, string _filename)
		{
			Error error(_kindOfError, _nameOfFunction, _numberOfLine, _filename);
			return error;
		}
		void addNextFunction(string _nameOfFunction)
		{
			nameOfFunction += "->";
			nameOfFunction += _nameOfFunction;
		}
		bool isWarning() const
		{
			if(kindOfError == 7)return true;
			else return false;
		}
};
class RegisterOfErrors
{
	private:
		vector<Error> errors;
		unsigned int quantityOfErrors;
	public:
		RegisterOfErrors()
		{
			quantityOfErrors = 0;
		}
		void addError(const Error &error)
		{
			errors.push_back(error);
			quantityOfErrors++;
		}
		Error getError(unsigned int numberOfError) const
		{
			return errors[numberOfError];
		}
};
#endif
