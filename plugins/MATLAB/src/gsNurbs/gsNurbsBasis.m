% @file gsNurbsBasis.m
%
%    @brief Matlab wrapper for gsNurbsBasis class
%
%    This file is part of the G+Smo library.
%
%    This Source Code Form is subject to the terms of the Mozilla Public
%    License, v. 2.0. If a copy of the MPL was not distributed with this
%    file, You can obtain one at http://mozilla.org/MPL/2.0/.
%
%    Author(s): H.M. Verhelst

classdef gsNurbsBasis < gsBasis

    methods(Access = public)

        % Constructor - Create a new C++ class instance 
        function this = gsNurbsBasis(varargin)
            % gsNurbsBasis - construct a gsNurbsBasis object
            %
            % Usage:
            %   bsb = gsNurbsBasis( kv1 )
            %
            % Input:
            %   kv1 - the knot vector
            %
            % Output:
            %  bsb - the gsNurbsBasis object
            %
            if (~nargin==2 || nargout>1)
                error('Invalid number of input and/or output arguments.')
            end
            
            if (isa(varargin{1},'uint64'))
                this.objectHandle = varargin{1};
            elseif (nargin==1)
                if ( isa(varargin{1},'double') )
                    error('Not implemented');
                    % this.objectHandle = calllib('libgismo','gsNurbsBasis2_create',varargin{:});

                    % this.objectHandle = mex_gsNurbsBasis('constructor', class(varargin{1}), varargin{:});
                elseif ( isa(varargin{1},'gsKnotVector') )
                    this.objectHandle = calllib('libgismo','gsNurbsBasis_create',varargin{1}.ptr());
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
            % knots - returns the knot vector of a gsBasis object
            %   of the specified level on the specified direction
            %
            % Usage:
            %   knt = thb.knots(dir)
            %
            % Input:
            %   thb: gsBasis, [1 x 1].
            %     The gsBasis object.
            %   dir: int, [1 x 1].
            %     Index of the direction of space to consider.
            %
            % Output:
            %   knt: double, [1 x numKnots].
            %     Knot vector corresponding to level lev in the direction
            %     dir.

            if (nargin~=2 || nargout>1)
                error('Invalid number of input and/or output arguments.')
            end
            if (~isa(varargin{1},'numeric') || ~isscalar(varargin{1}) || ...
                    ~(mod(varargin{1},1)==0) || varargin{1}<1 || varargin{1}>this.dim())
                error('Input argument no. 1 must be a strictly positive integer smaller than %d.', this.dim())
            end
            [varargout{1:nargout}] = calllib('libgismo','gsNurbsBasis_knots',this.objectHandle,varargin{1});
        end
    end
end
