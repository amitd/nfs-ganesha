/*
 * vim:expandtab:shiftwidth=8:tabstop=8:
 *
 * Copyright CEA/DAM/DIF  (2008)
 * contributeur : Philippe DENIEL   philippe.deniel@cea.fr
 *                Thomas LEIBOVICI  thomas.leibovici@cea.fr
 *
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 * ---------------------------------------
 */

/**
 * \file    mnt_UmntAll.c
 * \author  $Author: deniel $
 * \date    $Date: 2005/12/20 10:52:14 $
 * \version $Revision: 1.6 $
 * \brief   MOUNTPROC_UMNTALL for Mount protocol v1 and v3.
 *
 *
 */
#include "config.h"
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/file.h>           /* for having FNDELAY */
#include "HashTable.h"
#include "log.h"
#include "nfs23.h"
#include "nfs4.h"
#include "nfs_core.h"
#include "cache_inode.h"
#include "nfs_exports.h"
#include "nfs_creds.h"
#include "nfs_tools.h"
#include "mount.h"
#include "nfs_proto_functions.h"

/**
 * @brief The Mount proc umount_all function, for all versions.
 *
 * @param[in]  parg
 * @param[in]  pexport
 * @param[in]  req_ctx
 * @param[in]  pworker
 * @param[in]  preq
 * @param[out] pres
 *
 */

int mnt_UmntAll(nfs_arg_t *parg,
                exportlist_t *pexport,
		struct req_op_context *req_ctx,
                nfs_worker_data_t *pworker,
                struct svc_req *preq,
                nfs_res_t *pres)
{
  LogDebug(COMPONENT_NFSPROTO, "REQUEST PROCESSING: Calling mnt_UmntAll");

  /* TODO: This should clear all mounts for the calling client, using
   * nfs_Remove_MountList_Entry(hostname, NULL)
   */
  /* Just empty the Mount list, take void as argument and returns void */
  if(!nfs_Purge_MountList())
    {
      /* Purge mount list failed */
      LogCrit(COMPONENT_NFSPROTO,
              "UMOUNT ALL: Error when emptying the mount list");
    }

  return NFS_REQ_OK;
}                               /* mnt_UmntAll */

/**
 * mnt_UmntAll_Free: Frees the result structure allocated for mnt_UmntAll.
 * 
 * Frees the result structure allocated for mnt_UmntAll.
 * 
 * @param pres        [INOUT]   Pointer to the result structure.
 *
 */
void mnt_UmntAll_Free(nfs_res_t * pres)
{
  /* Nothing to do */
  return;
}                               /* mnt_UmntAll_Free */
