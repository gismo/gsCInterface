
module Fgismo
   use, intrinsic  :: iso_c_binding
   implicit none
   private

   interface
#     include "gsCMatrix.ifc"
#     include "gsCMatrixInt.ifc"
#     include "gsCVector.ifc"
#     include "gsCVectorInt.ifc"
#     include "gsCKnotVector.ifc"
#     include "gsCFunctionSet.ifc"
#     include "gsCMultiPatch.ifc"
#     include "gsCBasis.ifc"
#     include "gsCGeometry.ifc"
#     include "gsCReadFile.ifc"
   end interface

   public  t_gsmatrix
   public  f_gsmatrix_create
   public  f_gsmatrix_create_rcd
   public  f_gsmatrix_print
   public  f_gsmatrix_rows
   public  f_gsmatrix_cols
   public  f_gsmatrix_data
   public  f_gsmatrix_delete
   public  f_gsmatrix_update_data_ptr

!------------------------------------------------------------------------------------------------------------

   type :: t_gsmatrix
      type(C_PTR)                             :: c_mat          ! C/C++ gsMatrix object
      real(C_DOUBLE), dimension(:,:), pointer :: data => NULL() ! link to array in C/C++ gsMatrix
   end type t_gsmatrix

!------------------------------------------------------------------------------------------------------------

contains

!------------------------------------------------------------------------------------------------------------

function f_gsmatrix_create()
!--purpose: create empty gsmatrix object
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsmatrix_create
#endif
   implicit none
!--function result type:
   type(t_gsmatrix) :: f_gsmatrix_create

   f_gsmatrix_create%c_mat = gsMatrix_create()
   call f_gsmatrix_update_data_ptr( f_gsmatrix_create )

end function f_gsmatrix_create

!------------------------------------------------------------------------------------------------------------

function f_gsmatrix_create_rcd(nrows, ncols, data)
!--purpose: create gsmatrix object from input data
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsmatrix_create_rcd
#endif
   implicit none
!--function result type:
   type(t_gsmatrix) :: f_gsmatrix_create_rcd
!--function arguments:
   integer(C_INT)                 :: nrows, ncols
   real(C_DOUBLE), dimension(:,:) :: data

   associate( f_mat => f_gsmatrix_create_rcd )
   f_mat%c_mat = gsMatrix_create_rcd(nrows, ncols, data)
   call f_gsmatrix_update_data_ptr( f_mat )
   end associate

end function f_gsmatrix_create_rcd

!------------------------------------------------------------------------------------------------------------

subroutine f_gsmatrix_print(f_mat)
!--purpose: print contents of gsmatrix object
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsmatrix_print
#endif
   implicit none
!--subroutine arguments:
   type(t_gsmatrix) :: f_mat

   call gsMatrix_print(f_mat%c_mat)
   write(*,*) ! flush stdout(?)
end subroutine f_gsmatrix_print

!------------------------------------------------------------------------------------------------------------

function f_gsmatrix_rows(f_mat)
!--purpose: get number of rows from gsmatrix object
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsmatrix_rows
#endif
   implicit none
!--function return value:
   integer(C_INT)   :: f_gsmatrix_rows
!--function arguments:
   type(t_gsmatrix) :: f_mat

   f_gsmatrix_rows = gsMatrix_rows(f_mat%c_mat)
end function f_gsmatrix_rows

!------------------------------------------------------------------------------------------------------------

function f_gsmatrix_cols(f_mat)
!--purpose: get number of columns from gsmatrix object
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsmatrix_cols
#endif
   implicit none
!--function return value:
   integer(C_INT)   :: f_gsmatrix_cols
!--function arguments:
   type(t_gsmatrix) :: f_mat

   f_gsmatrix_cols = gsMatrix_cols(f_mat%c_mat)
end function f_gsmatrix_cols

!------------------------------------------------------------------------------------------------------------

subroutine f_gsmatrix_update_data_ptr(f_mat)
!--purpose: reconnect f_mat%data after possible (re)allocation in C/C++
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsmatrix_update_data_ptr
#endif
   implicit none
!--subroutine arguments:
   type(t_gsmatrix) :: f_mat
!--local variables:
   integer(C_INT)   :: nrows, ncols

   nrows  = gsMatrix_rows(f_mat%c_mat)
   ncols  = gsMatrix_cols(f_mat%c_mat)
   if (nrows.le.0 .or. ncols.le.0) then
      f_mat%data => NULL()
   else
      call C_F_POINTER( gsMatrix_data(f_mat%c_mat), f_mat%data, (/ nrows, ncols /))
   endif
end subroutine f_gsmatrix_update_data_ptr

!------------------------------------------------------------------------------------------------------------

function f_gsmatrix_data(f_mat)
!--purpose: get pointer to data array of a gsmatrix object
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsmatrix_data
#endif
   implicit none
!--function return value:
   real(C_DOUBLE), dimension(:,:), pointer :: f_gsmatrix_data
!--function arguments:
   type(t_gsmatrix) :: f_mat

   call f_gsmatrix_update_data_ptr(f_mat)
   f_gsmatrix_data => f_mat%data
end function f_gsmatrix_data

!------------------------------------------------------------------------------------------------------------

subroutine f_gsmatrix_delete(f_mat)
!--purpose: destroy a gsmatrix object
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsmatrix_delete
#endif
!--subroutine arguments:
   type(t_gsmatrix) :: f_mat

   call gsMatrix_delete(f_mat%c_mat)
   nullify(f_mat%data)
end subroutine f_gsmatrix_delete

!------------------------------------------------------------------------------------------------------------

end module Fgismo
