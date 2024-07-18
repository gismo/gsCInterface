% @file gsTHBSpline.m
%
%    @brief Matlab wrapper for gsTensorBSplineBasis class
%
%    This file is part of the G+Smo library.
%
%    This Source Code Form is subject to the terms of the Mozilla Public
%    License, v. 2.0. If a copy of the MPL was not distributed with this
%    file, You can obtain one at http://mozilla.org/MPL/2.0/.
%
%    Author(s): H.M. Verhelst

classdef gsTensorBSplineBasis < gsBasis

    methods(Access = public)

        function this = gsTensorBSplineBasis(varargin)
            % gsTensorBSplineBasis - construct a gsTensorBSplineBasis object
            %
            % Usage:
            %   tbb = gsTensorBSplineBasis( kv1, kv2 )
            %   tbb = gsTensorBSplineBasis( kv1, kv2, kv3 )
            %
            % Input:
            %   kv1 - the knot vector for the first parameter direction
            %   kv2 - the knot vector for the second parameter direction
            %   kv3 - the knot vector for the third parameter direction (optional)
            %
            % Output:
            %   tbb - the constructed gsTensorBSplineBasis object
            %
            % This function constructs a gsTensorBSplineBasis object. The object can be
            % used to represent a tensor-product B-spline basis defined over a
            % multi-dimensional domain. The basis is defined by the knot vectors kv1,
            % kv2, and kv3 (if provided) in the respective parameter directions.
            %```


            if (~(nargin==2 || nargin==3) || nargout>1)
                error('Invalid number of input and/or output arguments.')
            end
            
            if (isa(varargin{1},'uint64'))
                this.objectHandle = varargin{1};
            elseif (nargin==2)
                if ( isa(varargin{1},'double') && isa(varargin{2},'double') )
                    error('Not implemented');
                    % this.objectHandle = calllib('libgismo','gsTensorBSplineBasis2_create',varargin{:});

                    % this.objectHandle = mex_gsTensorBSplineBasis('constructor', class(varargin{1}), varargin{:});
                elseif ( isa(varargin{1},'gsKnotVector') && isa(varargin{2},'gsKnotVector') )
                    this.objectHandle = calllib('libgismo','gsTensorBSplineBasis2_create',varargin{1}.ptr(), varargin{2}.ptr());
                else
                    error('Input argument no. 1 should be of type ''double''.')
                end
            elseif (nargin==3)
                if ( isa(varargin{1},'double') && isa(varargin{2},'double') && isa(varargin{3},'double') )
                    error('Not implemented');
                    % this.objectHandle = mex_gsTensorBSplineBasis('constructor', class(varargin{1}), varargin{:});
                elseif ( isa(varargin{1},'gsKnotVector') && isa(varargin{2},'gsKnotVector') && isa(varargin{3},'gsKnotVector') )
                    this.objectHandle = calllib('libgismo','gsTensorBSplineBasis3_create',varargin{1}.ptr(), varargin{2}.ptr(),varargin{3}.ptr());
                else
                    error('Input argument no. 1 should be of type ''double''.')
                end
            end
        end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%Member function implementations%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

        % knots - call class method
        function [varargout] = knots(this, varargin)
            %knots - returns the knot vector of a gsBasis object
            %   of the specified level on the specified direction
            %
            %Usage:
            %  knt = thb.knots( dir )
            %
            %Input:
            %  thb: gsBasis, [1 x 1].
            %    The gsBasis object.
            %  dir: int, [1 x 1].
            %    index of the direction of space to consider.
            %
            %Output:
            %  knt: double, [1 x numKnots].
            %    Knot vector corresponding to level lev in the direction
            %    dir.

            if (nargin~=2 || nargout>1)
                error('Invalid number of input and/or output arguments.')
            end
            if (~isa(varargin{1},'numeric') || ~isscalar(varargin{1}) || ...
                    ~(mod(varargin{1},1)==0) || varargin{1}<1 || varargin{1}>this.dim())
                error('Input argument no. 1 must be a strictly positive integer smaller than %d.', this.dim())
            end
            [varargout{1:nargout}] = calllib('libgismo','gsTensorBSplineBasis_knots',this.objectHandle,varargin{1});
        end
    end
end
