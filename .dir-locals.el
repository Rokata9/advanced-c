;;; .dir-locals.el --- one project, many programs (see init.el section 12)
;; %p = the program the current file belongs to:
;;      a .c file with its own main() is a program by itself, e.g.
;;      exercises/sum.c -> exercises/sum (keep many in one folder; a main.c
;;      among them is one of them too: pointers/main.c -> pointers/main);
;;      otherwise the nearest folder above the file that has a main.c, e.g. hello.
;;      In a file outside every program it is the last program you used.
;;   Cmd+Shift+B    build the active program
;;   Ctrl+Option+N  build + run it (type input in the bottom panel)
;;   F5             build + debug it (stops at F9 breakpoints in any of its files)
;; -j... = compile files in parallel, one job per CPU core.

((nil . ((my/build-command . "make -j$(getconf _NPROCESSORS_ONLN) PROG=%p")
         (my/run-command   . "make -j$(getconf _NPROCESSORS_ONLN) run PROG=%p")
         (my/debug-program . "build/%p"))))
