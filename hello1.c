// SPDX-License-Identifier: GPL-2.0
#include <linux/module.h>
#include <linux/init.h>
#include <linux/printk.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include <linux/list.h>

MODULE_AUTHOR("Serhii Popovych <serhii.popovych@globallogic.com>");
MODULE_DESCRIPTION("Hello1 module for kernel training");
MODULE_LICENSE("Dual BSD/GPL");

struct event {
	struct list_head list;
	ktime_t start_time;
	ktime_t end_time;
};

static LIST_HEAD(event_list);

void print_hello(void)
{
	struct event *new_event;

	new_event = kmalloc(sizeof(*new_event), GFP_KERNEL);
	if (!new_event) {
		pr_err("Failed to allocate memory for event\n");
		return;
	}

	new_event->start_time = ktime_get();
	pr_info("Hello, world!\n");
	new_event->end_time = ktime_get();

	list_add_tail(&new_event->list, &event_list);
}
EXPORT_SYMBOL(print_hello);

static void __exit hello1_exit(void)
{
	struct event *entry, *tmp;

	pr_info("Exiting hello1 module and printing event times:\n");

	list_for_each_entry_safe(entry, tmp, &event_list, list) {
		pr_info("Event time: Start = %lld ns, End = %lld ns,\n"
			"Duration = %lld ns\n",
			ktime_to_ns(entry->start_time),
			ktime_to_ns(entry->end_time),
			ktime_to_ns(ktime_sub(entry->end_time,
					      entry->start_time)));
		list_del(&entry->list);
		kfree(entry);
	}
}

module_exit(hello1_exit);

