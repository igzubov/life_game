#include "fileVisualizer.h"


FileVisualizer::FileVisualizer(std::string fileName) : fileStream(fileName, std::ios_base::out){
}

// rewrite file
void FileVisualizer::showState(const intMatrix &state) {
    std::string outString = stateToString(state);
    fileStream << outString;
    fileStream.clear();
    fileStream.seekg(0, std::ios::beg);
}

std::string FileVisualizer::stateToString(const intMatrix &state) {
    std::string outString(1, ' ');
    for (int i = 0; i < state.at(0).size(); i++) {
        outString.append("_ ");
    }
    outString += '\n';
    for (int i = 0; i < state.size(); i++) {
        outString += '|';
        for (int j = 0; j < state.at(0).size(); j++) {
            if (state.at(i).at(j)) {
                outString += '*';
            }
            else {
                outString += ' ';
            }
            outString += '|';
        }
        outString += '\n';
    }
    outString += ' ';
    for (int i = 0; i < state.at(0).size(); i++) {
        outString.append("‾ ");
    }
    return outString;
}