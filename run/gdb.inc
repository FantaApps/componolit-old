if {[info exists ::env(GDB_PROG)]} {

   if {![info exists build_components]} {
      puts "\nVariable build_components does not exist.\n"
      exit 1
   }
   
   if {![info exists boot_modules]} {
      puts "\nVariable boot_modules does not exist.\n"
      exit 1
   }
   
   if {![info exists ::env(KERNEL)]} {
      puts "\nKERNEL must be configured.\n"
      exit 1
   }
   
   append build_components {
      drivers/uart
      app/gdb_monitor
   }
   lappend build_components "lib/gdbserver_platform-$::env(KERNEL)"
   
   proc binary_name_gdbserver_platform_lib_so { } {
      return "gdbserver_platform-$::env(KERNEL).lib.so"
   }
   
   append boot_modules {
      uart_drv
      gdb_monitor
      gdbserver_platform.lib.so
      libc_pipe.lib.so
      libc_terminal.lib.so
      libc.lib.so
      vfs.lib.so
   }
   
   append qemu_args "-serial mon:stdio "
   append qemu_args "-serial chardev:uart "
   append qemu_args "-chardev socket,id=uart,port=5555,host=localhost,server,nowait,ipv4 "

   # Found no way to prevent xsltproc from escaping the > sign contained in
   # session labels. We have to reverse that using sed.
   set config \
      [exec echo "$config" \
      | xsltproc --stringparam gdb_prog $::env(GDB_PROG) ${genode_dir}/repos/componolit/run/gdb.xsl - \
      | sed -e "s/&gt;/>/g"]
   
   # Make sure gdb can load symbols from ld.lib.so
   if { [have_spec nova] } {
   	exec ln -sf ld-nova.lib.so debug/ld.lib.so
   }

   # Create gdb init sequence
   append gdb_config {target remote localhost:5555
set interactive-mode off
break binary_ready_hook_for_gdb
continue
delete 1
}

   append gdb_config "file debug/$::env(GDB_PROG)"

   append gdb_config {
set solib-search-path debug
sharedlibrary
}

   if {[info exists ::env(GDB_BREAK)]} {
      append gdb_config "break $::env(GDB_BREAK)"
   } 

   set outfile [open debug/$::env(GDB_PROG).gdb w]
   puts $outfile $gdb_config
   flush $outfile
   close $outfile
}
