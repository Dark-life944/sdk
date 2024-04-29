%/*
% * Sun RPC is a product of Sun Microsystems, Inc. and is provided for
% * unrestricted use provided that this legend is included on all tape
% * media and as a part of the software program in whole or part.  Users
% * may copy or modify Sun RPC without charge, but are not authorized
% * to license or distribute it to anyone else except as part of a product or
% * program developed by the user or with the express written consent of
% * Sun Microsystems, Inc.
% *
% * SUN RPC IS PROVIDED AS IS WITH NO WARRANTIES OF ANY KIND INCLUDING THE
% * WARRANTIES OF DESIGN, MERCHANTIBILITY AND FITNESS FOR A PARTICULAR
% * PURPOSE, OR ARISING FROM A COURSE OF DEALING, USAGE OR TRADE PRACTICE.
% *
% * Sun RPC is provided with no support and without any obligation on the
% * part of Sun Microsystems, Inc. to assist in its use, correction,
% * modification or enhancement.
% *
% * SUN MICROSYSTEMS, INC. SHALL HAVE NO LIABILITY WITH RESPECT TO THE
% * INFRINGEMENT OF COPYRIGHTS, TRADE SECRETS OR ANY PATENTS BY SUN RPC
% * OR ANY PART THEREOF.
% *
% * In no event will Sun Microsystems, Inc. be liable for any lost revenue
% * or profits or other special, indirect and consequential damages, even if
% * Sun has been advised of the possibility of such damages.
% *
% * Sun Microsystems, Inc.
% * 2550 Garcia Avenue
% * Mountain View, California  94043
% */

%/*
% * Copyright (c) 1986, 1990 by Sun Microsystems, Inc.
% */
%
%/* from @(#)ypupdate_prot.x	1.3 91/03/11 TIRPC 1.0 */
#ifndef RPC_HDR
%#include <sys/cdefs.h>
%__FBSDID("$FreeBSD: releng/11.1/include/rpcsvc/ypupdate_prot.x 114629 2003-05-04 02:51:42Z obrien $");
#endif
%
%/*
% * Compiled from ypupdate_prot.x using rpcgen
% * This is NOT source code!
% * DO NOT EDIT THIS FILE!
% */

/*
 * YP update service protocol
 */
#ifdef RPC_HDR
%
%#ifndef _rpcsvc_ypupdate_prot_h
%#define _rpcsvc_ypupdate_prot_h
%
#endif

const MAXMAPNAMELEN = 255;
const MAXYPDATALEN  = 1023;
const MAXERRMSGLEN  = 255;

program YPU_PROG {
	version YPU_VERS {
		u_int YPU_CHANGE(ypupdate_args) = 1;
		u_int YPU_INSERT(ypupdate_args) = 2;
		u_int YPU_DELETE(ypdelete_args) = 3;
		u_int YPU_STORE(ypupdate_args)  = 4;
	} = 1;
} = 100028;

typedef opaque yp_buf<MAXYPDATALEN>;

struct ypupdate_args {
	string mapname<MAXMAPNAMELEN>;
	yp_buf key;
	yp_buf datum;
};

struct ypdelete_args {
	string mapname<MAXMAPNAMELEN>;
	yp_buf key;
};

#ifdef RPC_HDR
%
%#endif /* !_rpcsvc_ypupdate_prot_h */
#endif
