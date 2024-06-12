
module Fgismo
   use, intrinsic  :: iso_c_binding
   implicit none
   private

#  include "gismo.ifc"

   public  t_gsmatrix
   public  t_gsfunctionset
   public  t_gsgeometry

   ! functions from gsCMatrix.ifc:
   public  f_gsmatrix_create
   public  f_gsmatrix_create_rcd
   public  f_gsmatrix_print
   public  f_gsmatrix_rows
   public  f_gsmatrix_cols
   public  f_gsmatrix_data
   public  f_gsmatrix_delete
   public  f_gsmatrix_update_data_ptr

   ! functions from gsCFunctionSet.ifc:
   public  f_gsfunctionset_delete
   public  f_gsfunctionset_print
   public  f_gsfunctionset_domaindim
   public  f_gsfunctionset_eval_into

   ! functions from gsCReadFile.ifc:
   public  f_gscreadfile

   ! functions from gsCGeometry.ifc:
   public  f_gsgeometry_recoverpoints

!------------------------------------------------------------------------------------------------------------

   type :: t_gsmatrix
      type(C_PTR)                             :: c_mat          ! C/C++ gsMatrix object
      real(C_DOUBLE), dimension(:,:), pointer :: data => NULL() ! link to array in C/C++ gsMatrix
   end type t_gsmatrix

!------------------------------------------------------------------------------------------------------------

   type :: t_gsfunctionset
      type(C_PTR)                             :: c_fs           ! C/C++ gsFunctionSet object
   end type t_gsfunctionset

!------------------------------------------------------------------------------------------------------------

   type, extends(t_gsfunctionset) :: t_gsgeometry               ! C/C++ gsGeometry object
   end type t_gsgeometry

!------------------------------------------------------------------------------------------------------------

contains

!------------------------------------------------------------------------------------------------------------
! wrap functions from gsCMatrix.ifc:
!------------------------------------------------------------------------------------------------------------

function f_gsmatrix_create() result(f_mat)
!--purpose: create empty gsmatrix object
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsmatrix_create
#endif
   implicit none
!--function result:
   type(t_gsmatrix) :: f_mat

   f_mat%c_mat = gsMatrix_create()
   call f_gsmatrix_update_data_ptr( f_mat )

end function f_gsmatrix_create

!------------------------------------------------------------------------------------------------------------

function f_gsmatrix_create_rcd(nrows, ncols, data) result(f_mat)
!--purpose: create gsmatrix object from input data
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsmatrix_create_rcd
#endif
   implicit none
!--function result:
   type(t_gsmatrix) :: f_mat
!--function arguments:
   integer(C_INT)                 :: nrows, ncols
   real(C_DOUBLE), dimension(:,:) :: data

   f_mat%c_mat = gsMatrix_create_rcd(nrows, ncols, data)
   call f_gsmatrix_update_data_ptr( f_mat )

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

function f_gsmatrix_rows(f_mat) result(nrows)
!--purpose: get number of rows from gsmatrix object
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsmatrix_rows
#endif
   implicit none
!--function result:
   integer(C_INT)   :: nrows
!--function arguments:
   type(t_gsmatrix) :: f_mat

   nrows = gsMatrix_rows(f_mat%c_mat)
end function f_gsmatrix_rows

!------------------------------------------------------------------------------------------------------------

function f_gsmatrix_cols(f_mat) result(ncols)
!--purpose: get number of columns from gsmatrix object
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsmatrix_cols
#endif
   implicit none
!--function result:
   integer(C_INT)   :: ncols
!--function arguments:
   type(t_gsmatrix) :: f_mat

   ncols = gsMatrix_cols(f_mat%c_mat)
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

function f_gsmatrix_data(f_mat) result(f_data_ptr)
!--purpose: get pointer to data array of a gsmatrix object
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsmatrix_data
#endif
   implicit none
!--function result:
   real(C_DOUBLE), dimension(:,:), pointer :: f_data_ptr
!--function arguments:
   type(t_gsmatrix) :: f_mat

   call f_gsmatrix_update_data_ptr(f_mat)
   f_data_ptr => f_mat%data
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
! wrap functions of gsFunctionSet.ifc:
!------------------------------------------------------------------------------------------------------------

