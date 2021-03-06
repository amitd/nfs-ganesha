/*
 * Copyright IBM Corporation, 2010
 *  Contributor: Aneesh Kumar K.v  <aneesh.kumar@linux.vnet.ibm.com>
 *
 * --------------------------
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
 *
 */

#include "config.h"
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "log.h"
#include "ganesha_rpc.h"
#include "nlm4.h"
#include "sal_functions.h"
#include "nfs_proto_functions.h"
#include "nlm_util.h"

/**
 * @brief NSM notification
 *
 * @param[in]  parg
 * @param[in]  pexport
 * @param[in]  req_ctx
 * @param[in]  pworker
 * @param[in]  preq
 * @param[out] pres
 */

int nlm4_Sm_Notify(nfs_arg_t *parg,
                   exportlist_t *pexport,
		   struct req_op_context *req_ctx,
                   nfs_worker_data_t *pworker,
                   struct svc_req *preq,
                   nfs_res_t *pres)
{
  nlm4_sm_notifyargs * arg = &parg->arg_nlm4_sm_notify;
  state_status_t       state_status = STATE_SUCCESS;
  state_nsm_client_t * nsm_client;

  LogDebug(COMPONENT_NLM,
           "REQUEST PROCESSING: Calling nlm4_sm_notify for %s",
           arg->name);

  nsm_client = get_nsm_client(CARE_NOT, NULL, arg->name);
  if(nsm_client != NULL)
    {
      /* Cast the state number into a state pointer to protect
       * locks from a client that has rebooted from being released
       * by this SM_NOTIFY.
       */
      state_status = state_nlm_notify(nsm_client,
				      req_ctx,
				      (void*) (ptrdiff_t) arg->state);
		       
      if(state_status != STATE_SUCCESS)
        {
          /* TODO FSF: Deal with error */
        }

      dec_nsm_client_ref(nsm_client);
    }

  LogDebug(COMPONENT_NLM,
           "REQUEST RESULT: nlm4_sm_notify DONE");

  return NFS_REQ_OK;
}

/**
 * nlm4_Sm_Notify_Free: Frees the result structure allocated for nlm4_Sm_Notify
 *
 * Frees the result structure allocated for nlm4_Sm_Notify. Does Nothing in fact.
 *
 * @param pres        [INOUT]   Pointer to the result structure.
 *
 */
void nlm4_Sm_Notify_Free(nfs_res_t * pres)
{
  return;
}
