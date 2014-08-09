#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <map>
#include <string>
#include <sstream>

namespace library
{
	class Config
	{
	public:
		Config() {}
		Config(const std::string& file);
		bool load(const std::string& file);
		
		template <typename T>
		T get(const std::string& var, const T def)
		{
			// if variable is not found in hashmap, return default
			if (kv.find(var) == kv.end()) return def;
			// initialize result to default value
			T result;
			std::stringstream convert(kv[var]);
			// if the conversion fails, return default
			if (!(convert >> result)) return def;
			// return converted type T
			return result;
		}
		
		template <typename T>
		void set(const std::string& key, T val)
		{
			std::string value = std::to_string(val);
			if (kv.find(key) == kv.end()) 
			{
				kv.insert(
					std::make_pair(key, value)
				);
			}
			else kv[key] = value;
		}
	private:
		std::map<std::string, std::string> kv;
	};
}

#endif
