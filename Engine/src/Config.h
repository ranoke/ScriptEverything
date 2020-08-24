#pragma once
#include "Base.h"

#include <sstream>
#include <fstream>
#include <json.hpp>


class Config
{
public:
	Config()
	{
		{
			std::ifstream in(CONFIG_DIR"config.json");
			std::stringstream ss;
			ss << in.rdbuf();
			std::string src = ss.str();
			cfg = json::JSON::Load(src.c_str());
		}
	}
	~Config()
	{

	}

	inline json::JSON& GetJsonConfig() { return cfg; }

private:
	json::JSON cfg;
};

extern Config config;

#define cfg ::config.GetJsonConfig()