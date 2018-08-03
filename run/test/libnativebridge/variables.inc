set build_components {
	core init
	drivers/timer
	drivers/rtc
	server/ram_fs
	test/libnativebridge-dummy
}

set config {
<config verbose="yes">
	<parent-provides>
		<service name="ROM"/>
		<service name="CAP"/>
		<service name="RM"/>
		<service name="PD"/>
		<service name="CPU"/>
		<service name="LOG"/>
		<service name="SIGNAL"/>
		<service name="IO_PORT"/>
		<service name="IRQ"/>
		<service name="IO_MEM"/>
	</parent-provides>
	<default-route>
		<any-service> <parent/> <any-child/> </any-service>
	</default-route>
	<default caps="200"/>

	<start name="timer">
		<resource name="RAM" quantum="1M"/>
		<provides> <service name="Timer"/> </provides>
	</start>

	<start name="rtc_drv">
		<resource name="RAM" quantum="1M"/>
		<provides> <service name="Rtc"/> </provides>
	</start>

	<start name="ram_fs">
		<resource name="RAM" quantum="128M"/>
		<provides> <service name="File_system"/> </provides>
		<config>
			<default-policy root="/" writeable="true" />
		</config>
	</start>
}

set boot_modules {
	core init ld.lib.so
	timer ram_fs
	vfs.lib.so
	cxxthreads.lib.so
	libc.lib.so libm.lib.so pthread.lib.so stdcxx.lib.so
	libargv.lib.so
	liblog.lib.so libnativehelper.lib.so libnativebridge.lib.so
	libnativebridge-dummy.lib.so
	libnativebridge2-dummy.lib.so
	libnativebridge3-dummy.lib.so
	rtc_drv
}


set timeout 10
