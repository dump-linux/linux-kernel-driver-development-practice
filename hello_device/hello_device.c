#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

// 模块加载函数
static int __init hello_init(void)
{
	pr_info("Hello World!\n");
	return 0;
}

// 模块卸载函数
static void __exit hello_exit(void)
{
	pr_info("Goodbye!\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("dump linux");
MODULE_DESCRIPTION("hello world on an embedded device");
