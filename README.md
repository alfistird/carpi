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