subroutine f_gsfunctionset_delete(f_fs)
!--purpose: destroy a gsfunctionset object
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsfunctionset_delete
#endif
!--subroutine arguments:
   class(t_gsfunctionset) :: f_fs

   call gsFunctionSet_delete(f_fs%c_fs)
end subroutine f_gsfunctionset_delete

!------------------------------------------------------------------------------------------------------------

subroutine f_gsfunctionset_print(f_fs)
!--purpose: print contents of a gsfunctionset object
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsfunctionset_print
#endif
!--subroutine arguments:
   class(t_gsfunctionset) :: f_fs

   call gsfunctionset_print(f_fs%c_fs)
end subroutine f_gsfunctionset_print

!------------------------------------------------------------------------------------------------------------

function f_gsfunctionset_domaindim(f_fs) result(domdim)
!--purpose: get domain dimension of a gsfunctionset object
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsfunctionset_domaindim
#endif
!--function result:
   integer(C_INT)         :: domdim
!--function arguments:
   class(t_gsfunctionset) :: f_fs

   domdim = gsfunctionset_domaindim(f_fs%c_fs)
end function f_gsfunctionset_domaindim

!------------------------------------------------------------------------------------------------------------
!     GISMO_EXPORT int gsFunctionSet_targetDim(gsCFunctionSet * fs);

!------------------------------------------------------------------------------------------------------------
!     GISMO_EXPORT gsCMatrix* gsFunctionSet_support(gsCFunctionSet * fs);

!------------------------------------------------------------------------------------------------------------

subroutine f_gsfunctionset_eval_into(f_fs, f_uv, f_result)
!--purpose: evaluate gsfunctionset object at parameter values uv into result matrix
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsfunctionset_eval_into
#endif
!--subroutine arguments:
   class(t_gsfunctionset) :: f_fs
   type(t_gsmatrix)       :: f_uv, f_result

   call gsfunctionset_eval_into(f_fs%c_fs, f_uv%c_mat, f_result%c_mat )
   call f_gsmatrix_update_data_ptr( f_result )
end subroutine f_gsfunctionset_eval_into

!------------------------------------------------------------------------------------------------------------
!     GISMO_EXPORT void gsFunctionSet_deriv_into(gsCFunctionSet * fs,
!                                                gsCMatrix * u,
!                                                gsCMatrix * result);

!------------------------------------------------------------------------------------------------------------

!------------------------------------------------------------------------------------------------------------
! wrap functions of gsCReadFile.ifc:
!------------------------------------------------------------------------------------------------------------

subroutine f_gscreadfile(filename, f_fs)
!--purpose: read a gsgeometry object from a file
#ifdef _WIN32
!dec$ attributes dllexport :: f_gscreadfile
#endif
!--subroutine arguments:
   character(len=1,kind=C_CHAR) :: filename(*)
   class(t_gsfunctionset)       :: f_fs

   f_fs%c_fs = gsCReadFile(filename)
end subroutine f_gscreadfile

!------------------------------------------------------------------------------------------------------------
! wrap functions of gsCGeometry.ifc:
!------------------------------------------------------------------------------------------------------------

subroutine f_gsgeometry_recoverpoints(f_geom, f_uv, f_xyz, k, accuracy)
!--purpose: invert coordinates (x,y), (x,z), or (y,z) to corresponding (u,v) and fill in missing coordinate
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsgeometry_recoverpoints
#endif
!--subroutine arguments:
   type(t_gsgeometry)       :: f_geom
   type(t_gsmatrix)         :: f_uv, f_xyz
   integer(C_INT)           :: k
   real(C_DOUBLE)           :: accuracy

   call gsGeometry_recoverPoints(f_geom%c_fs, f_uv%c_mat, f_xyz%c_mat, k, accuracy)
   call f_gsmatrix_update_data_ptr( f_uv )
   call f_gsmatrix_update_data_ptr( f_xyz )

end subroutine f_gsgeometry_recoverpoints

!------------------------------------------------------------------------------------------------------------

end module Fgismo
