#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

static int major_no = 0;
static char dev_name[] = "gclip";
static int init(void);
static void xit(void);
static ssize_t gclip_read( struct file *, char *, size_t, loff_t *);
static ssize_t gclip_write (struct file *, const char __user *, size_t, loff_t *);
static char *buffer;
static f_pos = 0;



/* Represents a "clipping" linked list entry*/
typedef struct clipping {
  struct clipping *prev;
  char *contents;
} clipping;


/* For linked list*/
static clipping *head;
static clipping *tail;
static int clip_count;

/* Represents functions called when various actions taken on file*/
static struct file_operations fops = 
{
  .owner = THIS_MODULE,
  .read = gclip_read,
  .write = gclip_write
};



static int init(void) {
  printk(KERN_WARNING "ini called\n");
  int ret_val;
  /*register a char device */
  if ((ret_val = register_chrdev(0, dev_name, &fops)) == -1 ) {
  /* Driver registration failed */
    printk(KERN_WARNING "Gclip: device register failed");
    return ret_val;
    
  
  
  }
  else {
    /* driver registration sucessful*/
    major_no = ret_val;
    printk(KERN_NOTICE "Gclip: device registeed. Major number: %i", major_no);
     
    
    /*structure for char device file */  
    
    /*
    struct dev_t device = MKDEV

    int register_chrdev_region(dev_t first, 1, "gclip");



    struct cdev *cdev_s = cdev_alloc();
    cdev_s->ops = &fops;
    int retval = cdev_add(cdev_s, devno, 1); 
    printk(KERN_WARNING "cdev rt val: %d \n", retval);
    int alloc_chrdev_region(dev_t *dev, 0, 1, "gclip");
     
     
     
     /*allocate buffer memory */
     /* buffer = kmalloc(128000, GFP_KERNEL); */     
      
      return 0; /*success */
  }


}

static void xit(void) {
  if (major_no != -1) {
    unregister_chrdev(major_no, dev_name);
  }
}

/*register init and exit functions */
module_init(init);
module_exit(xit);



static ssize_t gclip_read( struct file * file_s , char * c, size_t size, loff_t *seek) {
  printk(KERN_NOTICE "read function invoked\n");  
  char *mess =  "nothing in clipboard\n";
  if (0  == 0) {
    printk(KERN_NOTICE "Empty Clipboard");

    copy_to_user(c, mess+f_pos, 1);
    f_pos++;
    if (f_pos > 21) {
      f_pos = 0;
      return 0;
    }
    return 1;
    
  }
  char *message = tail->contents;
  tail = tail->prev;
  clip_count--;
  /* TODO: something with the message to return it  */
  
  copy_to_user(c, message, sizeof(c));  
  return 0;
}


static ssize_t gclip_write (struct file * file_s, const char __user * user, size_t size , loff_t *seek) {
  
  printk(KERN_NOTICE "write function invoked\n");  
  char * read_in;
  /*copy_from_user(n )*/
  /* Allocate mem for a clipping and its contents*/
  clipping *next = kmalloc(sizeof(clipping), GFP_KERNEL);
  next->contents = kmalloc(sizeof(char) * sizeof(read_in), GFP_KERNEL);

  if (clip_count == 0) {
    head = next;
  }
  clip_count++;
  next->prev = tail;
  tail = next;
  return 0;
}
