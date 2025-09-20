#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/platform_device.h> // 平台设备核心
#include <linux/gpio/consumer.h>   // gpiod_ 接口
#include <linux/of.h>              // Open Firmware (Device Tree)

// 1. Probe 函数：当内核发现设备树节点与本驱动匹配时，自动调用
static int hello_gpio_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct gpio_desc *my_desc;

	dev_info(dev, "device detected!\n");

	// 获取 GPIO 描述符
	// 参数2: NULL 表示读取 dts 属性名为 "gpios" 的引脚 (若 dts 属性叫 "led-gpios"，则填 "led")
	// 参数3: 初始化为输出方向，且初始值为低电平
	my_desc = devm_gpiod_get(dev, NULL, GPIOD_OUT_LOW);
	if (IS_ERR(my_desc)) {
		dev_err(dev, "failed to get gpio\n");
		return PTR_ERR(my_desc);
	}

	// 保存到私有数据中以便其他函数使用
	platform_set_drvdata(pdev, my_desc);

	// 设置高电平
	gpiod_set_value(my_desc, 1);

	dev_info(dev, "gpio loaded and set to high\n");

	return 0;
}

// 2. Remove 函数：模块卸载或设备移除时调用
static int hello_gpio_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct gpio_desc *my_desc;

	// 从平台设备中取出 probe 时保存的 gpio 描述符
	my_desc = platform_get_drvdata(pdev);
	if (!my_desc) {
		dev_err(dev, "failed to get gpio\n");
		return -ENODEV;
	}

	// 设置低电平
	gpiod_set_value(my_desc, 0);

	// 注意：不需要调用 gpiod_put(my_desc);
	// 因为 probe 中使用的是 devm_gpiod_get，内核会自动释放资源。

	dev_info(dev, "gpio released and set to low\n");

	return 0;
}

// 3. 匹配表：告诉内核我能驱动哪个名字的设备
static const struct of_device_id hello_gpio_ids[] = {
	// 必须与 dts 中的 compatible 字符串完全一致
	{ .compatible = "hello_gpio" },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, hello_gpio_ids);

// 4. 定义驱动结构体
static struct platform_driver hello_gpio_driver = {
	.probe = hello_gpio_probe,
	.remove = hello_gpio_remove,
	.driver = {
		.name = "hello_gpio_driver",
		// 关联匹配表
		.of_match_table = hello_gpio_ids,
	},
};

// 注册平台驱动
module_platform_driver(hello_gpio_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("dump linux");
MODULE_DESCRIPTION("a minimal gpio driver with device tree");
