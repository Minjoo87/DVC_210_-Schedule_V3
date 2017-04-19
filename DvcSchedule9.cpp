// Programmer: Minjoo Kim
// Programmer's ID: 1581736

#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;

#include <cstring> // for strtok and strcpy

#include "AssociativeArray.h"
#include "DynamicArray.h"

int main(){
    cout << "Programmer: Minjoo Kim\n";
    cout << "Programmer's ID: 1581736\n";
    cout << "File: " << __FILE__ << endl;
    
    // for parsing the inputfile
    char* token;
    char buf[1000];
    const char* const tab = "\t";
    
    // open the input file
    ifstream fin;
    fin.open("dvc-schedule.txt");
    if (!fin.good()) throw "I/O error";
    
    AssociativeArray<string, AssociativeArray<string, bool> > alreadySeenAssociativeArray;
    AssociativeArray<string, AssociativeArray<string, int> > subjectAssociativeArray;
    
    
    int duplicates = 0;
    
    // read the input file
    while (fin.good()){
        
        // read the line
        string line;
        getline(fin, line);
        strcpy(buf, line.c_str());
        if (buf[0] == 0) continue; // skip blank lines
        
        // parse the line
        const string term(token = strtok(buf, tab));
        const string section((token = strtok(0, tab)) ? token : "");
        const string course((token = strtok(0, tab)) ? token : "");
        const string instructor((token = strtok(0, tab)) ? token : "");
        const string whenWhere((token = strtok(0, tab)) ? token : "");
        if (course.find('-') == string::npos) continue; // invalid line: no dash in course name
        
        const string subjectCode(course.begin(), course.begin() + course.find('-'));
        
        if (alreadySeenAssociativeArray[term].containsKey(section)){
            duplicates++;
        }
        else{
            alreadySeenAssociativeArray[term][section] = true;
            subjectAssociativeArray[subjectCode][course]++;
        }
    }
    
    fin.close();
    
    DynamicArray<string> subjectDynamicArray;
    queue<string> tempQueue = subjectAssociativeArray.keys();
    for(unsigned int i = 0; !tempQueue.empty(); i++){
        subjectDynamicArray[i] = tempQueue.front();
        tempQueue.pop();
    }
    
    for(int i = 0; i < subjectDynamicArray.capacity(); i++){
        for(int j = i + 1; j < subjectDynamicArray.capacity(); j++){
            if(subjectDynamicArray[i] > subjectDynamicArray[j]){
                swap(subjectDynamicArray[i], subjectDynamicArray[j]);
            }
        }
    }
    
    for(int i = 0; i < subjectAssociativeArray.size(); i++){
        
        DynamicArray<string> courseDynamicArray;
        tempQueue = subjectAssociativeArray[subjectDynamicArray[i]].keys();
        for(unsigned int i = 0; !tempQueue.empty(); i++){
            courseDynamicArray[i] = tempQueue.front();
            tempQueue.pop();
        }
        
        for(int x = 0; x < subjectAssociativeArray[subjectDynamicArray[i]].size(); x++){
            for(int y = x + 1; y < subjectAssociativeArray[subjectDynamicArray[i]].size(); y++){
                if(courseDynamicArray[x] > courseDynamicArray[y]){
                    swap(courseDynamicArray[x], courseDynamicArray[y]);
                }
            }
        }
        
        if(subjectDynamicArray[i] != "" && (subjectAssociativeArray[subjectDynamicArray[i]].size()) > 0){
            cout << subjectDynamicArray[i] << ", " << subjectAssociativeArray[subjectDynamicArray[i]].size() << " course(s)" << endl;
        }
        for(int j = 0; j < subjectAssociativeArray[subjectDynamicArray[i]].size(); j++){
            cout << "  " + courseDynamicArray[j] << ", " + to_string(subjectAssociativeArray[subjectDynamicArray[i]][courseDynamicArray[j]]) << " section(s)" << endl;
            
        }
    }
    
    cout  << "Number of duplicates: " << duplicates << endl;
}
