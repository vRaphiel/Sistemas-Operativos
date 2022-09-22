Resolución

execve("./hai", ["./hai", "ls"], 0x7fffc6884968 /* 60 vars */) = 0
strace: [ Process PID=4029 runs in 32 bit mode. ]
brk(NULL)                               = 0x91c2000         // Change data segment size

arch_prctl(0x3001 /* ARCH_??? */, 0xffb30c98) = -1 EINVAL (Argumento inválido)   // Set architecture-specific thread state
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No existe el archivo o el directorio)   // Check user permisions fr a file
mmap2(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0xf7f30000  // map files or devices into memory.

// Crea un nuevo mapeo de memoria en el espacio de direccion virtual para el proceso que esta llamando.
// Como es NULL el kernel elije la pagina para el mapeo

access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No existe el archivo o el directorio) (R_OK -> checkea si tiene permisos read)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_LARGEFILE|O_CLOEXEC) = 3    // open and possibility create a file
fstat64(3, {st_mode=S_IFREG|0644, st_size=134083, ...}) = 0 // Get file status
mmap2(NULL, 134083, PROT_READ, MAP_PRIVATE, 3, 0) = 0xf7f0f000 // Asigna memoria virtual a una memoria NULL para el archivo
close(3)                                = 0 // Cierra un descriptor de fila. Termina en buen estado

access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No existe el archivo o el directorio)
openat(AT_FDCWD, "/lib/i386-linux-gnu/libc.so.6", O_RDONLY|O_LARGEFILE|O_CLOEXEC) = 3
read(3, "\177ELF\1\1\1\3\0\0\0\0\0\0\0\0\3\0\3\0\1\0\0\0\220\260\1\0004\0\0\0"..., 512) = 512 // Lee el descriptor del archivo
pread64(3, "\4\0\0\0\24\0\0\0\3\0\0\0GNU\0\337\217\36\232\237\n\4\206\34\375\237~M:\344\277"..., 96, 468) = 96  // Lee desde o escribe a el descriptor en un determinado offset

