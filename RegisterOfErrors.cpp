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
#include "RegisterOfErrors.h"

using namespace std;
typedef unsigned short int ushort;

void Error::setDescriptionOfErrors() {
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
                    DescriptionOfErrors[9] = "THAT'S IMPOSSIBLE";
                    DescriptionOfErrors[10] = "ACTION WAS CANCELLED";
                }
Error::Error(ushort _kindOfError, string _nameOfFunction, ushort _numberOfLine, string _filename) {
	kindOfError = _kindOfError;
	nameOfFunction = _nameOfFunction;
	numberOfLine = _numberOfLine;
	filename =_filename;
}
string Error::getDescription() const {
	return DescriptionOfErrors[kindOfError];
}
ushort Error::getKindOfError() const {
			return kindOfError;
}
string Error::getNameOfFunction() const {
			return nameOfFunction;
}
ushort Error::getNumberOfLine() const {
			return numberOfLine;
}
string Error::getFilname() const {
			return filename;
}

Error Error::newError(ushort _kindOfError, string _nameOfFunction, ushort _numberOfLine, string _filename) {
	Error error(_kindOfError, _nameOfFunction, _numberOfLine, _filename);
	return error;
}
void Error::addNextFunction(string _nameOfFunction) {
	nameOfFunction += "->";
	nameOfFunction += _nameOfFunction;
}
bool Error::isWarning() const {
	if(kindOfError == 7)return true;
	else return false;
}
string Error::toString() const {
    string text;
    char char_text[100];
    sprintf(char_text, "DESCRIPTION: %s\n LINE: %d\n FILE: %s\n", getDescription().c_str(), numberOfLine, filename.c_str());
    text = char_text;
    return text;
}
void Error::eraseDerscriptionOfErros() {
    delete [] DescriptionOfErrors;
}