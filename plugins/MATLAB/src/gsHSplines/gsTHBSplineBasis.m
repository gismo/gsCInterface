% @file gsTHBSplineBasis.m
%
%    @brief Matlab wrapper for gsTHBSplineBasis class
%
%    This file is part of the G+Smo library.
%
%    This Source Code Form is subject to the terms of the Mozilla Public
%    License, v. 2.0. If a copy of the MPL was not distributed with this
%    file, You can obtain one at http://mozilla.org/MPL/2.0/.
%
%    Author(s): H.M. Verhelst

classdef gsTHBSplineBasis < gsHTensorBasis

    % properties (SetAccess = private, Hidden = true)
    %     objectHandle; % Handle to the underlying C++ class instance
    % end

    methods(Access = public)

        % Constructor - Create a new C++ class instance 
        function this = gsTHBSplineBasis(varargin)
            %gsTHBSplineBasis - construct a gsTHBSplineBasis object
            %
            %Usage:
            %  thb = gsTHBSplineBasis( file )
            %
            %Input:
            %  file: char, [1 x numChar].
            %    Name of input file from which to read/construct the
            %    gsTHBSplineBasis.
            %
            %Output:
            %  thb: gsTHBSplineBasis, [1 x 1].
            %    The gsTHBSplineBasis object.

            if (nargin~=1 || nargout>1)
                error('Invalid number of input and/or output arguments.')
            end
            
            if (isa(varargin{1},'uint64'))
                this.objectHandle = varargin{1};
            else
                if ( isa(varargin{1},'char') ) % construct using XML filename string
                    % % if exist(varargin{1},'file') then read from file..
                    % this.objectHandle = mex_gsTHBSplineBasis('constructor', class(varargin{1}), varargin{:});
                elseif ( isa(varargin{1},'gsTensorBSplineBasis') )
                    if (varargin{1}.dim()==2)
                        this.objectHandle = calllib('libgismo','gsTHBSplineBasis2_create',varargin{1}.ptr());
                    elseif (varargin{1}.dim()==3)
                        this.objectHandle = calllib('libgismo','gsTHBSplineBasis3_create',varargin{1}.ptr());
                    elseif (varargin{1}.dim()==4)
                        this.objectHandle = calllib('libgismo','gsTHBSplineBasis4_create',varargin{1}.ptr());
                    else
                        error('Not implemented');
                    end
                else
                    % error('Input argument no. 1 should be of type char, file or gsTensorBSplineBasis.')
                end
            end
        end
    end
end