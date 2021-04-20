#include <iostream>
#include <fstream>
#include <filesystem>

#include <Windows.h>

#include "JSONBuilder.h"
#include "JSONParser.h"
#include "Constants.h"

#pragma comment (lib, "JSON.lib")

using namespace std;

void createSettingsFile();

string readJSON();

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		cout << "GenerateDocumentation.exe must be started from cmd with <build configuration name> <WebFramework version>" << endl;

#ifdef NDEBUG
		system("pause");
#endif // _NDEBUG
	}

	if (!filesystem::exists(settingsFile))
	{
		createSettingsFile();
	}

	auto it = find(buildConfigurations.begin(), buildConfigurations.end(), argv[1]);
	json::JSONParser settings(readJSON());
	const unique_ptr<json::utility::jsonParserStruct>& root = settings.get<unique_ptr<json::utility::jsonParserStruct>>(jsonRootName);

	if (it != buildConfigurations.end() && get<bool>(root->data.at(*it)))
	{
		ostringstream command;

		command << "(TYPE Doxyfile & ECHO PROJECT_NUMBER=" << argv[2] << ") | doxygen.exe -";

		system(command.str().data());
	}
	else
	{
		cout << "Can't find this build configuration " << argv[1] << endl;
	}

#ifdef NDEBUG
	system("pause");
#endif // NDEBUG

	return 0;
}

void createSettingsFile()
{
	json::JSONBuilder builder(CP_OEMCP);
	unique_ptr<json::utility::jsonBuilderStruct> root(new json::utility::jsonBuilderStruct());
	ofstream out(settingsFile);

	for (const auto& i : buildConfigurations)
	{
		root->data.push_back({ i, false });
	}

	builder[jsonRootName] = move(root);

	out << builder;
}

string readJSON()
{
	ifstream in(settingsFile);
	string result;
	string tem;

	if (!in.is_open())
	{
		cout << "Can't find " + settingsFile << endl;

		exit(-1);

#ifdef NDEBUG
		system("pause");
#endif // NDEBUG
	}

	while (getline(in, tem))
	{
		result += tem;
	}

	return result;
}
