/* Desc: This program will create single thread using kthread_create fucntion,
 * which is defined in kthread.h and put thread for sleep to delay the exection
 *
 * kthread_create() - This macro will create a kthread on the current node, leaving it in
 * 	the stopped state.  This is just a helper for kthread_create_on_node();
 * 	see the documentation there for more details.
 * kthread_should_stop() - 
 * wake_up_process() - 
 * kthread_stop() - 
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>	/*Create thread */
#include <linux/delay.h> 	/* usleep_range */


static struct task_struct *kthread;

static int work_func(void *data)
{
    int i = 0;
    while (!kthread_should_stop()) {
        printk(KERN_INFO "%d\n", i);
        usleep_range(1000000, 1000001); /*ON-ATOMIC CONTEXT sleep */
        i++;
        if (i == 10)
            i = 0;
    }
    return 0;
}

int init_module(void)
{
    kthread = kthread_create(work_func, NULL, "mykthread");
    wake_up_process(kthread);
    return 0;
}

void cleanup_module(void)
{
    /* Waits for thread to return. */
    kthread_stop(kthread);
}
MODULE_LICENSE("MIT");

