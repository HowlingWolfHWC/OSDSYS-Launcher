This will launch a OSDSYS from your MC.

If you have a PS2 with v2.30 BIOS or higher, you can use this application as DEV1 (mc0:/BOOT/BOOT.ELF) as well as
a FORTUNA default ELF (mc0:/FORTUNA/BOOT.ELF) replacment and use it to launch the FMCB hacked OSDSYS or XEB/XEB+.

Detailed instructions for FMCB installation on SCPH-900XX or PSTV:
FMCB v1.8C (with modchip):
1 - Take a clean FMCB 1.8C release and decompress it
2 - Select the correct HWC's OSDSYS Launcher "BOOT.ELF" for your region IF REQUIERED (* read notes)
3 - Go to the INSTALL folder and paste "BOOT.ELF" in it
4 - Create a folder called "APPS" inside the "INSTALL" folder
5 - Paste you beloved apps in there (OPL, uLE, etc)
6 - Copy the installation files to a pendrive and put it on your PS2
7 - Use the method you want to launch the FMCB installer (a uLE DVD it's perfect if you have no MC with DEV1 ready)
8 - Select normal install and wait
9 - Once done, reset your PS2 and configure your modchip to boot from DEV1
10 - Now reset your PS2 again, when the FMCB logo shows up, press SELECT to configure FMCB.

FMCB v1.9 (with modchip):
1 - Take a clean FMCB 1.9 release and decompress it
2 - Delete the "BOOT.ELF" inside the "BOOT" folder
3 - Select the correct HWC's OSDSYS Launcher "BOOT.ELF" for your region IF REQUIERED (* read notes)
4 - Go to the "BOOT" folder inside the "INSTALL" folder and paste the HWC's OSDSYS Launcher "BOOT.ELF" in it
5 - Go to the "APPS" folder inside the "INSTALL" folder and paste you beloved apps in there (OPL, uLE, etc)
6 - Copy the installation files to a pendrive and put it on your PS2
7 - Use the method you want to launch the FMCB installer (a uLE DVD it's perfect if you have no MC with DEV1 ready)
8 - Select normal install and wait
9 - Once done, reset your PS2 and configure your modchip to boot from DEV1
10 - Now reset your PS2 again, when the FMCB logo shows up, press SELECT to configure FMCB.

FORTUNA Users (no modchip required):
1 - Install FMCB (you do not need to fellow the instructions above, you can use a noobie package if you want to).
2 - Select the correct HWC's OSDSYS Launcher "BOOT.ELF" for your region IF REQUIERED (* read notes)
3 - Replace the BOOT.ELF in the FORTUNA's folder (mc0:/FORTUNA/BOOT.ELF) with the HWC's OSDSYS Launcher's "BOOT.ELF"
4 - Now reset your PS2 again and go to the browser and launch the FOTUNA exploit as always
5 - When the FMCB logo shows up, press SELECT to configure FMCB.

Diferences with FORTUNA FMCB Launcher by VTSTech:
Well, it seems that VTSTech did NOT tested his application on real hardware. His application will NOT work properly
on consoles with v2.30+ BIOS. Of course, it will work as intended on any console with v2.20 or lower, but that's not
the main reason to use this application, right?

Notes:
We made a "small" adjustment on the software logic to avoid a certain issue: people having a messy FMCB installation
on their memory card AND users using a launcher from "certain developer" who does not knows how to reset IOP properly.
It seems that there's someone on eBay selling FMCB memory cards with a "multi-region" installed FMCB v1.8C which
includes three different FMCBs installations made from three different consoles. That setup is a nonsense as the
KELFs are not really region free, these are ELFs injected on the DVDELFs from XXX01, XXX04 and XXX06. That seller
does not seems to know that FMCB v1.9 exists and can do proper multi-region installations.
If you do not have these kind of frankenfmcb, ANY ELF in our release should work for you, but, if that's not the case,
please, select the proper one for your region.

--------------------------------------------
           Howling Wolf & Chelsea
     	          2017-2020
		Made In Cuba!
--------------------------------------------
  I you have any questions you can contact
  me on psx-place.com as "HWNJ" or send me
   an email to cerebro404hwc@gmail.com or
      howlingwolfandchelsea@gmail.com
--------------------------------------------
