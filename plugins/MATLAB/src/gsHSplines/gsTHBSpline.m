% @file gsTHBSpline.m
%
%    @brief Matlab wrapper for gsTHBSpline class
%
%    This file is part of the G+Smo library.
%
%    This Source Code Form is subject to the terms of the Mozilla Public
%    License, v. 2.0. If a copy of the MPL was not distributed with this
%    file, You can obtain one at http://mozilla.org/MPL/2.0/.
%
%    Author(s): H.M. Verhelst

classdef gsTHBSpline < gsGeometry

    methods(Access = public)

        % Constructor - Create a new C++ class instance
        function this = gsTHBSpline(varargin)
            %gsTHBSpline - construct a gsTHBSpline object
            %
            %Usage:
            %  TODO
            %
            %Input:
            %  TODO
            %
            %Output:
            %  TODO

            if (~nargin==2 || nargout>1)
                error('Invalid number of input and/or output arguments.')
            end

            if ( isa(varargin{1},'gsTHBSplineBasis') && ismatrix(varargin{2}) )
                assert(varargin{1}.size()==size(varargin{2},1), 'Size mismatch between basis and coefficients.')
                coefs = EigenMatrix(size(varargin{2},1),size(varargin{2},2),varargin{2});
                if (varargin{1}.domainDim()==2)
                    this.objectHandle = calllib('libgismo','gsTHBSpline2_create',varargin{1}.ptr(),coefs.ptr());
                elseif (varargin{1}.domainDim()==3)
                    this.objectHandle = calllib('libgismo','gsTHBSpline3_create',varargin{1}.ptr(),coefs.ptr());
                elseif (varargin{1}.domainDim()==4)
                    this.objectHandle = calllib('libgismo','gsTHBSpline4_create',varargin{1}.ptr(),coefs.ptr());
                else
                    error('Invalid domain dimension.')
                end
            else
                error('Input argument no. 1 should be of type ''gsTHBSplineBasis'' and argument no. 2 should be a matrix.')
            end
        end
    end
end
