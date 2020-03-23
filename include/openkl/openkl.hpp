// Software License for MTL5
//
// Copyright (c) 2017 SimuNova UG, www.simunova.com.
// All rights reserved.
// Author: Peter Gottschling (peter.gottschling@simunova.com)
//
// This file is part of the Matrix Template Library 5
//
// See also tools/license/license.mtl.txt in the distribution.
//
// File: driver.hpp
// Date: 2020-03-23

#ifndef MTL_INTERFACE_KPU_DRIVER_H
#define MTL_INTERFACE_KPU_DRIVER_H

#include <mtl/interface/universal/posit/posit_fwd.hpp>

#include <mtl/scalar/update.hpp>

#include <mtl/mat/irows.hpp>


namespace mtl {
namespace interface {
namespace kpu {

using posit32= sw::unum::posit<32, 2>; // or something else    

class object_id {}; // TBD  
    
/// Create dense (column) vector of size \p s and get data from address \p data and following
object_id create_dense_vector(size_t s, const posit32& data);

/// Read data from vector \p v. Error if \p v wasn't created with \ref create_dense_vector.
void read_dense_vector(object_id v, posit32& data);

/// \p u up= \p v + \p w; Error if arguments weren't created with \ref create_dense_vector.
/** up= is either =, += or -= 
 *  We can start with just storing and add the other versions later. **/
void add_dense_vector(object_id u, object_id v, object_id w, scalar::update_store);
void add_dense_vector(object_id u, object_id v, object_id w, scalar::update_plus);
void add_dense_vector(object_id u, object_id v, object_id w, scalar::update_minus);

/// \p u up= \p v - \p w; Error if arguments weren't created with \ref create_dense_vector.
void subtract_dense_vector(object_id u, object_id v, object_id w, scalar::update_store);
void subtract_dense_vector(object_id u, object_id v, object_id w, scalar::update_plus);
void subtract_dense_vector(object_id u, object_id v, object_id w, scalar::update_minus);

/** Create dense row-major matrix with \p nr rows and \p nc columns and get data from address 
 *  \p data and following **/
object_id create_dense_matrix(size_t nr, size_t nc, const posit32& data);

/// Read data from matrix \p A. Error if \p v wasn't created with \ref create_dense_matrix.
void read_dense_matrix(object_id A, posit32& data);

/// Dense matrix vector product \p u = \p A * \p v.
void dense_matrix_vector_product(object_id u, object_id A, object_id v);


/// Destroy object of any kind. 
/** Should we check that the last operation was a read? Would create extra housekeeping. So, probably not.
 *  It is users responsibility. **/
void destroy(object_id);



// ------------------------------
// Sparse Matrices probably later

/// Create CRS matrix with \p nr rows and \p nc columns, holding \p nnz entries.
/** Index data start at \p row_indices and \p column_indices respectively; data at \p data.
 *  Memory needed: (nr+1 + nnz) size_t entries and nnz posit32 entries
 *  see: https://en.wikipedia.org/wiki/Sparse_matrix#Compressed_sparse_row_(CSR,_CRS_or_Yale_format) **/
object_id create_crs_matrix(size_t nr, size_t nc, size_t nnz, const size_t& row_indices,
                            const size_t& column_indices, const posit32& data);

// no read operation as sparse matrices are set up only by MTL

/// CRS matrix vector product \p u up= \p A * \p v.
template <typename Updater>
void crs_matrix_vector_product(object_id u, object_id A, object_id v, Updater);
#if 0
{
    // something like:
    for (size_t r : mat::irows(A)) { // iterate over all rows; can be done in parallel
        Updater::init(u[r]);
        posit32 accu{0};
        for (size_t i= A.row_indices[r], end= A.row_indices[r+1]; i < end; ++i)
            accu+= A.data[i] * v[A.column_indices[i]];
        Updater::update(accu, u[r]);    
    }
}
#endif




}}} // namespace mtl::interface::kpu

#endif // MTL_INTERFACE_KPU_DRIVER_H
