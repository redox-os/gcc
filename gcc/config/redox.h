#undef TARGET_REDOX
#define TARGET_REDOX 1

#undef CPP_SPEC
#define CPP_SPEC "%{posix:-D_POSIX_SOURCE} %{pthread:-D_REENTRANT}"

// TODO: remove -lgcc_s, it should be linked "as-needed"
//       however it will break our hack-ish toolchain bootstrap process
//       as we're compiling bootstrap relibc without building libgcc first
#undef LIB_SPEC
#define LIB_SPEC "-lc %{!static:-lgcc_s}"

// TODO: -dynamic-linker arg was missing for years, add it
//       it when doing GCC update to prevent it changing again
#undef LINK_SPEC
#define LINK_SPEC "%{shared:-shared} %{static:-static} %{!shared: %{!static: %{rdynamic:-export-dynamic}}}"

#undef STARTFILE_SPEC
#define STARTFILE_SPEC "%{!shared:crt0.o%s} crti.o%s %{shared|pie:crtbeginS.o%s;:crtbegin.o%s}"

#undef ENDFILE_SPEC
#define ENDFILE_SPEC   "%{shared|pie:crtendS.o%s;:crtend.o%s} crtn.o%s"

/* Always use ELF.  */
#undef  OBJECT_FORMAT_ELF
#define OBJECT_FORMAT_ELF

/* Use --as-needed -lgcc_s for eh support.  */
#ifdef HAVE_LD_AS_NEEDED
#define USE_LD_AS_NEEDED 1
#endif

#if defined(HAVE_LD_EH_FRAME_HDR)
#define LINK_EH_SPEC "%{!static|static-pie:--eh-frame-hdr} "
#endif

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

/* Use int, instead of long int, for int32_t and uint32_t.  */
#undef STDINT_LONG32
#define STDINT_LONG32 0

#define TARGET_ASM_FILE_END file_end_indicate_exec_stack
