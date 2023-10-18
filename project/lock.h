#include <fcntl.h>

struct flock flock_struct;

int read_lock(int filefd, int index, size_t size)
{
    flock_struct.l_type = F_RDLCK;
    flock_struct.l_whence = SEEK_SET;
    if (index != -1)
    {
        flock_struct.l_start = (off_t)index * (off_t)size;
        flock_struct.l_len = (off_t)size;
    }
    else
    {
        flock_struct.l_start = 0;
        flock_struct.l_len = 0;
    }
    if (fcntl(filefd, F_SETLKW, &flock_struct) == -1)
        return 0;
    return 1;
}

int unlock_file(int filefd, int index, size_t size)
{
    flock_struct.l_type = F_UNLCK;
    flock_struct.l_whence = SEEK_SET;
    if (index != -1)
    {
        flock_struct.l_start = (off_t)index * (off_t)size;
        flock_struct.l_len = (off_t)size;
    }
    else
    {
        flock_struct.l_start = 0;
        flock_struct.l_len = 0;
    }
    if (fcntl(filefd, F_SETLKW, &flock_struct) == -1)
        return 0;
    return 1;
}

int write_lock(int filefd, int index, size_t size)
{
    flock_struct.l_type = F_WRLCK;
    flock_struct.l_whence = SEEK_SET;
    if (index != -1)
    {
        flock_struct.l_start = (off_t)index * (off_t)size;
        flock_struct.l_len = (off_t)size;
    }
    else
    {
        flock_struct.l_start = 0;
        flock_struct.l_len = 0;
    }
    if (fcntl(filefd, F_SETLKW, &flock_struct) == -1)
        return 0;
    return 1;
}
