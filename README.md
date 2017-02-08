# carpi
Raspberry CarPC

 - rtl-sdr
	- Source:	http://osmocom.org/projects/sdr/wiki/Rtl-sdr
	- Build:	http://osmocom.org/projects/sdr/wiki/Rtl-sdr#Building-the-software
	- Repo:		http://osmocom.org/projects/sdr/repository

 - rtl-sdr fm radio pvr kodi addon
	- Source:	http://esmasol.de/open-source/kodi-add-on-s/fm-radio-receiver
	- Repo:		https://github.com/AlwinEsch/pvr.rtl.radiofm

	# Build addon:

	Note: Make sure kodi's add-on depends are present libusb-1.0, libkodiplatform, libplatform and tinyxml):

		git clone https://github.com/AlwinEsch/pvr.rtl.radiofm
		mkdir ./pvr.rtl.radiofm/build
		cd ./pvr.rtl.radiofm/build
		cmake -DCMAKE_INSTALL_PREFIX=/usr ..
		make install

----------------------------------------------------------------------------------------------------------------

	Conflicts with DVB-T kernel modules provided by the Linux kernel

		Typical error of module conflict:

		  Using device 0: ezcap USB 2.0 DVB-T/DAB/FM dongle

		  Kernel driver is active, or device is claimed by second instance of librtlsdr.
		  In the first case, please either detach or blacklist the kernel module
		  (dvb_usb_rtl28xxu), or enable automatic detaching at compile time.

		  usb_claim_interface error -6
		  Failed to open rtlsdr device #0

	You may decide to blacklist this kernel module by doing (as root):

		echo "blacklist dvb_usb_rtl28xxu" > \
		 /etc/modprobe.d/librtlsdr-blacklist.conf

	Then unplug/plug the USB stick.

----------------------------------------------------------------------------------------------------------------

	Permissions

	If you have permissions issues please install the example udev rules from
	librtlsdr-0.5.2 folder (as root):

cp ./rtl-sdr.rules /etc/udev/rules.d/99-librtlsdr.rules
invoke-rc.d udev reload

 

   
Development code:

https://github.com/AlwinEsch/pvr.rtl.radiofm
    Current Branches:
        - master: Development branch
        - Isengard: Fixed add-on source for Kodi 15.2, support also Raspberry PI
