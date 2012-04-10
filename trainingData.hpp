/*                Konkord 
 *            Version 0.0.2009.04.19
 *    This program was created for learning words
 *            from different languages.
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
#ifndef TRAININGDATA_HPP
#define TRAININGDATA_HPP

#include <string>
#include <list>
#include <initializer_list>
#include "doublefann.h"
#include "fann_cpp.h"

typedef unsigned short int ushort;

class TrainingData {
    double**            outputss;
    double**            inputss;
    ushort              nLines;
    ushort              nOutputsInLine;
    ushort              nInputsInLine;
    std::list<double*>  queuedOutputs;
    std::list<double*>  queuedInputs;
    ushort              maxLines;
public:
    void addLine(std::initializer_list<double> Ainputs, std::initializer_list<double> Aoutputs);
    FANN::training_data getData() const;
    ushort getMaxLines() const;
    void save(const std::string& filename) const;
    void setMaxLines(const ushort& AmaxLines);
    void update();
    
    TrainingData(const std::string& filename);
    TrainingData(const ushort& AnInputsInLine, const ushort& AnOutputsInLine);
};

#endif // TRAINDATA_HPP
