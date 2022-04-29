#include <iostream>
#include <fstream>
#include <string>

#include <algorithm> // replace

std::string create_header(unsigned char* buffer, int size, std::string filename)
{
    std::string header;

	header.append("#pragma once\n\n");
    header.append("int " + filename + "_size = " + std::to_string(size) + ";\n\n");
    header.append("unsigned char " + filename + "[] = {");


    for (int i = 0; i < size; i++)
    {
        if (i % 16 == 0)
            header.append("\n\t");

		char hex_string[5];
		sprintf_s(hex_string, "0x%02X", buffer[i]);

        header.append(hex_string);

        if (i != size - 1)
            header.append(", ");
    }

    header.append("\n};");
    return header;
}

std::string base_name(std::string const& path)
{
	return path.substr(path.find_last_of("/\\") + 1);
}
std::string remove_extension(std::string const& filename)
{
	auto pos = filename.find_last_of('.');
    if (pos > 0 && pos != std::string::npos)
        return filename.substr(0, pos);
    else
       filename;
}

std::string space2underscore(std::string text)
{
	std::replace(text.begin(), text.end(), ' ', '_');
	return text;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
        return -1;

    std::string file_path = argv[1];
    std::string file_name = space2underscore(remove_extension(base_name(file_path)));

    //Read file into buffer
    std::ifstream input_file(file_path, std::ios::binary | std::ios::ate);
	int file_size = input_file.tellg(); // warning: streampos is 8 byte value
    unsigned char* buffer = new unsigned char[file_size];
    input_file.seekg(0, std::ios::beg);
    input_file.read((char*)buffer, file_size);
    input_file.close();

    // Write array to file
    std::ofstream  output_file(file_name + ".h");
    output_file << create_header(buffer, file_size, file_name);
    output_file.close();

    return 0;
}