#ifndef _BNX2I_DEBUGFS_H_
#define _BNX2I_DEBUGFS_H_
#include <linux/debugfs.h>
#include <linux/err.h>
#include "bnx2i.h"


void bnx2i_dbg_init(char *drv_name);
void bnx2i_dbg_exit(void);
void bnx2i_login_stats_init(struct Scsi_Host *shost);
void bnx2i_login_stats_exit(void);
#endif /* _BNX2I_DEBUGFS_H_ */
