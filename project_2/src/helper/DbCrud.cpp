// https://www.geeksforgeeks.org/csv-file-management-using-c/

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <typeinfo>
#include <vector>

#include "DbCrud.hpp"


namespace DataBase
{
	auto DbCrud::create_record(Entities::BaseEntity &e, std::string filename) noexcept -> cpp::result<bool, std::string>
	{
		// file pointer
		std::fstream fout;

		auto csv_str = e.parse_to_csv();

		try
		{
			// opens an existing csv file or creates a new file.
			fout.open(filename, std::ios::out | std::ios::app);

			fout << csv_str << std::endl;
		}
		catch (const std::ifstream::failure &e)
		{
			fout.close();
			return cpp::fail(e.what());
		}

		fout.close();

		return true;
	}

	auto DbCrud::read_records(std::vector<std::unique_ptr<Entities::BaseEntity>> &e, Entities::BaseEntity &source, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string>
	{
		if (match_func == nullptr)
		{
			return cpp::fail("No match function provided\n");
		}

		// File pointer
		std::fstream fin;

		// Open an existing file
		try
		{
			fin.open(filename, std::ios::in);
		}
		catch (const std::exception &e)
		{
			fin.close();
			return cpp::fail(e.what());
		}

		// Read the Data from the file
		// as std::string Vector
		std::vector<std::string> row;
		std::string line, word, temp;
		bool has_values = false;

		while (fin >> line)
		{

			row.clear();

			// read an entire row and
			// store it in a std::string variable 'line'
			//getline(fin, line);

			// used for breaking words
			std::stringstream s(line);

			// read every column data of a row and
			// store it in a std::string variable, 'word'
			while (getline(s, word, source.delimiter))
			{

				// add all the column data
				// of a row to a vector
				row.push_back(word);
			}

			// convert std::string to integer for comparision
			// roll2 = stoi(row[0]);
			int index = 0;
			std::unique_ptr<Entities::BaseEntity> target(nullptr);
			auto parse_r = source.parse_from_csv(target, row, index);

			if(parse_r.has_error())
			{
				fin.close();
				return cpp::fail(parse_r.error());
			}

			auto read_result = match_func(*target, source);

			if (read_result.has_error())
			{
				fin.close();
				return cpp::fail(read_result.error());
			}

			if (read_result.value() == true)
			{
				e.push_back(std::move(target));
				has_values = true;
			}
		}

		fin.close();
		return has_values;
	}

	auto DbCrud::read_all_records(std::vector<std::unique_ptr<Entities::BaseEntity>> &e, Entities::BaseEntity &source, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string>
	{
		if (match_func == nullptr)
		{
			return cpp::fail("No match function provided\n");
		}

		// File pointer
		std::fstream fin;

		// Open an existing file
		try
		{
			fin.open(filename, std::ios::in);
		}
		catch (const std::exception &e)
		{
			fin.close();
			return cpp::fail(e.what());
		}

		// Read the Data from the file
		// as std::string Vector
		std::vector<std::string> row;
		std::string line, word, temp;
		bool success = true;

		while (fin >> temp)
		{

			row.clear();

			// read an entire row and
			// store it in a std::string variable 'line'
			getline(fin, line);

			// used for breaking words
			std::stringstream s(line);

			// read every column data of a row and
			// store it in a std::string variable, 'word'
			while (getline(s, word, Entities::BaseEntity::delimiter))
			{

				// add all the column data
				// of a row to a vector
				row.push_back(word);
			}

			// convert std::string to integer for comparision
			// roll2 = stoi(row[0]);
			int index = 0;
			std::unique_ptr<Entities::BaseEntity> target(nullptr);
			auto parse_r = source.parse_from_csv(target, row, index);

			if(parse_r.has_error())
			{
				fin.close();
				return cpp::fail(parse_r.error());
			}

			auto read_result = match_func(*target, source);

			if (read_result.has_error())
			{
				fin.close();
				return cpp::fail(read_result.error());
			}

			if (read_result.value() == true)
			{
				e.push_back(std::move(target));
			}

		}

		fin.close();
		return true;
	}

	auto DbCrud::update_record(Entities::BaseEntity &e, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string>
	{
		if (match_func == nullptr)
		{
			return cpp::fail("No match function provided\n");
		}

		// File pointer
		std::fstream fin;
		try
		{
			fin.open(filename, std::ios::in);
		}
		catch (const std::exception &e)
		{
			fin.close();
			return cpp::fail(e.what());
		}

		// Create a new file to store updated data

		int rollnum, roll1, marks, count = 0, i;
		char sub;
		int index, new_marks;
		std::string line, word;
		std::vector<std::string> row;
		std::vector<std::string> updated_file_rows;
		bool updated = false;

		// Traverse the file
		while (!fin.eof())
		{

			row.clear();

			getline(fin, line);
			std::stringstream s(line);

			while (getline(s, word, e.delimiter))
			{
				row.push_back(word);
			}

			int index = 0;
			std::unique_ptr<Entities::BaseEntity> target(nullptr);
			auto parse_r = e.parse_from_csv(target, row, index);

			if(parse_r.has_error())
			{
				fin.close();
				return cpp::fail(parse_r.error());
			}

			auto read_result = match_func(*target, e);

			if(read_result.has_error()){
				fin.close();
				return cpp::fail(read_result.error());
			}

			if(read_result.value() == true)
			{
					updated_file_rows.push_back(e.parse_to_csv());
					updated = true;
			}
			else 
			{
				updated_file_rows.push_back(line);
			}
		}

		fin.close();

		if(!updated){
			return false;
		}

		std::fstream fout;
		try
		{
			fout.open(filename, std::ios::out);
		}
		catch (const std::exception &e)
		{
			fout.close();
			return cpp::fail(e.what());
		}

		// std::ofstream file_out("filename.txt");
		for (const auto &s : updated_file_rows)
		{
			fout << s << std::endl;
		}

		fout.close();
		return true;
	}

	auto DbCrud::delete_record(Entities::BaseEntity &e, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string>
	{
		if (match_func == nullptr)
		{
			return cpp::fail("No match function provided\n");
		}

		// File pointer
		std::fstream fin;
		try
		{
			fin.open(filename, std::ios::in);
		}
		catch (const std::exception &e)
		{
			fin.close();
			return cpp::fail(e.what());
		}

		int rollnum, roll1, marks, count = 0, i;
		char sub;
		int index, new_marks;
		std::string line, word;
		std::vector<std::string> row;
		std::vector<std::string> updated_file_rows;
		bool updated = false;

		// Check if this record exists
		// If exists, leave it and
		// add all other data to the new file
		while (!fin.eof())
		{

			row.clear();
			getline(fin, line);
			std::stringstream s(line);

			while (getline(s, word, e.delimiter))
			{
				row.push_back(word);
			}

			int index = 0;
			std::unique_ptr<Entities::BaseEntity> target(nullptr);
			auto parse_r = e.parse_from_csv(target, row, index);

			if(parse_r.has_error())
			{
				fin.close();
				return cpp::fail(parse_r.error());
			}

			auto read_result = match_func(*target, e);

			if(read_result.has_error()){
				fin.close();
				return cpp::fail(read_result.error());
			}

			if(read_result.value() == true)
			{
				//do nothing -> skipp line so it is deleted
				updated = true;
			}
			else 
			{
				updated_file_rows.push_back(line);
			}
		}

		fin.close();

		if(!updated){
			return false;
		}

		std::ofstream file_out(filename);
		for (const auto &s : updated_file_rows)
		{
			file_out << s << std::endl;
		}

		// Close the pointers
		file_out.close();
		return true;
	}
}
