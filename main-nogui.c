#include <debug.h>
#include <iopcontrol.h>
#include <iopheap.h>
#include <kernel.h>
#include <sifrpc.h>
#include <loadfile.h>
#include <stdio.h>
#include <unistd.h>
#include <input.h>
#include <time.h>
#include <string.h>
#include <libcdvd.h>
//#include <fileXio.h>
//#include <fileXio_rpc.h>
#include <fcntl.h>
#include <sbv_patches.h>
#include "OSDInit.h"

//Segments of code comes from uLE and some works of SP193

void ResetIOP()
{
	SifInitRpc(0);
	while(!SifIopReset("", 0)){};
	while(!SifIopSync()){};
	SifInitRpc(0);
}

void InitPS2()
{
	init_scr();
	ResetIOP();
	SifInitIopHeap();
	SifLoadFileInit();
	fioInit();
	sbv_patch_disable_prefix_check();
	SifLoadModule("rom0:SIO2MAN", 0, NULL);
	SifLoadModule("rom0:MCMAN", 0, NULL);
	SifLoadModule("rom0:MCSERV", 0, NULL);
}

void LoadElf(const char *elf, char* path)
{
	char* args[1];
	t_ExecData exec;	
	SifLoadElf(elf, &exec);

	if(exec.epc > 0)
	{	
		ResetIOP();

		if(path != 0)
		{
			args[0] = path;
			ExecPS2((void*)exec.epc, (void*)exec.gp, 1, args);
		}
		else
		{
			ExecPS2((void*)exec.epc, (void*)exec.gp, 0, NULL);
		}
	}
}

