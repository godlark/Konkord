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
 
#include "trainingData.hpp"
#include <fstream>
#include <climits>
 
using namespace std;
typedef unsigned short int ushort;

TrainingData::TrainingData(const std::string &filename) {
    fstream file;
    file.open(filename.c_str(), ios_base::in);
    
    file >> nLines;
    maxLines = nLines;
    file >> nInputsInLine;
    file >> nOutputsInLine;
    file.ignore(INT_MAX, '\n');
    
    queuedInputs = list<double*>();
    queuedOutputs = list<double*>();
    
    outputss = new double*[nLines];
    inputss = new double*[nLines];
    
    for(int i = 0; i < nLines; i++) {
        inputss[i] = new double[nInputsInLine];
        for(int j = 0; j < nInputsInLine; j++) {
            file >> inputss[i][j];
        }
        outputss[i] = new double[nOutputsInLine];
        for(int j = 0; j < nOutputsInLine; j++) {
            file >> outputss[i][j];
        }
    }
    file.close();
}

void TrainingData::save(const std::string &filename) const {
    fstream file;
    file.open(filename.c_str(), ios_base::out);
    
    file << nLines << '\t';
    file << nInputsInLine << '\t';
    file << nOutputsInLine << '\n';
    
    file.precision(16);
    for(int i = 0; i < nLines; i++) {
        for(int j = 0; j < nInputsInLine; j++) {
            file << fixed << inputss[i][j] << '\t';
        }
        file << '\n';
        for(int j = 0; j < nOutputsInLine; j++) {
            file << fixed << outputss[i][j] << '\t';
        }
        file << '\n';
    }
    file.close();
}

TrainingData::TrainingData(const ushort &AnInputsInLine, const ushort &AnOutputsInLine) {
    nInputsInLine = AnInputsInLine;
    nOutputsInLine = AnOutputsInLine;
    maxLines = nLines = 0;
    outputss = 0;
    inputss = 0;
    queuedInputs = list<double*>();
    queuedOutputs = list<double*>();
}

ushort TrainingData::getMaxLines() const {
    return maxLines;
}

void TrainingData::setMaxLines(const ushort& AmaxLines) {
    maxLines = AmaxLines;
}

FANN::training_data TrainingData::getData() const {
    FANN::training_data data = FANN::training_data();
    data.set_train_data(nLines, nInputsInLine, inputss, nOutputsInLine, outputss);
    return data;
}

void TrainingData::addLine(std::initializer_list<double> Ainputs, std::initializer_list<double> Aoutputs) {
    std::initializer_list<double>::iterator iter;
    
    double* inputs = new double[nInputsInLine];
    iter = Ainputs.begin();
    for(int i = 0; i < nInputsInLine; i++, iter++) {
        inputs[i] = *iter;
    }
    queuedInputs.push_back(inputs);
    
    double* outputs = new double[nOutputsInLine];
    iter = Aoutputs.begin();
    for(int i = 0; i < nOutputsInLine; i++, iter++) {
        outputs[i] = *iter;
    }
    queuedOutputs.push_back(outputs);
}

void TrainingData::update() {
    const ushort nNewLinesToAdd = queuedOutputs.size();
    
    ushort nOldLinesToDelete = nNewLinesToAdd+nLines;
    nOldLinesToDelete *= nNewLinesToAdd;
    nOldLinesToDelete /= maxLines;
    if(nOldLinesToDelete > maxLines)nOldLinesToDelete = maxLines;
    
    list<double*>::iterator iter;
    
    double** newOutputss = new double*[nLines+nNewLinesToAdd-nOldLinesToDelete];
    for(int i = 0; i < nOldLinesToDelete; i++) {
        delete [] outputss[i];
    }
    for(int i = nOldLinesToDelete; i < nLines; i++) {
        newOutputss[i-nOldLinesToDelete] = outputss[i];
    }
    iter = queuedOutputs.begin();
    for(int i = nLines; i < nLines+nNewLinesToAdd; i++, iter++) {
        newOutputss[i-nOldLinesToDelete] = *iter;
    }
    queuedOutputs.clear();
    delete [] outputss;
    outputss = newOutputss;
    
    double** newInputss = new double*[nLines+nNewLinesToAdd-nOldLinesToDelete];
    for(int i = 0; i < nOldLinesToDelete; i++) {
        delete [] inputss[i];
    }
    for(int i = nOldLinesToDelete; i < nLines; i++) {
        newInputss[i-nOldLinesToDelete] = inputss[i];
    }
    iter = queuedInputs.begin();
    for(int i = nLines; i < nLines+nNewLinesToAdd; i++, iter++) {
        newInputss[i-nOldLinesToDelete] = *iter;
    }
    queuedInputs.clear();
    delete [] inputss;
    inputss = newInputss;
    
    nLines = nLines+nNewLinesToAdd-nOldLinesToDelete;
}

TrainingData::~TrainingData() {
    ushort nQueuedLines = queuedOutputs.size();
    list<double*>::iterator iterQueuedOutputs = queuedOutputs.begin();
    list<double*>::iterator iterQueuedInputs = queuedInputs.begin();
    for(int i = 0; i < nQueuedLines; i++, iterQueuedOutputs++, iterQueuedInputs++) {
        delete *iterQueuedOutputs;
        delete *iterQueuedInputs;
    }
    queuedOutputs.clear();
    queuedInputs.clear();
    
    for(int i = 0; i < nLines; i++) {
        delete []inputss[i];
        delete []outputss[i];
    }
    delete []inputss;
    delete []outputss;
}
