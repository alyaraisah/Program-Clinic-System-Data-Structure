#pragma once

#include<string>
#include<iostream>
#include<string.h>
#include<fstream>
#include<vector>
#include"struct.cpp"
using namespace std;

void add_patient(Queue& Q);
void add_items(Order_Treatment* &items);
void printOrder(Orders* front);
void served(Queue &Q, Orders* &Served, Complete* &Completed);
void printComplete(Complete* head);
void printCSV(csv* head);
void readCSV();
bool file_exists(const std::string& str);
void createCSV(csv* head);
void completeOrder(Complete* head, csv* &added);
void update(Queue &Q);
void deleteOrder(Queue &Q, Orders* &deletion);
void undo_order(Queue& Q, Orders* &deletion);

