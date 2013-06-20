/* Max number of chars to read in */
#define BUFFER_SIZE 4096

/* Called when kernel loads module*/
static int init(void);

/* Called when kernel unloads module */
static void xit(void);

/* Called to read data from gclip*/
static ssize_t gclip_read( struct file *, char *, size_t, loff_t *);

/* Called to write data to gclip*/
static ssize_t gclip_write (struct file *, const char __user *, size_t, loff_t *);

