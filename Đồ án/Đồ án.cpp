// Test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> 
#include <list> 
#include <iterator> 
#include<vector>
#include <cstdlib>
#include <ctime>
#include "Graph.h"

using namespace std;
int main()
{
    int n = 20;
    srand((int)time(NULL));
    int s = rand() % 20;
    int t = rand() % 20;
    // tạo đồ thị
    Graph g(n);
    g.addEdge(0, 1);
    g.addEdge(0, 7);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(2, 7);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 6);
    g.addEdge(6, 9);
    g.addEdge(7, 8);
    g.addEdge(7, 10);
    g.addEdge(8, 9);
    g.addEdge(8, 11);
    g.addEdge(9, 11);
    g.addEdge(10, 12);
    g.addEdge(11, 12);
    g.addEdge(12, 13);
    g.addEdge(12, 14);
    g.addEdge(14, 17);
    g.addEdge(14, 18);
    g.addEdge(15, 16);
    g.addEdge(16, 17);
    g.addEdge(18, 19);
    //ma trận kề chứa thời gian đi lại giữa 2 điểm
    int fx[20][20]= 
    {
        {0,		71,	0,		0,		0,		0,	0,		151,	0,		0,		0,		0,		0,		0,	0,		0,	0,	0,		0,	0}, //Oradea
        {71,	0,	75,		0,		0,		0,	0,		0,		0,		0,		0,		0,		0,		0,	0,		0,	0,	0,		0,	0}, //Zerind
        {0,		75,	0,		118,	0,		0,	0,		140,	0,		0,		0,		0,		0,		0,	0,		0,	0,	0,		0,	0}, //Arad
        {0,		0,	118,	0,		111,	0,	0,		0,		0,		0,		0,		0,		0,		0,	0,		0,	0,	0,		0,	0}, //Timisoare
        {0,		0,	0,		111,	0,		70,	0,		0,		0,		0,		0,		0,		0,		0,	0,		0,	0,	0,		0,	0}, //Lugoj
        {0,		0,	0,		0,		70,		0,	75,		0,		0,		0,		0,		0,		0,		0,	0,		0,	0,	0,		0,	0}, //Mehadia
        {0,		0,	0,		0,		0,		75,	0,		0,		0,		120,	0,		0,		0,		0,	0,		0,	0,	0,		0,	0},	//Drobeta
        {151,	0,	140,	0,		0,		0,	0,		0,		80,		0,		99,		0,		0,		0,	0,		0,	0,	0,		0,	0},	//Sibiu
        {0,		0,	0,		0,		0,		0,	0,		80,		0,		146,	0,		97,		0,		0,	0,		0,	0,	0,		0,	0},	//Rimnicu Vilcea
        {0,		0,	0,		0,		0,		0,	120,	0,		146,	0,		0,		138,	0,		0,	0,		0,	0,	0,		0,	0},	//Craiova
        {0,		0,	0,		0,		0,		0,	0,		99,		0,		0,		0,		0,		211,	0,	0,		0,	0,	0,		0,	0},	//Fagares
        {0,		0,	0,		0,		0,		0,	0,		0,		97,		138,	0,		0,		101,	0,	0,		0,	0,	0,		0,	0},	//Pitesti
        {0,		0,	0,		0,		0,		0,	0,		0,		0,		0,		211,	101,	0,		90,	85,		0,	0,	0,		0,	0},	//Bucharest
        {0,		0,	0,		0,		0,		0,	0,		0,		0,		0,		0,		0,		90,		0,	0,		0,	0,	0,		0,	0},	//Giurgiu
        {0,		0,	0,		0,		0,		0,	0,		0,		0,		0,		0,		0,		85,		0,	0,		0,	0,	142,	98,	0},	//Urziceni
        {0,		0,	0,		0,		0,		0,	0,		0,		0,		0,		0,		0,		0,		0,	0,		0,	87,	0,		0,	0},	//Neamt
        {0,		0,	0,		0,		0,		0,	0,		0,		0,		0,		0,		0,		0,		0,	0,		87,	0,	92,		0,	0},	//Iasi
        {0,		0,	0,		0,		0,		0,	0,		0,		0,		0,		0,		0,		0,		0,	142,	0,	92,	0,		0,	0},	//Vaslui
        {0,		0,	0,		0,		0,		0,	0,		0,		0,		0,		0,		0,		0,		0,	98,		0,	0,	0,		0,	86},//Hirsova
        {0,		0,	0,		0,		0,		0,	0,		0,		0,		0,		0,		0,		0,		0,	0,		0,	0,	0,		86,	0},	//Eforie

    };
    
    
    if (g.biDirSearch1(s, t,fx) == -1)
        cout << "khong tim thay duong giua "
        << s << " va " << t << "\n";

    return 0;
}
