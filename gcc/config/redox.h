#undef TARGET_REDOX
#define TARGET_REDOX 1

#undef CPP_SPEC
#define CPP_SPEC "%{posix:-D_POSIX_SOURCE} %{pthread:-D_REENTRANT}"

#undef LIB_SPEC
#define LIB_SPEC "%{pthread:-lpthread} -lc %{shared:-lgcc_s}"

#undef LINK_SPEC
#define LINK_SPEC "%{shared:-shared} %{!shared:-static} %{!shared: %{!static: %{rdynamic:-export-dynamic}}}"

#undef STARTFILE_SPEC
#define STARTFILE_SPEC "%{!shared:crt0.o%s} crti.o%s %{shared|pie:crtbeginS.o%s;:crtbegin.o%s}"

#undef ENDFILE_SPEC
#define ENDFILE_SPEC "%{shared|pie:crtendS.o%s;:crtend.o%s} crtn.o%s"

#undef TARGET_OS_CPP_BUILTINS
#define TARGET_OS_CPP_BUILTINS()      \
  do {                                \
    builtin_define ("__redox__");      \
    builtin_define ("__unix__");      \
    builtin_assert ("system=redox");   \
    builtin_assert ("system=unix");   \
    builtin_assert ("system=posix");   \
  } while(0);

#undef TARGET_DEFAULT_SMALL_DATA_SIZE
#define TARGET_DEFAULT_SMALL_DATA_SIZE 0
