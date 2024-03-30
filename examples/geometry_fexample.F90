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
   type(c_ptr)      :: g
   integer            :: nu,  nv
   logical, parameter :: use_thb = .false.

   ! TODO: input option for xml-file?

   if (use_thb) then
      write(*,'(2(a,f5.1),a,i3)') 'reading XML for THB-spline'
      some_file = 'optional/gsWRContact/examples/sw_crossing/sw_thb.xml' // C_NULL_CHAR
      g = gsReadFile(some_file)
   else
      write(*,'(2(a,f5.1),a,i3)') 'reading XML for tensor B-spline'
      some_file = 'optional/gsWRContact/examples/sw_crossing/sw_tp.xml' // C_NULL_CHAR
      g = gsReadFile(some_file)
   endif
   write(*,'(a,i3)') 'done, g.dim=', domainDim(g)

   call print(g)

   if (.true.) then
      call show_basic_usage( g )
   endif

   if (.false.) then
      nu = 251
      nv = 201
      call sample_surface( g, nu, nv )
   endif

   if (.true.) then
      call show_recover_points( g )
   endif

   if (use_thb) then
      call destroy(g)
   else
      call destroy(g)
   endif
   write(*,*) 'done.'

end program geometry_fexample

!-----------------------------------------------------------------------------------------------------------

subroutine show_basic_usage( g )
!--purpose: evaluate positions (x,y,z) and derivatives d[xyz]/d[uv] at some arbitrary (u,v) \in [0,1)^2
   use, intrinsic  :: iso_c_binding
   implicit none
#  include "gsCInterface/gismo.ifc"
!--subroutine arguments
   type(c_ptr)                :: g
!--local variables
   integer(C_INT)               :: nRows, nCols, out_rows, out_cols, mode, irow, icol, icoor, ipar
   real(C_DOUBLE), dimension(:,:), allocatable :: uv
   real(C_DOUBLE), dimension(:,:), allocatable :: xyz, dxyz
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

   mode  = 0
   allocate(xyz(3,nCols))
   call eval_into(G, uv, nRows, nCols, xyz, 3*nCols, out_rows, out_cols, mode)

   write(*,'(3(a,i3))') 'Mode =',mode,': got #rows =', out_rows, ', #cols =', out_cols
   do irow = 1, out_rows
      write(*,'(3a,10f10.3)') '  ',c_coor(irow),': ', (xyz(irow,icol), icol=1,out_cols)
   enddo
   deallocate(xyz)
   deallocate(uv)

end subroutine show_basic_usage

!-----------------------------------------------------------------------------------------------------------

subroutine sample_surface( g, nu, nv )
!--purpose: evaluate positions (x,y,z) at uniform grid [0:du:1] x [0:dv:1], print table of results
   use, intrinsic  :: iso_c_binding
   implicit none
#  include "gsCInterface/gismo.ifc"
!--subroutine arguments
   type(c_ptr)                :: g
   integer,        intent(in)   :: nu, nv
!--local variables
   integer                      :: iu, iv, ii
   real(kind=8)                 :: du, dv, ui, vj
   integer(C_INT)               :: nRows, nCols, out_rows, out_cols, mode, irow, icol, icoor, ipar
   real(C_DOUBLE), dimension(:,:), allocatable :: uv
   real(C_DOUBLE), dimension(:,:), allocatable :: xyz
   character(len=1), parameter  :: c_param(2) = (/ 'u', 'v' /)
   character(len=1), parameter  :: c_coor(3)  = (/ 'x', 'y', 'z' /)

   write(*,*) '-------------------------------- sample_surface --------------------------------'
   ! set step-sizes for parameters u, v, interval [0,1] divided into equidistant positions

   du = 1d0 / (nu - 1)
   dv = 1d0 / (nv - 1)

   ! create input for gs_eval_geometry

   nRows =   2
   nCols =  nu * nv
   allocate(uv(nRows,nCols))

   do iu = 1, nu
      do iv = 1, nv
         ii = (iu-1) * nv + iv
         uv(1, ii) = (iu-1) * du
         uv(2, ii) = (iv-1) * dv
      enddo
   enddo

   write(*,'(2(a,i4),a)') 'Parameter grid nu x nv =',nu,' x',nv,' positions'

   ! evaluate positions (x,y,z) at given parameter values

   mode  = 0
   allocate(xyz(3,nCols))
   call eval_into(G, uv, nRows, nCols, xyz, 3*nCols, out_rows, out_cols, mode)

   ! print results in tabular form

   write(*,'(2(a,i3),a,i7)') 'Mode =',mode,': got #rows =', out_rows, ', #cols =', out_cols
   write(*,'(a)') '%   iu      iv      ii          ui          vj           xij         yij         zij'
   do iu = 1, nu
      do iv = 1, nv
         ii = (iu-1) * nv + iv
         write(*,'(3i8,2f12.6,f14.6,2f12.6)') iu, iv, ii, uv(1,ii), uv(2,ii),                           &
                        (xyz(irow,ii), irow=1,out_rows)
      enddo
   enddo
   deallocate(xyz)

end subroutine sample_surface

!-----------------------------------------------------------------------------------------------------------

subroutine show_recover_points( g )
!--purpose: for some positions (x,y), determine z on the surface and corresponding (u,v)
   use, intrinsic  :: iso_c_binding
   implicit none
#  include "gsCInterface/gismo.ifc"
!--subroutine arguments
   type(c_ptr)                :: g
!--local variables
   integer(C_INT), parameter    :: XDIR = 0, YDIR = 1, ZDIR = 2
   integer(C_INT)               :: nCols, irow, icol
   real(C_DOUBLE), dimension(:,:), allocatable :: uv, xyz
   character(len=1), parameter  :: c_param(2) = (/ 'u', 'v' /)
   character(len=1), parameter  :: c_coor(3)  = (/ 'x', 'y', 'z' /)

   write(*,*) '----------------------------- show_recover_points -----------------------------'
   nCols = 4
   allocate(xyz(3,ncols))
   allocate(uv(2,ncols))

   xyz(1, 1:ncols) = (/ 2451.0, 210.001, 708.0,   210.0 /)
   xyz(2, 1:ncols) = (/  122.3, -38.957,  18.568, -13.9 /)
   xyz(3, 1:ncols) = (/    0.0,   0.0,     0.0,     0.0 /)

   do icol = 1, nCols
      uv(:,icol) = 0d0
   enddo

   write(*,'(a,i3,a)') 'Input #cols =', nCols,', (x,y,z) =' 
   do irow = 1, 3
      write(*,'(3a,10f10.3)') '  ',c_coor(irow),': ', (xyz(irow,icol), icol=1,nCols)
   enddo

   ! evaluate z-positions and (u,v)-values for given (x,y)-positions

   call gs_recover_points(G, uv, xyz, nCols, ZDIR)

   write(*,'(a)') 'Output (u,v) =' 
   do irow = 1, 2
      write(*,'(3a,10f10.3)') '  ',c_param(irow),': ', (uv(irow,icol), icol=1, nCols)
   enddo
   write(*,'(a)') 'Output (x,y,z) =' 
   do irow = 1, 3
      write(*,'(3a,10f10.3)') '  ',c_coor(irow),': ', (xyz(irow,icol), icol=1, nCols)
   enddo

   deallocate(uv)
   deallocate(xyz)

end subroutine show_recover_points

!-----------------------------------------------------------------------------------------------------------
