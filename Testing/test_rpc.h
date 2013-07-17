/*
 * Copyright (C) 2013 Argonne National Laboratory, Department of Energy,
 *                    UChicago Argonne, LLC and The HDF Group.
 * All rights reserved.
 *
 * The full copyright notice, including terms governing use, modification,
 * and redistribution, is contained in the COPYING file that can be
 * found at the root of the source code distribution tree.
 */

#ifndef TEST_RPC_H
#define TEST_RPC_H

#include "mercury_macros.h"
#include "mercury_proc.h"

#ifdef HG_HAS_BOOST
/* 1. Generate processor and struct for additional struct types
 * MERCURY_GEN_PROC( struct_type_name, fields )
 */
MERCURY_GEN_PROC( bla_handle_t, ((uint64_t)(cookie)) )

/* Dummy function that needs to be shipped (already defined) */
int bla_open(const char *path, bla_handle_t handle, int *event_id);

/* 2. Generate processor and struct for required input/output structs
 * MERCURY_GEN_PROC( struct_type_name, fields )
 */
MERCURY_GEN_PROC( bla_open_in_t, ((hg_string_t)(path)) ((bla_handle_t)(handle)) )
MERCURY_GEN_PROC( bla_open_out_t, ((int32_t)(ret)) ((int32_t)(event_id)) )
#else
/* Define bla_handle_t */
typedef struct {
    uint64_t cookie;
} bla_handle_t;

/* Dummy function that needs to be shipped (already defined) */
int bla_open(const char *path, bla_handle_t handle, int *event_id);

/* Define hg_proc_bla_handle_t */
static inline int hg_proc_bla_handle_t(hg_proc_t proc, void *data)
{
    int ret = HG_SUCCESS;
    bla_handle_t *struct_data = (bla_handle_t *) data;

    ret = hg_proc_uint64_t(proc, &struct_data->cookie);
    if (ret != HG_SUCCESS) {
        HG_ERROR_DEFAULT("Proc error");
        ret = HG_FAIL;
        return ret;
    }

    return ret;
}

/* Define bla_open_in_t */
typedef struct {
    hg_string_t path;
    bla_handle_t handle;
} bla_open_in_t;

/* Define hg_proc_bla_open_in_t */
static inline int hg_proc_bla_open_in_t(hg_proc_t proc, void *data)
{
    int ret = HG_SUCCESS;
    bla_open_in_t *struct_data = (bla_open_in_t *) data;

    ret = hg_proc_hg_string_t(proc, &struct_data->path);
    if (ret != HG_SUCCESS) {
        HG_ERROR_DEFAULT("Proc error");
        ret = HG_FAIL;
        return ret;
    }

    ret = hg_proc_bla_handle_t(proc, &struct_data->handle);
    if (ret != HG_SUCCESS) {
        HG_ERROR_DEFAULT("Proc error");
        ret = HG_FAIL;
        return ret;
    }

    return ret;
}

/* Define bla_open_out_t */
typedef struct {
    int32_t ret;
    int32_t event_id;
} bla_open_out_t;

/* Define hg_proc_bla_open_out_t */
static inline int hg_proc_bla_open_out_t(hg_proc_t proc, void *data)
{
    int ret = HG_SUCCESS;
    bla_open_out_t *struct_data = (bla_open_out_t *) data;

    ret = hg_proc_int32_t(proc, &struct_data->ret);
    if (ret != HG_SUCCESS) {
        HG_ERROR_DEFAULT("Proc error");
        ret = HG_FAIL;
        return ret;
    }

    ret = hg_proc_int32_t(proc, &struct_data->event_id);
    if (ret != HG_SUCCESS) {
        HG_ERROR_DEFAULT("Proc error");
        ret = HG_FAIL;
        return ret;
    }

    return ret;
}
#endif

#endif /* TEST_RPC_H */