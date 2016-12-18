/*****************************************************************************
  Copyright (c) 2014, Intel Corp.
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of Intel Corporation nor the names of its contributors
      may be used to endorse or promote products derived from this software
      without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
  THE POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************
* Contents: Native high-level C interface to LAPACK function dsbevx_2stage
* Author: Intel Corporation
* Generated November 2015
*****************************************************************************/

#include "lapacke_utils.h"

lapack_int LAPACKE_dsbevx_2stage( int matrix_layout, char jobz, char range, char uplo,
                           lapack_int n, lapack_int kd, double* ab,
                           lapack_int ldab, double* q, lapack_int ldq,
                           double vl, double vu, lapack_int il, lapack_int iu,
                           double abstol, lapack_int* m, double* w, double* z,
                           lapack_int ldz, lapack_int* ifail )
{
    lapack_int info = 0;
    lapack_int lwork = -1;
    lapack_int* iwork = NULL;
    double* work = NULL;
    double work_query;
    if( matrix_layout != LAPACK_COL_MAJOR && matrix_layout != LAPACK_ROW_MAJOR ) {
        LAPACKE_xerbla( "LAPACKE_dsbevx_2stage", -1 );
        return -1;
    }
#ifndef LAPACK_DISABLE_NAN_CHECK
    /* Optionally check input matrices for NaNs */
    if( LAPACKE_dsb_nancheck( matrix_layout, uplo, n, kd, ab, ldab ) ) {
        return -7;
    }
    if( LAPACKE_d_nancheck( 1, &abstol, 1 ) ) {
        return -15;
    }
    if( LAPACKE_lsame( range, 'v' ) ) {
        if( LAPACKE_d_nancheck( 1, &vl, 1 ) ) {
            return -11;
        }
    }
    if( LAPACKE_lsame( range, 'v' ) ) {
        if( LAPACKE_d_nancheck( 1, &vu, 1 ) ) {
            return -12;
        }
    }
#endif
    /* Query optimal working array(s) size */
    info = LAPACKE_dsbevx_2stage_work( matrix_layout, jobz, range, uplo, n, kd, ab,
                                ldab, q, ldq, vl, vu, il, iu, abstol, m, w, z,
                                ldz, &work_query, lwork, iwork, ifail );
    if( info != 0 ) {
        goto exit_level_0;
    }
    lwork = (lapack_int) work_query;
    /* Allocate memory for working array(s) */
    iwork = (lapack_int*)LAPACKE_malloc( sizeof(lapack_int) * MAX(1,5*n) );
    if( iwork == NULL ) {
        info = LAPACK_WORK_MEMORY_ERROR;
        goto exit_level_0;
    }
    work = (double*)LAPACKE_malloc( sizeof(double) * lwork );
    if( work == NULL ) {
        info = LAPACK_WORK_MEMORY_ERROR;
        goto exit_level_1;
    }
    /* Call middle-level interface */
    info = LAPACKE_dsbevx_2stage_work( matrix_layout, jobz, range, uplo, n, kd, ab,
                                ldab, q, ldq, vl, vu, il, iu, abstol, m, w, z,
                                ldz, work, lwork, iwork, ifail );
    /* Release memory and exit */
    LAPACKE_free( work );
exit_level_1:
    LAPACKE_free( iwork );
exit_level_0:
    if( info == LAPACK_WORK_MEMORY_ERROR ) {
        LAPACKE_xerbla( "LAPACKE_dsbevx_2stage", info );
    }
    return info;
}
