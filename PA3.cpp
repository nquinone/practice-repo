/*
 * Copyright (c) 2009-2010, Oracle and/or its affiliates. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Oracle nor the names of its contributors
 *   may be used to endorse or promote products derived from this software without
 *   specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <string>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <deque>
#include <vector>
#include "PA3.h"
using namespace std;
deque<string> fileIntoLines(string filePath); //pulls out file data into traversable deque
string userFilePath(); // Prompts user for file path
string delSpaces(string &str); // Deletes whitespace
bool is_number(const string &s2); // Checks to see if a string a number, so it can be later classified as a constant
bool is_lowercase(string str); // Checks to see if string is all lowercase so it can be late classified as an identifier
void printVector(vector <string> input); // Method to print our vectors
int depthOfNest(vector <string> keyword); // Finds depth of for loops
void analysis(vector< vector<string> > final_Vector); // Where we call our printVector and look for error/ print error messages
vector <vector<string> > tokenize(deque<string>fileIntoLines); //Form our vectors with their respective info

int main() {
    string filePath;
    
    filePath=userFilePath();
    
    deque<string> file_into_lines = fileIntoLines(filePath);
    
    vector < vector<string> > resultantVector= tokenize(file_into_lines);
    
    analysis(resultantVector);
    
    return 0;
}

string userFilePath(){
    
    string entryFile;
    
    cout<<"Please enter the file path: "<< endl;
    cin>>entryFile;
    return entryFile;
    
}

deque<string> fileIntoLines(string filePath){
    
    string line;
    deque<string> fileToLines;
    ifstream intofile;
    
    intofile.open(filePath.c_str());
    
    //Traversing through the file and pushing that info onto our deque
    if(intofile.is_open()){
        
        while(getline(intofile,line)){
            
            fileToLines.push_back(line);
        }
        intofile.close();
    }
    else{
        cout<<"Error: File was not readable!"<<endl;
        exit(1);
        
    }
    return fileToLines;
    
}

vector < vector<string> > tokenize(deque<string>fileIntoLines){
    
    //The below lists are the sets by which we restrict our classification of data in the file
    vector<string> delimiter_list;
    delimiter_list.push_back(";");
    delimiter_list.push_back(")");
    delimiter_list.push_back("(");
    delimiter_list.push_back(",");
    
    vector<string> keyword_list;
    keyword_list.push_back("BEGIN");
    keyword_list.push_back("END");
    keyword_list.push_back("FOR");
    
    // Important to note: in operator list must place ++, --, == operators befor +, -, = operators since
    // when we iterate through the file lines we will see a + first and not the ++ operator thus we would
    // add the + operator followed by another + operator instead of the ++ operator
    
    vector<string> operator_list;
    operator_list.push_back("++");
    operator_list.push_back("--");
    operator_list.push_back("==");
    operator_list.push_back("=");
    operator_list.push_back("*");
    operator_list.push_back("-");
    operator_list.push_back("+");
    operator_list.push_back("<");
    operator_list.push_back(">");
    operator_list.push_back("||");
    operator_list.push_back("&&");
    operator_list.push_back("!");
    operator_list.push_back("/");
    
    vector<string> found_operator_list;
    vector<string> found_delimiter_list;
    vector<string> found_constant;
    vector<string> found_error;
    vector<string> found_identifier_list;
    vector<string> found_keyword_list;
    
    
    
    
    
    // Runs through file contents
    while(!fileIntoLines.empty()){
        
        string current_line= fileIntoLines.front();
        
        for (int i=0 ;i<operator_list.size();i++){
            
            string token = operator_list.at(i);
            
            //Iterates through line till end of string (Assuming operator is found)
            while(current_line.find(token)!= string::npos){
                //Adds operator to list of found operators, removes it from string
                //by replacing it with empty string
                found_operator_list.push_back(token);
                // Instead of empty string we want to replace it with a space so that
                // identifiers aren't concatenated together (i.e. if we have sum=sum-i+j
                // the identifier sumsumij would be add to the vector instead of sum, i, j)
                current_line.replace(current_line.find(token),token.length()," ");
                
            }
            
        }
        
        //Populating the keyword vector
        for (int i=0; i<keyword_list.size(); i++){
            
            string token=keyword_list.at(i);
            
            while(current_line.find(token)!= string::npos){
                
                found_keyword_list.push_back(token);
                current_line.replace(current_line.find(token),token.length(),"");
            }
        }
        
        //Populating the delimiter vector
        for(int i=0; i<delimiter_list.size();i++){
            
            string token=delimiter_list.at(i);
            
            while(current_line.find(token)!=string::npos){
                
                found_delimiter_list.push_back(token);
                current_line.replace(current_line.find(token),token.length(),"");
                
            }
            
        }
        //Finds errors (syntax like writing BEGAN instead of BEGIN)
        
        istringstream ss(current_line);
        
        string token2;
        
        // going through lines of file not yet classified and throwing them onto the
        // found error vector
        while(getline(ss, token2,' ')){
            
            string str2 = delSpaces(token2);
            
            if(find(found_error.begin(), found_error.end(), str2) == found_error.end()){
                
                found_error.push_back(str2);
                
            }
        }
        
        fileIntoLines.pop_front();
    }
    // Incase of empty error
    found_error.erase(remove(found_error.begin(),found_error.end(),""),found_error.end());
    
    // we originally push all values not classified yet(i.e. if its not a delimiter, keyword, or
    // operator) here we pull out values that are either a constant or an identifier and push
    // them on to their respective vectors
    for(int i=0;i<found_error.size();i++){
        string element=found_error.at(i);
        
        if(is_number(element)){
            
            found_constant.push_back(element);
            
            found_error.at(i) = "FOUND";
        }
        if(is_lowercase(element) && !is_number(element)){
            
            found_identifier_list.push_back(element);
            
            found_error.at(i) = "FOUND";
            
        }
    }
    //Remove the errors we found from our error list
    found_error.erase(remove(found_error.begin(), found_error.end(), "FOUND"), found_error.end());
    
    //Combine all our vectors
    
    vector< vector<string> > final_Vector;
    final_Vector.push_back(found_keyword_list);
    final_Vector.push_back(found_operator_list);
    final_Vector.push_back(found_identifier_list);
    final_Vector.push_back(found_constant);
    final_Vector.push_back(found_error);
    final_Vector.push_back(found_delimiter_list);
    return final_Vector;
}

bool is_number(const string &s2){
    
    string::const_iterator iter = s2.begin();
    // iterating through string to check if it is a number
    while(iter!=s2.end() && isdigit(*iter)){
        ++iter;
        
        
    }
    return !s2.empty() && iter==s2.end();
}

bool is_lowercase(string s){
    bool isLowercase;
    //looping through string to determine if it is lowercase
    for(int i=0;i<s.length();i++){
        if(islower(s[i])){
            isLowercase=true;
            
        }
        else
            return false;
        
    }
    return isLowercase;
    
}
string delSpaces(string &str){
    
    // Remove all Kinds of Whitespace
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    str.erase(remove(str.begin(), str.end(), '\t'), str.end());
    str.erase(remove(str.begin(), str.end(), '\n'), str.end());
    str.erase(remove(str.begin(), str.end(), '\v' ), str.end());
    str.erase(remove(str.begin(), str.end(), '\f'), str.end());
    str.erase(remove(str.begin(), str.end(), '\r'), str.end());
    return str;
    
}

void printVector(vector <string> input){
    //takes some input vector, then prints
    for(int i=0;i<input.size();i++){
        
        cout<<input.at(i)<<" ";
    }
    cout<<endl;
}

void analysis(vector< vector<string> > final_Vector){
    // Reassign our vectors for keyword etc, to this new storage
    vector <string> found_keyword_list = final_Vector[0];
    vector <string> found_operator_list = final_Vector[1];
    vector <string> found_identifier_list = final_Vector[2];
    vector <string> found_constant = final_Vector[3];
    vector <string> found_error = final_Vector[4];
    vector <string> found_delimiter_list = final_Vector[5];
    
    //Create a separate storage space for these vectors
    vector <string> specialKeyword= found_keyword_list;
    vector <string> specialOperator= found_operator_list;
    vector <string> specialIdentifier= found_identifier_list;
    vector <string> specialConstant= found_constant;
    vector <string> specialError= found_error;
    vector <string> specialDelimiter= found_delimiter_list;
    
    //Makes each vector unique (removing data if already in vector)
    sort(specialKeyword.begin(), specialKeyword.end());
    specialKeyword.erase( unique(specialKeyword.begin(), specialKeyword.end()), specialKeyword.end());
    
    sort(specialOperator.begin(), specialOperator.end());
    specialOperator.erase( unique(specialOperator.begin(), specialOperator.end()), specialOperator.end());
    
    sort(specialIdentifier.begin(), specialIdentifier.end());
    specialIdentifier.erase( unique(specialIdentifier.begin(), specialIdentifier.end()), specialIdentifier.end());
    
    sort(specialConstant.begin(), specialConstant.end());
    specialConstant.erase( unique(specialConstant.begin(), specialConstant.end()), specialConstant.end());
    
    sort(specialError.begin(), specialError.end());
    specialError.erase( unique(specialError.begin(), specialError.end()), specialError.end());
    
    sort(specialDelimiter.begin(), specialDelimiter.end());
    specialDelimiter.erase( unique(specialDelimiter.begin(), specialDelimiter.end()), specialDelimiter.end());
    
    int nestDepth = depthOfNest(found_keyword_list);
    //Output of desired information
    cout<<"The depth of the nested loop is: "<<nestDepth<<endl;
    cout<<"Keywords: ";
    printVector(specialKeyword);
    cout<<"Identifiers: ";
    printVector(specialIdentifier);
    cout<<"Constant: ";
    printVector(specialConstant);
    cout<<"Operators: ";
    printVector(specialOperator);
    cout<<"Delimiters: ";
    printVector(specialDelimiter);
    
    //Printing errors
    for(int i=0;i<specialError.size();i++){
        
        cout<<"Syntax Error(s): "<<specialError.at(i)<<endl;
    }
    // Symmetry for begin/end analysis
    int loopCount=0;
    int endCount=0;
    int beginCount=0;
    for(int i=0;i<found_keyword_list.size();i++){
        string current=found_keyword_list.at(i);
        
        if(current=="FOR"){
            
            loopCount++;
        }
        if(current=="BEGIN"){
            
            beginCount++;
        }
        if(current=="END"){
            
            endCount++;
        }
        
    }
    //Number of loops dont match number of Begin's
    if(beginCount!=endCount){
        
        if(loopCount!=beginCount){
            
            if(loopCount>beginCount){
        
                cout<<"Missing "<<loopCount-beginCount<<" BEGIN statements!";
                cout<<endl;
            }
            if(loopCount<beginCount){
                
                cout<<beginCount-loopCount<<" too many BEGIN statements";
                cout<<endl;
            
                }
                
            }
        //Number of loops dont match number of END's
        if(loopCount!=endCount){
            
            if(loopCount>endCount){
                
                cout<<"Missing "<<loopCount-endCount<<" END statements";
                cout<<endl;
                
                }
            if(loopCount<endCount){
                
                cout<<endCount-loopCount<<" too many END statements";
                cout<<endl;
            }
            }

        }
    //BEGIN/END statements match but do not match number of loops
    if(beginCount!=loopCount && beginCount==endCount){
        
        cout<<"Not enough loops for BEGIN/END statements!";
        cout<<endl;
    }
        
    
    
}
int depthOfNest(vector <string> keyword){
    //Assumption: we count every loop inside of some intial loop hence we start our initial
    // values at -1 since the first for we enter would be loop 0
    int maxDepth=-1;
    int depth=-1;
    
    for( int i=0;i<keyword.size();i++){
        string word= keyword.at(i);
        if(word=="FOR"){
            depth++;
        }
        if(word=="END"){
            if(depth>maxDepth){
                
                maxDepth=depth;
            }
            depth--;
        }
        
    }
    //To make sure we have the maximum depth on our last iteration of the loop
    if(maxDepth<depth){
        maxDepth=depth;
        
    }
    return maxDepth;
}