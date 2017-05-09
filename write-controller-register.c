 ///////////////////////////////////////////////////////////////////////////////
    #include <ctype.h>
    #include <string.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <math.h>
    #include <time.h>
    #include <signal.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <sys/mman.h>
    #include <sys/select.h>
    #include <pthread.h>
    #include <unistd.h>
    #include <sched.h>
    #include <errno.h>


 //   #define SW_PORTC_IO_BASE  0x01c20800
    #define SW_PORTC_IO_BASE 0x01F02C00 

    int main() {
       unsigned int * pc;
       int fd, i;
       char * ptr;
       unsigned int addr_start, addr_offset, PageSize, PageMask, data;

       PageSize = sysconf(_SC_PAGESIZE);
       PageMask = (~(PageSize-1));
       addr_start = SW_PORTC_IO_BASE & PageMask;
       addr_offset = SW_PORTC_IO_BASE & ~PageMask;

       fd = open("/dev/mem", O_RDWR);
       if(fd < 0) {
          perror("Unable to open /dev/mem");
          return(-1);
       }

       pc = mmap(0, PageSize*2, PROT_READ|PROT_WRITE, MAP_SHARED, fd, addr_start);

       if(pc == MAP_FAILED) {
          perror("Unable to mmap file");
          printf("pc:%lx\n", (unsigned long)pc);
          return(-1);
       }
       printf("PageSize:%8.8x\tPageMask:%8.8x\naddr_start:%8.8x\taddr_offset:%8.8x\n",PageSize,PageMask,addr_start,addr_offset);
       printf("pc:%8.8x\n", *(unsigned int *)pc);
       ptr = (char *)pc + addr_offset;
       data = *(unsigned int *)(ptr+0x00); //offset for controller register
       data &= ~(1<<12);                              //control register
       data &= ~(1<<13);                              //control register
       data &= ~(1<<14);                              //control register
       *(unsigned int *)(ptr+0x00) = data;

       return 0;
    }
