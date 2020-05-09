/*
 * =====================================================================================
 *
 *       Filename:  stats.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/08/20 18:37:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef __ROHAN_STATS_H__
#define __ROHAN_STATS_H__


#include <linux/types.h>
#include <asm/percpu.h>


/* ======================= Timing ========================= */
enum timing_category {
	/* Namei operations */
	namei_title_t,
	create_t,
	lookup_t,
	link_t,
	unlink_t,
	symlink_t,
	mkdir_t,
	rmdir_t,
	mknod_t,
	rename_t,
	readdir_t,
	setattr_t,

	/* I/O operations */
	io_title_t,	
	read_iter_t,
	write_iter_t,

	/* Others */
	others_title_t,
	fsync_t,
	fallocate_t,

	/* Mmap */
	mmap_title_t,
	pmd_fault_t,
	pfn_mkwrite_t,
	iomap_begin_t,
	iomap_end_t,
	map_blocks_t,
	map_blocks_zero_t,

	/* Sentinel */
	TIMING_NUM,
};

extern const char *Timingstring[TIMING_NUM];
extern u64 Timingstats[TIMING_NUM];
DECLARE_PER_CPU(u64[TIMING_NUM], Timingstats_percpu);
extern u64 Countstats[TIMING_NUM];
DECLARE_PER_CPU(u64[TIMING_NUM], Countstats_percpu);

typedef struct timespec timing_t;

#define XFS_START_TIMING(name, start) \
	{if (measure_timing) getrawmonotonic(&start); }

#define XFS_END_TIMING(name, start) \
	{if (measure_timing) { \
		timing_t end; \
		getrawmonotonic(&end); \
		__this_cpu_add(Timingstats_percpu[name], \
			(end.tv_sec - start.tv_sec) * 1000000000 + \
			(end.tv_nsec - start.tv_nsec)); \
	} \
	__this_cpu_add(Countstats_percpu[name], 1); \
	}

#endif
