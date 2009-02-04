#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xda94b953, "struct_module" },
	{ 0xa5423cc4, "param_get_int" },
	{ 0xcb32da10, "param_set_int" },
	{ 0x3c2c5af5, "sprintf" },
	{ 0x43de6658, "create_proc_entry" },
	{ 0x7eb4c363, "register_chrdev" },
	{ 0x6483665c, "x86_dma_fallback_dev" },
	{ 0x892e6b25, "dma_alloc_from_coherent" },
	{ 0x2cf190e3, "request_irq" },
	{ 0x7106852a, "pci_bus_read_config_dword" },
	{ 0x7b319595, "pci_bus_write_config_dword" },
	{ 0x19daf217, "pci_find_device" },
	{ 0xc280a525, "__copy_from_user_ll" },
	{ 0x37a0cba, "kfree" },
	{ 0xdc74cc24, "kmem_cache_alloc" },
	{ 0x77bf8cb, "malloc_sizes" },
	{ 0x6a2ef116, "init_timer" },
	{ 0x6cb34e5, "init_waitqueue_head" },
	{ 0x3af98f9e, "ioremap_nocache" },
	{ 0x692c2d9c, "__request_region" },
	{ 0xb8aa2342, "__check_region" },
	{ 0x707f93dd, "preempt_schedule" },
	{ 0xbed60566, "sub_preempt_count" },
	{ 0x4c6ff041, "add_preempt_count" },
	{ 0xd6c963c, "copy_from_user" },
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0xb6c70a7d, "__wake_up" },
	{ 0x51493d94, "finish_wait" },
	{ 0xbb2140b9, "del_timer" },
	{ 0x4292364c, "schedule" },
	{ 0x8085c7b1, "prepare_to_wait" },
	{ 0x743afae6, "__mod_timer" },
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0x2995a981, "per_cpu__current_task" },
	{ 0x7d11c268, "jiffies" },
	{ 0x7cf65f1a, "remap_pfn_range" },
	{ 0x9bce482f, "__release_region" },
	{ 0x788fe103, "iomem_resource" },
	{ 0x49ac3d2a, "dma_release_from_coherent" },
	{ 0x608c2831, "warn_on_slowpath" },
	{ 0xebd5db8c, "dma_ops" },
	{ 0x8fed84a6, "mem_map" },
	{ 0x9ef749e2, "unregister_chrdev" },
	{ 0xd90a9a81, "remove_proc_entry" },
	{ 0xedc03953, "iounmap" },
	{ 0xf20dabd8, "free_irq" },
	{ 0xb72397d5, "printk" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "D39627A874295710F847479");
