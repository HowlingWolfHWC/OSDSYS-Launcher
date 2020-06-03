int cdInitAdd(void);
int sceCdReadRegionParams(u8 *data, u32 *stat);
int sceCdReadPS1BootParam(char *param, u32 *stat);
int sceCdBootCertify(const u8* data);
int sceCdRM(char *ModelName, u32 *stat);
int sceCdRcBypassCtl(int bypass, u32 *stat);	//TODO: Not implemented.
