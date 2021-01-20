/******************************************************************************
 *
 *  Copyright (C) 2009-2012 Broadcom Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/

#ifndef BTIF_DM_H
#define BTIF_DM_H

#include "bta_api.h"
#include "bte_appl.h"
#include "btif_uid.h"
#include "osi/include/list.h"

/*******************************************************************************
 *  Functions
 ******************************************************************************/
void btif_dm_init(uid_set_t* set);
void btif_dm_cleanup(void);

/**
 * BTIF callback to switch context from bte to btif
 */
void bte_dm_evt(tBTA_DM_SEC_EVT event, tBTA_DM_SEC* p_data);

/**
 * Notify BT disable being initiated. DM may chose to abort
 * pending commands, like pairing
 */
void btif_dm_on_disable(void);

/**
 * Callout for handling io_capabilities request
 */
void btif_dm_proc_io_req(const RawAddress& bd_addr, tBTA_IO_CAP* p_io_cap,
                         tBTA_OOB_DATA* p_oob_data, tBTA_AUTH_REQ* p_auth_req,
                         bool is_orig);
/**
 * Callout for handling io_capabilities response
 */
void btif_dm_proc_io_rsp(const RawAddress& bd_addr, tBTA_IO_CAP io_cap,
                         tBTA_OOB_DATA oob_data, tBTA_AUTH_REQ auth_req);

/**
 * Out-of-band functions
 */
void btif_dm_set_oob_for_io_req(tBTA_OOB_DATA* p_oob_data);
void btif_dm_set_oob_for_le_io_req(const RawAddress& bd_addr,
                                   tBTA_OOB_DATA* p_oob_data,
                                   tBTA_LE_AUTH_REQ* p_auth_req);
#ifdef BTIF_DM_OOB_TEST
void btif_dm_load_local_oob(void);
void btif_dm_proc_loc_oob(bool valid, const Octet16& c, const Octet16& r);
bool btif_dm_proc_rmt_oob(const RawAddress& bd_addr, Octet16* p_c,
                          Octet16* p_r);
#endif /* BTIF_DM_OOB_TEST */

/*callout for reading SMP properties from Text file*/
bool btif_dm_get_smp_config(tBTE_APPL_CFG* p_cfg);

typedef struct {
  bool is_penc_key_rcvd;
  tBTM_LE_PENC_KEYS penc_key; /* received peer encryption key */
  bool is_pcsrk_key_rcvd;
  tBTM_LE_PCSRK_KEYS pcsrk_key; /* received peer device SRK */
  bool is_pid_key_rcvd;
  tBTM_LE_PID_KEYS pid_key; /* peer device ID key */
  bool is_lenc_key_rcvd;
  tBTM_LE_LENC_KEYS
      lenc_key; /* local encryption reproduction keys LTK = = d1(ER,DIV,0)*/
  bool is_lcsrk_key_rcvd;
  tBTM_LE_LCSRK_KEYS lcsrk_key; /* local device CSRK = d1(ER,DIV,1)*/
  bool is_lidk_key_rcvd;        /* local identity key received */
} btif_dm_ble_cb_t;

#define BTIF_DM_LE_KEY_PENC BTA_LE_KEY_PENC
#define BTIF_DM_LE_KEY_PID BTA_LE_KEY_PID
#define BTIF_DM_LE_KEY_PCSRK BTA_LE_KEY_PCSRK
#define BTIF_DM_LE_KEY_LENC BTA_LE_KEY_LENC
#define BTIF_DM_LE_KEY_LID BTA_LE_KEY_LID
#define BTIF_DM_LE_KEY_LCSRK BTA_LE_KEY_LCSRK

#define BTIF_DM_LE_LOCAL_KEY_IR (1 << 0)
#define BTIF_DM_LE_LOCAL_KEY_IRK (1 << 1)
#define BTIF_DM_LE_LOCAL_KEY_DHK (1 << 2)
#define BTIF_DM_LE_LOCAL_KEY_ER (1 << 3)

void btif_dm_load_ble_local_keys(void);
void btif_dm_get_ble_local_keys(tBTA_DM_BLE_LOCAL_KEY_MASK* p_key_mask,
                                Octet16* p_er,
                                tBTA_BLE_LOCAL_ID_KEYS* p_id_keys);
void btif_dm_save_ble_bonding_keys(RawAddress& bd_addr);
void btif_dm_remove_ble_bonding_keys(void);
void btif_dm_ble_sec_req_evt(tBTA_DM_BLE_SEC_REQ* p_ble_req, bool is_consent);

void btif_dm_update_ble_remote_properties(const RawAddress& bd_addr,
                                          BD_NAME bd_name,
                                          tBT_DEVICE_TYPE dev_type);
void btif_vendor_update_add_on_features();

void btif_vendor_update_whitelisted_media_players();

bool fetch_whitelisted_media_players(list_t** bl_devices);

#endif
