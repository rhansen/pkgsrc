#ifndef KSH_TIME_H
# define KSH_TIME_H

/* Wrapper around the ugly time.h,sys/time.h includes/ifdefs */
/* $Id: ksh_time.h,v 1.1.1.1 2008/05/23 17:15:20 tnn Exp $ */

#ifdef TIME_WITH_SYS_TIME
# include <sys/time.h>
# include <time.h>
#else /* TIME_WITH_SYS_TIME */
# ifdef HAVE_SYS_TIME_H
#  include <sys/time.h>
# else
#  include <time.h>
# endif
#endif /* TIME_WITH_SYS_TIME */

#ifndef TIME_DECLARED
extern time_t time ARGS((time_t *));
#endif

#ifndef CLK_TCK
# define CLK_TCK 60			/* 60HZ */
#endif
#endif /* KSH_TIME_H */
