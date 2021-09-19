#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char* filename(char *path)
{
    char *p;
    for(p=path+strlen(path); p>=path && *p != '/'; p--)
        ;
    p++;
    return p;
}

void find(char *path, char *target)
{
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;
    if((fd=open(path, 0)) < 0)
    {
        printf("find: cannot open %s\n", path);
        return;//调用open打开path的输出口，打不开函数返回
    }
    if(fstat(fd, &st) < 0)
    {
        printf("find: cannot stat %s\n", path);
        close(fd);
        return;//调用fstat把文件信息放进st，失败就返回
    }
    switch(st.type)
    {
    case T_FILE://是文件
        if(strcmp(filename(path), target) == 0)
        {
            printf("%s\n", path);
        }

	break;
    case T_DIR://是目录
        if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf)
        {
            printf("find: path too long\n");
            break;
        }
        strcpy(buf, path);//buf==path
        p = buf+strlen(buf);//p位于buf结尾
        *p++ = '/';//buf最后面添加/
        while(read(fd, &de, sizeof(de)) == sizeof(de))//读path目录下的文件
        {
              if(de.inum == 0) 
              {
                  continue;
              }
              if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)//跳过子目录的.和..
              { 
                  continue;
              }
              memmove(p, de.name, DIRSIZ);//读到真正的文件就加在p后面，也就是buf末尾 
              p[DIRSIZ] = 0;//在字符串最后加0表示结束
              find(buf, target);
        }
        break;
    }
    close(fd);
}
int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        printf("error");
        exit(0);
    }
    find(argv[1], argv[2]);
    exit(0);
}
