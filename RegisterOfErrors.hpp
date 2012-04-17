/*				Konkord 
 *		    Version 0.0.2009.04.19
 *	This program was created for learning words
 *		    from different languages.
 *    Copyright(C) 2009 Sławomir Domagała	
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *																			
 * This program is distributed in the hope that it will be useful,				
 * but WITHOUT ANY WARRANTY; without even the implied warranty of				
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the				
 * GNU General Public License for more details.								
 *																			
 * You should have received a copy of the GNU General Public License			
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *																				
 * E-mail: E-mail: g_o_d_l_a_r_k / monkey / g_m_a_i_l / dot / c_o_m									
 */
#ifndef RegisterOfErrors_hpp
#define RegisterOfErrors_hpp

#include <string>
#include <vector>

typedef unsigned int uint;

class Error {
	private:
		uint kindOfError;
		std::string nameOfFunction;
		uint numberOfLine;
		std::string filename;
	public:
		static const uint QUANTITY_OF_ERRORS = 11;
		static std::string *DescriptionOfErrors;
		static const uint OTHER_ERROR = 0;
		static const uint ERROR_SAVE_FILE = 1;
		static const uint ERROR_READ_FILE = 2;
		static const uint ERROR_OPEN_FILE = 3;
		static const uint OUTPASS_ABOVE_SPACE_OF_ARRAY = 4;
		static const uint OUTPASS_MAX_SIZE_OF_ARRAY = 5;
		static const uint BAD_ARGUMENT = 6;
		static const uint IGNORED_LINE_IN_FILE = 7; // warning
		static const uint BOOST__REGEX_ERROR = 8;
		static const uint IMPOSSIBLE = 9;
		static const uint CANCELLED = 10;
		//przy dodaniu kolejnych błędów i ostrzeżeń trzeba zmienić funkcję "isWarning()"
		Error(uint _kindOfError, std::string _nameOfFunction, uint _numberOfLine, std::string _filename);
		std::string getDescription() const;
		uint getKindOfError() const;
		std::string getNameOfFunction() const;
		uint getNumberOfLine() const;
		std::string getFilname() const;
		static void setDescriptionOfErrors();
				static void eraseDerscriptionOfErros();
		static Error newError(uint _kindOfError, std::string _nameOfFunction, uint _numberOfLine, std::string _filename);
		void addNextFunction(std::string _nameOfFunction);
		bool isWarning() const;
		std::string toString() const;
};
class RegisterOfErrors {
        private:
                std::vector<Error> errors;
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
