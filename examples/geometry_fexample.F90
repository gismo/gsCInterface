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
   type(C_PTR)                  :: uvm, xyzm, xyz1
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

   uvm = gsMatrix_create_rcd(nRows, nCols, uv)
   xyzm = gsMatrix_create()
   call gsFunctionSet_eval_into(G, uvm, xyzm)
   call gsMatrix_print(xyzm)

   xyz1 = gsMatrix_data(xyzm)
   call C_F_POINTER(xyz1, xyz, (/ 3,nCols /))

   out_rows = size(xyz, 1)
   out_cols = size(xyz, 2)
   write(*,'(3(a,i3))') 'Got #rows =', out_rows, ', #cols =', out_cols
   do irow = 1, out_rows
      write(*,'(3a,10f10.3)') '  ',c_coor(irow),': ', (xyz(irow,icol), icol=1,out_cols)
   enddo
   deallocate(uv)

end subroutine show_basic_usage

!-----------------------------------------------------------------------------------------------------------

