/*
 * Copyright (c) 2011-2018 The DragonFly Project.  All rights reserved.
 *
 * This code is derived from software contributed to The DragonFly Project
 * by Vadim Zhukov <zhuk@openbsd.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of The DragonFly Project nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/sysctl.h>

// TODO: check if needed
#include "hammer2.h"
#include "hammer2_mount.h"


int	hammer2_sysctl(int *, u_int, void *, size_t *, void *, size_t,
	    struct proc *);

const struct vfsops hammer2fs_vfsops = {
	.vfs_mount	= hammer2_mount,
	.vfs_start	= hammer2_start,
	.vfs_unmount	= hammer2_unmount,
	.vfs_root	= hammer2_root,
	.vfs_quotactl	= hammer2_quotactl,
	.vfs_statfs	= hammer2_statfs,
	.vfs_sync	= hammer2_sync,
	.vfs_vget	= hammer2_vget,
	.vfs_fhtovp	= hammer2_fhtovp,
	.vfs_vptofh	= hammer2_vptofh,
	.vfs_init	= hammer2_init,
	.vfs_sysctl	= hammer2_sysctl,
	.vfs_checkexp	= hammer2_checkexp,
};

const int hammer2_supported_version = HAMMER2_VOL_VERSION_DEFAULT;

const struct sysctl_bounded_args hammer2_vars[] = {
        { HAMMER2_SUPPORTED_VERSION, &hammer2_supported_version, SYSCTL_INT_READONLY },
};


int
hammer2_sysctl(int *name, u_int namelen, void *oldp, size_t *oldlenp, void *newp, size_t newlen, struct proc *p) {
	return sysctl_bounded_arr(hammer2_vars, nitems(hammer2_vars), name,
	    namelen, oldp, oldlenp, newp, newlen);
}
