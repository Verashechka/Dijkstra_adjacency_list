#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include"E:\Вера\учёба\АиСД\4 семестр\Dijkstra_adjacency_list\Dijkstra_adjacency_list\Dijkstra.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Is_map_empty)
		{
			string name_of_file = "C:\\Авиарейсы2.txt";
			map_rb_tree <string, map_data>*adjacency_list = new map_rb_tree <string, map_data>;
			file_to_map(adjacency_list, name_of_file);
			Assert::AreEqual(false, adjacency_list->is_empty());
		}
		TEST_METHOD(Is_size_of_map_right)
		{	// there are 4 different cities in file, so size of map must be 4
			string name_of_file = "C:\\Авиарейсы2.txt";
			map_rb_tree <string, map_data>*adjacency_list = new map_rb_tree <string, map_data>;
			file_to_map(adjacency_list, name_of_file);
			Assert::AreEqual(size_t(4),adjacency_list->get_size());
		}
		TEST_METHOD(way_doesnt_exist_is_way_max)
		{	// dijkstra must return max of int, because there's no way from ufa to moscow
			string name_of_file = "C:\\Авиарейсы2.txt", from_city = "Уфа", to_city = "Москва";
			map_rb_tree <string, map_data>*adjacency_list = new map_rb_tree <string, map_data>;
			int final_price , maximum = INT_MAX;
			try
			{
				
				file_to_map(adjacency_list, name_of_file);
			}
			catch (...)
			{
			}
			Assert::AreEqual(maximum, final_price=dijkstra(adjacency_list,from_city,to_city));
		}
		TEST_METHOD(way_exists_is_price_correct)
		{	// 
			string name_of_file = "C:\\Авиарейсы2.txt", from_city = "Санкт-Петербург", to_city = "Вологда";
			map_rb_tree <string, map_data>*adjacency_list = new map_rb_tree <string, map_data>;
			file_to_map(adjacency_list, name_of_file);

			int final_price = dijkstra(adjacency_list, from_city, to_city);
			Assert::AreEqual(70, final_price);
		}
	};
}