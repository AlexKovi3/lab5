// SPDX-License-Identifier: GPL-2.0
#include <linux/module.h>
#include <linux/init.h>
#include <linux/printk.h>
#include "hello1.h"

MODULE_AUTHOR("Serhii Popovych <serhii.popovych@globallogic.com>");
MODULE_DESCRIPTION("Hello2 module for kernel training");
MODULE_LICENSE("Dual BSD/GPL");

static uint print_count = 1;
module_param(print_count, uint, 0444);
MODULE_PARM_DESC(print_count, "Number of times to print 'Hello, world!'");

static int __init hello2_init(void)
{
	uint i;

	if (print_count == 0 || (print_count >= 5 && print_count <= 10))
		pr_warn("Warning: print_count is 0 or between 5 and 10. Proceeding...\n");
	else if (print_count > 10) {
		pr_err("Error: print_count > 10. Module not loaded.\n");
		return -EINVAL;
	}

	for (i = 0; i < print_count; i++)
		print_hello();

	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("Exiting hello2 module.\n");
}

module_init(hello2_init);
module_exit(hello2_exit);

