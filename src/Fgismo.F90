
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

   public t_gsmatrix
   public f_gsmatrix_create
   public f_gsmatrix_create_rcd
   public f_gsmatrix_print
   public f_gsmatrix_rows
   public f_gsmatrix_cols
   public f_gsmatrix_data

!------------------------------------------------------------------------------------------------------------

   type :: t_gsmatrix
      type(C_PTR)                             :: c_mat
      real(C_DOUBLE), dimension(:,:), pointer :: data => NULL()
   end type t_gsmatrix

!------------------------------------------------------------------------------------------------------------

contains

!------------------------------------------------------------------------------------------------------------

function f_gsmatrix_create_rcd(nrows, ncols, data)
!--function result type:
   type(t_gsmatrix) :: f_gsmatrix_create_rcd
!--function arguments:
   integer(C_INT)   :: nrows, ncols
   real(C_DOUBLE), dimension(:,:) :: data
!--local variables:

   associate( f_mat => f_gsmatrix_create_rcd )
   f_mat%c_mat = gsMatrix_create_rcd(nrows, ncols, data)
   f_mat%data  = f_gsmatrix_data(f_mat)
   end associate

end function f_gsmatrix_create_rcd

!------------------------------------------------------------------------------------------------------------

function f_gsmatrix_create()
!--function result type:
   type(t_gsmatrix) :: f_gsmatrix_create

   f_gsmatrix_create%c_mat = gsMatrix_create()
   f_gsmatrix_create%data  => NULL()
end function f_gsmatrix_create

!------------------------------------------------------------------------------------------------------------

subroutine f_gsmatrix_print(f_mat)
!--subroutine arguments:
   type(t_gsmatrix) :: f_mat

   call gsMatrix_print(f_mat%c_mat)
end subroutine f_gsmatrix_print

!------------------------------------------------------------------------------------------------------------

function f_gsmatrix_rows(f_mat)
!--function return value:
   integer(C_INT)   :: f_gsmatrix_rows
!--function arguments:
   type(t_gsmatrix) :: f_mat

   f_gsmatrix_rows = gsMatrix_rows(f_mat%c_mat)
end function f_gsmatrix_rows

!------------------------------------------------------------------------------------------------------------

function f_gsmatrix_cols(f_mat)
!--function return value:
   integer(C_INT)   :: f_gsmatrix_cols
!--function arguments:
   type(t_gsmatrix) :: f_mat

   f_gsmatrix_cols = gsMatrix_cols(f_mat%c_mat)
end function f_gsmatrix_cols

!------------------------------------------------------------------------------------------------------------

function f_gsmatrix_data(f_mat)
!--function return value:
   real(C_DOUBLE), dimension(:,:), pointer :: f_gsmatrix_data
!--function arguments:
   type(t_gsmatrix) :: f_mat
!--local variables:
   integer(C_INT)   :: nrows, ncols
   type(C_PTR)      :: c_data

   nrows  = gsMatrix_rows(f_mat%c_mat)
   ncols  = gsMatrix_cols(f_mat%c_mat)
   c_data = gsMatrix_data(f_mat%c_mat)
   call C_F_POINTER(c_data, f_gsmatrix_data, (/ nrows, ncols /))
end function f_gsmatrix_data

!------------------------------------------------------------------------------------------------------------

subroutine f_gsmatrix_delete(f_mat)
!--subroutine arguments:
   type(t_gsmatrix) :: f_mat

   call gsMatrix_delete(f_mat%c_mat)
   nullify(f_mat%data)
end subroutine f_gsmatrix_delete

!------------------------------------------------------------------------------------------------------------

end module Fgismo
