#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([07_Environmental], [0.0.1], [animarosaceus@mail.ru])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_SRCDIR([rhasher.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([rhash], [rhash_msg], , [AC_MSG_ERROR([rhash library not found.])])

AC_ARG_WITH([readline],
            [AS_HELP_STRING([--with-readline], 
                [Build with readline support])],
            [AC_CHECK_LIB([readline], [readline], , [AC_MSG_ERROR([readline library not found.])]), 
                rhasher_CFLAGS += -USE_READLINE, 
                rhasher_LDADD += -lreadline],
            [])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([strcasecmp])
AC_CHECK_FUNCS([strerror])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT