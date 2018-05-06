#include <hack/archive_file.h>
#include <hack/archive.h>

ArchiveFile::ArchiveFile() : _data(nullptr), _size(0), _cursor(0)
{

}

ArchiveFile::~ArchiveFile()
{
    close();
}

void ArchiveFile::open(const Archive& archive, const char* path)
{
    close();
    _size = archive.read(nullptr, path);
    _data = new char[_size];
    archive.read(_data, path);
}

void ArchiveFile::close()
{
    delete [] _data;
    _data = nullptr;
    _size = 0;
    _cursor = 0;
}


void ArchiveFile::read(char* dst, size_t size)
{
    memcpy(dst, _data + _cursor, size);
    _cursor += size;
}
