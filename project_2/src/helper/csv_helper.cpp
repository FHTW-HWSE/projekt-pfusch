// https://www.geeksforgeeks.org/csv-file-management-using-c/

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <typeinfo>
#include <vector>

#include "Base.hpp"
#include "csv_helper.hpp"
#include "result.hpp"


namespace csv_helper
{
	auto create_record(std::unique_ptr<Entities::BaseEntity> &e, std::string filename) noexcept -> cpp::result<bool, std::string>
	{
		// file pointer
		std::fstream fout;

		auto write_r = e.get()->db_write_record();

		if (write_r.has_error())
		{
			return cpp::fail(write_r.error());
		}

		try
		{
			// opens an existing csv file or creates a new file.
			fout.open(filename, std::ios::out | std::ios::app);

			fout << write_r.value() << '\n';
		}
		catch (const std::ifstream::failure &e)
		{
			fout.close();
			return cpp::fail(e.what());
		}

		fout.close();

		return true;
	}

	auto read_records(std::vector<std::unique_ptr<Entities::BaseEntity>> &e, std::unique_ptr<Entities::BaseEntity> &source, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string>
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
			while (getline(s, word, source.get()->delimiter))
			{

				// add all the column data
				// of a row to a vector
				row.push_back(word);
			}

			// convert std::string to integer for comparision
			// roll2 = stoi(row[0]);
			int index = 0;

			auto read_result = match_func(source, row, index);

			if (read_result.has_error())
			{
				fin.close();
				return cpp::fail(read_result.error());
			}

			std::unique_ptr<Entities::BaseEntity> target(nullptr);


			if (read_result.has_value() && read_result.value() == true)
			{
				index = 0;
				auto read_result = source.get()->db_read_record(target, row, index);
				
				if(read_result.has_error()){
					fin.close();
					return cpp::fail(read_result.error());
				}

				if(read_result.value()){
					e.push_back(std::move(target));
					has_values = true;
				}
			}

			if (read_result.has_error())
			{
				fin.close();
				return cpp::fail(read_result.error());
			}
		}

		fin.close();
		return has_values;
	}

	auto read_all_records(std::vector<std::unique_ptr<Entities::BaseEntity>> &e, std::unique_ptr<Entities::BaseEntity> &source, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string>
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

			auto read_result = match_func(source, row, index);

			if (read_result.has_error())
			{
				fin.close();
				return cpp::fail(read_result.error());
			}

			if (read_result.value() == true)
			{
				std::unique_ptr<Entities::BaseEntity> target(nullptr);
				index = 0;

				auto r_read = source.get()->db_read_record(target, row, index);

				if(r_read.has_error()){
					fin.close();
					return cpp::fail(r_read.error());
				}

				if(r_read.value()){
					e.push_back(std::move(target));
				}
			}

		}

		fin.close();
		return true;
	}

	auto update_record(std::unique_ptr<Entities::BaseEntity> &e, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string>
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

			while (getline(s, word, e.get()->delimiter))
			{
				row.push_back(word);
			}

			int index = 0;
			auto match_result = match_func(e, row, index);

			if(match_result.has_error()){
				fin.close();
				return cpp::fail(match_result.error());
			}

			if(match_result.value()){
				auto db_write_r = e.get()->db_write_record();

				if(db_write_r.has_error()){
					fin.close();
					return cpp::fail(db_write_r.error());
				}
				else
				{
					updated_file_rows.push_back(db_write_r.value());
					updated = true;
				}
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

	auto delete_record(std::unique_ptr<Entities::BaseEntity> &e, std::string filename, Entities::BaseEntity::MATCH_FUNC match_func) noexcept -> cpp::result<bool, std::string>
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

			while (getline(s, word, e.get()->delimiter))
			{
				row.push_back(word);
			}

			auto match_result = match_func(e, row, index);

			if(match_result.has_error()){
				fin.close();
				return cpp::fail(match_result.error());
			}

			if(match_result.value()){
				auto db_write_r = e.get()->db_write_record();

				if(db_write_r.has_error()){
					fin.close();
					return cpp::fail(db_write_r.error());
				}

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
