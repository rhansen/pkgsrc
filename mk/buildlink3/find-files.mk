# $NetBSD: find-files.mk,v 1.6 2010/05/03 05:52:59 obache Exp $
#
# Copyright (c) 2005 The NetBSD Foundation, Inc.
# All rights reserved.
#
# This code is derived from software contributed to The NetBSD Foundation
# by Johnny C. Lam.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. All advertising materials mentioning features or use of this software
#    must display the following acknowledgement:
#        This product includes software developed by the NetBSD
#        Foundation, Inc. and its contributors.
# 4. Neither the name of The NetBSD Foundation nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
# ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
# TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
# BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#

#
# This is a "subroutine" that can be included to detect the presence of
# files in the base system.
#
# The following variables must be defined before including this file:
#
#    BUILTIN_FIND_FILES_VAR is a list of variables to define.  These
#	variables take the value of the path to the file that is
#	"found".
#
#    BUILTIN_FIND_FILES.<var> is the list of paths to files to find, in
#	order, on the filesystem.  The variable <var> is set to the
#	first path "found" on the filesystem.
#
# Optionally, the following variables may also be defined:
#
#    BUILTIN_FIND_GREP.<var> is a regular expression that must be
#	matched within a file in order for the file to be considered
#	"found".  If it isn't defined, then we simply check for the
#	existence of the file.
#
# After including this file, the following variables are defined:
#
#    <var> is the first of the files listed in ${BUILTIN_FIND_FILES.<var>}
#	that is "found", or else it is "__nonexistent__".
#
# An example use is:
#
# BUILTIN_FIND_FILES_VAR:=	FOO BAR
#
# BUILTIN_FIND_FILES.FOO=	/path1 /path2
# BUILTIN_FIND_GREP.FOO=	\#define.*FOO
#
# BUILTIN_FIND_FILES.BAR=	/path3 /path4
# .include "../../mk/buildlink3/builtin-files.mk"
#

.if empty(USE_TOOLS:Mecho)
USE_TOOLS+=	echo
.endif
.if empty(USE_TOOLS:Mgrep)
USE_TOOLS+=	grep
.endif

.for _var_ in ${BUILTIN_FIND_FILES_VAR}
.  if !defined(${_var_})
${_var_}=	__nonexistent__
.    for _file_ in ${BUILTIN_FIND_FILES.${_var_}}
.      if !empty(${_var_}:M__nonexistent__)
_real_file_=	__nonexistent__
.       if exists(${_file_})
_real_file_=	${_file_}
.       endif
.       if !empty(_real_file_:M__nonexistent__) && defined(BEINCLUDES) && !empty(BEINCLUDES)
.        for _try_file_ in ${BEINCLUDES:S/;/ /g:=${_file_:S/\/usr\/include\//\//g}}
.          if !empty(_real_file_:M__nonexistent__) && exists(${_try_file_})
_real_file_=	${_try_file_}
.          endif
.        endfor
.       endif
.       if empty(_real_file_:M__nonexistent__)
.        if !defined(BUILTIN_FIND_GREP.${_var_})
${_var_}:=	${_real_file_}
.        else
${_var_}!=								\
	if ${GREP} -q ${BUILTIN_FIND_GREP.${_var_}:Q} ${_real_file_:Q}; then	\
		${ECHO} ${_real_file_:Q};				\
	else								\
		${ECHO} __nonexistent__;				\
	fi
.        endif
.       endif
.      endif
.    endfor
.  endif
MAKEVARS+=	${_var_}
.endfor
