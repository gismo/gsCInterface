!** @file f_xml_io.c
!
!   @brief Tests Fortran interface
!
!   This file is part of the G+Smo library.
!
!   This Source Code Form is subject to the terms of the Mozilla Public
!   License, v. 2.0. If a copy of the MPL was not distributed with this
!   file, You can obtain one at http://mozilla.org/MPL/2.0/.
!
!   Author(s): E. Vollebregt
! 

program geometry_fexample
   use, intrinsic  :: iso_c_binding
   implicit none
#  include "gsCInterface/gismo.ifc"
   character(len=80, kind=C_CHAR) :: some_file
   type(c_ptr)        :: g
   integer            :: nu,  nv

   ! TODO: input option for xml-file?

   write(*,'(2(a,f5.1),a,i3)') 'reading XML for tensor B-spline'
   some_file = 'optional/gsWRContact/examples/sw_crossing/sw_tp.xml' // C_NULL_CHAR
   g = gsCReadFile(some_file)

   write(*,'(a,i3)') 'done, g.dim=', gsFunctionSet_domainDim(g)

   call gsFunctionSet_print(g)

   if (.true.) then
      call show_basic_usage( g )
   endif

   if (.true.) then
      call show_recover_points( g )
   endif

   call gsFunctionSet_delete(g)
   write(*,*) 'done.'

end program geometry_fexample

!-----------------------------------------------------------------------------------------------------------

subroutine show_basic_usage( g )
!--purpose: evaluate positions (x,y,z) and derivatives d[xyz]/d[uv] at some arbitrary (u,v) \in [0,1)^2
   use, intrinsic  :: iso_c_binding
   implicit none
#  include "gsCInterface/gismo.ifc"
!--subroutine arguments
   type(c_ptr)                  :: g
!--local variables
   integer(C_INT)               :: nRows, nCols, out_rows, out_cols, irow, icol, icoor, ipar
   type(C_PTR)                  :: uvm, xyzm, xyz_p
   real(C_DOUBLE), dimension(:,:), allocatable :: uv
   real(C_DOUBLE), dimension(:,:), pointer     :: xyz
   character(len=1), parameter  :: c_param(2) = (/ 'u', 'v' /)
   character(len=1), parameter  :: c_coor(3)  = (/ 'x', 'y', 'z' /)

   nRows = 2
   nCols = 7
   allocate(uv(nrows,ncols))
   uv(1, 1:nCols) = (/ 0.0, 0.1, 0.5, 0.5, 0.5, 0.5, 1.0 /)
   uv(2, 1:nCols) = (/ 0.0, 0.0, 0.0, 0.2, 0.5, 0.9, 1.0 /)

   write(*,*) '------------------------------ show_basic_usage ------------------------------'
   write(*,'(2(a,i3))') 'Input #rows =', nRows, ', #cols =', nCols
   do irow = 1, nRows
      write(*,'(3a,10f10.3)') '  ',c_param(irow),': ', (uv(irow,icol), icol=1,nCols)
   enddo

   ! evaluate positions (x,y,z) at given parameter values

   uvm  = gsMatrix_create_rcd(nRows, nCols, uv)
   xyzm = gsMatrix_create()
   call gsFunctionSet_eval_into(G, uvm, xyzm)
   ! call gsMatrix_print(xyzm)

   ! get pointer to matrix data

   out_rows = gsMatrix_rows(xyzm)
   out_cols = gsMatrix_cols(xyzm)
   xyz_p    = gsMatrix_data(xyzm)
   call C_F_POINTER(xyz_p, xyz, (/ out_rows, out_cols /))

   write(*,'(3(a,i3))') 'Got #rows =', out_rows, ', #cols =', out_cols
   do irow = 1, out_rows
      write(*,'(3a,10f10.3)') '  ',c_coor(irow),': ', (xyz(irow,icol), icol=1,out_cols)
   enddo

   call gsMatrix_delete(uvm)
   call gsMatrix_delete(xyzm)
   ! write(*,*) 'deallocate uv'
   ! deallocate(uv)

end subroutine show_basic_usage

!-----------------------------------------------------------------------------------------------------------

subroutine show_recover_points( g )
!--purpose: for some positions (x,y), determine z on the surface and corresponding (u,v)
   use, intrinsic  :: iso_c_binding
   implicit none
#  include "gsCInterface/gismo.ifc"
!--subroutine arguments
   type(c_ptr)                  :: g
!--local variables
   integer(C_INT), parameter    :: XDIR = 0, YDIR = 1, ZDIR = 2
   integer(C_INT)               :: nCols, irow, icol, out_rows, out_cols
   real(C_DOUBLE)               :: eps
   real(C_DOUBLE), dimension(:,:), allocatable :: xyz
   real(C_DOUBLE), dimension(:,:), pointer     :: uv
   type(C_PTR)                  :: uvm, xyzm, uv_p
   character(len=1), parameter  :: c_param(2) = (/ 'u', 'v' /)
   character(len=1), parameter  :: c_coor(3)  = (/ 'x', 'y', 'z' /)

   write(*,*) '----------------------------- show_recover_points -----------------------------'
   nCols = 4
   allocate(xyz(3,ncols))

   xyz(1, 1:ncols) = (/ 2451.0, 210.001, 708.0,   210.0 /)
   xyz(2, 1:ncols) = (/  122.3, -38.957,  18.568, -13.9 /)
   xyz(3, 1:ncols) = (/    0.0,   0.0,     0.0,     0.0 /)

   write(*,'(a,i3,a)') 'Input #cols =', nCols,', (x,y,z) =' 
   do irow = 1, 3
      write(*,'(3a,10f10.3)') '  ',c_coor(irow),': ', (xyz(irow,icol), icol=1,nCols)
   enddo

   ! evaluate z-positions and (u,v)-values for given (x,y)-positions

   ! evaluate positions (x,y,z) at given parameter values

   xyzm = gsMatrix_create_rcd(3, ncols, xyz)
   uvm  = gsMatrix_create()

   eps = 1d-6
   call gsGeometry_recoverPoints(G, uvm, xyzm, ZDIR, eps)

   ! get pointer to matrix data

   out_rows = gsMatrix_rows(uvm)
   out_cols = gsMatrix_cols(uvm)
   uv_p     = gsMatrix_data(uvm)
   call C_F_POINTER(uv_p, uv, (/ out_rows, out_cols /))

   write(*,'(a)') 'Output (u,v) =' 
   do irow = 1, 2
      write(*,'(3a,10f10.3)') '  ',c_param(irow),': ', (uv(irow,icol), icol=1, nCols)
   enddo
   write(*,'(a)') 'Output (x,y,z) =' 
   do irow = 1, 3
      write(*,'(3a,10f10.3)') '  ',c_coor(irow),': ', (xyz(irow,icol), icol=1, nCols)
   enddo

   ! clean up input data, matrices used

   call gsMatrix_delete(xyzm)
   call gsMatrix_delete(uvm)
   deallocate(xyz)

end subroutine show_recover_points

!-----------------------------------------------------------------------------------------------------------

