#undef pr_fmt
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/init_task.h>

static int num=0;
static long bar4_start = 0xb0000000;
static long bar4_len = 0x10000000;

module_param(num, int, 0660);
module_param(bar4_start, long, 0660);
module_param(bar4_len, long, 0660);

static int __init initfunc(void)
{

	void *addr;

	addr = ioremap(bar4_start, bar4_len);
	if (!addr) {
		pr_info("Failed to ioremap");
		return 0;
	}

	writel(num, addr);
	pr_info("Write %d to %#lx\n", num, bar4_start);

	return 0;
}
module_init(initfunc);


static void __exit exitfunc(void)
{
	return;
}
module_exit(exitfunc);

MODULE_LICENSE("GPL");