int main(int argc, char *argv[], char **envp)
{
	InitPS2();
	scr_clear();
    scr_printf("\n\n HWC's OSDSYS Launcher v1.7 \n");	//NOGUI
	
	char *mi_rom_es;
	char *simple_es;
	mi_rom_es=GetRomName("5");
	simple_es=strncpy("????", mi_rom_es, 4);
	
	u8 romver[16];
	int fdn;
	if((fdn = open("rom0:ROMVER", O_RDONLY)) > 0) 
	{
		read(fdn, romver, sizeof romver);
		close(fdn);
	}
	int file_exists(char filepath[])
	{	
		filepath[6] = (romver[4] == 'E' ? 'E' : 
			(romver[4] == 'J' ? 'I' : 
				(romver[4] == 'H' ? 'A' : 
					(romver[4] == 'U' ? 'A' : romver[4]))));
		
		int fdn;
		
		fdn = open(filepath, O_RDONLY);
		if (fdn < 0) return 0;
		close(fdn);
		
		return 1;
	}
	void CargarelOSDSYS(char default_OSDSYS_path[])
	{
		char arg0[20], arg1[20], arg2[20], arg3[40];
		char *args[4] = {arg0, arg1, arg2, arg3};
		char kelf_loader[40];
		int argc;
		char path[1025];
		
		default_OSDSYS_path[6] = (romver[4] == 'E' ? 'E' : 
			(romver[4] == 'J' ? 'I' : 
				(romver[4] == 'H' ? 'A' : 
					(romver[4] == 'U' ? 'A' : romver[4]))));
		/*
		if(romver[4] == 'J') default_OSDSYS_path[] = "mc:/BIEXEC-SYSTEM/osdmain.elf";
		else if(romver[4] == 'E') default_OSDSYS_path[] = "mc:/BEEXEC-SYSTEM/osdmain.elf";
		else default_OSDSYS_path[] = "mc:/BAEXEC-SYSTEM/osdmain.elf";
		*/
		
		strcpy(path, default_OSDSYS_path);
		
		strcpy(arg0, "-m rom0:SIO2MAN");
		strcpy(arg1, "-m rom0:MCMAN");
		strcpy(arg2, "-m rom0:MCSERV");
		sprintf(arg3, "-x %s", path);
		argc = 4;
		strcpy(kelf_loader, "moduleload");
		LoadExecPS2(kelf_loader, argc, args);
	}
	
	
	if (file_exists("mc0:/B?EXEC-SYSTEM/osdmain.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osdmain.elf");
	if (file_exists("mc0:/B?EXEC-SYSTEM/osd110.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd110.elf");
	if (file_exists("mc0:/B?EXEC-SYSTEM/osd120.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd120.elf");
	if (file_exists("mc0:/B?EXEC-SYSTEM/osd130.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd130.elf");
	if (file_exists("mc0:/B?EXEC-SYSTEM/osd140.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd140.elf");
	if (file_exists("mc0:/B?EXEC-SYSTEM/osd150.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd150.elf");
	if (file_exists("mc0:/B?EXEC-SYSTEM/osd160.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd160.elf");
	if (file_exists("mc0:/B?EXEC-SYSTEM/osd170.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd170.elf");
	if (file_exists("mc0:/B?EXEC-SYSTEM/osd180.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd180.elf");
	if (file_exists("mc0:/B?EXEC-SYSTEM/osd190.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd190.elf");
	if (file_exists("mc0:/B?EXEC-SYSTEM/osd200.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd200.elf");
	if (file_exists("mc0:/B?EXEC-SYSTEM/osd210.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd210.elf");
	if (file_exists("mc0:/B?EXEC-SYSTEM/osd220.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd220.elf");
	if (file_exists("mc0:/B?EXEC-SYSTEM/osd230.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd230.elf");
	if (file_exists("mc0:/B?EXEC-SYSTEM/osd240.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd240.elf");
	if (file_exists("mc0:/B?EXEC-SYSTEM/osd250.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd250.elf");
	if (file_exists("mc0:/B?EXEC-SYSTEM/osd260.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd260.elf");
	if (file_exists("mc0:/B?EXEC-SYSTEM/osd270.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd270.elf");

        if (file_exists("mc1:/B?EXEC-SYSTEM/osdmain.elf")) CargarelOSDSYS("mc1:/B?EXEC-SYSTEM/osdmain.elf");
	if (file_exists("mc1:/B?EXEC-SYSTEM/osd110.elf")) CargarelOSDSYS("mc1:/B?EXEC-SYSTEM/osd110.elf");
	if (file_exists("mc1:/B?EXEC-SYSTEM/osd120.elf")) CargarelOSDSYS("mc1:/B?EXEC-SYSTEM/osd120.elf");
	if (file_exists("mc1:/B?EXEC-SYSTEM/osd130.elf")) CargarelOSDSYS("mc1:/B?EXEC-SYSTEM/osd130.elf");
	if (file_exists("mc1:/B?EXEC-SYSTEM/osd140.elf")) CargarelOSDSYS("mc1:/B?EXEC-SYSTEM/osd140.elf");
	if (file_exists("mc1:/B?EXEC-SYSTEM/osd150.elf")) CargarelOSDSYS("mc1:/B?EXEC-SYSTEM/osd150.elf");
	if (file_exists("mc1:/B?EXEC-SYSTEM/osd160.elf")) CargarelOSDSYS("mc1:/B?EXEC-SYSTEM/osd160.elf");
	if (file_exists("mc1:/B?EXEC-SYSTEM/osd170.elf")) CargarelOSDSYS("mc1:/B?EXEC-SYSTEM/osd170.elf");
	if (file_exists("mc1:/B?EXEC-SYSTEM/osd180.elf")) CargarelOSDSYS("mc1:/B?EXEC-SYSTEM/osd180.elf");
	if (file_exists("mc1:/B?EXEC-SYSTEM/osd190.elf")) CargarelOSDSYS("mc1:/B?EXEC-SYSTEM/osd190.elf");
	if (file_exists("mc1:/B?EXEC-SYSTEM/osd200.elf")) CargarelOSDSYS("mc1:/B?EXEC-SYSTEM/osd200.elf");
	if (file_exists("mc1:/B?EXEC-SYSTEM/osd210.elf")) CargarelOSDSYS("mc1:/B?EXEC-SYSTEM/osd210.elf");
	if (file_exists("mc1:/B?EXEC-SYSTEM/osd220.elf")) CargarelOSDSYS("mc1:/B?EXEC-SYSTEM/osd220.elf");
	if (file_exists("mc1:/B?EXEC-SYSTEM/osd230.elf")) CargarelOSDSYS("mc1:/B?EXEC-SYSTEM/osd230.elf");
	if (file_exists("mc1:/B?EXEC-SYSTEM/osd240.elf")) CargarelOSDSYS("mc1:/B?EXEC-SYSTEM/osd240.elf");
	if (file_exists("mc1:/B?EXEC-SYSTEM/osd250.elf")) CargarelOSDSYS("mc1:/B?EXEC-SYSTEM/osd250.elf");
	if (file_exists("mc1:/B?EXEC-SYSTEM/osd260.elf")) CargarelOSDSYS("mc1:/B?EXEC-SYSTEM/osd260.elf");
	if (file_exists("mc1:/B?EXEC-SYSTEM/osd270.elf")) CargarelOSDSYS("mc1:/B?EXEC-SYSTEM/osd270.elf");
	/*
	if (file_exists("mc0:/BAEXEC-SYSTEM/osdmain.elf")) CargarelOSDSYS("mc:/BAEXEC-SYSTEM/osdmain.elf");
	if (file_exists("mc0:/BAEXEC-SYSTEM/osd110.elf")) CargarelOSDSYS("mc:/BAEXEC-SYSTEM/osd110.elf");
	if (file_exists("mc0:/BAEXEC-SYSTEM/osd120.elf")) CargarelOSDSYS("mc:/BAEXEC-SYSTEM/osd120.elf");
	if (file_exists("mc0:/BAEXEC-SYSTEM/osd130.elf")) CargarelOSDSYS("mc:/BAEXEC-SYSTEM/osd130.elf");
	if (file_exists("mc0:/BAEXEC-SYSTEM/osd140.elf")) CargarelOSDSYS("mc:/BAEXEC-SYSTEM/osd140.elf");
	if (file_exists("mc0:/BAEXEC-SYSTEM/osd150.elf")) CargarelOSDSYS("mc:/BAEXEC-SYSTEM/osd150.elf");
	if (file_exists("mc0:/BAEXEC-SYSTEM/osd160.elf")) CargarelOSDSYS("mc:/BAEXEC-SYSTEM/osd160.elf");
	if (file_exists("mc0:/BAEXEC-SYSTEM/osd170.elf")) CargarelOSDSYS("mc:/BAEXEC-SYSTEM/osd170.elf");
	if (file_exists("mc0:/BAEXEC-SYSTEM/osd180.elf")) CargarelOSDSYS("mc:/BAEXEC-SYSTEM/osd180.elf");
	if (file_exists("mc0:/BAEXEC-SYSTEM/osd190.elf")) CargarelOSDSYS("mc:/BAEXEC-SYSTEM/osd190.elf");
	if (file_exists("mc0:/BAEXEC-SYSTEM/osd200.elf")) CargarelOSDSYS("mc:/BAEXEC-SYSTEM/osd200.elf");
	if (file_exists("mc0:/BAEXEC-SYSTEM/osd210.elf")) CargarelOSDSYS("mc:/BAEXEC-SYSTEM/osd210.elf");
	if (file_exists("mc0:/BAEXEC-SYSTEM/osd220.elf")) CargarelOSDSYS("mc:/BAEXEC-SYSTEM/osd220.elf");
	if (file_exists("mc0:/BAEXEC-SYSTEM/osd230.elf")) CargarelOSDSYS("mc:/BAEXEC-SYSTEM/osd230.elf");
	if (file_exists("mc0:/BAEXEC-SYSTEM/osd240.elf")) CargarelOSDSYS("mc:/BAEXEC-SYSTEM/osd240.elf");
	if (file_exists("mc0:/BAEXEC-SYSTEM/osd250.elf")) CargarelOSDSYS("mc:/BAEXEC-SYSTEM/osd250.elf");
	if (file_exists("mc0:/BAEXEC-SYSTEM/osd260.elf")) CargarelOSDSYS("mc:/BAEXEC-SYSTEM/osd260.elf");
	if (file_exists("mc0:/BAEXEC-SYSTEM/osd270.elf")) CargarelOSDSYS("mc:/BAEXEC-SYSTEM/osd270.elf");
	if (file_exists("mc0:/BEEXEC-SYSTEM/osdmain.elf")) CargarelOSDSYS("mc:/BEEXEC-SYSTEM/osdmain.elf");
	if (file_exists("mc0:/BEEXEC-SYSTEM/osd110.elf")) CargarelOSDSYS("mc:/BEEXEC-SYSTEM/osd110.elf");
	if (file_exists("mc0:/BEEXEC-SYSTEM/osd120.elf")) CargarelOSDSYS("mc:/BEEXEC-SYSTEM/osd120.elf");
	if (file_exists("mc0:/BEEXEC-SYSTEM/osd130.elf")) CargarelOSDSYS("mc:/BEEXEC-SYSTEM/osd130.elf");
	if (file_exists("mc0:/BEEXEC-SYSTEM/osd140.elf")) CargarelOSDSYS("mc:/BEEXEC-SYSTEM/osd140.elf");
	if (file_exists("mc0:/BEEXEC-SYSTEM/osd150.elf")) CargarelOSDSYS("mc:/BEEXEC-SYSTEM/osd150.elf");
	if (file_exists("mc0:/BEEXEC-SYSTEM/osd160.elf")) CargarelOSDSYS("mc:/BEEXEC-SYSTEM/osd160.elf");
	if (file_exists("mc0:/BEEXEC-SYSTEM/osd170.elf")) CargarelOSDSYS("mc:/BEEXEC-SYSTEM/osd170.elf");
	if (file_exists("mc0:/BEEXEC-SYSTEM/osd180.elf")) CargarelOSDSYS("mc:/BEEXEC-SYSTEM/osd180.elf");
	if (file_exists("mc0:/BEEXEC-SYSTEM/osd190.elf")) CargarelOSDSYS("mc:/BEEXEC-SYSTEM/osd190.elf");
	if (file_exists("mc0:/BEEXEC-SYSTEM/osd200.elf")) CargarelOSDSYS("mc:/BEEXEC-SYSTEM/osd200.elf");
	if (file_exists("mc0:/BEEXEC-SYSTEM/osd210.elf")) CargarelOSDSYS("mc:/BEEXEC-SYSTEM/osd210.elf");
	if (file_exists("mc0:/BEEXEC-SYSTEM/osd220.elf")) CargarelOSDSYS("mc:/BEEXEC-SYSTEM/osd220.elf");
	if (file_exists("mc0:/BEEXEC-SYSTEM/osd230.elf")) CargarelOSDSYS("mc:/BEEXEC-SYSTEM/osd230.elf");
	if (file_exists("mc0:/BEEXEC-SYSTEM/osd240.elf")) CargarelOSDSYS("mc:/BEEXEC-SYSTEM/osd240.elf");
	if (file_exists("mc0:/BEEXEC-SYSTEM/osd250.elf")) CargarelOSDSYS("mc:/BEEXEC-SYSTEM/osd250.elf");
	if (file_exists("mc0:/BEEXEC-SYSTEM/osd260.elf")) CargarelOSDSYS("mc:/BEEXEC-SYSTEM/osd260.elf");
	if (file_exists("mc0:/BEEXEC-SYSTEM/osd270.elf")) CargarelOSDSYS("mc:/BEEXEC-SYSTEM/osd270.elf");
	if (file_exists("mc0:/BIEXEC-SYSTEM/osdmain.elf")) CargarelOSDSYS("mc:/BIEXEC-SYSTEM/osdmain.elf");
	if (file_exists("mc0:/BIEXEC-SYSTEM/osd110.elf")) CargarelOSDSYS("mc:/BIEXEC-SYSTEM/osd110.elf");
	if (file_exists("mc0:/BIEXEC-SYSTEM/osd120.elf")) CargarelOSDSYS("mc:/BIEXEC-SYSTEM/osd120.elf");
	if (file_exists("mc0:/BIEXEC-SYSTEM/osd130.elf")) CargarelOSDSYS("mc:/BIEXEC-SYSTEM/osd130.elf");
	if (file_exists("mc0:/BIEXEC-SYSTEM/osd140.elf")) CargarelOSDSYS("mc:/BIEXEC-SYSTEM/osd140.elf");
	if (file_exists("mc0:/BIEXEC-SYSTEM/osd150.elf")) CargarelOSDSYS("mc:/BIEXEC-SYSTEM/osd150.elf");
	if (file_exists("mc0:/BIEXEC-SYSTEM/osd160.elf")) CargarelOSDSYS("mc:/BIEXEC-SYSTEM/osd160.elf");
	if (file_exists("mc0:/BIEXEC-SYSTEM/osd170.elf")) CargarelOSDSYS("mc:/BIEXEC-SYSTEM/osd170.elf");
	if (file_exists("mc0:/BIEXEC-SYSTEM/osd180.elf")) CargarelOSDSYS("mc:/BIEXEC-SYSTEM/osd180.elf");
	if (file_exists("mc0:/BIEXEC-SYSTEM/osd190.elf")) CargarelOSDSYS("mc:/BIEXEC-SYSTEM/osd190.elf");
	if (file_exists("mc0:/BIEXEC-SYSTEM/osd200.elf")) CargarelOSDSYS("mc:/BIEXEC-SYSTEM/osd200.elf");
	if (file_exists("mc0:/BIEXEC-SYSTEM/osd210.elf")) CargarelOSDSYS("mc:/BIEXEC-SYSTEM/osd210.elf");
	if (file_exists("mc0:/BIEXEC-SYSTEM/osd220.elf")) CargarelOSDSYS("mc:/BIEXEC-SYSTEM/osd220.elf");
	if (file_exists("mc0:/BIEXEC-SYSTEM/osd230.elf")) CargarelOSDSYS("mc:/BIEXEC-SYSTEM/osd230.elf");
	if (file_exists("mc0:/BIEXEC-SYSTEM/osd240.elf")) CargarelOSDSYS("mc:/BIEXEC-SYSTEM/osd240.elf");
	if (file_exists("mc0:/BIEXEC-SYSTEM/osd250.elf")) CargarelOSDSYS("mc:/BIEXEC-SYSTEM/osd250.elf");
	if (file_exists("mc0:/BIEXEC-SYSTEM/osd260.elf")) CargarelOSDSYS("mc:/BIEXEC-SYSTEM/osd260.elf");
	if (file_exists("mc0:/BIEXEC-SYSTEM/osd270.elf")) CargarelOSDSYS("mc:/BIEXEC-SYSTEM/osd270.elf");
	*/
	/////////////////
	// Agregar dentro del while la llamada al SYSLOOP.ELF
	scr_printf("\n Prioritary region: EUR \n");	
	scr_printf("\n\n If you stuck on this screen for a while, \n verify you have connected a Memory Card \n with XtremeEliteBoot+ or FreeMCBoot \n properly installed. \n");	
	while(1){
		if (file_exists("mc0:/B?EXEC-SYSTEM/osdmain.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osdmain.elf");
		if (file_exists("mc0:/B?EXEC-SYSTEM/osd110.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd110.elf");
		if (file_exists("mc0:/B?EXEC-SYSTEM/osd120.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd120.elf");
		if (file_exists("mc0:/B?EXEC-SYSTEM/osd130.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd130.elf");
		if (file_exists("mc0:/B?EXEC-SYSTEM/osd140.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd140.elf");
		if (file_exists("mc0:/B?EXEC-SYSTEM/osd150.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd150.elf");
		if (file_exists("mc0:/B?EXEC-SYSTEM/osd160.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd160.elf");
		if (file_exists("mc0:/B?EXEC-SYSTEM/osd170.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd170.elf");
		if (file_exists("mc0:/B?EXEC-SYSTEM/osd180.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd180.elf");
		if (file_exists("mc0:/B?EXEC-SYSTEM/osd190.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd190.elf");
		if (file_exists("mc0:/B?EXEC-SYSTEM/osd200.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd200.elf");
		if (file_exists("mc0:/B?EXEC-SYSTEM/osd210.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd210.elf");
		if (file_exists("mc0:/B?EXEC-SYSTEM/osd220.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd220.elf");
		if (file_exists("mc0:/B?EXEC-SYSTEM/osd230.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd230.elf");
		if (file_exists("mc0:/B?EXEC-SYSTEM/osd240.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd240.elf");
		if (file_exists("mc0:/B?EXEC-SYSTEM/osd250.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd250.elf");
		if (file_exists("mc0:/B?EXEC-SYSTEM/osd260.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd260.elf");
		if (file_exists("mc0:/B?EXEC-SYSTEM/osd270.elf")) CargarelOSDSYS("mc0:/B?EXEC-SYSTEM/osd270.elf");
		//
		if (file_exists("mc0:/BEEXEC-SYSTEM/osdmain.elf")) CargarelOSDSYS("mc0:/BEEXEC-SYSTEM/osdmain.elf");
		if (file_exists("mc0:/BEEXEC-SYSTEM/osd110.elf")) CargarelOSDSYS("mc0:/BEEXEC-SYSTEM/osd110.elf");
		if (file_exists("mc0:/BEEXEC-SYSTEM/osd120.elf")) CargarelOSDSYS("mc0:/BEEXEC-SYSTEM/osd120.elf");
		if (file_exists("mc0:/BEEXEC-SYSTEM/osd130.elf")) CargarelOSDSYS("mc0:/BEEXEC-SYSTEM/osd130.elf");
		if (file_exists("mc0:/BEEXEC-SYSTEM/osd140.elf")) CargarelOSDSYS("mc0:/BEEXEC-SYSTEM/osd140.elf");
		if (file_exists("mc0:/BEEXEC-SYSTEM/osd150.elf")) CargarelOSDSYS("mc0:/BEEXEC-SYSTEM/osd150.elf");
		if (file_exists("mc0:/BEEXEC-SYSTEM/osd160.elf")) CargarelOSDSYS("mc0:/BEEXEC-SYSTEM/osd160.elf");
		if (file_exists("mc0:/BEEXEC-SYSTEM/osd170.elf")) CargarelOSDSYS("mc0:/BEEXEC-SYSTEM/osd170.elf");
		if (file_exists("mc0:/BEEXEC-SYSTEM/osd180.elf")) CargarelOSDSYS("mc0:/BEEXEC-SYSTEM/osd180.elf");
		if (file_exists("mc0:/BEEXEC-SYSTEM/osd190.elf")) CargarelOSDSYS("mc0:/BEEXEC-SYSTEM/osd190.elf");
		if (file_exists("mc0:/BEEXEC-SYSTEM/osd200.elf")) CargarelOSDSYS("mc0:/BEEXEC-SYSTEM/osd200.elf");
		if (file_exists("mc0:/BEEXEC-SYSTEM/osd210.elf")) CargarelOSDSYS("mc0:/BEEXEC-SYSTEM/osd210.elf");
		if (file_exists("mc0:/BEEXEC-SYSTEM/osd220.elf")) CargarelOSDSYS("mc0:/BEEXEC-SYSTEM/osd220.elf");
		if (file_exists("mc0:/BEEXEC-SYSTEM/osd230.elf")) CargarelOSDSYS("mc0:/BEEXEC-SYSTEM/osd230.elf");
		if (file_exists("mc0:/BEEXEC-SYSTEM/osd240.elf")) CargarelOSDSYS("mc0:/BEEXEC-SYSTEM/osd240.elf");
		if (file_exists("mc0:/BEEXEC-SYSTEM/osd250.elf")) CargarelOSDSYS("mc0:/BEEXEC-SYSTEM/osd250.elf");
		if (file_exists("mc0:/BEEXEC-SYSTEM/osd260.elf")) CargarelOSDSYS("mc0:/BEEXEC-SYSTEM/osd260.elf");
		if (file_exists("mc0:/BEEXEC-SYSTEM/osd270.elf")) CargarelOSDSYS("mc0:/BEEXEC-SYSTEM/osd270.elf");
		//
		if (file_exists("mc0:/BAEXEC-SYSTEM/osdmain.elf")) CargarelOSDSYS("mc0:/BAEXEC-SYSTEM/osdmain.elf");
		if (file_exists("mc0:/BAEXEC-SYSTEM/osd110.elf")) CargarelOSDSYS("mc0:/BAEXEC-SYSTEM/osd110.elf");
		if (file_exists("mc0:/BAEXEC-SYSTEM/osdsys.elf")) CargarelOSDSYS("mc0:/BAEXEC-SYSTEM/osdsys.elf");
		if (file_exists("mc0:/BAEXEC-SYSTEM/osdmain.elf")) CargarelOSDSYS("mc0:/BAEXEC-SYSTEM/osdmain.elf");
		if (file_exists("mc0:/BAEXEC-SYSTEM/osd110.elf")) CargarelOSDSYS("mc0:/BAEXEC-SYSTEM/osd110.elf");
		if (file_exists("mc0:/BAEXEC-SYSTEM/osd120.elf")) CargarelOSDSYS("mc0:/BAEXEC-SYSTEM/osd120.elf");
		if (file_exists("mc0:/BAEXEC-SYSTEM/osd130.elf")) CargarelOSDSYS("mc0:/BAEXEC-SYSTEM/osd130.elf");
		if (file_exists("mc0:/BAEXEC-SYSTEM/osd140.elf")) CargarelOSDSYS("mc0:/BAEXEC-SYSTEM/osd140.elf");
		if (file_exists("mc0:/BAEXEC-SYSTEM/osd150.elf")) CargarelOSDSYS("mc0:/BAEXEC-SYSTEM/osd150.elf");
		if (file_exists("mc0:/BAEXEC-SYSTEM/osd160.elf")) CargarelOSDSYS("mc0:/BAEXEC-SYSTEM/osd160.elf");
		if (file_exists("mc0:/BAEXEC-SYSTEM/osd170.elf")) CargarelOSDSYS("mc0:/BAEXEC-SYSTEM/osd170.elf");
		if (file_exists("mc0:/BAEXEC-SYSTEM/osd180.elf")) CargarelOSDSYS("mc0:/BAEXEC-SYSTEM/osd180.elf");
		if (file_exists("mc0:/BAEXEC-SYSTEM/osd190.elf")) CargarelOSDSYS("mc0:/BAEXEC-SYSTEM/osd190.elf");
		if (file_exists("mc0:/BAEXEC-SYSTEM/osd200.elf")) CargarelOSDSYS("mc0:/BAEXEC-SYSTEM/osd200.elf");
		if (file_exists("mc0:/BAEXEC-SYSTEM/osd210.elf")) CargarelOSDSYS("mc0:/BAEXEC-SYSTEM/osd210.elf");
		if (file_exists("mc0:/BAEXEC-SYSTEM/osd220.elf")) CargarelOSDSYS("mc0:/BAEXEC-SYSTEM/osd220.elf");
		if (file_exists("mc0:/BAEXEC-SYSTEM/osd230.elf")) CargarelOSDSYS("mc0:/BAEXEC-SYSTEM/osd230.elf");
		if (file_exists("mc0:/BAEXEC-SYSTEM/osd240.elf")) CargarelOSDSYS("mc0:/BAEXEC-SYSTEM/osd240.elf");
		if (file_exists("mc0:/BAEXEC-SYSTEM/osd250.elf")) CargarelOSDSYS("mc0:/BAEXEC-SYSTEM/osd250.elf");
		if (file_exists("mc0:/BAEXEC-SYSTEM/osd260.elf")) CargarelOSDSYS("mc0:/BAEXEC-SYSTEM/osd260.elf");
		if (file_exists("mc0:/BAEXEC-SYSTEM/osd270.elf")) CargarelOSDSYS("mc0:/BAEXEC-SYSTEM/osd270.elf");
		//
		if (file_exists("mc0:/BIEXEC-SYSTEM/osdmain.elf"))CargarelOSDSYS("mc0:/BIEXEC-SYSTEM/osdmain.elf");
		if (file_exists("mc0:/BIEXEC-SYSTEM/osd110.elf")) CargarelOSDSYS("mc0:/BIEXEC-SYSTEM/osd110.elf");
		if (file_exists("mc0:/BIEXEC-SYSTEM/osd120.elf")) CargarelOSDSYS("mc0:/BIEXEC-SYSTEM/osd120.elf");
		if (file_exists("mc0:/BIEXEC-SYSTEM/osd130.elf")) CargarelOSDSYS("mc0:/BIEXEC-SYSTEM/osd130.elf");
		if (file_exists("mc0:/BIEXEC-SYSTEM/osd140.elf")) CargarelOSDSYS("mc0:/BIEXEC-SYSTEM/osd140.elf");
		if (file_exists("mc0:/BIEXEC-SYSTEM/osd150.elf")) CargarelOSDSYS("mc0:/BIEXEC-SYSTEM/osd150.elf");
		if (file_exists("mc0:/BIEXEC-SYSTEM/osd160.elf")) CargarelOSDSYS("mc0:/BIEXEC-SYSTEM/osd160.elf");
		if (file_exists("mc0:/BIEXEC-SYSTEM/osd170.elf")) CargarelOSDSYS("mc0:/BIEXEC-SYSTEM/osd170.elf");
		if (file_exists("mc0:/BIEXEC-SYSTEM/osd180.elf")) CargarelOSDSYS("mc0:/BIEXEC-SYSTEM/osd180.elf");
		if (file_exists("mc0:/BIEXEC-SYSTEM/osd190.elf")) CargarelOSDSYS("mc0:/BIEXEC-SYSTEM/osd190.elf");
		if (file_exists("mc0:/BIEXEC-SYSTEM/osd200.elf")) CargarelOSDSYS("mc0:/BIEXEC-SYSTEM/osd200.elf");
		if (file_exists("mc0:/BIEXEC-SYSTEM/osd210.elf")) CargarelOSDSYS("mc0:/BIEXEC-SYSTEM/osd210.elf");
		if (file_exists("mc0:/BIEXEC-SYSTEM/osd220.elf")) CargarelOSDSYS("mc0:/BIEXEC-SYSTEM/osd220.elf");
		if (file_exists("mc0:/BIEXEC-SYSTEM/osd230.elf")) CargarelOSDSYS("mc0:/BIEXEC-SYSTEM/osd230.elf");
		if (file_exists("mc0:/BIEXEC-SYSTEM/osd240.elf")) CargarelOSDSYS("mc0:/BIEXEC-SYSTEM/osd240.elf");
		if (file_exists("mc0:/BIEXEC-SYSTEM/osd250.elf")) CargarelOSDSYS("mc0:/BIEXEC-SYSTEM/osd250.elf");
		if (file_exists("mc0:/BIEXEC-SYSTEM/osd260.elf")) CargarelOSDSYS("mc0:/BIEXEC-SYSTEM/osd260.elf");
		if (file_exists("mc0:/BIEXEC-SYSTEM/osd270.elf")) CargarelOSDSYS("mc0:/BIEXEC-SYSTEM/osd270.elf");
		//CargarelOSDSYS("mc:/B?EXEC-SYSTEM/osdmain.elf");
		if (file_exists("mc0:/BOOT/BOOT2.ELF")) LoadElf("mc0:/BOOT/BOOT2.ELF", "mc0:/BOOT/");
		if (file_exists("mc0:/FORTUNA/BOOT2.ELF")) LoadElf("mc0:/FORTUNA/BOOT2.ELF", "mc0:/FORTUNA/");
		if (file_exists("mc0:/APPS/BOOT.ELF")) LoadElf("mc0:/APPS/BOOT.ELF", "mc0:/APPS/");
		if (file_exists("mc0:/APPS/ULE.ELF")) LoadElf("mc0:/APPS/ULE.ELF", "mc0:/APPS/");
		if (file_exists("mc0:/BOOT/ULE.ELF")) LoadElf("mc0:/BOOT/ULE.ELF", "mc0:/BOOT/");
		if (file_exists("mc0:/APPS/WLE.ELF")) LoadElf("mc0:/APPS/WLE.ELF", "mc0:/APPS/");
		if (file_exists("mc0:/BOOT/WLE.ELF")) LoadElf("mc0:/BOOT/WLE.ELF", "mc0:/BOOT/");
		if (file_exists("mc1:/BOOT/BOOT.ELF")) LoadElf("mc1:/BOOT/BOOT.ELF", "mc1:/BOOT/");
		if (file_exists("mc1:/FORTUNA/BOOT2.ELF")) LoadElf("mc1:/FORTUNA/BOOT2.ELF", "mc1:/FORTUNA/");
		if (file_exists("mc1:/APPS/BOOT.ELF")) LoadElf("mc1:/APPS/BOOT.ELF", "mc1:/APPS/");
		if (file_exists("mc1:/APPS/ULE.ELF")) LoadElf("mc1:/APPS/ULE.ELF", "mc1:/APPS/");
		if (file_exists("mc1:/BOOT/ULE.ELF")) LoadElf("mc1:/BOOT/ULE.ELF", "mc1:/BOOT/");
		if (file_exists("mc1:/APPS/WLE.ELF")) LoadElf("mc1:/APPS/WLE.ELF", "mc1:/APPS/");
		if (file_exists("mc1:/BOOT/WLE.ELF")) LoadElf("mc1:/BOOT/WLE.ELF", "mc1:/BOOT/");
		if (file_exists("mc1:/FORTUNA/BOOT.ELF")) LoadElf("mc1:/FORTUNA/BOOT.ELF", "mc1:/FORTUNA/");
	}
	return 0; //Nadie deberá llegar a acá
}
