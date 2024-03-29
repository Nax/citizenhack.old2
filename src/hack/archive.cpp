#include <hack/archive.h>

Archive::Archive()
{

}

Archive::~Archive()
{
    close();
}

void Archive::open(const char* path)
{
    uint64_t    entry_count;
    uint64_t    offset;
    uint64_t    size;
    uint64_t    name_size;
    char        name[4096];
    Entry       entry;

    _stream.open(path);
    _stream.read(reinterpret_cast<char*>(&entry_count), 8);
    _header_size = 8;
    for (size_t i = 0; i < entry_count; ++i)
    {
        _stream.read(reinterpret_cast<char*>(&offset), 8);
        _stream.read(reinterpret_cast<char*>(&size), 8);
        _stream.read(reinterpret_cast<char*>(&name_size), 8);
        _stream.read(name, name_size);
        name[name_size] = 0;
        _header_size += 24 + name_size;
        entry.size = size;
        entry.offset = offset;
        _entries[name] = entry;
    }
}

size_t Archive::read(char* dst, const char* path) const
{
    const auto entry = _entries.find(path);

    if (entry == _entries.cend())
        return 0;

    const Archive::Entry* e = &entry->second;

    if (dst)
    {
        _stream.seekg(_header_size + e->offset);
        _stream.read(dst, e->size);
    }
    return e->size;
}

void Archive::close()
{

}
