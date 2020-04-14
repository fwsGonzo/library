#include <library/log.hpp>
#include <unistd.h>
#include <ctime>

using namespace std;

namespace library
{
Log logger;

Log::Log(std::string filename) : Log() {
	this->open(filename);
}

Log::~Log()
{
    // close file, if open
    this->file.close();
}

void Log::open(std::string filename)
{
    if (file.good()) file.close();
    // output logfile
    this->file.open(filename.c_str(), ios::app | ios::out);
}

Log& operator<<(Log& out, const Log::LogLevel level)
{
    if (level) // not ENDL
    {
        // add timestamp to log
        time_t rawtime;
        time(&rawtime);
        tm* t = gmtime(&rawtime);

		char buffer[256];
		const size_t len = std::strftime(
				buffer, sizeof(buffer), 
				"[%H:%M:%S] ", t);
        out.log.append(buffer, len);

        // add loglevel: symbol --> text
        switch (level) {
        case Log::INFO:
            out.log += "INFO: ";
            break;
        case Log::WARN:
            out.log += "WARN: ";
            break;
        case Log::ERR:
            out.log += "ERROR: ";
            break;
        case Log::ENDL:
            break;
        }
    }
    else // Log::log_level_t.ENDL
    {
        if (out.outputConsole) {
            // output to console, if enabled
			out.log.append("\n", 1);
            write(STDOUT_FILENO, out.log.c_str(), out.log.size());;
        }
        // output to file
        if (out.file.good())
			out.file << out.log << endl;
        out.log.clear();
    }
    // outgoing = incoming Log, for chaining
    return out;
}

} // namespace library
