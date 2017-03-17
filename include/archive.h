#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <map>
#include <fstream>
#include <string>
#include <non_copyable.h>

class Archive : public NonCopyable
{
public:
    struct Entry
    {
        uint64_t    offset;
        uint64_t    size;
    };

    Archive();
    ~Archive();

    void            open(const char* path);
    void            close();
    size_t          read(char* dst, const char* path) const;

private:
    std::map<std::string, Entry>    _entries;
    std::ifstream                   _stream;
    size_t                          _header_size;
};

#endif
