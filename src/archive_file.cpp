#include <archive_file.h>
#include <archive.h>

ArchiveFile::ArchiveFile() : _data(nullptr), _size(0), _cursor(0)
{

}

ArchiveFile::~ArchiveFile()
{
    close();
}

void ArchiveFile::open(Archive& archive, const char* path)
{

}

void ArchiveFile::close()
{
    delete _data;
    _data = nullptr;
    _size = 0;
    _cursor = 0;
}


void ArchiveFile::read(char* dst, size_t size)
{
    memcpy(dst, _data + _cursor, size);
    _cursor += size;
}
