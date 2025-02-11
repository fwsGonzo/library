#ifndef LIBRARY_CONFIG_HPP
#define LIBRARY_CONFIG_HPP

#include <unordered_map>
#include <string>

namespace library
{
class Config
{
public:
    Config() {}
    Config(const std::string& file);
    bool load(const std::string& file);

    template <typename T>
    auto get(const std::string& var, const T def)
    {
        auto it = kv.find(var);
        if (it == kv.end()) {
			if constexpr (std::is_same_v<T, const char*>)
				return std::string(def);
			else
				return def;
		}
		if constexpr (std::is_same_v<std::remove_cvref_t<T>, std::string> || std::is_same_v<T, const char*>)
			return it->second;
		else
			return static_cast<T>(std::stod(it->second));
    }

    void set(const std::string& key, const std::string& value)
    {
        if (kv.find(key) == kv.end()) { kv.insert(std::make_pair(key, value)); }
        else
            kv[key] = value;
    }

    template <typename T>
    void set(const std::string& key, T val)
    {
        set(key, std::to_string(val));
    }

private:
    std::unordered_map<std::string, std::string> kv;
};
} // namespace library

#endif
