#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "Errors.h"
#include "Map.h"
#include "List.h"

struct City_price
{
	string city;
	int price;
	City_price(string user_city, int user_price) { city = user_city; price = user_price;}
	City_price() {};
};

struct map_data
{
	int label; // shortest way to this city
	bool is_visited; // was this city processed or not
	list<City_price>* adjacency_list; // adjacency list for this city
	map_data() { label = INT_MAX; adjacency_list = new list<City_price>; is_visited = false; }
	map_data(list<City_price>* user_adjacency_list) {adjacency_list = user_adjacency_list; };
	~map_data() { adjacency_list = nullptr; };
};

ostream& operator<< (ostream& output_stream, City_price& a)
{
	cout << a.city << " - " << a.price;
	return output_stream;
}
ostream& operator<< (ostream& output_stream, map_data& a)
{
	cout << *(a.adjacency_list);
	return output_stream;
}

template<class T, class L> // creates map from text file with cities and prices
void file_to_map(map_rb_tree< T, L>* adjacency_list, string full_name_of_file)
{
	ifstream text_file;
	text_file.open(full_name_of_file);
	if (text_file.is_open())
	{	//	file is open an ready to work
		while (!text_file.eof())
		{
			string city_1 = "";
			string city_2 = "";
			string price_1 = "";
			string price_2 = "";
			int price_1_int;
			int price_2_int;
			// reading cities and prices
			char symbol;
			while ((symbol = text_file.get()) != ';')
				city_1 += symbol;
			while ((symbol = text_file.get()) != ';')
				city_2 += symbol;
			while ((symbol = text_file.get()) != ';')
				price_1 += symbol;
			while (((symbol = text_file.get()) != '\n') && (!text_file.eof()))
				price_2 += symbol;

			map_data first_city, second_city;
			node<string, map_data>* nod = new node<string, map_data>;
			nod = adjacency_list->find(city_1);
			if (price_1!="N/A") // flight there exists
			{
				price_1_int = atoi(price_1.c_str());
				City_price smth(city_2, price_1_int);
				list<City_price> *something = new list<City_price>;

				if (nod)
				{// flight exists, node exists
					first_city = adjacency_list->find_value(city_1);
					something = first_city.adjacency_list;
					something->push_back(smth);
					first_city.adjacency_list = something;
					adjacency_list->edit_data(city_1, first_city);
				}
				else
				{//flight exists, node doesnt exists
					something->push_back(smth);
					first_city.adjacency_list = something;
					adjacency_list->insert(city_1, first_city);
				}
			}
			else
			{
				if (!nod)
				{// flight there doesnt exist, nod doesnt exist
					adjacency_list->insert(city_1, first_city);
				}
			}
			nod = adjacency_list->find(city_2);
			if (price_2 != "N/A") // flight exists
			{
				price_2_int = atoi(price_2.c_str());
				City_price smth(city_1, price_2_int);
				list<City_price> *something = new list<City_price>;

				if (nod)
				{// flight exists, node exists
					second_city = adjacency_list->find_value(city_2);
					something = second_city.adjacency_list;
					something->push_back(smth);
					second_city.adjacency_list = something;
					adjacency_list->edit_data(city_2, second_city);
				}
				else
				{//flight exists, node doesnt exists
					something->push_back(smth);
					second_city.adjacency_list = something;
					adjacency_list->insert(city_2, second_city);
				}
			}
			else
			{
				if (!nod)
				{// flight doesnt exist, nod doesnt exist
					adjacency_list->insert(city_2, second_city);
				}
			}
			
			
		}
		text_file.close();
	}
	else throw File_is_not_open();

}

template<class T, class L> // returns the shortest way from requested city to another requested city
int dijkstra(map_rb_tree<T, L>* adjacency_list, string from_city, string to_city)
{
	list<string>* keys = adjacency_list->get_keys(); // list of cities
	node<T, L>* next = adjacency_list->find(from_city); // processed city
	size_t counter = 0;
	next->data.label = 0;
	do
	{	// moving throught the adjacency list for current city
		for (size_t i = 0; i < next->data.adjacency_list->get_size(); i++)
		{
			City_price copy = next->data.adjacency_list->at(i + 1);
			node<T, L>* current_city = adjacency_list->find(copy.city);
			if (current_city->data.label > next->data.label + copy.price)
			{//change the shortest way to city
				current_city->data.label = next->data.label + copy.price;
			}
		}
		next->data.is_visited = true;
		++counter;
		int min = INT_MAX;
		node<T, L>* current = nullptr;
		for (size_t i = 0; i < keys->get_size(); i++)
		{// find the city with the smallest way to it
			current = adjacency_list->find(keys->at(i + 1));
			if ((min > current->data.label) && !(current->data.is_visited))
			{
				next = current;
				min = next->data.label;
			}
		}
	} while (keys->get_size() != counter);
	return adjacency_list->find(to_city)->data.label;
}