#include <iostream>
#include "console.h"
#include "filelib.h"
#include "random.h"
#include "vector.h"
#include "map.h"
#include "simpio.h"
#include "stdlib.h"
#include "strlib.h"
#include <string>

using namespace std;

void WelcomeMessages();
int Ninput();
void mapCreation(string filename, Map <Vector<string>, Vector<string>> &map);
void RandomTxtGen();
int total_Num_Input(int N);

int main() {
    WelcomeMessages();
    RandomTxtGen();
    return 0;
}
void WelcomeMessages(){
    cout << "Welcome to CS 106B/X Random Writer('N-Grams')!" << endl;
    cout << "This program generates random text based on a document." << endl;
    cout << "Give me an input file and an 'N' value for groups" << endl;
    cout << "of words, and I'll create random text for you" << endl;
    cout << " " << endl;
}

// create the map based on the input of N
void mapCreation(string filename, Map <Vector<string>, Vector<string>> &Nmap, int& N){
     ifstream input;
     string prompt, reprompt, word;
     Nmap = {};
     Vector<string> buffer, window, values;
     filename = promptUserForFile(input, prompt = "Input file name? ", reprompt);
     N = Ninput();
     int length = 0;
     while (input >> word){
         length ++;
         if (length < N){
             window.add(word);
             buffer.add(word);
          }
         else {
             if (Nmap.containsKey(window)){
                 Nmap.put(window,Nmap.get(window)+word);
                 window.remove(0);
                 window.add(word);
             }
             else {
                 values.clear();
                 values.add(word);
                 Nmap.put(window, values);
                 window.remove(0);
                 window.add(word);
             }
         }
     }
// The map should wrap around
     for (int k = 0; k < N-1; k++){
         if (Nmap.containsKey(window)){
             Nmap.put(window,Nmap.get(window)+buffer[k]);
             window.remove(0);
             window.add(buffer[k]);
         }
         else {
             values.clear();
             values.add(buffer[k]);
             Nmap.put(window, values);
             window.remove(0);
             window.add(buffer[k]);
         }
     }
     input.close();
}

int Ninput(){
    string prompt = "Value of N? ";
    string reprompt;
    int n = getInteger(prompt, reprompt);
    while (n < 2){
        reprompt = "The value you input should be larger than 1, please try again ";
        cout << reprompt << endl;
        n = getInteger(prompt);
    }
    return n;
}

// Generate random text based on the input of user
void RandomTxtGen(){
    int index, N, totalNum;
    Vector<string> window, currOutput, suffix;
    Vector<Vector <string>> prefix;
    Map<Vector<string>, Vector<string>> genMap;
    string  filename, output;
    mapCreation(filename, genMap, N);
    totalNum = total_Num_Input(N);
    while (totalNum) {
        index = randomInteger(0,genMap.size()-1);
        prefix = genMap.keys();
        window = prefix[index];
        currOutput = window;
        for (int i = 0; i < totalNum-N+1; i++){
            suffix = genMap.get(window);
            index = randomInteger(0, suffix.size()-1);
            currOutput.add(suffix[index]);
            window.remove(0);
            window.add(suffix[index]);
        }
        for (int i = 0; i < currOutput.size(); i++){
            output += currOutput[i];
            output += " ";
        }
        cout << "..." << output << "..." << endl;
        cout << " " <<endl;
        output.clear();
        totalNum = total_Num_Input(N);
    }
}

// Input the number of words you want to generate
int total_Num_Input(int N){
    cout << " " << endl;
    string prompt = "# of random words to generate (0 to quit)?  ";
    string reprompt;
    int totalNum = getInteger(prompt, reprompt);
    while (totalNum < N && totalNum > 0){
        reprompt = "The Number of random txt should be at least equal to N";
        cout << reprompt << endl;
        totalNum = getInteger(prompt);
    }
    if (totalNum == 0){
        cout << "Exiting." << endl;
        exit(0);
    }
    return totalNum;
}
