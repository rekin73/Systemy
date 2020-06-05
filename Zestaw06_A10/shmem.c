#include "shmem.h"
int shmCreate(const char *name, int size)
{
    int tmp;
    if ((tmp = shm_open(name, O_RDWR | O_CREAT | O_TRUNC, 0777)) == -1)
    {
        perror("create error");
        exit(1);
    }
    if (ftruncate(tmp, size) == -1)
    {
        perror("ftruncate error");
        exit(1);
    }
    printf("utworzono shmem o nazwie %s\n", name);

    return tmp;
}

int shmOpen(const char *name)
{
    int tmp;
    if ((tmp = shm_open(name, O_RDWR, 0777)) == -1)
    {
        perror("shmem open error");
        exit(1);
    }
    return tmp;
}

void shmRm(const char *name)
{
    if (shm_unlink(name) == -1)
    {
        perror("shmem remove error");
        exit(1);
    }
}

void *shmMap(int fd, int size)
{
    void *tmp;
    if ((tmp = mmap(NULL, size, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED)
    {
        perror("map error");
        exit(1);
    }
    return tmp;
}

void shmClose(void *ptr, int fd, int size)
{
    if (munmap(ptr, size) == -1)
    {
        perror("munmap error");
        exit(1);
    }
    if (close(fd) == -1)
    {
        perror("shmem close error");
        exit(1);
    }
}

int shmSize(int fd)
{
    struct stat statbuf;
    if (fstat(fd, &statbuf) == -1)
    {
        perror("fstat error");
        exit(1);
    }
    return statbuf.st_size;
}

void shmInfo(int fd)
{
    struct stat sb;
    if (fstat(fd, &sb) == -1)
    {
        perror("fstat error");
        exit(1);
    }
    printf("ID of containing device:  [%lx,%lx]\n",
                (long) major(sb.st_dev), (long) minor(sb.st_dev));

           printf("File type:                ");

           switch (sb.st_mode & S_IFMT) {
           case S_IFBLK:  printf("block device\n");            break;
           case S_IFCHR:  printf("character device\n");        break;
           case S_IFDIR:  printf("directory\n");               break;
           case S_IFIFO:  printf("FIFO/pipe\n");               break;
           case S_IFLNK:  printf("symlink\n");                 break;
           case S_IFREG:  printf("regular file\n");            break;
           case S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown?\n");                break;
           }

           printf("I-node number:            %ld\n", (long) sb.st_ino);

           printf("Mode:                     %lo (octal)\n",
                   (unsigned long) sb.st_mode);

           printf("Link count:               %ld\n", (long) sb.st_nlink);
           printf("Ownership:                UID=%ld   GID=%ld\n",
                   (long) sb.st_uid, (long) sb.st_gid);

           printf("Preferred I/O block size: %ld bytes\n",
                   (long) sb.st_blksize);
           printf("File size:                %lld bytes\n",
                   (long long) sb.st_size);
           printf("Blocks allocated:         %lld\n",
                   (long long) sb.st_blocks);

           printf("Last status change:       %s", ctime(&sb.st_ctime));
           printf("Last file access:         %s", ctime(&sb.st_atime));
           printf("Last file modification:   %s", ctime(&sb.st_mtime));
}