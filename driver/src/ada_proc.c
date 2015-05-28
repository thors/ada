#include <linux/module.h>  /* Needed by all modules */
#include <linux/kernel.h>  /* Needed for KERN_ALERT */
#include <linux/proc_fs.h>
#include <linux/slab.h>

/*
 * This file was created to suffice my needs. Feel free to extend, in
 * case you need more.
 *
 * What should be supported eventually:
 *    - create one folder within an existing subfoler
 *    - create files within that subfolder
 *    - hook in ada read function
 *
 * What won't be supported:
 *    - manage multiple subfolders
 *    - hook in ada for write function
 */

typedef struct proc_file_list proc_file_list;
typedef proc_file_list *proc_file_list_p;
typedef ssize_t (*proc_read_p) (struct file *, char __user *, size_t, loff_t *);

struct proc_file_list {
  struct file_operations fops;  
  char *file_n;
  proc_file_list *next;
};

static proc_file_list_p module_file_list,module_file_list_tail;

static struct proc_dir_entry *module_folder = NULL;
static char *module_folder_n;

/**
 * Only adding files supported at the time, not removing (except for unloading
 * the module)
 */
int ada_create_proc_read_entry(const char* file_n, const char* folder_n, 
			       proc_read_p proc_read) {
  proc_file_list_p newEntry = (proc_file_list_p)kmalloc(sizeof(proc_file_list), __GFP_WAIT | __GFP_IO | __GFP_FS);
  if (NULL == newEntry) {
    return -1;
  }
  newEntry->next = NULL;
  newEntry->fops.read = proc_read;
  if (!module_file_list) {
    module_file_list = newEntry;
  } else {
    module_file_list_tail->next = newEntry;
  }
  module_file_list_tail = newEntry;
  return 0;
}

int ada_create_folder(const char* folder_n) {
  if (NULL != module_folder_n || NULL == folder_n) {
    return -1;
  }
  module_folder = folder_n ? proc_mkdir(folder_n, NULL) : NULL;
  if (NULL == module_folder) {
    return -1;
  }
  module_folder_n = (char*) kmalloc(strnlen(folder_n,20) + 1, __GFP_WAIT | __GFP_IO | __GFP_FS);;
  if (NULL == module_folder_n) {
    return -1;
  }
  strncpy(module_folder_n, folder_n, 20);
  return 0;
} 

proc_file_list_p delete_entry(proc_file_list_p entry) {
  proc_file_list_p next;
  next = entry ? entry->next : NULL;
  entry->file_n ? remove_proc_entry(entry->file_n, module_folder) : NULL;
  return next;
}

void ada_proc_cleanup(void) {
  proc_file_list_p next = NULL;
  while(module_file_list) {
    next = module_file_list->next;
    kfree(module_file_list);
    module_file_list = next;
  }
  next ? kfree(next) : NULL;
  module_folder ? remove_proc_entry(module_folder_n, NULL) : NULL;
  kfree(module_folder_n);
}

void ada_proc_init(void) {
  module_file_list = NULL;
  module_file_list_tail = NULL;
  module_folder = NULL;
  module_folder_n = NULL;
}

#ifdef EXAMPLE_PROCS
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/string.h>

static int len,temp;

static char *msg;
static char *dirname="driver/mydriver";
static char *dirname2="settings";
struct proc_dir_entry *subdirparent;
struct proc_dir_entry *parent;
struct proc_dir_entry *parent2;
static ssize_t read_proc(struct file *filp,char *buf,size_t count,loff_t *offp )
{
    if(count>temp){count=temp;}
    temp=temp-count;
    copy_to_user(buf,msg, count);
    if(count==0){temp=len;}

    return count;
}

static ssize_t write_proc(struct file *filp,const char *buf,size_t count,loff_t *offp)
{
    copy_from_user(msg,buf,count);
    len=count;
    temp=len;

    return count;
}

struct file_operations proc_fops = {
    read: read_proc,
    write: write_proc
};

static void create_new_proc_entry(void)
{
    parent = proc_mkdir(dirname, NULL);
    parent2 = proc_mkdir(dirname2,parent);
    proc_create("private_setting",0644,parent2,&proc_fops);
    msg=kmalloc(GFP_KERNEL,10*sizeof(char));
}


static int proc_init (void)
{
 create_new_proc_entry();
 return 0;
}

static void proc_cleanup(void)
{
    remove_proc_entry("private_setting",parent2);
    remove_proc_entry(dirname2,parent);
    remove_proc_entry(dirname,NULL);
}

MODULE_LICENSE("GPL"); 
module_init(proc_init);
module_exit(proc_cleanup);
#endif // EXAMPLE_PROCS
