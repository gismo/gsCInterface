/** @file basis_example.c

    @brief Tests C interface

    This file is part of the G+Smo library.

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.

    Author(s): 
*/

#include <gsCInterface/Cgismo.h>

#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    double knots[6];
    knots[0]=knots[1]=knots[2]=0;
    knots[3]=knots[4]=knots[5]=1;

    gsCKnotVector * kv = gsKnotVector_create(knots,6);

    gsKnotVector_print(kv);

    gsCBasis * b = gsBSplineBasis_create(kv);
    
    gsKnotVector_delete(kv);
    printf("\n\n");
    gsFunctionSet_print(b);
    printf("\n");
    gsBasis_delete(b);

    return 0;
}
