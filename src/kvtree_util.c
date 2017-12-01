/*
 * Copyright (c) 2009, Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 * Written by Adam Moody <moody20@llnl.gov>.
 * LLNL-CODE-411039.
 * All rights reserved.
 * This file was originally part of The Scalable Checkpoint / Restart (SCR) library.
 * For details, see https://sourceforge.net/projects/scalablecr/
 * Please also read this file: LICENSE.TXT.
*/

/* Implements some common tasks for SCR operations on hashes */

#include "kvtree.h"
#include "kvtree_util.h"
#include "kvtree_helpers.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>

int kvtree_util_set_bytecount(kvtree* hash, const char* key, unsigned long count)
{
  /* first, unset any current setting */
  kvtree_unset(hash, key);

  /* then set the new value */
  kvtree* hash2 = kvtree_setf(hash, NULL, "%s %lu", key, count);

  /* if there wasn't a hash, return failure */
  if (hash2 == NULL) {
    return KVTREE_FAILURE;
  }
  return KVTREE_SUCCESS;
}

int kvtree_util_set_crc32(kvtree* hash, const char* key, uLong crc)
{
  /* first, unset any current setting */
  kvtree_unset(hash, key);

  /* then set the new value */
  kvtree* hash2 = kvtree_setf(hash, NULL, "%s %#x", key, (uint32_t) crc);

  /* if there wasn't a hash, return failure */
  if (hash2 == NULL) {
    return KVTREE_FAILURE;
  }
  return KVTREE_SUCCESS;
}

int kvtree_util_set_int(kvtree* hash, const char* key, int value)
{
  /* first, unset any current setting */
  kvtree_unset(hash, key);

  /* then set the new value */
  kvtree* hash2 = kvtree_set_kv_int(hash, key, value);

  /* if there wasn't a hash, return failure */
  if (hash2 == NULL) {
    return KVTREE_FAILURE;
  }
  return KVTREE_SUCCESS;
}

int kvtree_util_set_unsigned_long(kvtree* hash, const char* key, unsigned long value)
{
  /* first, unset any current setting */
  kvtree_unset(hash, key);

  /* then set the new value */
  kvtree* hash2 = kvtree_setf(hash, NULL, "%s %lu", key, value);

  /* if there wasn't a hash, return failure */
  if (hash2 == NULL) {
    return KVTREE_FAILURE;
  }
  return KVTREE_SUCCESS;
}

int kvtree_util_set_str(kvtree* hash, const char* key, const char* value)
{
  /* first, unset any current setting */
  kvtree_unset(hash, key);

  /* then set the new value */
  kvtree* hash2 = kvtree_set_kv(hash, key, value);

  /* if there wasn't a hash, return failure */
  if (hash2 == NULL) {
    return KVTREE_FAILURE;
  }
  return KVTREE_SUCCESS;
}

int kvtree_util_set_int64(kvtree* hash, const char* key, int64_t value)
{
  /* first, unset any current setting */
  kvtree_unset(hash, key);

  /* then set the new value */
  kvtree* hash2 = kvtree_setf(hash, NULL, "%s %lld", key, value);

  /* if there wasn't a hash, return failure */
  if (hash2 == NULL) {
    return KVTREE_FAILURE;
  }
  return KVTREE_SUCCESS;
}

int kvtree_util_set_double(kvtree* hash, const char* key, double value)
{
  /* first, unset any current setting */
  kvtree_unset(hash, key);

  /* then set the new value */
  kvtree* hash2 = kvtree_setf(hash, NULL, "%s %f", key, value);

  /* if there wasn't a hash, return failure */
  if (hash2 == NULL) {
    return KVTREE_FAILURE;
  }
  return KVTREE_SUCCESS;
}

int kvtree_util_get_bytecount(const kvtree* hash, const char* key, unsigned long* val)
{
  int rc = KVTREE_FAILURE;

  /* check whether this key is even set */
  char* val_str = kvtree_get_val(hash, key);
  if (val_str != NULL) {
    /* convert the key string */
    *val = strtoul(val_str, NULL, 0);
    rc = KVTREE_SUCCESS;
  }

  return rc;
}

int kvtree_util_get_crc32(const kvtree* hash, const char* key, uLong* val)
{
  int rc = KVTREE_FAILURE;

  /* check whether this key is even set */
  char* val_str = kvtree_get_val(hash, key);
  if (val_str != NULL) {
    /* convert the key string */
    *val = (uLong) strtoul(val_str, NULL, 0);
    rc = KVTREE_SUCCESS;
  }

  return rc;
}

int kvtree_util_get_int(const kvtree* hash, const char* key, int* value)
{
  int rc = KVTREE_FAILURE;

  char* val_str = kvtree_elem_get_first_val(hash, key);
  if (val_str != NULL) {
    *value = atoi(val_str);
    return KVTREE_SUCCESS;
  }

  return rc;
}

int kvtree_util_get_unsigned_long(const kvtree* hash, const char* key, unsigned long* val)
{
  int rc = KVTREE_FAILURE;

  /* check whether this key is even set */
  char* val_str = kvtree_get_val(hash, key);
  if (val_str != NULL) {
    /* convert the key string */
    *val = strtoul(val_str, NULL, 0);
    rc = KVTREE_SUCCESS;
  }

  return rc;
}

int kvtree_util_get_str(const kvtree* hash, const char* key, char** val)
{
  int rc = KVTREE_FAILURE;

  /* check whether this key is even set */
  char* val_str = kvtree_get_val(hash, key);
  if (val_str != NULL) {
    /* convert the key string */
    *val = val_str;
    rc = KVTREE_SUCCESS;
  }

  return rc;
}

int kvtree_util_get_int64(const kvtree* hash, const char* key, int64_t* val)
{
  int rc = KVTREE_FAILURE;

  /* check whether this key is even set */
  char* val_str = kvtree_get_val(hash, key);
  if (val_str != NULL) {
    /* convert the key string */
    *val = (int64_t) strtoll(val_str, NULL, 0);
    rc = KVTREE_SUCCESS;
  }

  return rc;
}

int kvtree_util_get_double(const kvtree* hash, const char* key, double* val)
{
  int rc = KVTREE_FAILURE;

  /* check whether this key is even set */
  char* val_str = kvtree_get_val(hash, key);
  if (val_str != NULL) {
    /* convert the key string */
    double val_tmp;
    if (kvtree_atod(val_str, &val_tmp) == KVTREE_SUCCESS) {
      *val = val_tmp;
      rc = KVTREE_SUCCESS;
    }
  }

  return rc;
}