#include <iostream>
#include <string>
#include "Errors.h"
#include "Map.h"
#include "Dijkstra.h"
using namespace std;

int main()
{
	setlocale(0, "Russian");
	map_rb_tree <string, map_data>*adjacency_list = new map_rb_tree <string, map_data>;
	string full_name = "C:\\Авиарейсы2.txt";
	file_to_map(adjacency_list, full_name);
	(adjacency_list)->output_adjacency_list();
	string from_city = "Санкт-Петербург", to_city = "Вологда";
	int final_price = dijkstra(adjacency_list, from_city, to_city);
	cout <<"Перелёт из города "<<from_city<<" в город "<< to_city<<" : "<< final_price<<endl << endl;
	system("pause");
	return 0;
}