fstat64(3, {st_mode=S_IFREG|0755, st_size=2020588, ...}) = 0
pread64(3, "\4\0\0\0\24\0\0\0\3\0\0\0GNU\0\337\217\36\232\237\n\4\206\34\375\237~M:\344\277"..., 96, 468) = 96
mmap2(NULL, 2025152, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0xf7d20000
mprotect(0xf7d39000, 1900544, PROT_NONE) = 0
mmap2(0xf7d39000, 1421312, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x19000) = 0xf7d39000
mmap2(0xf7e94000, 475136, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x174000) = 0xf7e94000
mmap2(0xf7f09000, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1e8000) = 0xf7f09000
mmap2(0xf7f0c000, 9920, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0xf7f0c000
close(3)                                = 0

set_thread_area({entry_number=-1, base_addr=0xf7f310c0, limit=0x0fffff, seg_32bit=1, contents=0, read_exec_only=0, limit_in_pages=1, seg_not_present=0, useable=1}) = 0 (entry_number=12)
mprotect(0xf7f09000, 8192, PROT_READ)   = 0
mprotect(0x8049000, 4096, PROT_READ)    = 0
mprotect(0xf7f63000, 4096, PROT_READ)   = 0
munmap(0xf7f0f000, 134083)              = 0

// Hasta aca esto es PRE MAIN - Luego de aca sigue todo lo que hace el programa
clone(child_stack=NULL, flags=CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD, child_tidptr=0xf7f8f128) = 6823

strace: Process 6823 attached

[pid  6822] rt_sigaction(SIGINT, {sa_handler=0x8048615, sa_mask=[INT], sa_flags=SA_RESTART}, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
// Examina y cambia la accion ante una señal. Actua en relacion a lo que viene en el SIGINT, hecho eso ejecuta el handler RESTART. El segundo parametro es un puntero a la acción a ejecutar.
// El SIGINT es el Ctrl+C. Es decir, querer terminar el proceso.

[pid  6822] clock_nanosleep_time64(CLOCK_REALTIME, 0, {tv_sec=1, tv_nsec=0},  <unfinished ...>
[pid  6823] rt_sigaction(SIGURG, {sa_handler=0x80485e4, sa_mask=[URG], sa_flags=SA_RESTART}, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
[pid  6822] <... clock_nanosleep_time64 resumed>0xfffe77dc) = 0

[pid  6822] write(1, "sup!\n", 5sup!)       = 5
[pid  6822] kill(6823, SIGURG)          = 0
[pid  6823] --- SIGURG {si_signo=SIGURG, si_code=SI_USER, si_pid=6822, si_uid=1002} ---
[pid  6822] clock_nanosleep_time64(CLOCK_REALTIME, 0, {tv_sec=1, tv_nsec=0},  <unfinished ...>
[pid  6823] write(1, "ya va!\n", 7ya va!)     = 7
[pid  6823] sigreturn({mask=[]})        = 0
[pid  6822] <... clock_nanosleep_time64 resumed>0xfffe77dc) = 0

[pid  6822] write(1, "sup!\n", 5sup!)       = 5
[pid  6822] kill(6823, SIGURG)          = 0
[pid  6823] --- SIGURG {si_signo=SIGURG, si_code=SI_USER, si_pid=6822, si_uid=1002} ---
[pid  6822] clock_nanosleep_time64(CLOCK_REALTIME, 0, {tv_sec=1, tv_nsec=0},  <unfinished ...>
[pid  6823] write(1, "ya va!\n", 7ya va!)     = 7
[pid  6823] sigreturn({mask=[]})        = 1
[pid  6822] <... clock_nanosleep_time64 resumed>0xfffe77dc) = 0

[pid  6822] write(1, "sup!\n", 5sup!)       = 5
[pid  6822] kill(6823, SIGURG)          = 0
[pid  6823] --- SIGURG {si_signo=SIGURG, si_code=SI_USER, si_pid=6822, si_uid=1002} ---
[pid  6823] write(1, "ya va!\n", 7ya va! <unfinished ...>
[pid  6822] clock_nanosleep_time64(CLOCK_REALTIME, 0, {tv_sec=1, tv_nsec=0},  <unfinished ...>
[pid  6823] <... write resumed>)        = 7
[pid  6823] sigreturn({mask=[]})        = 2
[pid  6822] <... clock_nanosleep_time64 resumed>0xfffe77dc) = 0

[pid  6822] write(1, "sup!\n", 5sup!)       = 5
[pid  6822] kill(6823, SIGURG)          = 0
[pid  6823] --- SIGURG {si_signo=SIGURG, si_code=SI_USER, si_pid=6822, si_uid=1002} ---
[pid  6823] write(1, "ya va!\n", 7ya va!<unfinished ...>
[pid  6822] clock_nanosleep_time64(CLOCK_REALTIME, 0, {tv_sec=1, tv_nsec=0},  <unfinished ...>
[pid  6823] <... write resumed>)        = 7
[pid  6823] sigreturn({mask=[]})        = 3
[pid  6822] <... clock_nanosleep_time64 resumed>0xfffe77dc) = 0

[pid  6822] write(1, "sup!\n", 5sup!)       = 5
[pid  6822] kill(6823, SIGURG)          = 0
[pid  6823] --- SIGURG {si_signo=SIGURG, si_code=SI_USER, si_pid=6822, si_uid=1002} ---
[pid  6822] clock_nanosleep_time64(CLOCK_REALTIME, 0, {tv_sec=1, tv_nsec=0},  <unfinished ...>
[pid  6823] write(1, "ya va!\n", 7ya va!)     = 7
[pid  6823] sigreturn({mask=[]})        = 4
[pid  6823] getppid()                   = 6822
[pid  6823] kill(6822, SIGINT <unfinished ...>
[pid  6822] <... clock_nanosleep_time64 resumed>{tv_sec=0, tv_nsec=999626598}) = ? ERESTART_RESTARTBLOCK (Interrupted by signal)

[pid  6823] <... kill resumed>)         = 0
[pid  6822] --- SIGINT {si_signo=SIGINT, si_code=SI_USER, si_pid=6823, si_uid=1002} ---
[pid  6822] wait4(-1,  <unfinished ...>

[pid  6823] execve("/opt/miniconda3/bin/ls", ["ls"], 0xfffe7940 /* 60 vars */) = -1 ENOENT (No existe el archivo o el directorio)
[pid  6823] execve("/opt/miniconda3/condabin/ls", ["ls"], 0xfffe7940 /* 60 vars */) = -1 ENOENT (No existe el archivo o el directorio)
[pid  6823] execve("/home/clinux01/.local/bin/ls", ["ls"], 0xfffe7940 /* 60 vars */) = -1 ENOENT (No existe el archivo o el directorio)
[pid  6823] execve("/usr/local/sbin/ls", ["ls"], 0xfffe7940 /* 60 vars */) = -1 ENOENT (No existe el archivo o el directorio)
[pid  6823] execve("/usr/local/bin/ls", ["ls"], 0xfffe7940 /* 60 vars */) = -1 ENOENT (No existe el archivo o el directorio)
[pid  6823] execve("/usr/sbin/ls", ["ls"], 0xfffe7940 /* 60 vars */) = -1 ENOENT (No existe el archivo o el directorio)
[pid  6823] execve("/usr/bin/ls", ["ls"], 0xfffe7940 /* 60 vars */) = 0 strace: [ Process PID=6823 runs in 64 bit mode. ]
[pid  6823] brk(NULL)                   = 0x55bb563d4000
[pid  6823] arch_prctl(0x3001 /* ARCH_??? */, 0x7fffda42f8e0) = -1 EINVAL (Argumento inválido)
[pid  6823] access("/etc/ld.so.preload", R_OK) = -1 ENOENT (No existe el archivo o el directorio)
[pid  6823] openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
[pid  6823] fstat(3, {st_mode=S_IFREG|0644, st_size=134083, ...}) = 0
[pid  6823] mmap(NULL, 134083, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f7df8bd4000
[pid  6823] close(3)         Al imprimir el mensaje busca hacer un kill del mismo. En dicho caso, lo que hace es como callback producir un mensaje al querer hacerlo. Luego se duerme el procesador un tiempo y repite el proceso. Todo con el mismo PID.
Como el proceso tiene el flag SA_RESTART, muy posiblemente desde el callback del kill se vuelve a levantar el proceso.
Esto es hasta el ultimo momento donde termina.
El padre mata el kill, al hijo. =S_IFREG|0644, st_size=163200, ...}) = 0
[pid  6823] mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f7df8bd2000
[pid  6823] mmap(NULL, 174600, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f7df8ba7000
[pid  6823] mprotect(0x7f7df8bad000, 135168, PROT_NONE) = 0
[pid  6823] mmap(0x7f7df8bad000, 102400, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x6000) = 0x7f7df8bad000
[pid  6823] mmap(0x7f7df8bc6000, 28672, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1f000) = 0x7f7df8bc6000
[pid  6823] mmap(0x7f7df8bce000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x26000) = 0x7f7df8bce000
[pid  6823] mmap(0x7f7df8bd0000, 6664, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f7df8bd0000
[pid  6823] close(3)                    = 0
[pid  6823] openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
[pid  6823] read(3, "\177ELF\Al imprimir el mensaje busca hacer un kill del mismo. En dicho caso, lo que hace es como callback producir un mensaje al querer hacerlo. Luego se duerme el procesador un tiempo y repite el proceso. Todo con el mismo PID.
Como el proceso tiene el flag SA_RESTART, muy posiblemente desde el callback del kill se vuelve a levantar el proceso.
Esto es hasta el ultimo momento donde termina.
El padre mata el kill, al hijo. 0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
[pid  6823] pread64(3, "\4\0\0\0\20\0\0\0\5\0\0\0GNU\0\2\0\0\300\4\0\0\0\3\0\0\0\0\0\0\0", 32, 848) = 32
[pid  6823] pread64(3, "\4\0\0\0\24\0\0\0\3\0\0\0GNU\0\30x\346\264ur\f|Q\226\236i\253-'o"..., 68, 880) = 68
[pid  6823] fstat(3, {st_mode=S_IFREG|0755, st_size=2029592, ...}) = 0
[pid  6823] pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
[pid  6823] pread64(3, "\4\0\0\0\20\0\0\0\5\0\0\0GNU\0\2\0\0\300\4\0\0\0\3\0\0\0\0\0\0\0", 32, 848) = 32
[pid  6823] pread64(3, "\4\0\0\0\24\0\0\0\3\0\0\0GNU\0\30x\346\264ur\f|Q\226\236i\253-'o"..., 68, 880) = 68
[pid  6823] mmap(NULL, 2037344, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f7df89b5000
[pid  6823] mmap(0x7f7df89d7000, 1540096, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x22000) = 0x7f7df89d7000
[pid  6823] mmap(0x7f7df8b4f000, 319488, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x19a000) = 0x7f7df8b4f000
[pid  6823] mmap(0x7f7df8b9d000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1e7000) = 0x7f7df8b9d000
[pid  6823] mmap(0x7f7df8ba3000, 13920, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f7df8ba3000
[pid  6823] close(3)                    = 0
[pid  6823] openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libpcre2-8.so.0", O_RDONLY|O_CLOEXEC) = 3
[pid  6823] read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\340\"\0\0\0\0\0\0"..., 832) = 832
[pid  6823] fstat(3, {st_mode=S_IFREG|0644, st_size=584392, ...}) = 0
[pid  6823] mmap(NULL, 586536, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f7df8925000
[pid  6823] mmap(0x7f7df8927000, 409600, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x2000) = 0x7f7df8927000
[pid  6823] mmap(0x7f7df898b000, 163840, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x66000) = 0x7f7df898b000
[pid  6823] mmap(0x7f7df89b3000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x8d000) = 0x7f7df89b3000
[pid  6823] close(3)                    = 0
[pid  6823] openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libdl.so.2", O_RDONLY|O_CLOEXEC) = 3
[pid  6823] read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0 \22\0\0\0\0\0\0"..., 832) = 832
[pid  6823] fstat(3, {st_mode=S_IFREG|0644, st_size=18848, ...}) = 0
[pid  6823] mmap(NULL, 20752, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f7df891f000
[pid  6823] mmap(0x7f7df8920000, 8192, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1000) = 0x7f7df8920000
[pid  6823] mmap(0x7f7df8922000, 4096, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x3000) = 0x7f7df8922000
[pid  6823] mmap(0x7f7df8923000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x3000) = 0x7f7df8923000
[pid  6823] close(3)                    = 0
[pid  6823] openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libpthread.so.0", O_RDONLY|O_CLOEXEC) = 3
[pid  6823] read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\220q\0\0\0\0\0\0"..., 832) = 832
[pid  6823] pread64(3, "\4\0\0\0\24\0\0\0\3\0\0\0GNU\0{E6\364\34\332\245\210\204\10\350-\0106\343="..., 68, 824) = 68
[pid  6823] fstat(3, {st_mode=S_IFREG|0755, st_size=157224, ...}) = 0
[pid  6823] pread64(3, "\4\0\0\0\24\0\0\0\3\0\0\0GNU\0{E6\364\34\332\245\210\204\10\350-\0106\343="..., 68, 824) = 68
[pid  6823] mmap(NULL, 140408, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f7df88fc000
[pid  6823] mmap(0x7f7df8902000, 69632, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x6000) = 0x7f7df8902000
[pid  6823] mmap(0x7f7df8913000, 24576, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x17000) = 0x7f7df8913000
[pid  6823] mmap(0x7f7df8919000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1c000) = 0x7f7df8919000
[pid  6823] mmap(0x7f7df891b000, 13432, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f7df891b000
[pid  6823] close(3)                    = 0
[pid  6823] mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f7df88fa000
[pid  6823] arch_prctl(ARCH_SET_FS, 0x7f7df88fb400) = 0
[pid  6823] mprotect(0x7f7df8b9d000, 16384, PROT_READ) = 0
[pid  6823] mprotect(0x7f7df8919000, 4096, PROT_READ) = 0
[pid  6823] mprotect(0x7f7df8923000, 4096, PROT_READ) = 0
[pid  6823] mprotect(0x7f7df89b3000, 4096, PROT_READ) = 0
[pid  6823] mprotect(0x7f7df8bce000, 4096, PROT_READ) = 0
[pid  6823] mprotect(0x55bb54458000, 4096, PROT_READ) = 0
[pid  6823] mprotect(0x7f7df8c22000, 4096, PROT_READ) = 0
[pid  6823] munmap(0x7f7df8bd4000, 134083) = 0
[pid  6823] set_tid_address(0x7f7df88fb6d0) = 6823
[pid  6823] set_robust_list(0x7f7df88fb6e0, 24) = 0
[pid  6823] rt_sigaction(SIGRTMIN, {sa_handler=0x7f7df8902bf0, sa_mask=[], sa_flags=SA_RESTORER|SA_SIGINFO, sa_restorer=0x7f7df8910420}, NULL, 8) = 0
[pid  6823] rt_sigaction(SIGRT_1, {sa_handler=0x7f7df8902c90, sa_mask=[], sa_flags=SA_RESTORER|SA_RESTART|SA_SIGINFO, sa_restorer=0x7f7df8910420}, NULL, 8) = 0
[pid  6823] rt_sigprocmask(SIG_UNBLOCK, [RTMIN RT_1], NULL, 8) = 0
[pid  6823] prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
[pid  6823] statfs("/sys/fs/selinux", 0x7fffda42f830) = -1 ENOENT (No existe el archivo o el directorio)
[pid  6823] statfs("/selinux", 0x7fffda42f830) = -1 ENOENT (No existe el archivo o el directorio)
[pid  6823] brk(NULL)                   = 0x55bb563d4000
[pid  6823] brk(0x55bb563f5000)         = 0x55bb563f5000
[pid  6823] openat(AT_FDCWD, "/proc/filesystems", O_RDONLY|O_CLOEXEC) = 3
[pid  6823] fstat(3, {st_mode=S_IFREG|0444, st_size=0, ...}) = 0
[pid  6823] read(3, "nodev\tsysfs\nnodev\ttmpfs\nnodev\tbd"..., 1024) = 393
[pid  6823] read(3, "", 1024)           = 0
[pid  6823] close(3)                    = 0
[pid  6823] access("/etc/selinux/config", F_OK) = -1 ENOENT (No existe el archivo o el directorio)
[pid  6823] openat(AT_FDCWD, "/usr/lib/locale/locale-archive", O_RDONLY|O_CLOEXEC) = 3
[pid  6823] fstat(3, {st_mode=S_IFREG|0644, st_size=8378608, ...}) = 0
[pid  6823] mmap(NULL, 8378608, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f7df80fc000
[pid  6823] close(3)                    = 0sigreturncol=203, ws_xpixel=0, ws_ypixel=0}) = 0
[pid  6823] openat(AT_FDCWD, ".", O_RDONLY|O_NONBLOCK|O_CLOEXEC|O_DIRECTORY) = 3
[pid  6823] fstat(3, {st_mode=S_IFDIR|0777, st_size=4096, ...}) = 0
[pid  6823] getdents64(3, /* 4 entri6822
[pid  6823] close(1)                    = 0
[pid  6823] close(2)                    = 0
[pid  6823] exit_group(0)               = ?
[pid  6823] +++ exited with 0 +++
<... wait4 resumed>[{WIFEXITED(s) && WEXITSTATUS(s) == 0}], 0, NULL) = 6823
--- SIGCHLD {si_signo=SIGCHLD, si_code=CLD_EXITED, si_pid=6823, si_uid=1002, si_status=0, si_utime=500, si_stime=0} ---
exit_group(0)                           = ?
+++ exited with 0 +++


### Ejercicio 1

## Item a

La cantidad de procesos que tira son: 5

## Item b

Si utilizan un IPC, el sigreturn y el kill(PID, SIGURG). Al ocurrir el kill el padre se va a dormimr con nanosleep hasta que el sigreturn devuelva algo.

## Item c

Del programa se puede decir que, crea un proceso que imprime un mensaje, clona su PID y luego cicla con ese PID durante 5 veces haciendo que se imprima el mensaje. 

Antes de eso, al padre se asigna un handler en evento SIGINT y, al hijo, un handler en evento SIGURG.
Cuando ocurre SIGURG, se ejecuta el handler ante la ocurrencia y el padre se va a dormir. Una vez hecho esto, el hijo responde al mensaje, imprime por pantalla y hace una devolución de la señal. Cuando se recibe, el padre se despierta al proximo ciclo de clock y luego continua con lo mismo.

La señal devuelta va a ir incrementando de 1 en 1 hasta que llegue la situación en la que sea 4. Cuando ocurre, se obtiene el PID del padre y, ocurrido, se lo mata.