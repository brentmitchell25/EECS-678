
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/list.h>

struct birthday {
  int day;
  int month;
  int year;
  struct list_head list;
};
struct birthday *person1, *person2, *person3, *person4, *person5;
  static LIST_HEAD(birthday_list);

  

/* This function is called when the module is loaded. */
int simple_init(void)
{

  printk(KERN_INFO "Loading Module\n");

  person1 = kmalloc(sizeof(*person1), GFP_KERNEL);
  person1->day = 2;
  person1->month = 8;
  person1->year = 1995;
  INIT_LIST_HEAD(&person1->list);
  list_add_tail(&person1->list,&birthday_list);

  person2 = kmalloc(sizeof(*person2), GFP_KERNEL);
  person2->day = 4;
  person2->month = 10;
  person2->year = 1996;
  list_add_tail(&person2->list,&birthday_list);

  person3 = kmalloc(sizeof(*person2), GFP_KERNEL);
  person3->day = 5;
  person3->month = 1;
  person3->year = 2000;
  list_add_tail(&person3->list,&birthday_list);

  person4 = kmalloc(sizeof(*person4), GFP_KERNEL);
  person4->day = 1;
  person4->month = 4;
  person4->year = 2004;
  list_add_tail(&person4->list,&birthday_list);

  person5 = kmalloc(sizeof(*person5), GFP_KERNEL);
  person5->day = 1;
  person5->month = 1;
  person5->year = 2015;
  list_add_tail(&person5->list,&birthday_list);

  struct birthday *ptr;
  list_for_each_entry(ptr, &birthday_list, list) {
    printk(KERN_INFO "Day %d; Month: %d; Year: %d\n", ptr->day, ptr->month, ptr->year);
  }


  return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {
  struct birthday *ptr,*next;
  list_for_each_entry_safe(ptr,next,&birthday_list,list) {
    list_del(&ptr->list);
    kfree(ptr);
  }

  printk(KERN_INFO "Removing Module\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

