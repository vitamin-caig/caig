AC_DEFUN([AC_CHECK_QT],
[
AC_MSG_CHECKING([for QT])
qt_inc=""
qt_lib=""
qt_cxx=""
qt_link=""
UIC=""
MOC=""

if test -z "$QTDIR"; then
    result=no
    errmsg="QTDIR not found!"
else
    qt_inc="$QTDIR/include"
    qt_lib="$QTDIR/lib"
    UIC="$QTDIR/bin/uic"
    MOC="$QTDIR/bin/moc"
    qt_cxx="-DQT_SHARED -DQT_NO_DEBUG -DQT_THREAD_SUPPORT -D_REENTRANT"
    qt_link="-lqt-mt"
    result=yes

    if test ! -x "$UIC"; then
	errmsg="$errmsg; $UIC not executable"
	result=no
    fi

    if test ! -x "$MOC"; then
	errmsg="$errmsg; $MOC not executable"
	result=no
    fi
    
    if test ! -d "$qt_inc"; then
	errmsg="$errmsg; $qt_inc does not exist"
	result=no
    fi

    if test ! -d "$qt_lib"; then
	errmsg="$errmsg; $qt_lib does not exist"
	result=no
    fi

fi

if test "x$result" = "xno"; then
    AC_MSG_ERROR([QT Error: $errmsg])
else
    AC_SUBST(qt_inc)
    AC_SUBST(qt_lib)
    AC_SUBST(qt_cxx)
    AC_SUBST(qt_link)
    AC_SUBST(UIC)
    AC_SUBST(MOC)
    AC_MSG_RESULT([$result])
fi
])

AC_DEFUN([AC_SET_MODE],
[
AC_ARG_ENABLE(debug,
	      AC_HELP_STRING([--enable-debug=0|1|2], [enables debugging level 1..3 [default=0]]),
	      [dbg_level=$enableval], [dbg_level=0]
	      )

    CXXFLAGS="-fno-check-new -fno-common"
    AC_PROG_CXX
    if test "$GXX" = "yes"; then
        case $dbg_level in
	    1)	#minimum debug
		CXXFLAGS="$CXXFLAGS -D_DEBUG_ -g1 -O2 -Wall"
		builddir="./debug"
		;;
	    2)	#maximum debug
	        CXXFLAGS="$CXXFLAGS -D_DEBUG_ -g3 -O0 -Wall"
		builddir="./debug"
		;;
    	    *)	#no debug
		CXXFLAGS="$CXXFLAGS -g0 -O3"
		builddir="./result"
		;;
	esac
	if ! test -d $top_builddir; then
		mkdir $builddir
	fi
    fi
    
    CXXFLAGS="$CXXFLAGS $qt_cxx"
    LDFLAGS=" $LDFLAGS $qt_link"
    all_includes="-I${qt_inc}"
    all_libraries="-L${qt_lib}"
    AC_SUBST(all_includes)
    AC_SUBST(all_libraries)
])
