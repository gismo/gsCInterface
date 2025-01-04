
module Fgismo
   use, intrinsic  :: iso_c_binding
   implicit none
   private

#  include "gismo.ifc"

   public  t_gsvector
   public  t_gsvectorint
   public  t_gsmatrix
   public  t_gsfunctionset
   public  t_gsgeometry
   public  t_gsgeometrytransform

   ! functions from gsCVector.ifc:
   public  f_gsvector_create
   public  f_gsvector_create_rd
   public  f_gsvector_print
   public  f_gsvector_rows
   public  f_gsvector_cols
   public  f_gsvector_data
   public  f_gsvector_delete
   public  f_gsvector_update_data_ptr

   ! functions from gsCVectorInt.ifc:
   public  f_gsvectorint_create
   public  f_gsvectorint_create_rd
   public  f_gsvectorint_print
   public  f_gsvectorint_rows
   public  f_gsvectorint_cols
   public  f_gsvectorint_data
   public  f_gsvectorint_delete
   public  f_gsvectorint_update_data_ptr

   ! functions from gsCMatrix.ifc:
   public  f_gsmatrix_create
   public  f_gsmatrix_create_rc
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
   public  f_gsfunctionset_deriv_into

   ! functions from gsCReadFile.ifc:
   public  f_gscreadfile

   ! functions from gsCGeometry.ifc:
   public  f_gsgeometry_delete
   public  f_gsgeometry_print
   public  f_gsgeometry_recoverpoints
   public  f_gsgeometry_recoverpointgrid
   public  f_gsgeometry_eval_into
   public  f_gsgeometry_deriv_into

   ! functions from gsCGeometryTransform.ifc:
   public  f_gsgeometrytransform_create
   public  f_gsgeometrytransform_delete
   public  f_gsgeometrytransform_print
   public  f_gsgeometrytransform_recoverpoints
   public  f_gsgeometrytransform_recoverpointgrid
   public  f_gsgeometrytransform_eval_into
   public  f_gsgeometrytransform_deriv_into

!------------------------------------------------------------------------------------------------------------

   type :: t_gsvector
      type(C_PTR)                             :: c_vec          ! C/C++ gsVector object
      real(C_DOUBLE), dimension(:),   pointer :: data => NULL() ! link to array in C/C++ gsVector
   end type t_gsvector

!------------------------------------------------------------------------------------------------------------

   type :: t_gsvectorint
      type(C_PTR)                             :: c_vec          ! C/C++ gsVector object
      real(C_INT),    dimension(:),   pointer :: data => NULL() ! link to array in C/C++ gsVector
   end type t_gsvectorint

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

   ! define delete, print, eval_into --> functionset_delete, print, eval_into
   interface f_gsgeometry_delete
      module procedure f_gsfunctionset_delete
   end interface
   interface f_gsgeometry_print
      module procedure f_gsfunctionset_print
   end interface
   interface f_gsgeometry_eval_into
      module procedure f_gsfunctionset_eval_into
   end interface
   interface f_gsgeometry_deriv_into
      module procedure f_gsfunctionset_deriv_into
   end interface

!------------------------------------------------------------------------------------------------------------

   type, extends(t_gsgeometry) :: t_gsgeometrytransform         ! C/C++ gsGeometryTransform object
   end type t_gsgeometrytransform

   ! define delete, print, eval_into --> geometry_delete, print, eval_into
   interface f_gsgeometrytransform_delete
      module procedure f_gsfunctionset_delete
   end interface
   interface f_gsgeometrytransform_print
      module procedure f_gsfunctionset_print
   end interface
   interface f_gsgeometrytransform_eval_into
      module procedure f_gsfunctionset_eval_into
   end interface
   interface f_gsgeometrytransform_deriv_into
      module procedure f_gsfunctionset_deriv_into
   end interface
   interface f_gsgeometrytransform_recoverpoints
      module procedure f_gsgeometry_recoverpoints
   end interface
   interface f_gsgeometrytransform_recoverpointgrid
      module procedure f_gsgeometry_recoverpointgrid
   end interface

!------------------------------------------------------------------------------------------------------------

contains

!------------------------------------------------------------------------------------------------------------
! wrap functions from gsCVector.ifc:
!------------------------------------------------------------------------------------------------------------

function f_gsvector_create() result(f_vec)
!--purpose: create empty gsvector object
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsvector_create
#endif
   implicit none
!--function result:
   type(t_gsvector) :: f_vec

   f_vec%c_vec = gsVector_create()
   call f_gsvector_update_data_ptr( f_vec )

end function f_gsvector_create

!------------------------------------------------------------------------------------------------------------

function f_gsvector_create_rd(nrows, data) result(f_vec)
!--purpose: create gsvector object from input data
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsvector_create_rd
#endif
   implicit none
!--function result:
   type(t_gsvector) :: f_vec
!--function arguments:
   integer(C_INT)                 :: nrows
   real(C_DOUBLE), dimension(:)   :: data

   f_vec%c_vec = gsVector_create_rd(nrows, data)
   call f_gsvector_update_data_ptr( f_vec )

end function f_gsvector_create_rd

!------------------------------------------------------------------------------------------------------------

subroutine f_gsvector_print(f_vec)
!--purpose: print contents of gsvector object
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsvector_print
#endif
   implicit none
!--subroutine arguments:
   type(t_gsvector) :: f_vec

   call gsVector_print(f_vec%c_vec)
!--   write(*,*) ! flush stdout(?)
end subroutine f_gsvector_print

!------------------------------------------------------------------------------------------------------------

function f_gsvector_rows(f_vec) result(nrows)
!--purpose: get number of rows from gsvector object
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsvector_rows
#endif
   implicit none
!--function result:
   integer(C_INT)   :: nrows
!--function arguments:
   type(t_gsvector) :: f_vec

   nrows = gsVector_rows(f_vec%c_vec)
end function f_gsvector_rows

!------------------------------------------------------------------------------------------------------------

function f_gsvector_cols(f_vec) result(ncols)
!--purpose: get number of columns from gsvector object
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsvector_cols
#endif
   implicit none
!--function result:
   integer(C_INT)   :: ncols
!--function arguments:
   type(t_gsvector) :: f_vec

   ncols = gsVector_cols(f_vec%c_vec)
end function f_gsvector_cols

!------------------------------------------------------------------------------------------------------------

subroutine f_gsvector_update_data_ptr(f_vec)
!--purpose: reconnect f_vec%data after possible (re)allocation in C/C++
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsvector_update_data_ptr
#endif
   implicit none
!--subroutine arguments:
   type(t_gsvector) :: f_vec
!--local variables:
   integer(C_INT)   :: nrows

   nrows  = gsVector_rows(f_vec%c_vec)
   if (nrows.le.0) then
      f_vec%data => NULL()
   else
      call C_F_POINTER( gsVector_data(f_vec%c_vec), f_vec%data, (/ nrows /))
   endif
end subroutine f_gsvector_update_data_ptr

!------------------------------------------------------------------------------------------------------------

function f_gsvector_data(f_vec) result(f_data_ptr)
!--purpose: get pointer to data array of a gsvector object
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsvector_data
#endif
   implicit none
!--function result:
   real(C_DOUBLE), dimension(:),   pointer :: f_data_ptr
!--function arguments:
   type(t_gsvector) :: f_vec

   call f_gsvector_update_data_ptr(f_vec)
   f_data_ptr => f_vec%data
end function f_gsvector_data

!------------------------------------------------------------------------------------------------------------

subroutine f_gsvector_delete(f_vec)
!--purpose: destroy a gsvector object
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsvector_delete
#endif
!--subroutine arguments:
   type(t_gsvector) :: f_vec

   call gsVector_delete(f_vec%c_vec)
   nullify(f_vec%data)
end subroutine f_gsvector_delete

!------------------------------------------------------------------------------------------------------------
! wrap functions from gsCVectorInt.ifc:
!------------------------------------------------------------------------------------------------------------

