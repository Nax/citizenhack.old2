#ifndef ARCHIVE_FILE_H
#define ARCHIVE_FILE_H

#include <cstring>
#include <cstdint>
#include <cstddef>
#include <hack/non_copyable.h>

class Archive;
class ArchiveFile : public NonCopyable
{
public:
    ArchiveFile();
    ~ArchiveFile();

    void    open(const Archive& archive, const char* path);
    void    close();
    void    read(char* dst, size_t size);

    template <typename T>
    T read()
    {
        constexpr const size_t len = sizeof(T);

        char tmp[len];
        T ret;

        read(tmp, len);
        memcpy((char*)&ret, tmp, len);
        return ret;
    }

    int8_t      read8() { return read<int8_t>(); }
    int16_t     read16() { return read<int16_t>(); }
    int32_t     read32() { return read<int32_t>(); }
    int64_t     read64() { return read<int64_t>(); }

    uint8_t     read8u() { return read<uint8_t>(); }
    uint16_t    read16u() { return read<uint16_t>(); }
    uint32_t    read32u() { return read<uint32_t>(); }
    uint64_t    read64u() { return read<uint64_t>(); }


private:
    char*   _data;
    size_t  _size;
    size_t  _cursor;
};

#endif
