#
# Copyright (c) 2000-2005 Silicon Graphics, Inc.
# All Rights Reserved.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it would be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write the Free Software Foundation,
# Inc.,  51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#

ccflags-y += -I$(src)			# needed for trace events
ccflags-y += -I$(src)/libxfs

obj-m				+= xfs_allocator.o

# this one should be compiled first, as the tracing macros can easily blow up
xfs_allocator-y				+= xfs_trace.o

# build the libxfs code first
xfs_allocator-y				+= $(addprefix libxfs/, \
				   xfs_alloc.o \
				   xfs_alloc_btree.o \
				   xfs_attr.o \
				   xfs_attr_leaf.o \
				   xfs_attr_remote.o \
				   xfs_bit.o \
				   xfs_bmap.o \
				   xfs_bmap_btree.o \
				   xfs_btree.o \
				   xfs_da_btree.o \
				   xfs_da_format.o \
				   xfs_defer.o \
				   xfs_dir2.o \
				   xfs_dir2_block.o \
				   xfs_dir2_data.o \
				   xfs_dir2_leaf.o \
				   xfs_dir2_node.o \
				   xfs_dir2_sf.o \
				   xfs_dquot_buf.o \
				   xfs_ialloc.o \
				   xfs_ialloc_btree.o \
				   xfs_inode_fork.o \
				   xfs_inode_buf.o \
				   xfs_log_rlimit.o \
				   xfs_ag_resv.o \
				   xfs_rmap.o \
				   xfs_rmap_btree.o \
				   xfs_refcount.o \
				   xfs_refcount_btree.o \
				   xfs_sb.o \
				   xfs_symlink_remote.o \
				   xfs_trans_resv.o \
				   )
# xfs_rtbitmap is shared with libxfs
xfs_allocator-$(CONFIG_XFS_RT)		+= $(addprefix libxfs/, \
				   xfs_rtbitmap.o \
				   )

# highlevel code
xfs_allocator-y				+= xfs_aops.o \
				   xfs_attr_inactive.o \
				   xfs_attr_list.o \
				   xfs_bmap_util.o \
				   xfs_buf.o \
				   xfs_dir2_readdir.o \
				   xfs_discard.o \
				   xfs_error.o \
				   xfs_export.o \
				   xfs_extent_busy.o \
				   xfs_file.o \
				   xfs_filestream.o \
				   xfs_fsmap.o \
				   xfs_fsops.o \
				   xfs_globals.o \
				   xfs_icache.o \
				   xfs_ioctl.o \
				   xfs_iomap.o \
				   xfs_iops.o \
				   xfs_inode.o \
				   xfs_itable.o \
				   xfs_message.o \
				   xfs_mount.o \
				   xfs_mru_cache.o \
				   xfs_reflink.o \
				   xfs_stats.o \
				   xfs_super.o \
				   xfs_symlink.o \
				   xfs_sysfs.o \
				   xfs_trans.o \
				   xfs_xattr.o \
				   stats.o \
				   kmem.o

# low-level transaction/log code
xfs_allocator-y				+= xfs_log.o \
				   xfs_log_cil.o \
				   xfs_bmap_item.o \
				   xfs_buf_item.o \
				   xfs_extfree_item.o \
				   xfs_icreate_item.o \
				   xfs_inode_item.o \
				   xfs_refcount_item.o \
				   xfs_rmap_item.o \
				   xfs_log_recover.o \
				   xfs_trans_ail.o \
				   xfs_trans_bmap.o \
				   xfs_trans_buf.o \
				   xfs_trans_extfree.o \
				   xfs_trans_inode.o \
				   xfs_trans_refcount.o \
				   xfs_trans_rmap.o \
				   xfs_rtalloc.o \
				   xfs_acl.o \
				   xfs_sysctl.o \
				   xfs_ioctl32.o \
				   xfs_pnfs.o \
				   xfs_dquot.o \
				   xfs_dquot_item.o \
				   xfs_trans_dquot.o \
				   xfs_qm_syscalls.o \
				   xfs_qm_bhv.o \
				   xfs_qm.o \
				   xfs_quotaops.o \

all:
	make -C /lib/modules/$(shell uname -r)/build M=`pwd`

clean:
	make -C /lib/modules/$(shell uname -r)/build M=`pwd` clean