function f_gsvectorint_create() result(f_vec)
!--purpose: create empty vectorint object
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsvectorint_create
#endif
   implicit none
!--function result:
   type(t_gsvectorint) :: f_vec

   f_vec%c_vec = gsVectorInt_create()
   call f_gsvectorint_update_data_ptr( f_vec )

end function f_gsvectorint_create

!------------------------------------------------------------------------------------------------------------

function f_gsvectorint_create_rd(nrows, data) result(f_vec)
!--purpose: create vectorint object from input data
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsvectorint_create_rd
#endif
   implicit none
!--function result:
   type(t_gsvectorint) :: f_vec
!--function arguments:
   integer(C_INT)                 :: nrows
   integer(C_INT), dimension(:)   :: data

   f_vec%c_vec = gsVectorInt_create_rd(nrows, data)
   call f_gsvectorint_update_data_ptr( f_vec )

end function f_gsvectorint_create_rd

!------------------------------------------------------------------------------------------------------------

subroutine f_gsvectorint_print(f_vec)
!--purpose: print contents of vectorint object
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsvectorint_print
#endif
   implicit none
!--subroutine arguments:
   type(t_gsvectorint) :: f_vec

   call gsVectorInt_print(f_vec%c_vec)
!--   write(*,*) ! flush stdout(?)
end subroutine f_gsvectorint_print

!------------------------------------------------------------------------------------------------------------

function f_gsvectorint_rows(f_vec) result(nrows)
!--purpose: get number of rows from vectorint object
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsvectorint_rows
#endif
   implicit none
!--function result:
   integer(C_INT)   :: nrows
!--function arguments:
   type(t_gsvectorint) :: f_vec

   nrows = gsVectorInt_rows(f_vec%c_vec)
end function f_gsvectorint_rows

!------------------------------------------------------------------------------------------------------------

function f_gsvectorint_cols(f_vec) result(ncols)
!--purpose: get number of columns from vectorint object
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsvectorint_cols
#endif
   implicit none
!--function result:
   integer(C_INT)   :: ncols
!--function arguments:
   type(t_gsvectorint) :: f_vec

   ncols = gsVectorInt_cols(f_vec%c_vec)
end function f_gsvectorint_cols

!------------------------------------------------------------------------------------------------------------

subroutine f_gsvectorint_update_data_ptr(f_vec)
!--purpose: reconnect f_vec%data after possible (re)allocation in C/C++
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsvectorint_update_data_ptr
#endif
   implicit none
!--subroutine arguments:
   type(t_gsvectorint) :: f_vec
!--local variables:
   integer(C_INT)   :: nrows

   nrows  = gsVectorInt_rows(f_vec%c_vec)
   if (nrows.le.0) then
      f_vec%data => NULL()
   else
      call C_F_POINTER( gsVectorInt_data(f_vec%c_vec), f_vec%data, (/ nrows /))
   endif
end subroutine f_gsvectorint_update_data_ptr

!------------------------------------------------------------------------------------------------------------

function f_gsvectorint_data(f_vec) result(f_data_ptr)
!--purpose: get pointer to data array of a vectorint object
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsvectorint_data
#endif
   implicit none
!--function result:
   real(C_INT),    dimension(:),   pointer :: f_data_ptr
!--function arguments:
   type(t_gsvectorint) :: f_vec

   call f_gsvectorint_update_data_ptr(f_vec)
   f_data_ptr => f_vec%data
end function f_gsvectorint_data

!------------------------------------------------------------------------------------------------------------

subroutine f_gsvectorint_delete(f_vec)
!--purpose: destroy a vectorint object
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsvectorint_delete
#endif
!--subroutine arguments:
   type(t_gsvectorint) :: f_vec

   call gsVectorInt_delete(f_vec%c_vec)
   nullify(f_vec%data)
end subroutine f_gsvectorint_delete

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

function f_gsmatrix_create_rc(nrows, ncols) result(f_mat)
!--purpose: create gsmatrix object with given size
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsmatrix_create_rc
#endif
   implicit none
