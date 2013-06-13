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
static int f_pos = 0;
static int wr_ptr = 0;
static char *wr_buffer;


/* Represents a "clipping" linked list entry*/
typedef struct clipping {
  struct clipping *prev;
  char *contents;
} clipping;


/* Allocate new clipping */
static clipping *new_clipping(size_t);

/* Top of stack*/
static clipping *top = NULL;

/* Represents functions called when various actions taken on file*/
static struct file_operations fops = 
{
  .owner = THIS_MODULE,
  .read = gclip_read,
  .write = gclip_write
};



static int init(void) {
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
    printk(KERN_WARNING "Gclip: device registeed. Major number: %i", major_no);
    wr_buffer = kmalloc(1024, GFP_KERNEL);
    return 0; /*success */
  }
}

static void xit(void) {
  /* Unregister if needed */
  if (major_no != -1) {
    unregister_chrdev(major_no, dev_name);
  }
}

/*register init and exit functions */
module_init(init);
module_exit(xit);

static ssize_t gclip_read( struct file * file_s , char *c, size_t size, loff_t *seek) {

  /* TODO: implement seek */
  printk(KERN_NOTICE "read function invokedo\n");
  
  /* If nothing on clipboard, end read */
  if (top == NULL) {
    return 0;
  }
  
  /* Get the text from the top clip on the stack */
  char *clip_txt = top->contents; 

  printk(KERN_NOTICE "read function invoked, size is %d\n\n", size);  
    copy_to_user(c, (clip_txt+f_pos++), 1);
    /* When the end of the text has been reached  */  
    if (clip_txt[f_pos] == '\0') {
      f_pos = 0;
      /* Go to next clip and return 0 to end read */
      clipping *temp = top->prev;
      kfree(top);
      top = temp;
      return 0;
    } 
  return 1; /* Error: only read one byte at a time */
}


static ssize_t gclip_write (struct file * file_s, const char __user * c, size_t size , loff_t *seek) {
  
  /* Allocate mem for a clipping and its contents*/
  /* TODO: deal with size */
  
    /*wr_buffer[wr_ptr++] = *c;*/
    copy_from_user((wr_buffer+(wr_ptr++)), c, 1);
    printk(KERN_WARNING "ascii val is %d\n", *c);
    printk(KERN_WARNING "size is: %d\n", size);
  
    if (size == 1) { /*Last char just read in*/
      clipping *new = new_clipping(sizeof(char) * 1024);
      new->prev = top;
      top = new;
      memcpy(new->contents, wr_buffer, wr_ptr);
      wr_ptr = 0;
    }
  
  return 1;
}


/* Allocates and returns a pointer to a clipping struct
   with a message of given size
*/
static clipping *new_clipping(size_t txt_size) {
  clipping *new = kmalloc(sizeof(clipping), GFP_KERNEL);
  new->contents = kmalloc(sizeof(txt_size), GFP_KERNEL);
  new->prev = NULL;
  return new;
}


