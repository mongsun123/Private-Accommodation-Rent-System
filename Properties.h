#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;


struct Property {
    int ads_id;
    string prop_name;
    string completion_year;
    string monthly_rent;
    string location;
    string property_type;
    string rooms;
    string parking;
    string bathroom;
    string size;
    string furnished;
    vector<string> facilities;
    vector<string> additional_facilities;
    string region;
    Property* prev, * next; // add prev and next pointers

    Property* left;   // left child for BST
    Property* right;  // right child for BST

    Property() : left(nullptr), right(nullptr), prev(nullptr), next(nullptr) {} //This list initializes the pointers to nullptr whenever a new instance of Property is created.
};

vector<string> split(const string& s, char delimiter);
vector<string> splitBST(const string& s, char delimiter);
Property* read_csv(string filename);
void printPropertiesForFilter(Property* head);
Property* linearSearchProperty(Property* head, int ads_id);
Property* mergeSort(Property* head);
Property* split(Property* head, int step);
Property* merge(Property* tail, Property* left, Property* right);
void displayProperties(Property* head);
void bubbleSort(Property* head);
void swap(Property* a, Property* b);
void postOrder(Property* root);
void inOrder(Property* root);
void preOrder(Property* root);
void printProperty(Property* prop);
Property* findMinValueNode(Property* root);
Property* bstSearch(Property* root, int ads_id);
Property* bstInsert(Property* root, Property prop);
Property* read_csvBST(string filename);
#endif
