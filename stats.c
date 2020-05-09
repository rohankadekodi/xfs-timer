/*
 * =====================================================================================
 *
 *       Filename:  stats.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/08/20 18:39:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "xfs.h"

const char *Timingstring[TIMING_NUM] = {
	/* Namei operations */
	"============= Directory operations =============",
	"create",
	"lookup",
	"link",
	"unlink",
	"symlink",
	"mkdir",
	"rmdir",
	"mknod",
	"rename",
	"readdir",
	"setattr",

	/* I/O operations */
	"================ I/O operations ================",
	"read_iter",
	"write_iter",

	/* Others */
	"================ Miscellaneous =================",
	"fsync",
	"fallocate",

	/* Mmap */
	"=============== MMap operations ================",
	"mmap_pmd_fault",
	"mmap_pfn_mkwrite",
	"iomap_begin",
	"iomap_end",
	"map_blocks",
	"map_blocks_zero",

};

u64 Timingstats[TIMING_NUM];
DEFINE_PER_CPU(u64[TIMING_NUM], Timingstats_percpu);
u64 Countstats[TIMING_NUM];
DEFINE_PER_CPU(u64[TIMING_NUM], Countstats_percpu);

void xfs_get_timing_stats(void)
{
	int i;
	int cpu;

	for (i = 0; i < TIMING_NUM; i++) {
		Timingstats[i] = 0;
		Countstats[i] = 0;
		for_each_possible_cpu(cpu) {
			Timingstats[i] += per_cpu(Timingstats_percpu[i], cpu);
			Countstats[i] += per_cpu(Countstats_percpu[i], cpu);
		}
	}
}

void xfs_print_timing_stats(struct super_block *sb)
{
	int i;

	xfs_get_timing_stats();

	printk(KERN_INFO "=========== XFS kernel timing stats ============\n");
	for (i = 0; i < TIMING_NUM; i++) {
		/* Title */
		if (Timingstring[i][0] == '=') {
			printk(KERN_INFO "\n%s\n\n", Timingstring[i]);
			continue;
		}

		if (measure_timing || Timingstats[i]) {
			printk(KERN_INFO "%s: count %llu, timing %llu, average %llu\n",
				Timingstring[i],
				Countstats[i],
				Timingstats[i],
				Countstats[i] ?
				Timingstats[i] / Countstats[i] : 0);
		} else {
		        printk(KERN_INFO "%s: count %llu\n",
				Timingstring[i],
				Countstats[i]);
		}
	}

	printk(KERN_INFO "============ XFS REMOTE ACCESSES ==============\n");
	printk(KERN_INFO "Remote writes %ld\n", sb->remote_writes.counter);
	printk(KERN_INFO "Local writes %ld\n", sb->local_writes.counter);
	printk(KERN_INFO "Remote reads %ld\n", sb->remote_reads.counter);
	printk(KERN_INFO "Local reads %ld\n", sb->local_reads.counter);

	printk(KERN_INFO "\n");
}

static void xfs_clear_timing_stats(void)
{
	int i;
	int cpu;

	for (i = 0; i < TIMING_NUM; i++) {
		Countstats[i] = 0;
		Timingstats[i] = 0;
		for_each_possible_cpu(cpu) {
			per_cpu(Timingstats_percpu[i], cpu) = 0;
			per_cpu(Countstats_percpu[i], cpu) = 0;
		}
	}
}

void xfs_clear_stats(struct super_block *sb)
{
	xfs_clear_timing_stats();
}
