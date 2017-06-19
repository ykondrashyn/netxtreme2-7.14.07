#include "bnx2i_debugfs.h"


static struct dentry *bnx2i_dbg_root = NULL;
static struct dentry *bnx2i_login_stats_root = NULL;

#define BNX2I_LOGIN_STATS_ATTR_U32(_name, _mode, _parent) \
	attr = debugfs_create_u32(#_name, _mode, _parent, &hba->login_stats._name); \
	if (!attr) {	\
		pr_err("bnx2i: failed to create debugfs attr " #_name "\n");	\
		debugfs_remove_recursive(hba->login_stats_dir);	\
		return;	\
	}	

/**
 * bnx2i_create_login_stats_attrs - create the login stats debugfs attrs
 **/ 
static void bnx2i_create_login_stats_attrs(struct bnx2i_hba *hba)
{
	struct dentry *attr;

	BNX2I_LOGIN_STATS_ATTR_U32(login_successes, 0400,
				   hba->login_stats_dir);
	BNX2I_LOGIN_STATS_ATTR_U32(login_failures, 0400,
				   hba->login_stats_dir);
	BNX2I_LOGIN_STATS_ATTR_U32(login_negotiation_failures, 0400,
				   hba->login_stats_dir);
	BNX2I_LOGIN_STATS_ATTR_U32(login_authentication_failures, 0400,
				   hba->login_stats_dir);
	BNX2I_LOGIN_STATS_ATTR_U32(login_authorization_failures, 0400,
				   hba->login_stats_dir);
	BNX2I_LOGIN_STATS_ATTR_U32(login_redirect_responses, 0400,
				   hba->login_stats_dir);
	BNX2I_LOGIN_STATS_ATTR_U32(logout_normals, 0400,
				   hba->login_stats_dir);
	BNX2I_LOGIN_STATS_ATTR_U32(logout_others, 0400,
				   hba->login_stats_dir);
	BNX2I_LOGIN_STATS_ATTR_U32(connection_timeouts, 0400,
				   hba->login_stats_dir);
	BNX2I_LOGIN_STATS_ATTR_U32(session_failures, 0400,
				   hba->login_stats_dir);
	BNX2I_LOGIN_STATS_ATTR_U32(digest_errors, 0400,
				   hba->login_stats_dir);
	BNX2I_LOGIN_STATS_ATTR_U32(format_errors, 0400,
				   hba->login_stats_dir);
}

/**
 * bnx2i_login_stats_init - start up debugfs for bnx2i hosts iscsi stats
 **/
void bnx2i_login_stats_init(struct Scsi_Host *shost)
{
	struct bnx2i_hba *hba = iscsi_host_priv(shost);
	char host_dir[32];

	if (!bnx2i_dbg_root) {
		pr_err("bnx2i: debugfs root entry not present!\n");
		return;
	}

	/* create iscsi stats root for bnx2i hosts in debugfs. */
	if (!bnx2i_login_stats_root)
		bnx2i_login_stats_root = debugfs_create_dir("iscsi_stats",
							    bnx2i_dbg_root);
	if (!bnx2i_login_stats_root)
		pr_err("bnx2i: iscsi stats debugfs init failed!\n");

	sprintf(host_dir, "host%u", shost->host_no);

	hba->login_stats_dir = debugfs_create_dir(host_dir,
						  bnx2i_login_stats_root);
	if (!hba->login_stats_dir) {
		pr_err("bnx2i: iscsi stats debugfs init failed for host %u\n",
		       shost->host_no);
		return;
	}

	bnx2i_create_login_stats_attrs(hba);
}

/**
 * bnx2i_login_stats_exit - start up debugfs for bnx2i hosts iscsi stats
 **/
void bnx2i_login_stats_exit(void)
{
	pr_info("bnx2i: remove iscsi stats debugfs node\n");
	debugfs_remove_recursive(bnx2i_login_stats_root);
	bnx2i_login_stats_root = NULL;
}

/**
 * bnx2i_dbg_init - start up debugfs for the driver
 **/
void bnx2i_dbg_init(char *drv_name)
{
	/* create bnx2i dir in root of debugfs. NULL means debugfs root */
	bnx2i_dbg_root = debugfs_create_dir(drv_name, NULL);
	if (!bnx2i_dbg_root) {
		pr_err("bnx2i: debugfs init failed!\n");
		return;
	}

	pr_info("bnx2i: created debugfs root node!\n");
}

/**
 * bnx2i_dbg_exit - remove debugfs entries for the driver
 **/
void bnx2i_dbg_exit(void)
{
	pr_info("bnx2i: remove debugfs root entry\n");
	debugfs_remove_recursive(bnx2i_dbg_root);
	bnx2i_dbg_root = NULL;
}
