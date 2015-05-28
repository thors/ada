#ifndef ada_proc_h
#define ada_proc_h

/**
 * This file is supposed to provide a small interface to the procfs file system
 * to ada. The interface does not (yet) support the proopagation of file modes
 */


/**
   read_proc_t is imported from proc_fs.h. At the time this header was 
   written, it is 

   typedef int (read_proc_t)(char *page, char **start, off_t off,
                            int count, int *eof, void *data);

   where type off_t is an integer type with platform-dependant size.
*/

int ada_create_proc_read_entry(const char* file_n, const char* folder_n, read_proc_t *reader, char *data);

#endif //ada_proc_h
