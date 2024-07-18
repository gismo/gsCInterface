% @file gsBasis.m
%
%    @brief Matlab wrapper for gsBasis class
%
%    This file is part of the G+Smo library.
%
%    This Source Code Form is subject to the terms of the Mozilla Public
%    License, v. 2.0. If a copy of the MPL was not distributed with this
%    file, You can obtain one at http://mozilla.org/MPL/2.0/.
%
%    Author(s): H.M.Verhelst

classdef gsBasis < gsFunctionSet

    properties (SetAccess = public, Hidden = true)
        objectHandle; % Handle to the underlying C++ class instance
    end

    methods(Access = public)

        function varargout = dim(this, varargin)
            %dim - dimension of a gsBasis object
            %
            %Usage:
            %  num = this.dim()
            %
            %Input:
            %  this: gsBasis, [1 x 1].
            %    The gsBasis object.
            %
            %Output:
            %  num: double, [1 x 1].
            %    Dimension of the gsBasis.
            if (nargin~=1 || nargout>1)
                error('Invalid number of input and/or output arguments.')
            end
            [varargout{1:nargout}] = calllib('libgismo','gsBasis_dim',this.objectHandle);
        end
        
        function varargout = numElements(this, varargin)
            %numElements - The number of elements.
            %
            %Usage:
            %  num = this.numElements()
            %
            %Input:
            %  this: gsBasis, [1 x 1].
            %    The gsBasis object.
            %
            %Output:
            %  num: double, [1 x 1].
            %    Number of elements in the gsBasis.
            if (nargin~=1 || nargout>1)
                error('Invalid number of input and/or output arguments.')
            end
            [varargout{1:nargout}] = calllib('libgismo','gsBasis_numElements',this.objectHandle);
        end

        function uniformRefine(this, varargin)
            % uniformRefine - Performs uniform refinement on the gsBasis object.
            %   
            %   Refine the basis uniformly by inserting num new
            %   knots with multiplicity mul on each knot span in 
            %   direction dir
            %
            %   Inputs:
            %   - this: The gsBasis object.
            %   - num: (Optional) The number of refinements to perform. Default is 1.
            %   - mul: (Optional) The multiplicity of the refined basis functions.
            %     Default is 1.
            %   - dir: (Optional) The direction of refinement. Default is -1.
            %
            %   See also gsBasis            
            if (~(nargin>=1 && nargin <= 4) || nargout>1)
                error('Invalid number of input and/or output arguments.')
            end
            
            if (nargin<4) dir = -1; else dir = varargin{3}; end
            if (nargin<3) mul =  1; else mul = varargin{2}; end
            if (nargin<2) num =  1; else num = varargin{1}; end

            calllib('libgismo','gsBasis_uniformRefine',this.objectHandle,num,mul,dir);
        end


        function refineElements(this, varargin)
            % refineElements - Insert the given boxes into the quadtree.
            %
            %   Each box is defined by 2d+1 indices, where d is the dimension
            %   of the parameter domain.
            %   The first index defines the level in which the box should be inserted,
            %   the next d indices the "coordinates" of the lower corner in the index space,
            %   and the last d indices the "coordinates" of the upper corner.
            %
            %   Example: Let d=3 and
            %   boxes = [ L^1, ell_x^1, ell_y^1, ell_z^1, u_x^1, u_y^1, u_z^1,
            %             L^2, ell_x^2, ell_y^2, ell_z^2, u_x^2, u_y^2, u_z^2,
            %             L^3, ell_x^3, ell_y^3,
            %             ... ],
            %   then, the first box will be inserted in level L^1 and its
            %   lower and upper corner will have the indices
            %   (ell_x^1, ell_y^1, ell_z^1) and (u_x^1, u_y^1, u_z^1)
            %   in the index space of level L^1, respectively.
            %
            %   Inputs:
            %   - this: The gsBasis object.
            %   - boxes: Vector of size N (2d+1), where
            %     N is the number of boxes,
            %     d is the dimension of the parameter domain.
            %     See description above for details on the format.
            %
            %   See also gsBasis

            if (nargin~=2 || nargout>1)
                error('Invalid number of input and/or output arguments.')
            end

            boxes = int32(varargin{1});
            len = length(boxes);
            if (~isa(boxes,'integer') || ~isvector(boxes) || ~isequal(mod(len,2*this.domainDim()+1),0))
                error('Input argument no. 1 must be an integer vector and with 2*d+1 rows or cols.')
            end
            calllib('libgismo','gsBasis_refineElements',this.objectHandle,varargin{1},len);
        end
        

        function refine(this, varargin)
            % refine - Refine the basis to levels and in the areas defined by
            % boxes with an extension.
            %
            % Inputs:
            %   - this: The gsBasis object.
            %   - boxes: gsMatrix of size d x n, where
            %     n is the number of refinement boxes.
            %     Every two consecutive columns specify the lower and upper corner of one refinement box.
            %     (See also documentation of refine() for the format of box)
            %   - refExt: (Optional) An integer specifying how many cells should also be
            %     refined around the respective boxes. Default is 0.
            %
            % See also gsBasis

            if (~(nargin==2 || nargin==3) || nargout>1)
                error('Invalid number of input and/or output arguments.')
            end

            if (nargin<3) refExt = 0; else dir = varargin{2}; end

            len = length(varargin{1});
            if (~isa(varargin{1},'numeric') || ~ismatrix(varargin{1}))
                error('Input argument no. 1 must be a numeric matrix.')
            end

            assert(isequal(size(varargin{1},1),this.domainDim()) && isequal(size(varargin{1},2),2),"Boxes must be domainDim() by 2")

            boxes = EigenMatrix(size(varargin{1},1),size(varargin{1},2),varargin{1});
            calllib('libgismo','gsBasis_refine',this.objectHandle,boxes.ptr(),refExt);
        end

        function varargout = support(this, varargin)
            % support - Returns (a bounding box for) the domain of the whole basis.
            %
            %   Returns a dx2 matrix, containing the two diagonally extreme
            %   corners of a hypercube.
            %   
            %  Inputs:
            %   - this: The gsBasis object.
            %   - idx: (Optional) The index of the basis function
            
            
            if (~(nargin==1 || nargin==2) || nargout>1)
                error('Invalid number of input and/or output arguments.')
            end
            if (nargin==1)
                [varargout{1:nargout}] = calllib('libgismo','gsFunctionSet_support',this.objectHandle);
            elseif (nargin==2)
                [varargout{1:nargout}] = calllib('libgismo','gsBasis_support',this.objectHandle, varargin{:});
            end
        end

        % size - call class method
        function varargout = size(this, varargin)
            %size - size of a gsBasis object
            %
            %Usage:
            %  num = this.size()
            %
            %Input:
            %  this: gsBasis, [1 x 1].
            %    The gsBasis object.
            %
            %Output:
            %  num: double, [1 x 1].
            %    Size of the gsBasis.
            
            if (nargin~=1 || nargout>1)
                error('Invalid number of input and/or output arguments.')
            end
            [varargout{1:nargout}] = calllib('libgismo','gsBasis_size',this.objectHandle);
        end

        % degree - call class method
        %
        %   Degree with respect to the i-th variable.
        %   If the basis is a tensor product of (piecewise)
        %   polynomial bases, then this function returns the polynomial
        %   degree of the i-th component.
        %
        %   Inputs:
        %   - this: The gsBasis object.
        %   - i: The index of the variable.
        %
        %   Outputs:
        %   - varargout: The polynomial degree of the i-th component.
        
        function [varargout] = degree(this, varargin)
            
            if (nargin~=2 || nargout>1)
                error('Invalid number of input and/or output arguments.')
            end
            if (~isa(varargin{1},'numeric') || ~isscalar(varargin{1}) || ...
                    ~(mod(varargin{1},1)==0) || varargin{1}>this.dim())
                error('Input argument must be an integer less than %d.', this.dim())
            end
            [varargout{1:nargout}] = calllib('libgismo','gsBasis_degree',this.objectHandle, varargin{:});
        end
        
        function [varargout] = active(this, varargin)
            % active - Returns the indices of active basis functions at points
            % u, as a list of indices, in result. A function is said to be
            % active in a point if this point lies in the closure of the
            % function's support.
            %
            % Inputs:
            % - this: The gsBasis object.
            % - u: gsMatrix containing evaluation points. Each column represents one evaluation point.
            %
            % Outputs:
            % - result: For every column i of u, a column containing the indices of the
            %   active basis functions at evaluation point u(:,i).
            if (nargin~=2 || nargout>1)
                error('Invalid number of input and/or output arguments.')
            end

            if (~isa(varargin{1},'numeric') || ~ismatrix(varargin{1}) || ~isequal(size(varargin{1},1),this.dim()))
                error('Input argument no. 1 must be numeric, 2-dimensional, and with d rows.')
            end

            assert(size(varargin{1},1)==this.domainDim(),"Domain dimension should be equal to the number of rows of the points");
            uu = EigenMatrix(size(varargin{1},1),size(varargin{1},2),varargin{1});
            result = EigenMatrixInt();
            calllib('libgismo','gsBasis_active_into',this.objectHandle,uu.ptr(),result.ptr());
            [varargout{1:nargout}] = result.asMatrix();
        end

        % evalSingle - call class method
        function [varargout] = evalSingle(this, varargin)
            % evalSingle - Evaluate a single function in a gsBasis object.
            %
            % Usage:
            %   val = this.evalSingle(fun, pts)
            %
            % Inputs:
            %   - fun: double, [1 x 1].
            %     Index of the function to evaluate.
            %   - pts: double, [d x numPts].
            %     Points at which to evaluate the function.
            %
            % Output:
            %   - val: double, [1 x numPts].
            %     Value of the specified function at each of the specified points.

            if (nargin~=3 || nargout>1)
                error('Invalid number of input and/or output arguments.')
            end

            if (~isa(varargin{2},'numeric') || ~ismatrix(varargin{2}) || ~isequal(size(varargin{2},1),this.dim()))
                error('Input argument no. 1 must be numeric, 2-dimensional, and with d rows.')
            end

            assert(size(varargin{2},1)==this.domainDim(),"Domain dimension should be equal to the number of rows of the points");
            uu = EigenMatrix(size(varargin{2},1),size(varargin{2},2),varargin{2});
            result = EigenMatrix();
            calllib('libgismo','gsBasis_evalSingle_into',this.objectHandle,varargin{1},uu.ptr(),result.ptr());
            [varargout{1:nargout}] = result.asMatrix();
        end

        % derivSingle - call class method
        function [varargout] = derivSingle(this, varargin)
            % derivSingle - Evaluate a single function in a gsBasis object.
            %
            % Usage:
            %   val = this.derivSingle(fun, pts)
            %
            % Inputs:
            %   - fun: double, [1 x 1].
            %     Index of the function to evaluate.
            %   - pts: double, [d x numPts].
            %     Points at which to evaluate the function.
            %
            % Output:
            %   - val: double, [1 x numPts].
            %     Value of the specified function at each of the specified points.

            if (nargin~=3 || nargout>1)
                error('Invalid number of input and/or output arguments.')
            end

            if (~isa(varargin{2},'numeric') || ~ismatrix(varargin{2}) || ~isequal(size(varargin{2},1),this.dim()))
                error('Input argument no. 1 must be numeric, 2-dimensional, and with d rows.')
            end

            assert(size(varargin{2},1)==this.domainDim(),"Domain dimension should be equal to the number of rows of the points");
            uu = EigenMatrix(size(varargin{2},1),size(varargin{2},2),varargin{2});
            result = EigenMatrix();
            calllib('libgismo','gsBasis_derivSingle_into',this.objectHandle,varargin{1},uu.ptr(),result.ptr());
            [varargout{1:nargout}] = result.asMatrix();
        end

        % deriv2Single - call class method
        function [varargout] = deriv2Single(this, varargin)
            % deriv2Single - Evaluate a single function in a gsBasis object.
            %
            % Usage:
            %   val = this.deriv2Single(fun, pts)
            %
            % Inputs:
            %   - fun: double, [1 x 1].
            %     Index of the function to evaluate.
            %   - pts: double, [d x numPts].
            %     Points at which to evaluate the function.
            %
            % Output:
            %   - val: double, [1 x numPts].
            %     Value of the specified function at each of the specified points.

            if (nargin~=3 || nargout>1)
                error('Invalid number of input and/or output arguments.')
            end

            if (~isa(varargin{2},'numeric') || ~ismatrix(varargin{2}) || ~isequal(size(varargin{2},1),this.dim()))
                error('Input argument no. 1 must be numeric, 2-dimensional, and with d rows.')
            end

            assert(size(varargin{2},1)==this.domainDim(),"Domain dimension should be equal to the number of rows of the points");
            uu = EigenMatrix(size(varargin{2},1),size(varargin{2},2),varargin{2});
            result = EigenMatrix();
            calllib('libgismo','gsBasis_deriv2Single_into',this.objectHandle,varargin{1},uu.ptr(),result.ptr());
            [varargout{1:nargout}] = result.asMatrix();
        end

    end
end