!--function result:
   type(t_gsmatrix)               :: f_mat
!--function arguments:
   integer(C_INT)                 :: nrows, ncols

   f_mat%c_mat = gsMatrix_create_rc(nrows, ncols)
   call f_gsmatrix_update_data_ptr( f_mat )

end function f_gsmatrix_create_rc

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
!--   write(*,*) ! flush stdout(?)
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
! wrap functions of gsCFunctionSet.ifc:
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

subroutine f_gsfunctionset_deriv_into(f_fs, f_uv, f_result)
!--purpose: evaluate derivatives for gsfunctionset object at parameter values uv into result matrix
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsfunctionset_deriv_into
#endif
!--subroutine arguments:
   class(t_gsfunctionset) :: f_fs
   type(t_gsmatrix)       :: f_uv, f_result

   call gsfunctionset_deriv_into(f_fs%c_fs, f_uv%c_mat, f_result%c_mat )
   call f_gsmatrix_update_data_ptr( f_result )
end subroutine f_gsfunctionset_deriv_into

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

   ! TODO: check initialization of f_uv and f_xyz
   call gsGeometry_recoverPoints(f_geom%c_fs, f_uv%c_mat, f_xyz%c_mat, k, accuracy)
   call f_gsmatrix_update_data_ptr( f_uv )
   call f_gsmatrix_update_data_ptr( f_xyz )

end subroutine f_gsgeometry_recoverpoints

!------------------------------------------------------------------------------------------------------------

subroutine f_gsgeometry_recoverpointgrid(f_geom, xlow, xhig, npnt, f_xyz, f_uv, c, accuracy)
!--purpose: for a grid (xlow, xhig, npnt), invert coordinates (x,y), (x,z), or (y,z) (c=2, 1, 0)
!           to corresponding (u,v) and fill in missing coordinate
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsgeometry_recoverpointgrid
#endif
!--subroutine arguments:
   type(t_gsgeometry)       :: f_geom
   type(t_gsmatrix)         :: f_xyz, f_uv
   integer(C_INT)           :: npnt(:), c
   real(C_DOUBLE)           :: xlow(:), xhig(:), accuracy
!--local variables:
   type(t_gsvector)         :: f_a, f_b
   type(t_gsvectorint)      :: f_sz

   f_a  = f_gsvector_create_rd( size(xlow), xlow )
   f_b  = f_gsvector_create_rd( size(xhig), xhig )
   f_sz = f_gsvectorint_create_rd( size(npnt), npnt )
   ! TODO: check initialization of f_uv and f_xyz
   call gsGeometry_recoverPointgrid(f_geom%c_fs, f_a%c_vec, f_b%c_vec, f_sz%c_vec, f_xyz%c_mat,         &
           f_uv%c_mat, c, accuracy)
   call f_gsmatrix_update_data_ptr( f_xyz )
   call f_gsmatrix_update_data_ptr( f_uv )
   call f_gsvector_delete( f_a )
   call f_gsvector_delete( f_b )
   call f_gsvectorint_delete( f_sz )

end subroutine f_gsgeometry_recoverpointgrid

!------------------------------------------------------------------------------------------------------------
! wrap functions of gsCGeometryTransform.ifc:
!------------------------------------------------------------------------------------------------------------

function f_gsgeometrytransform_create(f_geom, f_mat, f_vec) result(f_trnsf)
!--purpose: create gsgeometrytransform object from geometry + rot.matrix + transl.vector
#ifdef _WIN32
!dec$ attributes dllexport :: f_gsgeometrytransform_create
#endif
   implicit none
!--function result:
   type(t_gsgeometry) :: f_trnsf
!--function arguments:
   type(t_gsgeometry) :: f_geom
   type(t_gsmatrix)   :: f_mat
   type(t_gsvector)   :: f_vec

   f_trnsf%c_fs = gsGeometryTransform_create(f_geom%c_fs, f_mat%c_mat, f_vec%c_vec)

end function f_gsgeometrytransform_create

!------------------------------------------------------------------------------------------------------------

end module Fgismo
