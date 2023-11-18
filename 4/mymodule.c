#include <linux/kernel.h>
#include <linux/module.h>

#include <linux/slab.h>
#include <linux/types.h>
#include <linux/random.h>

MODULE_LICENSE("MIT");
MODULE_AUTHOR("Babich Denys");
MODULE_DESCRIPTION("Labwork 4");

#define LIST_LENGTH 12
#define MSG_PREF "TEST: "

#define print_msg(msg, ...) printk(KERN_ERR MSG_PREF msg, ##__VA_ARGS__);

typedef struct 
{
	struct list_head node;
	uint32_t value;
} int_node_t;

#define ilfree(list_head) \
	do \
	{ \
		int_node_t *__ptr, *__tmp; \
		list_for_each_entry_safe(__ptr, __tmp, (list_head), node) \
		{ \
			kfree(__ptr); \
		} \
	} \
	while(0) \

#define ilprint(list_head) \
	do \
	{ \
		int_node_t *__ptr; \
		print_msg("List: {"); \
		list_for_each_entry(__ptr, (list_head), node) \
		{ \
			printk(KERN_ERR "\t%i ", __ptr->value); \
		} \
		printk(KERN_ERR "}\n"); \
	} \
	while(0) \

// Initialization of the list
// https://elixir.bootlin.com/linux/latest/source/include/linux/list.h#L714

static struct list_head list = LIST_HEAD_INIT(list);

static void perform_task(void)
{
	int_node_t* ptr;
	uint32_t result = ~0;

	list_for_each_entry(ptr, &list, node)
	{
		result &= ptr->value; // Perform bitwise AND with each element
	}

	print_msg("Bitwise AND of all elements: %u\n", result);
}

static int __init mymodule_init(void)
{
	int i;
	int ret = 0;
	print_msg("The beginning of mymodule allocation process.\n");

	for (i = 0; i < LIST_LENGTH; ++i)
	{
		int_node_t* ptr = (int_node_t*)kmalloc(sizeof(*ptr), GFP_KERNEL);

		if (!ptr) 
		{
			print_msg("Failed to allocate memory for the list.\n");
			ret = -ENOMEM;
			goto alloc_err;
		}

		get_random_bytes(&ptr->value, sizeof(ptr->value));
		list_add_tail(&ptr->node, &list);
	}

	print_msg("List allocation successfully finished.\n");

	ilprint(&list);

	perform_task();

	return 0;

alloc_err:
	ilfree(&list);
	return ret;
}

static void __exit mymodule_exit(void)
{
	ilfree(&list);
	print_msg("mymodule deallocation succeded.\n");
}

module_init(mymodule_init);
module_exit(mymodule_exit);