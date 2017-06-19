/* bnx2x_compat.h: QLogic Everest network driver.
 *
 * Copyright 2007-2013 Broadcom Corporation
 * Copyright 2014-2015 QLogic Corporation
 * All rights reserved
 *
 * Unless you and QLogic execute a separate written software license
 * agreement governing use of this software, this software is licensed to you
 * under the terms of the GNU General Public License version 2, available
 * at http://www.gnu.org/licenses/old-licenses/gpl-2.0.html (the "GPL").
 *
 * Notwithstanding the above, under no circumstances may you combine this
 * software in any way with any other QLogic software provided under a
 * license other than the GPL, without QLogic's express prior written
 * consent.
 *
 */
#ifndef __BNX2X_COMPAT_H__
#define __BNX2X_COMPAT_H__

#ifndef __VMKLNX__
#define VMWARE_ESX_DDK_VERSION		0
#define bnx2x_esx_remove(bp)
#define bnx2x_esx_trigger_grcdump(bp, cxt)
#define bnx2x_esx_collect_grcdump(bp)
#define bnx2x_esx_stats_count(bp) 0
#define bnx2x_esx_get_strings(buf)
#define bnx2x_esx_get_ethtool_stats(bp, buf)
#define bnx2x_esx_update_stats(bp, skb, xmit_type, bytes)
#define ESX_CXT_PARITY_TRIGGER 1
#define ESX_CXT_TXTO_TRIGGER 2
#define ESX_CXT_STSTO_TRIGGER 3
#elif (VMWARE_ESX_DDK_VERSION >= 50000)
#define __COMPAT_LAYER_2_6_18_PLUS__	1
#define __USE_COMPAT_LAYER_2_6_18_PLUS__ 1
#endif

#include <linux/version.h>
#include <linux/netdevice.h>
#include <linux/delay.h>
#include <linux/pci.h>

#ifndef KERNEL_VERSION
#define KERNEL_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))
#endif

#define XENSERVER_VERSION(a, b, c)	(((a) << 16) + ((b) << 8) + (c))
#ifndef XENSERVER_DISTRO
#define XENSERVER_DISTRO		0
#endif

/* LINUX_VERSION macros */
#define LINUX_PRE_VERSION(a, b, c) \
	(LINUX_VERSION_CODE < KERNEL_VERSION((a), (b), (c)))
#define LINUX_POST_VERSION(a, b, c) \
	(LINUX_VERSION_CODE > KERNEL_VERSION((a), (b), (c)))
#define LINUX_STARTING_AT_VERSION(a, b, c) \
	(LINUX_VERSION_CODE >= KERNEL_VERSION((a), (b), (c)))

/* RHEL version macros */
#define NOT_RHEL_OR_PRE_VERSION(a, b) \
	(!defined(RHEL_RELEASE_CODE) || \
	 RHEL_RELEASE_CODE < RHEL_RELEASE_VERSION((a), (b)))
#define RHEL_PRE_VERSION(a, b) \
	(defined(RHEL_RELEASE_CODE) && \
	 RHEL_RELEASE_CODE < RHEL_RELEASE_VERSION((a), (b)))
#define RHEL_STARTING_AT_VERSION(a, b) \
	(defined(RHEL_RELEASE_CODE) && \
	 RHEL_RELEASE_CODE >= RHEL_RELEASE_VERSION((a), (b)))
#define RHEL_IS_VERSION(a, b) \
	(defined(RHEL_RELEASE_CODE) && \
	 RHEL_RELEASE_CODE ==  RHEL_RELEASE_VERSION((a), (b)))

/* SLES version macros */
#define NOT_SLES_OR_PRE_VERSION(a) \
	(!defined(SLES_DISTRO) || (SLES_DISTRO < (a)))
#define SLES_PRE_VERSION(a) \
	(defined(SLES_DISTRO) && (SLES_DISTRO < (a)))
#define SLES_STARTING_AT_VERSION(a) \
	(defined(SLES_DISTRO) && (SLES_DISTRO >= (a)))
#define SLES_IS_VERSION(a) \
	(defined(SLES_DISTRO) && (SLES_DISTRO == (a)))
#define SLES11		0x1100
#define SLES11_SP1	0x1101
#define SLES11_SP2	0x1102
#define SLES11_SP3	0x1103
#define SLES12_SP1	0x1201
#if defined(SLES_DISTRO) && (SLES_DISTRO == SLES11_SP1) && defined(MODULE_ALIAS_NETDEV)
/* Special SLES11.1 updated kernel 2.6.32.XX */
#define SLES11_SP1_UP1
#endif

/* VMWare version macros */
#define ESX_STARTING_AT(a) \
	(defined(__VMKLNX__) && VMWARE_ESX_DDK_VERSION >= (a))
#define ESX_PRE(a) \
	(defined(__VMKLNX__) && VMWARE_ESX_DDK_VERSION < (a))

#if (LINUX_PRE_VERSION(2, 6, 29))
#include <linux/pci.h> /* for vpd */
#endif
#if (LINUX_STARTING_AT_VERSION(2, 6, 19) && LINUX_PRE_VERSION(3, 12, 0))
#include <linux/pci_hotplug.h> /* for pci_bus_speed & width */
#endif
#if (LINUX_STARTING_AT_VERSION(3, 2, 0) && LINUX_PRE_VERSION(3, 10, 0))
#include <linux/export.h> /* to export symbols */
#endif

#include <linux/in.h>
#include <linux/in6.h>
#include <linux/if_vlan.h>
#include <linux/ethtool.h>

#ifndef RHEL_RELEASE_VERSION
#define RHEL_RELEASE_VERSION(a, b) 0
#endif

#if (LINUX_PRE_VERSION(2, 6, 37)) && (!defined(RHEL_RELEASE_CODE) || (RHEL_RELEASE_CODE < RHEL_RELEASE_VERSION(6,8)))
#define OLD_VLAN			1
#endif

#if defined(OLD_VLAN) && (defined(CONFIG_VLAN_8021Q) || defined(CONFIG_VLAN_8021Q_MODULE))
#define BCM_VLAN			1
#endif

#if (LINUX_POST_VERSION(2,6,38))
#define BCM_MULTI_COS
#endif

#if (LINUX_STARTING_AT_VERSION(3,10,0))
#define VLAN_8021AD_ADDED
#endif

#if (LINUX_STARTING_AT_VERSION(2,6,23)) && \
    !defined(NETIF_F_MULTI_QUEUE) || \
    ESX_STARTING_AT(40000)
#define BNX2X_MULTI_QUEUE
#endif

#if (LINUX_STARTING_AT_VERSION(2, 6, 24)) || defined(__VMKLNX__)
#define BNX2X_NEW_NAPI
#endif

#if !defined(BNX2X_NEW_NAPI) && defined(NAPI_GRO_CB)
#define USE_NAPI_GRO
#endif

#if defined(BNX2X_MULTI_QUEUE) && !defined(__VMKLNX__)
#define BNX2X_SAFC
#endif


#if defined(__VMKLNX__)
#if (VMWARE_ESX_DDK_VERSION >= 40000)
#define BNX2X_VMWARE_BMAPILNX
#else
#define __NO_TPA__		1
#endif
#if (VMWARE_ESX_DDK_VERSION == 41000)
typedef int bool;
#define false 0
#define true  1
#endif

#undef get_page
#undef put_page

#define get_page(PAGE)
#define put_page(PAGE)
#endif

#if (VMWARE_ESX_DDK_VERSION == 50000)
#define VMKNETDDI_QUEUEOPS_QUEUE_FEAT_RSS	4
#endif

#if (LINUX_PRE_VERSION(2, 6, 20))
#define __wsum u32
#define __sum16 u16
#endif

#if defined(__VMKLNX__) /* ! BNX2X_UPSTREAM */
/*
 *  On ESX the wmb() instruction is defined to only a compiler barrier
 *  The macro wmb() need to be overrode to properly synchronize memory
 */
#undef wmb
#define wmb()   asm volatile("sfence" ::: "memory")
#endif

#if (LINUX_PRE_VERSION(2,6,30))
#define skb_record_rx_queue(skb, index)
#ifdef BNX2X_MULTI_QUEUE
static inline bool skb_rx_queue_recorded(const struct sk_buff *skb)
{
	return (skb->queue_mapping != 0);
}

static inline u16 skb_get_rx_queue(const struct sk_buff *skb)
{
	return skb->queue_mapping - 1;
}
#if !defined(__VMKLNX__)
#include <linux/jhash.h>
#else
/**
 *  Taken from linux/jhash.h
 */

#define __jhash_mix(a, b, c) \
{ \
  a -= b; a -= c; a ^= (c>>13); \
  b -= c; b -= a; b ^= (a<<8); \
  c -= a; c -= b; c ^= (b>>13); \
  a -= b; a -= c; a ^= (c>>12);  \
  b -= c; b -= a; b ^= (a<<16); \
  c -= a; c -= b; c ^= (b>>5); \
  a -= b; a -= c; a ^= (c>>3);  \
  b -= c; b -= a; b ^= (a<<10); \
  c -= a; c -= b; c ^= (b>>15); \
}

/* The golden ration: an arbitrary value */
#define JHASH_GOLDEN_RATIO      0x9e3779b9

/* A special ultra-optimized versions that knows they are hashing exactly
 * 3, 2 or 1 word(s).
 *
 * NOTE: In partilar the "c += length; __jhash_mix(a,b,c);" normally
 *       done at the end is not done here.
 */
static inline u32 jhash_3words(u32 a, u32 b, u32 c, u32 initval)
{
	a += JHASH_GOLDEN_RATIO;
	b += JHASH_GOLDEN_RATIO;
	c += initval;

	__jhash_mix(a, b, c);

	return c;
}

static inline u32 jhash_1word(u32 a, u32 initval)
{
	return jhash_3words(a, 0, 0, initval);
}
#endif
#endif
#endif
#if defined(BNX2X_MULTI_QUEUE) && \
	NOT_RHEL_OR_PRE_VERSION(6, 1) && \
	LINUX_PRE_VERSION(2, 6, 38)

#include <net/sock.h>
#if !defined(__VMKLNX__)
#include <linux/jhash.h>
#endif
#include <linux/random.h>
static u32 bnx2x_skb_tx_hashrnd;
static inline u16 __skb_tx_hash(const struct net_device *dev,
				const struct sk_buff *skb,
				unsigned int num_tx_queues)
{
	u32 hash;
	u16 qcount = num_tx_queues;

	if (skb_rx_queue_recorded(skb)) {
		hash = skb_get_rx_queue(skb);
		while (unlikely(hash >= num_tx_queues))
			hash -= num_tx_queues;
		return hash;
	}

#if !defined(__VMKLNX__)
	if (skb->sk && skb->sk->sk_hash)
		hash = skb->sk->sk_hash;
	else
#endif
		hash = skb->protocol;

	hash = jhash_1word(hash, bnx2x_skb_tx_hashrnd);

	return (u16) (((u64) hash * qcount) >> 32);
}
#endif

#if (LINUX_PRE_VERSION(2, 6, 24)) && (VMWARE_ESX_DDK_VERSION < 40000) && !defined(NETIF_F_GRO)
#define napi_complete(napi)		netif_rx_complete(dev)
#endif
#if (LINUX_PRE_VERSION(2, 6, 24)) && (VMWARE_ESX_DDK_VERSION < 40000)
#define napi_schedule(dev)		netif_rx_schedule(dev)
#endif

#if (!defined(BNX2X_NEW_NAPI)) && defined(NETIF_F_GRO)
#define napi_complete(napi)		do {				  \
						napi_gro_flush(&fp->napi);\
						netif_rx_complete(dev);	  \
					} while(0)
#endif

#ifndef NETIF_F_GRO
#define NO_GRO_SUPPORT
#define napi_gro_receive(napi, skb) netif_receive_skb(skb)
#define vlan_gro_receive(napi, vlgrp, vlan, skb) \
				vlan_hwaccel_receive_skb(skb, vlgrp, vlan)
#endif

#ifndef BNX2X_MULTI_QUEUE
#define netif_tx_wake_all_queues	netif_wake_queue
#define netif_tx_start_all_queues	netif_start_queue
#endif

#if (LINUX_PRE_VERSION(2, 6, 22))
#define skb_copy_from_linear_data_offset(skb, pad, new_skb_data, len) \
				memcpy(new_skb_data, skb->data + pad, len)

/* skb_buff accessors */
#define ip_hdr(skb)			(skb)->nh.iph
#define ipv6_hdr(skb)			(skb)->nh.ipv6h
#define ip_hdrlen(skb)			(ip_hdr(skb)->ihl * 4)
#define tcp_hdr(skb)			(skb)->h.th
#define tcp_hdrlen(skb)			(tcp_hdr(skb)->doff * 4)
#define udp_hdr(skb)			(skb)->h.uh
#define skb_mac_header(skb)		((skb)->mac.raw)
#define skb_network_header(skb)		((skb)->nh.raw)
#define skb_transport_header(skb)	((skb)->h.raw)
#if (!defined(__VMKLNX__) && NOT_RHEL_OR_PRE_VERSION(5, 0))
static inline int skb_transport_offset(const struct sk_buff *skb)
{
	return skb_transport_header(skb) - skb->data;
}
#endif
#endif


#ifndef CHECKSUM_PARTIAL
#define CHECKSUM_PARTIAL		CHECKSUM_HW
#endif


#if (LINUX_PRE_VERSION(2, 6, 0))
#define might_sleep()

#define num_online_cpus()		1

#define dev_info(dev, format, args...) \
				printk(KERN_INFO "bnx2x: " format, ##args)

#define dev_err(dev, format, args...) \
				printk(KERN_ERR "bnx2x: " format, ##args)

static inline int dma_mapping_error(dma_addr_t mapping)
{
	return 0;
}

#define synchronize_irq(X)		synchronize_irq()
#define flush_scheduled_work()
#endif



#ifndef SET_MODULE_OWNER
#define SET_MODULE_OWNER(dev)
#endif


#if (LINUX_PRE_VERSION(2, 6, 4))
#define MODULE_VERSION(version)
#endif


#if (LINUX_PRE_VERSION(2, 6, 5))
static inline void pci_dma_sync_single_for_device(struct pci_dev *dev,
						  dma_addr_t map, size_t size,
						  int dir)
{
}
#endif


#if (LINUX_PRE_VERSION(2, 5, 71))
#define pci_set_consistent_dma_mask(X, Y)	(0)
#endif


#if (LINUX_PRE_VERSION(2, 6, 7))
#define msleep(x) \
	do { \
		current->state = TASK_UNINTERRUPTIBLE; \
		schedule_timeout((HZ * (x)) / 1000); \
	} while (0)

#ifndef ADVERTISE_1000XPAUSE
static inline struct mii_ioctl_data *if_mii(struct ifreq *rq)
{
	return (struct mii_ioctl_data *)&rq->ifr_ifru;
}
#endif

#define pci_enable_msix(X, Y, Z)	(-1)
#endif


#if (LINUX_PRE_VERSION(2, 6, 9))
#define msleep_interruptible(x) \
	do{ \
		current->state = TASK_INTERRUPTIBLE; \
		schedule_timeout((HZ * (x)) / 1000); \
	} while (0)

#endif


#if (LINUX_PRE_VERSION(2, 6, 11))
#define pm_message_t			u32
#define pci_power_t			u32
#define PCI_D0				0
#define PCI_D3hot			3
#define pci_choose_state(pdev, state)	state
#endif


#if (LINUX_PRE_VERSION(2, 6, 14))
#define touch_softlockup_watchdog()
#endif


#if (LINUX_PRE_VERSION(2, 6, 18))
static inline struct sk_buff *netdev_alloc_skb(struct net_device *dev,
					       unsigned int length)
{
	struct sk_buff *skb = dev_alloc_skb(length);

	if (skb)
		skb->dev = dev;
	return skb;
}
#endif


#if (LINUX_PRE_VERSION(2, 6, 20))
#define PCI_VDEVICE(vendor, device)             \
	PCI_VENDOR_ID_##vendor, (device),       \
	PCI_ANY_ID, PCI_ANY_ID, 0, 0
#endif

#if (LINUX_PRE_VERSION(2, 6, 21))
#define vlan_group_set_device(vg, vlan_id, dev)	vg->vlan_devices[vlan_id] = dev
#endif


#ifndef IRQ_RETVAL
typedef void				irqreturn_t;
#define IRQ_HANDLED
#define IRQ_NONE
#endif


#ifndef IRQF_SHARED
#define IRQF_SHARED			SA_SHIRQ
#endif


#ifndef NETIF_F_GSO
static inline void netif_tx_lock(struct net_device *dev)
{
	spin_lock(&dev->xmit_lock);
	dev->xmit_lock_owner = smp_processor_id();
}

static inline void netif_tx_unlock(struct net_device *dev)
{
	dev->xmit_lock_owner = -1;
	spin_unlock(&dev->xmit_lock);
}

static inline void netif_tx_lock_bh(struct net_device *dev)
{
	spin_lock_bh(&dev->xmit_lock);
	dev->xmit_lock_owner = smp_processor_id();
}

static inline void netif_tx_unlock_bh(struct net_device *dev)
{
	dev->xmit_lock_owner = -1;
	spin_unlock_bh(&dev->xmit_lock);
}
#endif

#ifndef list_first_entry
/**
 * list_first_entry - get the first element from a list
 * @ptr:	the list head to take the element from.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the list_struct within the struct.
 *
 * Note, that list is expected to be not empty.
 */
#define list_first_entry(ptr, type, member) \
	list_entry((ptr)->next, type, member)
#endif


#ifndef skb_shinfo
#define skb_shinfo(SKB)	((struct skb_shared_info *)(skb_end_pointer(SKB)))
#endif


#ifdef NETIF_F_TSO
#ifndef NETIF_F_GSO

static inline int skb_is_gso(const struct sk_buff *skb)
{
	return skb_shinfo(skb)->tso_size;
}

#define gso_size			tso_size

#endif /* NETIF_F_GSO */

#ifndef NETIF_F_GSO_SOFTWARE
#define NETIF_F_GSO_SOFTWARE		(NETIF_F_TSO)
#endif

#ifndef NETIF_F_TSO6
static inline int skb_is_gso_v6(const struct sk_buff *skb)
{
	return 0;
}
#endif

#endif /* NETIF_F_TSO */

#ifndef NETIF_F_TSO_ECN
#define NETIF_F_TSO_ECN			0
#endif

#ifndef NEXTHDR_IPV6
#define NEXTHDR_IPV6            41      /* IPv6 in IPv6 */
#endif /* NEXTHDR_IPV6 */

#if !defined(mmiowb)
#define mmiowb()
#endif

#if !defined(__iomem)
#define __iomem
#endif

#ifndef noinline
#define noinline
#endif

#if !defined(INIT_WORK)
#define INIT_WORK INIT_TQUEUE
#define schedule_work			schedule_task
#define work_struct			tq_struct
#endif

#if !defined(HAVE_NETDEV_PRIV) && (LINUX_PRE_VERSION(3, 0, 0)) && (LINUX_VERSION_CODE != 0x020603) && (LINUX_VERSION_CODE != 0x020604) && (LINUX_VERSION_CODE != KERNEL_VERSION(2, 6, 5))
#define netdev_priv(dev)		(dev)->priv
#endif

/* Missing defines */
#ifndef SPEED_2500
#define SPEED_2500			2500
#endif

#ifndef SUPPORTED_Pause
#define SUPPORTED_Pause			(1 << 13)
#endif
#ifndef SUPPORTED_Asym_Pause
#define SUPPORTED_Asym_Pause		(1 << 14)
#endif

#ifndef ADVERTISED_Pause
#define ADVERTISED_Pause		(1 << 13)
#endif

#ifndef ADVERTISED_Asym_Pause
#define ADVERTISED_Asym_Pause		(1 << 14)
#endif

#ifndef ADVERTISED_1000baseKX_Full
#define ADVERTISED_1000baseKX_Full	(1 << 17)
#endif

#ifndef ADVERTISED_10000baseKX4_Full
#define ADVERTISED_10000baseKX4_Full    (1 << 18)
#endif

#ifndef ADVERTISED_10000baseKR_Full
#define ADVERTISED_10000baseKR_Full     (1 << 19)
#endif

#ifndef NETDEV_TX_OK
#define NETDEV_TX_OK			0 /* driver took care of packet */
#endif

#ifndef DMA_BIT_MASK
#define DMA_BIT_MASK(n)		(((n) == 64) ? ~0ULL : ((1ULL<<(n)) - 1))
#endif

#ifndef PCI_CAP_ID_EXP
#define PCI_CAP_ID_EXP			0x10
#endif

#ifndef PCI_EXP_DEVCTL
#define PCI_EXP_DEVCTL			8	/* Device Control */
#endif

#ifndef PCI_EXP_DEVCTL_PAYLOAD
#define PCI_EXP_DEVCTL_PAYLOAD		0x00e0	/* Max_Payload_Size */
#endif

#ifndef PCI_EXP_DEVCTL_READRQ
#define PCI_EXP_DEVCTL_READRQ		0x7000	/* Max_Read_Request_Size */
#endif

#ifndef ETH_P_FCOE
#define ETH_P_FCOE			0x8906
#endif

#ifndef ETH_P_FIP
#define ETH_P_FIP			0x8914
#endif

#ifndef PORT_DA
#define PORT_DA				0x05
#endif

#ifndef PORT_NONE
#define PORT_NONE			0xef
#endif

#ifndef PORT_OTHER
#define PORT_OTHER			0xff
#endif


#if (LINUX_PRE_VERSION(2, 6, 24))

#ifndef NETIF_F_HW_CSUM
#define NETIF_F_HW_CSUM			8
#endif

static inline int bnx2x_set_tx_hw_csum(struct net_device *dev, u32 data)
{
	if (data)
		dev->features |= NETIF_F_HW_CSUM;
	else
		dev->features &= ~NETIF_F_HW_CSUM;
	return 0;
}
#endif


/* If mutex is not available, use semaphore */
#ifndef __LINUX_MUTEX_H
#define mutex				semaphore
#define mutex_lock(x)			down(x)
#define mutex_unlock(x)			up(x)
#define mutex_init(x)			sema_init(x,1)
#endif


#ifndef KERN_CONT
#define KERN_CONT			""
#endif


#if (LINUX_PRE_VERSION(2, 6, 25))
#define le16_add_cpu(var, val) *var = cpu_to_le16(le16_to_cpup(var) + val)
#define le32_add_cpu(var, val) *var = cpu_to_le32(le32_to_cpup(var) + val)
#endif

#if (LINUX_PRE_VERSION(2, 6, 32))
/* Driver transmit return codes */
#undef NETDEV_TX_OK
#undef NETDEV_TX_BUSY
#undef NETDEV_TX_LOCKED
enum netdev_tx {
	NETDEV_TX_OK = 0,	/* driver took care of packet */
	NETDEV_TX_BUSY,		/* driver tx path was busy*/
	NETDEV_TX_LOCKED = -1,	/* driver tx lock was already taken */
};
typedef enum netdev_tx netdev_tx_t;
#endif

#if (LINUX_PRE_VERSION(2, 6, 27)) || defined(BNX2X_DRIVER_DISK) || defined(__VMKLNX__)

/*
 * This is the CRC-32C table
 * Generated with:
 * width = 32 bits
 * poly = 0x1EDC6F41
 * reflect input bytes = true
 * reflect output bytes = true
 */

static u32 crc32c_table[256] = {
	0x00000000L, 0xF26B8303L, 0xE13B70F7L, 0x1350F3F4L,
	0xC79A971FL, 0x35F1141CL, 0x26A1E7E8L, 0xD4CA64EBL,
	0x8AD958CFL, 0x78B2DBCCL, 0x6BE22838L, 0x9989AB3BL,
	0x4D43CFD0L, 0xBF284CD3L, 0xAC78BF27L, 0x5E133C24L,
	0x105EC76FL, 0xE235446CL, 0xF165B798L, 0x030E349BL,
	0xD7C45070L, 0x25AFD373L, 0x36FF2087L, 0xC494A384L,
	0x9A879FA0L, 0x68EC1CA3L, 0x7BBCEF57L, 0x89D76C54L,
	0x5D1D08BFL, 0xAF768BBCL, 0xBC267848L, 0x4E4DFB4BL,
	0x20BD8EDEL, 0xD2D60DDDL, 0xC186FE29L, 0x33ED7D2AL,
	0xE72719C1L, 0x154C9AC2L, 0x061C6936L, 0xF477EA35L,
	0xAA64D611L, 0x580F5512L, 0x4B5FA6E6L, 0xB93425E5L,
	0x6DFE410EL, 0x9F95C20DL, 0x8CC531F9L, 0x7EAEB2FAL,
	0x30E349B1L, 0xC288CAB2L, 0xD1D83946L, 0x23B3BA45L,
	0xF779DEAEL, 0x05125DADL, 0x1642AE59L, 0xE4292D5AL,
	0xBA3A117EL, 0x4851927DL, 0x5B016189L, 0xA96AE28AL,
	0x7DA08661L, 0x8FCB0562L, 0x9C9BF696L, 0x6EF07595L,
	0x417B1DBCL, 0xB3109EBFL, 0xA0406D4BL, 0x522BEE48L,
	0x86E18AA3L, 0x748A09A0L, 0x67DAFA54L, 0x95B17957L,
	0xCBA24573L, 0x39C9C670L, 0x2A993584L, 0xD8F2B687L,
	0x0C38D26CL, 0xFE53516FL, 0xED03A29BL, 0x1F682198L,
	0x5125DAD3L, 0xA34E59D0L, 0xB01EAA24L, 0x42752927L,
	0x96BF4DCCL, 0x64D4CECFL, 0x77843D3BL, 0x85EFBE38L,
	0xDBFC821CL, 0x2997011FL, 0x3AC7F2EBL, 0xC8AC71E8L,
	0x1C661503L, 0xEE0D9600L, 0xFD5D65F4L, 0x0F36E6F7L,
	0x61C69362L, 0x93AD1061L, 0x80FDE395L, 0x72966096L,
	0xA65C047DL, 0x5437877EL, 0x4767748AL, 0xB50CF789L,
	0xEB1FCBADL, 0x197448AEL, 0x0A24BB5AL, 0xF84F3859L,
	0x2C855CB2L, 0xDEEEDFB1L, 0xCDBE2C45L, 0x3FD5AF46L,
	0x7198540DL, 0x83F3D70EL, 0x90A324FAL, 0x62C8A7F9L,
	0xB602C312L, 0x44694011L, 0x5739B3E5L, 0xA55230E6L,
	0xFB410CC2L, 0x092A8FC1L, 0x1A7A7C35L, 0xE811FF36L,
	0x3CDB9BDDL, 0xCEB018DEL, 0xDDE0EB2AL, 0x2F8B6829L,
	0x82F63B78L, 0x709DB87BL, 0x63CD4B8FL, 0x91A6C88CL,
	0x456CAC67L, 0xB7072F64L, 0xA457DC90L, 0x563C5F93L,
	0x082F63B7L, 0xFA44E0B4L, 0xE9141340L, 0x1B7F9043L,
	0xCFB5F4A8L, 0x3DDE77ABL, 0x2E8E845FL, 0xDCE5075CL,
	0x92A8FC17L, 0x60C37F14L, 0x73938CE0L, 0x81F80FE3L,
	0x55326B08L, 0xA759E80BL, 0xB4091BFFL, 0x466298FCL,
	0x1871A4D8L, 0xEA1A27DBL, 0xF94AD42FL, 0x0B21572CL,
	0xDFEB33C7L, 0x2D80B0C4L, 0x3ED04330L, 0xCCBBC033L,
	0xA24BB5A6L, 0x502036A5L, 0x4370C551L, 0xB11B4652L,
	0x65D122B9L, 0x97BAA1BAL, 0x84EA524EL, 0x7681D14DL,
	0x2892ED69L, 0xDAF96E6AL, 0xC9A99D9EL, 0x3BC21E9DL,
	0xEF087A76L, 0x1D63F975L, 0x0E330A81L, 0xFC588982L,
	0xB21572C9L, 0x407EF1CAL, 0x532E023EL, 0xA145813DL,
	0x758FE5D6L, 0x87E466D5L, 0x94B49521L, 0x66DF1622L,
	0x38CC2A06L, 0xCAA7A905L, 0xD9F75AF1L, 0x2B9CD9F2L,
	0xFF56BD19L, 0x0D3D3E1AL, 0x1E6DCDEEL, 0xEC064EEDL,
	0xC38D26C4L, 0x31E6A5C7L, 0x22B65633L, 0xD0DDD530L,
	0x0417B1DBL, 0xF67C32D8L, 0xE52CC12CL, 0x1747422FL,
	0x49547E0BL, 0xBB3FFD08L, 0xA86F0EFCL, 0x5A048DFFL,
	0x8ECEE914L, 0x7CA56A17L, 0x6FF599E3L, 0x9D9E1AE0L,
	0xD3D3E1ABL, 0x21B862A8L, 0x32E8915CL, 0xC083125FL,
	0x144976B4L, 0xE622F5B7L, 0xF5720643L, 0x07198540L,
	0x590AB964L, 0xAB613A67L, 0xB831C993L, 0x4A5A4A90L,
	0x9E902E7BL, 0x6CFBAD78L, 0x7FAB5E8CL, 0x8DC0DD8FL,
	0xE330A81AL, 0x115B2B19L, 0x020BD8EDL, 0xF0605BEEL,
	0x24AA3F05L, 0xD6C1BC06L, 0xC5914FF2L, 0x37FACCF1L,
	0x69E9F0D5L, 0x9B8273D6L, 0x88D28022L, 0x7AB90321L,
	0xAE7367CAL, 0x5C18E4C9L, 0x4F48173DL, 0xBD23943EL,
	0xF36E6F75L, 0x0105EC76L, 0x12551F82L, 0xE03E9C81L,
	0x34F4F86AL, 0xC69F7B69L, 0xD5CF889DL, 0x27A40B9EL,
	0x79B737BAL, 0x8BDCB4B9L, 0x988C474DL, 0x6AE7C44EL,
	0xBE2DA0A5L, 0x4C4623A6L, 0x5F16D052L, 0xAD7D5351L
};

/*
 * Steps through buffer one byte at at time, calculates reflected
 * crc using table.
 */

static inline u32 /*__attribute_pure__*/
crc32c_le(u32 seed, unsigned char const *data, size_t length)
{
	__le32 crc = __cpu_to_le32(seed);

	while (length--)
		crc = crc32c_table[(crc ^ *data++) & 0xFFL] ^ (crc >> 8);

	return __le32_to_cpu(crc);
}
#endif

/* Taken from drivers/net/mdio.c */
#if (LINUX_PRE_VERSION(2, 6, 31))
#include <linux/mii.h>

/* MDIO Manageable Devices (MMDs). */
#define MDIO_MMD_AN		7	/* Auto-Negotiation */

/* Generic MDIO registers. */
#define MDIO_AN_ADVERTISE	16	/* AN advertising (base page) */
#define MDIO_AN_LPA		19	/* AN LP abilities (base page) */

/* Device present registers. */
#define MDIO_DEVS_PRESENT(devad)	(1 << (devad))
#define MDIO_DEVS_AN			MDIO_DEVS_PRESENT(MDIO_MMD_AN)

/**
 * struct mdio_if_info - Ethernet controller MDIO interface
 * @prtad: PRTAD of the PHY (%MDIO_PRTAD_NONE if not present/unknown)
 * @mmds: Mask of MMDs expected to be present in the PHY.  This must be
 *	non-zero unless @prtad = %MDIO_PRTAD_NONE.
 * @mode_support: MDIO modes supported.  If %MDIO_SUPPORTS_C22 is set then
 *	MII register access will be passed through with @devad =
 *	%MDIO_DEVAD_NONE.  If %MDIO_EMULATE_C22 is set then access to
 *	commonly used clause 22 registers will be translated into
 *	clause 45 registers.
 * @dev: Net device structure
 * @mdio_read: Register read function; returns value or negative error code
 * @mdio_write: Register write function; returns 0 or negative error code
 */
struct mdio_if_info {
	int prtad;
	u32 __bitwise mmds;
	unsigned mode_support;

	struct net_device *dev;
	int (*mdio_read)(struct net_device *dev, int prtad, int devad,
			 u16 addr);
	int (*mdio_write)(struct net_device *dev, int prtad, int devad,
			  u16 addr, u16 val);
};

#define MDIO_PRTAD_NONE			(-1)
#define MDIO_DEVAD_NONE			(-1)
#define MDIO_EMULATE_C22		4

/* Mapping between MDIO PRTAD/DEVAD and mii_ioctl_data::phy_id */

#define MDIO_PHY_ID_C45			0x8000
#define MDIO_PHY_ID_PRTAD		0x03e0
#define MDIO_PHY_ID_DEVAD		0x001f
#define MDIO_PHY_ID_C45_MASK						\
	(MDIO_PHY_ID_C45 | MDIO_PHY_ID_PRTAD | MDIO_PHY_ID_DEVAD)

static inline int mdio_phy_id_is_c45(int phy_id)
{
	return (phy_id & MDIO_PHY_ID_C45) && !(phy_id & ~MDIO_PHY_ID_C45_MASK);
}

static inline __u16 mdio_phy_id_prtad(int phy_id)
{
	return (phy_id & MDIO_PHY_ID_PRTAD) >> 5;
}

static inline __u16 mdio_phy_id_devad(int phy_id)
{
	return phy_id & MDIO_PHY_ID_DEVAD;
}

#define MDIO_SUPPORTS_C22		1
#define MDIO_SUPPORTS_C45		2

/**
 * mdio_mii_ioctl - MII ioctl interface for MDIO (clause 22 or 45) PHYs
 * @mdio: MDIO interface
 * @mii_data: MII ioctl data structure
 * @cmd: MII ioctl command
 *
 * Returns 0 on success, negative on error.
 */
static inline int mdio_mii_ioctl(const struct mdio_if_info *mdio,
				 struct mii_ioctl_data *mii_data, int cmd)
{
	int prtad, devad;
	u16 addr = mii_data->reg_num;

	/* Validate/convert cmd to one of SIOC{G,S}MIIREG */
	switch (cmd) {
	case SIOCGMIIPHY:
		if (mdio->prtad == MDIO_PRTAD_NONE)
			return -EOPNOTSUPP;
		mii_data->phy_id = mdio->prtad;
		cmd = SIOCGMIIREG;
		break;
	case SIOCGMIIREG:
		break;
	case SIOCSMIIREG:
		if (!capable(CAP_NET_ADMIN))
			return -EPERM;
		break;
	default:
		return -EOPNOTSUPP;
	}

	/* Validate/convert phy_id */
	if ((mdio->mode_support & MDIO_SUPPORTS_C45) &&
	    mdio_phy_id_is_c45(mii_data->phy_id)) {
		prtad = mdio_phy_id_prtad(mii_data->phy_id);
		devad = mdio_phy_id_devad(mii_data->phy_id);
	} else if ((mdio->mode_support & MDIO_SUPPORTS_C22) &&
		   mii_data->phy_id < 0x20) {
		prtad = mii_data->phy_id;
		devad = MDIO_DEVAD_NONE;
		addr &= 0x1f;
	} else if ((mdio->mode_support & MDIO_EMULATE_C22) &&
		   mdio->prtad != MDIO_PRTAD_NONE &&
		   mii_data->phy_id == mdio->prtad) {
		/* Remap commonly-used MII registers. */
		prtad = mdio->prtad;
		switch (addr) {
		case MII_BMCR:
		case MII_BMSR:
		case MII_PHYSID1:
		case MII_PHYSID2:
			devad = __ffs(mdio->mmds);
			break;
		case MII_ADVERTISE:
		case MII_LPA:
			if (!(mdio->mmds & MDIO_DEVS_AN))
				return -EINVAL;
			devad = MDIO_MMD_AN;
			if (addr == MII_ADVERTISE)
				addr = MDIO_AN_ADVERTISE;
			else
				addr = MDIO_AN_LPA;
			break;
		default:
			return -EINVAL;
		}
	} else {
		return -EINVAL;
	}

	if (cmd == SIOCGMIIREG) {
		int rc = mdio->mdio_read(mdio->dev, prtad, devad, addr);
		if (rc < 0)
			return rc;
		mii_data->val_out = rc;
		return 0;
	} else {
		return mdio->mdio_write(mdio->dev, prtad, devad, addr,
					mii_data->val_in);
	}
}
#endif

#if (LINUX_PRE_VERSION(2, 6, 36) && NOT_RHEL_OR_PRE_VERSION(6, 3))
static inline void usleep_range(unsigned long min, unsigned long max)
{
	if (min < 1000)
		udelay(min);
	else
		msleep(min / 1000);
}
#endif

#if RHEL_IS_VERSION(6, 3)
/** RHEL6.3 is missing in 'arch/x86/Kconfig' the logic which sets
 *  'CONFIG_NEED_DMA_MAP_STATE'. Therefore, we supplement that logic here,
 *  possibly replacing the 'dma_unmap_*' macros.
 */
#if defined(CONFIG_X86_64) || defined(CONFIG_INTEL_IOMMU) || defined(CONFIG_DMA_API_DEBUG)
#undef DEFINE_DMA_UNMAP_ADDR
#define DEFINE_DMA_UNMAP_ADDR(ADDR_NAME)        dma_addr_t ADDR_NAME
#undef DEFINE_DMA_UNMAP_LEN
#define DEFINE_DMA_UNMAP_LEN(LEN_NAME)          __u32 LEN_NAME
#undef dma_unmap_addr
#define dma_unmap_addr(PTR, ADDR_NAME)           ((PTR)->ADDR_NAME)
#undef dma_unmap_addr_set
#define dma_unmap_addr_set(PTR, ADDR_NAME, VAL)  (((PTR)->ADDR_NAME) = (VAL))
#undef dma_unmap_len
#define dma_unmap_len(PTR, LEN_NAME)             ((PTR)->LEN_NAME)
#undef dma_unmap_len_set
#define dma_unmap_len_set(PTR, LEN_NAME, VAL)    (((PTR)->LEN_NAME) = (VAL))
#endif
#endif

#if (LINUX_PRE_VERSION(2, 6, 29))
static inline ssize_t
pci_read_vpd(struct pci_dev *dev, loff_t pos, size_t count, u8 *buf)
{
	int i, vpd_cap;

	vpd_cap = pci_find_capability(dev, PCI_CAP_ID_VPD);
	if (!vpd_cap)
		return -ENODEV;

	for (i = pos; i < count + pos; i += 4) {
		u32 tmp, j = 0;
		__le32 v;
		u16 tmp16;

		pci_write_config_word(dev, vpd_cap + PCI_VPD_ADDR, i);
		while (j++ < 100) {
			pci_read_config_word(dev, vpd_cap +
					     PCI_VPD_ADDR, &tmp16);
			if (tmp16 & 0x8000)
				break;
			usleep_range(1000, 1000);
		}
		if (!(tmp16 & 0x8000))
			break;

		pci_read_config_dword(dev, vpd_cap + PCI_VPD_DATA, &tmp);
		v = cpu_to_le32(tmp);
		memcpy(&buf[i - pos], &v, sizeof(v));
	}

	return i;
}
#endif

#ifndef ____ilog2_NaN
#define ____ilog2_NaN(x) (-1)
#endif

#ifndef ilog2
static inline
int bnx2x_ilog2(int x)
{
	int log = 0;
	while (x >>=1 )
		log++;
	return log;
}
#define ilog2(x)	bnx2x_ilog2(x)
#endif


#ifndef bool
#define bool int
#endif

#ifndef false
#define false 0
#define true 1
#endif

#ifndef DIV_ROUND_UP
#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))
#endif

#if (LINUX_PRE_VERSION(2, 6, 12)) && !defined(RHEL_RELEASE_CODE)
#define is_multicast_ether_addr(addr) (0x01 & (addr)[0])
#endif

#if (LINUX_PRE_VERSION(2, 6, 14)) && !defined(RHEL_RELEASE_CODE)
#define is_broadcast_ether_addr(addr)\
	(((addr)[0] & (addr)[1] & (addr)[2] & (addr)[3] \
	& (addr)[4] & (addr)[5]) == 0xff)
#endif

#ifndef roundup
#define roundup(x, y) ((((x) + ((y) - 1)) / (y)) * (y))
#endif

#ifndef DEFINE_PCI_DEVICE_TABLE
#define DEFINE_PCI_DEVICE_TABLE(tbl) const struct pci_device_id bnx2x_pci_tbl[]
#endif

#if (LINUX_PRE_VERSION(2, 6, 6))
#undef netdev_printk
#undef netdev_err
#undef netdev_info
#endif

#if (LINUX_PRE_VERSION(2, 6, 36))
#if defined(_DEFINE_NETDEV_NAME) || defined(__VMKLNX__)
static inline const char *netdev_name(const struct net_device *dev)
{
	if (dev->reg_state != NETREG_REGISTERED)
		return "(unregistered net_device)";
	return dev->name;
}
#endif
#if (LINUX_PRE_VERSION(2, 6, 21))
#define NET_PARENT_DEV(netdev)  ((netdev)->class_dev.dev)
#else
#define NET_PARENT_DEV(netdev)  ((netdev)->dev.parent)
#endif

#if (LINUX_PRE_VERSION(2, 6, 18))
static inline const char *dev_driver_string(struct device *dev)
{
	return dev->driver ? dev->driver->name :
		(dev->bus ? dev->bus->name : "");
}
#endif

#if !defined(__VMKLNX__)
#if (LINUX_PRE_VERSION(2, 6, 26))
#undef netdev_printk
#define netdev_printk(level, netdev, format, args...)		\
	printk("%s"						\
	       "%s %s: %s: " format, level,			\
	       dev_driver_string(NET_PARENT_DEV(netdev)),	\
	       NET_PARENT_DEV(netdev)->bus_id,			\
	       netdev_name(netdev), ##args)
#elif (LINUX_STARTING_AT_VERSION(2, 6, 26)) && (LINUX_PRE_VERSION(2, 6, 36))
#undef netdev_printk
#define netdev_printk(level, netdev, format, args...)		\
	printk("%s"						\
	       "%s %s: %s: " format, level,			\
	       dev_driver_string(NET_PARENT_DEV(netdev)),	\
	       dev_name(NET_PARENT_DEV(netdev)),		\
	       netdev_name(netdev), ##args)
#endif
#else /*(__VMKLNX__)*/
#define netdev_printk(level, netdev, format, args...)           \
	printk("%s" \
	       "%s %s: %s: " format, level,                     \
	       DRV_MODULE_NAME, pci_name(netdev->pdev),         \
	       netdev_name(netdev), ##args)
#endif/*(__VMKLNX__)*/
#endif/*(LINUX_PRE_VERSION(2, 6, 36))*/

#ifndef netdev_err
#define netdev_err(dev, format, args...)			\
	netdev_printk(KERN_ERR, dev, format, ##args)
#endif

#ifndef netdev_dbg
#define netdev_dbg(dev, format, args...)			\
	netdev_printk(KERN_DEBUG, dev, format, ##args)
#endif

#ifndef pr_cont
#define pr_cont(fmt, ...) \
	printk(KERN_CONT fmt, ##__VA_ARGS__)
#endif

#ifndef netdev_info
#define netdev_info(dev, format, args...)			\
	netdev_printk(KERN_INFO, dev, format, ##args)
#endif

#ifndef pr_fmt
#define pr_fmt(fmt) fmt
#endif

#ifndef pr_alert
#define pr_alert(fmt, ...) \
	printk(KERN_ALERT pr_fmt(fmt), ##__VA_ARGS__)
#endif

#ifndef pr_err
#define pr_err(fmt, ...) \
	printk(KERN_ERR pr_fmt(fmt), ##__VA_ARGS__)
#endif

#ifndef pr_notice
#define pr_notice(fmt, ...) \
	printk(KERN_NOTICE pr_fmt(fmt), ##__VA_ARGS__)
	#endif

#ifndef pr_info
#define pr_info(fmt, ...) \
	printk(KERN_INFO pr_fmt(fmt), ##__VA_ARGS__)
#endif

#ifndef pr_cont
#define pr_cont(fmt, ...) \
	printk(KERN_CONT fmt, ##__VA_ARGS__)
#endif

#ifndef netdev_mc_count
#define netdev_mc_count(dev) ((dev)->mc_count)
#endif

#ifndef dev_alert
#define dev_alert(dev, format, arg...)		\
	dev_printk(KERN_ALERT , dev , format , ## arg)
#endif

#ifndef netdev_for_each_mc_addr
#define netdev_for_each_mc_addr(mclist, dev) \
	for (mclist = (dev)->mc_list; mclist; mclist = mclist->next)
#endif

#if (LINUX_PRE_VERSION(2, 6, 31))
#define netdev_for_each_uc_addr(uclist, dev) \
	for (uclist = (dev)->uc_list; uclist; uclist = uclist->next)
#elif !defined(netdev_for_each_uc_addr)
#define netdev_for_each_uc_addr(uclist, dev) \
	list_for_each_entry(uclist, &((dev)->uc).list, list)
#endif

#if (LINUX_PRE_VERSION(2, 6, 31))
#define bnx2x_uc_addr(ha)      ((ha)->dmi_addr)
#else
#define bnx2x_uc_addr(ha)      ((ha)->addr)
#endif

#ifndef netdev_hw_addr_list_for_each
#define bnx2x_mc_addr(ha)      ((ha)->dmi_addr)
#else
#define bnx2x_mc_addr(ha)      ((ha)->addr)
#endif

#ifndef PCI_SRIOV_NUM_BARS
#define PCI_SRIOV_NUM_BARS	6
#endif

#ifndef PCI_IOV_RESOURCES
#define PCI_IOV_RESOURCES	7
#endif

#ifndef PCI_EXT_CAP_ID_SRIOV
#define PCI_EXT_CAP_ID_SRIOV	16
#endif

#ifndef PCI_SRIOV_CAP
#define PCI_SRIOV_CAP		0x04
#endif

#ifndef PCI_SRIOV_CTRL
#define PCI_SRIOV_CTRL		0x08
#endif

#ifndef PCI_SRIOV_INITIAL_VF
#define PCI_SRIOV_INITIAL_VF	0x0c
#endif

#ifndef PCI_SRIOV_TOTAL_VF
#define PCI_SRIOV_TOTAL_VF	0x0e
#endif

#ifndef PCI_SRIOV_FUNC_LINK
#define PCI_SRIOV_FUNC_LINK	0x12
#endif

#ifndef PCI_SRIOV_VF_OFFSET
#define PCI_SRIOV_VF_OFFSET	0x14
#endif

#ifndef PCI_SRIOV_VF_STRIDE
#define PCI_SRIOV_VF_STRIDE	0x16
#endif

#ifndef PCI_SRIOV_SUP_PGSIZE
#define PCI_SRIOV_SUP_PGSIZE	0x1c
#endif

#ifndef	PCI_EXP_DEVCTL2
#define PCI_EXP_DEVCTL2		40
#endif
#if (LINUX_PRE_VERSION(2, 6, 27))
#define netif_addr_lock_bh(dev) netif_tx_lock_bh(dev)
#define netif_addr_unlock_bh(dev) netif_tx_unlock_bh(dev)
#endif

#if (LINUX_PRE_VERSION(2, 6, 35))
#define ETH_FLAG_RXHASH	(0x1 << 28)
#endif

#if (LINUX_PRE_VERSION(2, 6, 24))
#define ETH_FLAG_LRO	(1 << 15)
#endif

#if (LINUX_PRE_VERSION(2, 6, 34))
#define ETH_FLAG_NTUPLE	(1 << 27)
#endif

#if (LINUX_PRE_VERSION(2, 6, 37))
#define ETH_FLAG_TXVLAN		(1 << 7) /* TX VLAN offload enabled */
#define ETH_FLAG_RXVLAN		(1 << 8) /* RX VLAN offload enabled */
#endif

#if (LINUX_PRE_VERSION(2, 6, 19))

/* The below code is similar to what is done random32() in
 * 2.6.19 but much simpler. ;)
 */
#if !defined(RHEL_RELEASE_CODE)
#define TAUSWORTHE(s,a,b,c,d) ((((s)&(c))<<(d)) ^ ((((s) <<(a)) ^ (s))>>(b)))
static inline u32 random32(void) {
	static u32 s1 = 4294967294UL;
	static u32 s2 = 4294967288UL;
	static u32 s3 = 4294967280UL;
	u32 cycles;

	/* This would be our seed for this step */
	cycles = get_cycles();

	s1 = TAUSWORTHE(s1 + cycles, 13, 19, 4294967294UL, 12);
	s2 = TAUSWORTHE(s2 + cycles, 2, 25, 4294967288UL, 4);
	s3 = TAUSWORTHE(s3 + cycles, 3, 11, 4294967280UL, 17);

	return (s1 ^ s2 ^ s3);
}
#elif RHEL_PRE_VERSION(5, 6)
#define TAUSWORTHE(s,a,b,c,d) ((((s)&(c))<<(d)) ^ ((((s) <<(a)) ^ (s))>>(b)))
static inline u32 random32(void) {
	static u32 s1 = 4294967294UL;
	static u32 s2 = 4294967288UL;
	static u32 s3 = 4294967280UL;
	u32 cycles;

	/* This would be our seed for this step */
	cycles = get_cycles();

	s1 = TAUSWORTHE(s1 + cycles, 13, 19, 4294967294UL, 12);
	s2 = TAUSWORTHE(s2 + cycles, 2, 25, 4294967288UL, 4);
	s3 = TAUSWORTHE(s3 + cycles, 3, 11, 4294967280UL, 17);

	return (s1 ^ s2 ^ s3);
}
#endif
#endif

#if ((!defined(RHEL_RELEASE_CODE) && (LINUX_PRE_VERSION(2, 6, 37))) || \
	(defined(RHEL_RELEASE_CODE) && \
		(((RHEL_MAJOR == 6) && (RHEL_MINOR < 1)) || \
		 ((RHEL_MAJOR == 5) && (RHEL_MINOR < 7)) || \
		  (RHEL_MAJOR < 5))))
static inline void skb_checksum_none_assert(struct sk_buff *skb)
{
	skb->ip_summed = CHECKSUM_NONE;
}
#endif

#if ((!defined(RHEL_RELEASE_CODE) && (LINUX_PRE_VERSION(2, 6, 34))) || \
      (defined(RHEL_RELEASE_CODE) && \
		(((RHEL_MAJOR == 6) && (RHEL_MINOR < 1)) || \
		 ((RHEL_MAJOR == 5) && (RHEL_MINOR < 7)) || \
		  (RHEL_MAJOR < 5))))
#define PCI_VPD_LRDT			0x80	/* Large Resource Data Type */
#define PCI_VPD_LRDT_ID(x)		(x | PCI_VPD_LRDT)

/* Large Resource Data Type Item Names */
#define PCI_VPD_LRDT_LIN_ID_STRING	0x02	/* Identifier String */
#define PCI_VPD_LRDT_LIN_RO_DATA	0x10	/* Read-Only Data */
#define PCI_VPD_LRDT_LIN_RW_DATA	0x11	/* Read-Write Data */

#ifndef PCI_VPD_LRDT_ID_STRING
#define PCI_VPD_LRDT_ID_STRING \
	PCI_VPD_LRDT_ID(PCI_VPD_LRDT_LIN_ID_STRING)
#define PCI_VPD_LRDT_RO_DATA \
	PCI_VPD_LRDT_ID(PCI_VPD_LRDT_LIN_RO_DATA)
#define PCI_VPD_LRDT_RW_DATA \
	PCI_VPD_LRDT_ID(PCI_VPD_LRDT_LIN_RW_DATA)

/* Small Resource Data Type Item Names */
#define PCI_VPD_SRDT_SIN_END		0x78	/* End */

#define PCI_VPD_SRDT_END		PCI_VPD_SRDT_SIN_END

#define PCI_VPD_RO_KEYWORD_PARTNO	"PN"
#define PCI_VPD_RO_KEYWORD_VENDOR0	"V0"
#define PCI_VPD_RO_KEYWORD_MFR_ID	"MN"

#define PCI_VPD_SRDT_SIN_MASK		0x78
#define PCI_VPD_SRDT_LEN_MASK		0x07

#define PCI_VPD_LRDT_TAG_SIZE		3
#define PCI_VPD_SRDT_TAG_SIZE		1
#define PCI_VPD_INFO_FLD_HDR_SIZE	3

static inline u16 pci_vpd_lrdt_size(u8 *lrdt)
{
	return (u16)lrdt[1] + ((u16)lrdt[2] << 8);
}

static inline u8 pci_vpd_srdt_size(u8 *srdt)
{
	return (*srdt) & PCI_VPD_SRDT_LEN_MASK;
}

static inline int __devinit pci_vpd_find_tag(char *data, unsigned int start,
				      unsigned int len, u8 tagid)
{
	int i;

	for (i = start; i < len; ) {
		u8 val = (u8)data[i];

		if (val & PCI_VPD_LRDT) {
			/* Don't return success of the tag isn't complete */
			if (i + PCI_VPD_LRDT_TAG_SIZE > len)
				break;

			if (val == tagid)
				return i;

			i += PCI_VPD_LRDT_TAG_SIZE +
			     pci_vpd_lrdt_size(&data[i]);
		} else {
			u8 tag = val & ~PCI_VPD_SRDT_LEN_MASK;

			if (tag == tagid)
				return i;

			if (tag == PCI_VPD_SRDT_SIN_END)
				break;

			i += PCI_VPD_SRDT_TAG_SIZE +
			     pci_vpd_srdt_size(&data[i]);
		}
	}

	return -1;
}

static inline u8 pci_vpd_info_field_size(u8 *info_field)
{
	return info_field[2];
}

static inline int __devinit pci_vpd_find_info_keyword(u8 *rodata,
					       unsigned int start,
					       unsigned int rosize,
					       char *kw)
{
	int i;

	for (i = start; i + PCI_VPD_INFO_FLD_HDR_SIZE <= start + rosize;) {
		if (rodata[i + 0] == kw[0] &&
		    rodata[i + 1] == kw[1])
			return i;

		i += PCI_VPD_INFO_FLD_HDR_SIZE +
		     pci_vpd_info_field_size(&rodata[i]);
	}

	return -1;
}
#else
#define DEBIAN_MERGED_PCI_CODE
#endif
#endif

#ifndef PCI_MSIX_FLAGS
#define PCI_MSIX_FLAGS		2
#endif
#ifndef PCI_MSIX_FLAGS_QSIZE
#define PCI_MSIX_FLAGS_QSIZE	0x7FF
#endif

#if (LINUX_PRE_VERSION(2, 6, 15))
#define atomic_cmpxchg(p, old, new) cmpxchg((volatile int *)(p), old, new)
#endif


#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr)	(sizeof(arr) / sizeof((arr)[0]))
#endif

#if (!defined(SLES_DISTRO) || (LINUX_PRE_VERSION(2, 6, 16))) && (LINUX_PRE_VERSION(2, 6, 18))
static inline int list_is_last(const struct list_head *list,
				const struct list_head *head)
{
	return list->next == head;
}
#endif

#if (LINUX_PRE_VERSION(2, 6, 37) && NOT_RHEL_OR_PRE_VERSION(6, 4))
static inline int netif_set_real_num_rx_queues(struct net_device *dev, int num)
{
	return 0;
}
#endif

#if !defined(RHEL_RELEASE_CODE) && (LINUX_PRE_VERSION(2, 6, 35) && defined(BNX2X_MULTI_QUEUE) && NOT_SLES_OR_PRE_VERSION(SLES11_SP2) && !defined(SLES11_SP1_UP1)) && (XENSERVER_DISTRO < XENSERVER_VERSION(6, 1, 0))
static inline void netif_set_real_num_tx_queues(struct net_device *dev,
						unsigned int txq)
{
	dev->real_num_tx_queues = txq;
}
#endif

/* vlan structure defines*/
#ifndef VLAN_PRIO_MASK
#define VLAN_PRIO_MASK		0xe000 /* Priority Code Point */
#endif
#ifndef VLAN_PRIO_SHIFT
#define VLAN_PRIO_SHIFT		13
#endif


#if defined(OLD_VLAN) && \
	(!defined(RHEL_RELEASE_CODE) || \
		(((RHEL_MAJOR == 6) && (RHEL_MINOR < 1)) || \
		 ((RHEL_MAJOR == 5) && (RHEL_MINOR < 7)) || \
		  (RHEL_MAJOR < 5)))
/**
 * vlan_get_protocol - get protocol EtherType.
 * @skb: skbuff to query
 *
 * Returns the EtherType of the packet, regardless of whether it is
 * vlan encapsulated (normal or hardware accelerated) or not.
 */
static inline __be16 vlan_get_protocol(const struct sk_buff *skb)
{
	__be16 protocol = 0;

#ifdef BCM_VLAN
	if (vlan_tx_tag_present(skb) ||
	     skb->protocol != cpu_to_be16(ETH_P_8021Q))
#else
	if (skb->protocol != cpu_to_be16(ETH_P_8021Q))
#endif
		protocol = skb->protocol;
	else {
		__be16 proto, *protop;
		protop = skb_header_pointer(skb, offsetof(struct vlan_ethhdr,
						h_vlan_encapsulated_proto),
						sizeof(proto), &proto);
		if (likely(protop))
			protocol = *protop;
	}

	return protocol;
}
#endif

#if (LINUX_PRE_VERSION(2, 6, 36))

static const u32 bnx2x_flags_dup_features =
	(ETH_FLAG_LRO | ETH_FLAG_NTUPLE | ETH_FLAG_RXHASH);


static inline int bnx2x_ethtool_op_set_flags(struct net_device *dev, u32 data,
					     u32 supported)
{
	if (data & ~supported)
		return -EINVAL;

	dev->features = ((dev->features & ~bnx2x_flags_dup_features) |
			  (data & bnx2x_flags_dup_features));
	return 0;
}
#endif

#if defined(NETIF_F_TSO6) && ((!defined(RHEL_RELEASE_CODE) && (LINUX_PRE_VERSION(2, 6, 24))) || \
			      (defined(RHEL_RELEASE_CODE) && (RHEL_RELEASE_CODE < RHEL_RELEASE_VERSION(5,5))) || \
			      defined(__VMKLNX__))
static inline int skb_is_gso_v6(const struct sk_buff *skb)
{
	return skb_shinfo(skb)->gso_type & SKB_GSO_TCPV6;
}
#endif

#if (LINUX_STARTING_AT_VERSION(2, 6, 32)) || \
	(defined(__VMKLNX__) && \
	 (((VMWARE_ESX_DDK_VERSION == 50000) && !defined(BNX2X_INBOX)) || \
	  (VMWARE_ESX_DDK_VERSION > 50000)))
#define BCM_DCB		1
#endif

#if (LINUX_PRE_VERSION(2,6,27))
static inline void ethtool_cmd_speed_set(struct ethtool_cmd *ep,
					 __u32 speed)
{
	ep->speed = (__u16)speed;
}

static inline __u32 ethtool_cmd_speed(struct ethtool_cmd *ep)
{
	return ep->speed;
}
#endif

#ifndef SPEED_UNKNOWN
#define SPEED_UNKNOWN (-1)
#endif

#ifndef DUPLEX_UNKNOWN
#define DUPLEX_UNKNOWN (0xff)
#endif

#ifndef __rcu
#define __rcu
#endif

#ifndef NETIF_F_LOOPBACK
#define NETIF_F_LOOPBACK	(1 << 31) /* Enable loopback */
#endif

#ifndef SUPPORTED_1000baseKX_Full
#define SUPPORTED_1000baseKX_Full	(1 << 17)
#endif

#ifndef SUPPORTED_10000baseKR_Full
#define SUPPORTED_10000baseKR_Full	(1 << 19)
#endif

#ifndef SUPPORTED_20000baseMLD2_Full
#define SUPPORTED_20000baseMLD2_Full	(1 << 21)
#endif

#ifndef SUPPORTED_20000baseKR2_Full
#define SUPPORTED_20000baseKR2_Full	(1 << 22)
#endif

#ifndef ADVERTISED_20000baseKR2_Full
#define ADVERTISED_20000baseKR2_Full	(1 << 22)
#endif

#ifndef MDIO_PMA_LASI_RXCTRL
#define	MDIO_PMA_LASI_RXCTRL	0x9000
#endif

#ifndef MDIO_PMA_LASI_TXCTRL
#define	MDIO_PMA_LASI_TXCTRL	0x9001
#endif

#ifndef MDIO_PMA_LASI_CTRL
#define	MDIO_PMA_LASI_CTRL	0x9002
#endif

#ifndef MDIO_PMA_LASI_RXSTAT
#define	MDIO_PMA_LASI_RXSTAT	0x9003
#endif

#ifndef MDIO_PMA_LASI_TXSTAT
#define	MDIO_PMA_LASI_TXSTAT	0x9004
#endif

#ifndef MDIO_PMA_LASI_STAT
#define	MDIO_PMA_LASI_STAT	0x9005
#endif

#ifndef rcu_dereference_protected
#define rcu_dereference_protected(p, c) (p)
#endif

#if (LINUX_PRE_VERSION(2, 6, 38) && defined(BNX2X_MULTI_QUEUE) && NOT_RHEL_OR_PRE_VERSION(6,2))
/* Older kernels do not support different amount of mqs.
 * Only txqs is used for TX structure allocation.
 */
static inline struct net_device *alloc_etherdev_mqs(int sizeof_priv,
						    unsigned int txqs,
						    unsigned int rxqs)
{
	return alloc_etherdev_mq(sizeof_priv, txqs);
}
#endif

#if (LINUX_PRE_VERSION(2, 6, 27)) && !defined(__VMKLNX__)
struct netdev_queue { };
static inline struct netdev_queue *netdev_get_tx_queue(struct net_device *dev,
						       int q)
{
	return NULL;
}
#endif

#if (NOT_RHEL_OR_PRE_VERSION(6,1) && LINUX_PRE_VERSION(2,6,39))
/* older kernels do not support the interface for multiple queues
 * for traffic classes
 */
struct netdev_queue;
static inline void netdev_reset_tc(struct net_device *dev) { }
static inline int netdev_set_tc_queue(struct net_device *dev, u8 tc,u16 count, u16 offset) {return 0; }
static inline int netdev_set_num_tc(struct net_device *dev, u8 num_tc) {return 0; }
static inline int netdev_get_num_tc(struct net_device *dev) { return 0; }
static inline int netdev_set_prio_tc_map(struct net_device *dev, u8 prio, u8 tc) {return 0; }
#endif

#if (NOT_RHEL_OR_PRE_VERSION(5,8) && LINUX_PRE_VERSION(2,6,33) && !defined(DEBIAN_MERGED_PCI_CODE))
static inline int pci_pcie_cap(struct pci_dev *dev)
{
	return pci_find_capability(dev, PCI_CAP_ID_EXP);
}
#endif

#if ((!defined(RHEL_RELEASE_CODE) && (LINUX_PRE_VERSION(2,6,33))) || \
	(defined(RHEL_RELEASE_CODE) && \
		(((RHEL_MAJOR == 6) && (RHEL_MINOR < 1)) || \
		 ((RHEL_MAJOR == 5) && (RHEL_MINOR < 8)) || \
		  (RHEL_MAJOR < 5))))
static inline bool pci_is_pcie(struct pci_dev *dev)
{
	return !!pci_pcie_cap(dev);
}
#endif

#ifndef RCU_INIT_POINTER
#define RCU_INIT_POINTER(ptr, val)  rcu_assign_pointer(ptr, val)
#endif

#if (LINUX_PRE_VERSION(3, 1, 0) && NOT_RHEL_OR_PRE_VERSION(6,2) && NOT_SLES_OR_PRE_VERSION(SLES11_SP2))
#ifndef DCB_CMD_CEE_GET
#define DCB_CMD_CEE_GET (-1) /* invalid value */
#endif
static inline int dcbnl_cee_notify(struct net_device *dev, int event, int cmd,
				   u32 seq, u32 pid)
{
	return -EOPNOTSUPP;
}
#endif

#if (LINUX_PRE_VERSION(3, 2, 0) && NOT_RHEL_OR_PRE_VERSION(6, 3) && NOT_SLES_OR_PRE_VERSION(SLES11_SP3))
static inline struct page *skb_frag_page(const skb_frag_t *frag)
{
	return frag->page;
}

static inline dma_addr_t skb_frag_dma_map(struct device *dev,
					  const skb_frag_t *frag,
					  size_t offset, size_t size,
					  enum dma_data_direction dir)
{
	return dma_map_page(dev, skb_frag_page(frag),
			    frag->page_offset + offset, size, dir);
}
#endif

#if (LINUX_STARTING_AT_VERSION(3, 0, 0) || RHEL_STARTING_AT_VERSION(6, 2))
#define  DCB_CEE_SUPPORT 1
#endif
#if (LINUX_PRE_VERSION(3, 3, 0))
#define netdev_features_t u32

#if NOT_SLES_OR_PRE_VERSION(SLES11_SP3)
#if NOT_RHEL_OR_PRE_VERSION(6, 4)
static inline u32 ethtool_rxfh_indir_default(u32 index, u32 n_rx_rings)
{
	return index % n_rx_rings;
}
#endif
#endif
#endif
#if defined(_DEFINE_NETDEV_TX_COMPLETED_QUEUE) || defined(__VMKLNX__)
static inline void netdev_tx_completed_queue(struct netdev_queue *q,
					    unsigned int a, unsigned int b) { }
static inline void netdev_tx_reset_queue(struct netdev_queue *q) { }
static inline void netdev_tx_sent_queue(struct netdev_queue *q,
					unsigned int len) { }
#endif

#ifndef eth_hw_addr_random
#define eth_hw_addr_random(dev) random_ether_addr(dev->dev_addr)
#endif

#if defined(_DEFINE_ETH_ZERO_ADDR_)
static inline void eth_zero_addr(u8 *addr)
{
	memset(addr, 0x00, ETH_ALEN);
}
#endif

#if LINUX_PRE_VERSION(2, 6, 14)
static inline void
pci_intx(struct pci_dev *pdev, int enable)
{
	u16 pci_command, new;

	pci_read_config_word(pdev, PCI_COMMAND, &pci_command);

	if (enable) {
		new = pci_command & ~PCI_COMMAND_INTX_DISABLE;
	} else {
		new = pci_command | PCI_COMMAND_INTX_DISABLE;
	}

	if (new != pci_command) {
		pci_write_config_word(pdev, PCI_COMMAND, new);
	}
}
#endif

#ifndef DEFINE_SEMAPHORE
#define DEFINE_SEMAPHORE(sem) DECLARE_MUTEX(sem)
#endif

#ifndef PCI_EXP_DEVCTL_BCR_FLR
#define PCI_EXP_DEVCTL_BCR_FLR 0x8000
#endif

#ifndef PCI_EXP_DEVCAP_FLR
#define PCI_EXP_DEVCAP_FLR 0x10000000
#endif

#if defined(CONFIG_XEN)
#ifndef PCI_MSIX_FLAGS
#define PCI_MSIX_FLAGS		2
#endif

#ifndef PCI_MSIX_FLAGS_ENABLE
#define PCI_MSIX_FLAGS_ENABLE	(1 << 15)
#endif

static inline void bnx2x_msix_set_enable(struct pci_dev *dev, int enable)
{
	int pos;
	u16 control;

	pos = pci_find_capability(dev, PCI_CAP_ID_MSIX);
	if (pos) {
		pci_read_config_word(dev, pos + PCI_MSIX_FLAGS, &control);
		control &= ~PCI_MSIX_FLAGS_ENABLE;
		if (enable)
			control |= PCI_MSIX_FLAGS_ENABLE;
		pci_write_config_word(dev, pos + PCI_MSIX_FLAGS, control);
	}
}
#endif

#ifndef ETH_TEST_FL_EXTERNAL_LB  /* ! BNX2X_UPSTREAM */
#define ETH_TEST_FL_EXTERNAL_LB		(1 << 2)
#endif
#ifndef ETH_TEST_FL_EXTERNAL_LB_DONE  /* ! BNX2X_UPSTREAM */
#define	ETH_TEST_FL_EXTERNAL_LB_DONE	(1 << 3)
#endif

#if (LINUX_PRE_VERSION(2, 6, 36) && (NOT_RHEL_OR_PRE_VERSION(6, 4)))
static inline void skb_tx_timestamp(struct sk_buff *skb)
{
	return;
}
#endif

#if (LINUX_PRE_VERSION(3, 2, 0))
#define skb_frag_size(frag) ((frag)->size)
#endif

#if defined(_DEFINE_PCI_ENABLE_MSIX_RANGE)
static inline int pci_enable_msix_range(struct pci_dev *dev,
					struct msix_entry *entries,
					int minvec, int maxvec)
{
	int rc;

	rc = pci_enable_msix(dev, entries, maxvec);
	if (!rc)
		return maxvec;

	/* Try with less - but still in range */
	if (rc >= minvec) {
		int try = rc;

		rc = pci_enable_msix(dev, entries, try);
		if (!rc)
			return try;
	}

	/* If can't supply in range but can supply something */
	if (rc > 0)
		return -ENOSPC;

	/* Return error */
	return rc;
}
#endif

#if defined(_DEFINE_NETIF_GET_NUM_DEFAULT_RSS_QUEUES)
static inline int netif_get_num_default_rss_queues(void)
{
	return min_t(int, 8, num_online_cpus());
}
#endif

#if defined(_DEFINE_SMP_MB_BEFORE_ATOMIC) && defined(_DEFINE_SMP_MB_BEFORE_ATOMIC_V2)
#define smp_mb__before_atomic()	smp_mb__before_clear_bit()
#define smp_mb__after_atomic()	smp_mb__after_clear_bit()
#endif

#if (LINUX_PRE_VERSION(2, 6, 12))
static inline int is_zero_ether_addr(const u8 *addr)
{
	return !(addr[0] | addr[1] | addr[2] | addr[3] | addr[4] | addr[5]);
}
#endif

#if (LINUX_PRE_VERSION(2, 6, 12))
/**
 * mutex_is_locked - is the mutex locked
 * @lock: the mutex to be queried
 *
 * Returns 1 if the mutex is locked, 0 if unlocked.
 */
static inline int mutex_is_locked(struct mutex *lock)
{
	return atomic_read(&lock->count) != 1;
}
#endif

#if ((LINUX_PRE_VERSION(2, 6, 19) && \
	!defined SLES_DISTRO && !defined(RHEL_RELEASE_CODE)) || \
	defined(RHEL_RELEASE_CODE) && (RHEL_RELEASE_CODE < RHEL_RELEASE_VERSION(5, 2)))
static inline struct pci_dev *pci_get_bus_and_slot(unsigned int bus,
						unsigned int devfn)
{ return NULL; }
#endif

#if ((LINUX_PRE_VERSION(2, 6, 30) && !defined(RHEL_RELEASE_CODE)) ||\
	(defined(RHEL_RELEASE_CODE) && RHEL_RELEASE_CODE < RHEL_RELEASE_VERSION(5, 4)))
static inline int pci_enable_sriov(struct pci_dev *dev, int nr_virtfn) {return 0; }
static inline void pci_disable_sriov(struct pci_dev *dev) { }
#endif

/* RH4.8 contains the prototype of pci_find_ext_capability but not the
 * implementation, so had to resort to ugly preprocessing...
 */
#if (defined(RHEL_RELEASE_CODE) && RHEL_RELEASE_CODE < RHEL_RELEASE_VERSION(4, 9))
#define pci_find_ext_capability dummy_find_ext_cap
static inline int dummy_find_ext_cap(struct pci_dev *dev, int cap) {return 0;}
#endif
#if (defined(SLES_DISTRO) && (SLES_DISTRO < 0x1005))
static inline int pci_find_ext_capability(struct pci_dev *dev, int cap) {return 0; }
#define bnx2x_pci_find_ext_capability(dev, cap) \
	pci_find_ext_capability(dev, cap)
#elif ESX_STARTING_AT(50000)

#define PCI_CFG_SPACE_SIZE      256
#define PCI_CFG_SPACE_EXP_SIZE  4096

int bnx2x_vmk_pci_find_ext_capability(struct pci_dev *dev, int cap);

#define pci_enable_sriov(pdev, x) (vmklnx_enable_vfs(pdev, x, NULL, NULL) != (x) ? -ENOTSUPP : 0)

#define pci_disable_sriov(pdev) vmklnx_disable_vfs(pdev, \
					(BP_VFDB(bp)->sriov.nr_virtfn), \
					NULL, NULL);

#if defined(bnx2x_vf_devfn)
#undef bnx2x_vf_devfn
#endif /* bnx2x_vf_devfn */
#define bnx2x_vf_devfn(bp, vfid)	bnx2x_vmk_vf_devfn(bp, vfid)

#if defined(bnx2x_vf_bus)
#undef bnx2x_vf_bus
#endif /* bnx2x_vf_bus */
#define bnx2x_vf_bus(bp, vfid)		bnx2x_vmk_vf_bus(bp, vfid)

#if defined(bnx2x_pci_find_ext_capability)
#undef bnx2x_pci_find_ext_capability
#endif /* bnx2x_pci_find_ext_capability */
#define bnx2x_pci_find_ext_capability(dev, cap) \
				bnx2x_vmk_pci_find_ext_capability(dev, cap)

#if defined(bnx2x_vf_is_pcie_pending)
#undef bnx2x_vf_is_pcie_pending
#endif /* bnx2x_vf_is_pcie_pending */
#define bnx2x_vf_is_pcie_pending(bp, abs_vfid) \
				bnx2x_vmk_vf_is_pcie_pending(bp, abs_vfid)

#elif ESX_PRE(50000)

static inline int bnx2x_pci_find_ext_capability(struct pci_dev *dev, int cap) {return 0; }

#else
#define bnx2x_pci_find_ext_capability(dev, cap) \
	pci_find_ext_capability(dev, cap)

#endif

#if ESX_STARTING_AT(50000)
#define bnx2x_open_epilog(bp)	bnx2x_vmk_open_epilog(bp)
#endif

#ifndef WARN
#define WARN(...)
#endif
#ifndef WARN_ONCE
#define WARN_ONCE(...)
#endif

/* If you don't support IS_ENABLED you obviously don't care about modern features */
#ifndef IS_ENABLED
#define IS_ENABLED(cfg) 0
#endif

#if LINUX_PRE_VERSION(2, 6, 14) && !defined(RHEL_RELEASE_CODE)
/**
 * kzalloc - allocate memory. The memory is set to zero.
 * @size: how many bytes of memory are required.
 * @flags: the type of memory to allocate (see kmalloc).
 */
static inline void *kzalloc(size_t size, unsigned int flags)
{
	void *ret = kmalloc(size, flags);
	if (ret)
		memset(ret, 0, size);
	return ret;
}
#endif

#if defined(__VMKLNX__)
#ifdef dev_info
#undef dev_info
#define dev_info(dev, format, arg...) printk(KERN_INFO "bnx2x: " format, ##arg)
#endif /* dev_info */

/* The following patch allows ESX to enter functions into D3hot */
#ifndef SYSTEM_POWER_OFF
#define SYSTEM_POWER_OFF	(3)
#endif
#define system_state		SYSTEM_POWER_OFF
#endif /* __VMKLNX__ */

#if defined(_DEFINE_PCIE_CAPABILITY_READ_WORD_)
static inline int pcie_capability_read_word(struct pci_dev *dev,
					    int pos, u16 *val)
{
	return pci_read_config_word(dev, pci_pcie_cap(dev) + pos, val);
}
#endif /*LINUX_PRE_VERSION(3, 7, 0)*/

#ifndef aligned_u64
#define aligned_u64 __u64 __attribute__((aligned(8)))
#endif

/* RHEL did not port ENCAPSULATION infrastucture */
#if ((defined(NETIF_F_GSO_GRE) && !defined(RHEL_RELEASE_CODE)) || \
     (defined(NETIF_F_GSO_GRE) && defined(RHEL_RELEASE_CODE) && \
      (RHEL_RELEASE_CODE >= RHEL_RELEASE_VERSION(7, 0))))
#define ENC_SUPPORTED 1
#elif ESX_STARTING_AT(55000)
#include <net/encap_offload.h>

#if (VMWARE_ESX_DDK_VERSION >= 60000)
#define IS_GENEVE(skb) (vmklnx_skb_geneve_present(skb))
#else
#define IS_GENEVE(skb) (0)
#endif

#define IS_VXLAN(skb) (vmklnx_skb_encap_present(skb))

#define IS_ENCAP(skb) ((IS_VXLAN(skb) || IS_GENEVE(skb)) && \
			 (skb->ip_summed == CHECKSUM_HW_ENCAP))
#define skb_inner_network_header esx_skb_inner_network_header
#define skb_inner_transport_header esx_skb_inner_transport_header
#define inner_tcp_hdrlen esx_inner_tcp_hdrlen
#define inner_ipv6_hdr esx_inner_ipv6_hdr
#define inner_ip_hdr esx_inner_ip_hdr
#define inner_tcp_hdr esx_inner_tcp_hdr

static inline unsigned char *esx_skb_inner_network_header(
					const struct sk_buff *skb)
{
	return skb->head + vmklnx_skb_encap_get_inner_ip_hdr_offset(skb);
}

static inline unsigned char *esx_skb_inner_transport_header(
					const struct sk_buff *skb)
{
	return skb->head + vmklnx_skb_encap_get_inner_l4_hdr_offset(skb);
}

static inline struct tcphdr *esx_inner_tcp_hdr(const struct sk_buff *skb)
{
	return (struct tcphdr *)esx_skb_inner_transport_header(skb);
}

static inline unsigned int esx_inner_tcp_hdrlen(const struct sk_buff *skb)
{
	return esx_inner_tcp_hdr(skb)->doff * 4;
}

static inline struct ipv6hdr *esx_inner_ipv6_hdr(const struct sk_buff *skb)
{
	return (struct ipv6hdr *)esx_skb_inner_network_header(skb);
}

static inline struct iphdr *esx_inner_ip_hdr(const struct sk_buff *skb)
{
	return (struct iphdr *)esx_skb_inner_network_header(skb);
}
#else
#ifndef NETIF_F_GSO_GRE
#define NETIF_F_GSO_GRE		0
#endif
#define skb_inner_network_header skb_network_header
#define skb_inner_transport_header skb_transport_header
#define inner_tcp_hdrlen tcp_hdrlen

#if defined(_DEFINE_INNER_IPV6_HDR) || defined(__VMKLNX__)
static inline struct ipv6hdr *inner_ipv6_hdr(const struct sk_buff *skb)
{
	return (struct ipv6hdr *)skb_inner_network_header(skb);
}
#endif

#if defined(_DEFINE_INNER_IP_HDR)  || defined(__VMKLNX__)
static inline struct iphdr *inner_ip_hdr(const struct sk_buff *skb)
{
	return (struct iphdr *)skb_inner_network_header(skb);
}
#endif

#if defined(_DEFINE_INNER_TCP_HDR) || defined(__VMKLNX__)
static inline struct tcphdr *inner_tcp_hdr(const struct sk_buff *skb)
{
	return (struct tcphdr *)skb_transport_header(skb);
}
#endif /* _DEFINE_INNER_TCP_HDR */
#endif /* NETIF_F_GSO_GRE */

#ifndef NETIF_F_GSO_UDP_TUNNEL
#define NETIF_F_GSO_UDP_TUNNEL 0
#endif

#if (LINUX_PRE_VERSION(2, 6, 33)) && !defined(__VMKLNX__)
#define pci_wake_from_d3(dev, enable)	pci_enable_wake(dev, PCI_D3hot, enable)
#endif

#if (LINUX_STARTING_AT_VERSION(3, 7, 0))
#undef __devinit
#define __devinit
#undef __devexit
#define __devexit
#undef __devinitdata
#define __devinitdata
#undef __devexit_p
#define __devexit_p(val)	val
#endif

#if (LINUX_PRE_VERSION(3, 8, 0))
#ifndef _HAVE_ARCH_IPV6_CSUM
#if ((defined(RHEL_RELEASE_CODE) && (RHEL_RELEASE_CODE >= RHEL_RELEASE_VERSION(6, 0))) || (defined(SLES_DISTRO) && (SLES_DISTRO > SLES11_SP1)))
#include <net/ip6_checksum.h>
#else
static inline __sum16 csum_ipv6_magic(const struct in6_addr *saddr,
					  const struct in6_addr *daddr,
					  __u32 len, unsigned short proto,
					  __wsum csum)
{

	int carry;
	__u32 ulen;
	__u32 uproto;
	__u32 sum = (__force u32)csum;

	sum += (__force u32)saddr->s6_addr32[0];
	carry = (sum < (__force u32)saddr->s6_addr32[0]);
	sum += carry;

	sum += (__force u32)saddr->s6_addr32[1];
	carry = (sum < (__force u32)saddr->s6_addr32[1]);
	sum += carry;

	sum += (__force u32)saddr->s6_addr32[2];
	carry = (sum < (__force u32)saddr->s6_addr32[2]);
	sum += carry;

	sum += (__force u32)saddr->s6_addr32[3];
	carry = (sum < (__force u32)saddr->s6_addr32[3]);
	sum += carry;

	sum += (__force u32)daddr->s6_addr32[0];
	carry = (sum < (__force u32)daddr->s6_addr32[0]);
	sum += carry;

	sum += (__force u32)daddr->s6_addr32[1];
	carry = (sum < (__force u32)daddr->s6_addr32[1]);
	sum += carry;

	sum += (__force u32)daddr->s6_addr32[2];
	carry = (sum < (__force u32)daddr->s6_addr32[2]);
	sum += carry;

	sum += (__force u32)daddr->s6_addr32[3];
	carry = (sum < (__force u32)daddr->s6_addr32[3]);
	sum += carry;

	ulen = (__force u32)htonl((__u32) len);
	sum += ulen;
	carry = (sum < ulen);
	sum += carry;

	uproto = (__force u32)htonl(proto);
	sum += uproto;
	carry = (sum < uproto);
	sum += carry;

	return csum_fold((__force __wsum)sum);
}
#endif
#endif
#if defined(_DEFINE_TCP_V6_CHECK_)
static inline __sum16 tcp_v6_check(int len,
					struct in6_addr *saddr,
					struct in6_addr *daddr,
					__wsum base)
{
	return csum_ipv6_magic(saddr, daddr, len, IPPROTO_TCP, base);
}
#endif
#endif

#if (LINUX_STARTING_AT_VERSION(2, 6, 21))
#define TCP_V4_CHECK_NEW
#endif

#ifndef CONFIG_BNX2X_SRIOV
#define CONFIG_BNX2X_SRIOV
#endif

#if RHEL_PRE_VERSION(6, 0) || \
    SLES_PRE_VERSION(SLES11_SP2) || \
    (0 < XENSERVER_DISTRO && XENSERVER_DISTRO < XENSERVER_VERSION(6, 1, 0)) || \
    (!(defined(RHEL_RELEASE_CODE) || defined(SLES_DISTRO) || 0 < XENSERVER_DISTRO) && \
     (LINUX_PRE_VERSION(2, 6, 34)))
struct ifla_vf_info {
	__u32 vf;
	__u8 mac[32];
	__u32 vlan;
	__u32 qos;
	__u32 tx_rate;
};
#endif

#if (LINUX_STARTING_AT_VERSION(3, 3, 0))
#define BCM_HAS_BUILD_SKB 1
#if (LINUX_STARTING_AT_VERSION(3, 5, 0))
#define BCM_HAS_BUILD_SKB_V2 1
#endif
#endif

#ifndef NETIF_F_HW_VLAN_CTAG_RX
#define NETIF_F_HW_VLAN_CTAG_RX	NETIF_F_HW_VLAN_RX
#endif

#ifndef NETIF_F_HW_VLAN_CTAG_TX
#define NETIF_F_HW_VLAN_CTAG_TX	NETIF_F_HW_VLAN_TX
#endif

#if defined(_DEFINE_PRANDOM_BYTES_)
static inline void prandom_bytes(void *buf, int bytes)
{
	int i;

	for (i = 0; i < bytes / 4; i ++)
		((u32*)buf)[i] = random32();

}
#endif

#ifndef NAPI_POLL_WEIGHT
#define NAPI_POLL_WEIGHT 64
#endif

#if ((!defined(RHEL_RELEASE_CODE) && (LINUX_PRE_VERSION(2, 6, 37))) || \
	(defined(RHEL_RELEASE_CODE) && \
		(((RHEL_MAJOR == 6) && (RHEL_MINOR < 1)) || \
		 ((RHEL_MAJOR == 5) && (RHEL_MINOR < 7)) || \
		  (RHEL_MAJOR < 5))))
/**
 * vzalloc - allocate memory. The memory is set to zero.
 * @size: how many bytes of memory are required.
 */
static inline void *vzalloc(size_t size)
{
	void *ret = vmalloc(size);
	if (ret)
		memset(ret, 0, size);
	return ret;
}
#endif

#ifndef IFF_UNICAST_FLT
#define IFF_UNICAST_FLT	0x20000
#endif

/* ESX / bnx2x queue loop difference */
#if !defined(__VMKLNX__)
#define for_each_eth_queue_(bp, var)	for_each_eth_queue(bp, var)
#define for_each_tx_queue_(bp, var)	for_each_tx_queue(bp, var)
#define for_each_rx_queue_(bp, var)	for_each_rx_queue(bp, var)
#define for_each_nondefault_eth_queue_(bp, var) \
	for_each_nondefault_eth_queue(bp, var)
#define _STAEU	static
#endif

#if (LINUX_STARTING_AT_VERSION(2, 6, 34)) || \
    RHEL_STARTING_AT_VERSION(6, 1) || \
    SLES_STARTING_AT_VERSION(SLES11_SP2) || \
    (0 < XENSERVER_DISTRO && (XENSERVER_DISTRO >= XENSERVER_VERSION(6, 1, 0)))
#define BNX2X_COMPAT_VF_NDO /* BNX2X_UPSTREAM */
#endif

#if (LINUX_STARTING_AT_VERSION(3, 9, 0))
#define BNX2X_COMPAT_NETDEV_PICK_TX
#endif

#if defined(_DEFINE_PCI_VFS_ASSIGNED_)
#if (defined(CONFIG_PCI_IOV) && ((LINUX_STARTING_AT_VERSION(3, 2, 0))  || \
				 RHEL_STARTING_AT_VERSION(6, 3) || \
				 SLES_STARTING_AT_VERSION(SLES11_SP3)))
int bnx2x_get_vf_pci_id(struct pci_dev *dev);

static inline int pci_vfs_assigned(struct pci_dev *dev)
{
	unsigned int vfs_assigned = 0;
	struct pci_dev *vfdev;
	u16 dev_id = bnx2x_get_vf_pci_id(dev);

	/* only search if we are a PF */
	if (!dev->is_physfn)
		return 0;

	/* loop through all the VFs to see if we own any that are assigned */
	vfdev = pci_get_device(dev->vendor, dev_id, NULL);
	while (vfdev) {
		/* if we don't own it we don't care */
		if ((vfdev->is_virtfn && vfdev->physfn == dev) &&
		    (vfdev->dev_flags & PCI_DEV_FLAGS_ASSIGNED))
			vfs_assigned++;

		vfdev = pci_get_device(dev->vendor, dev_id, vfdev);
	}

	return vfs_assigned;
}
#elif defined(__VMKLNX__)
static inline int pci_vfs_assigned(struct pci_dev *dev)
{
	return 0; /* vmkernel will prevent unload if VF is in use */
}
#else /* PCI_DEV_FLAGS_ASSIGNED */
static inline int pci_vfs_assigned(struct pci_dev *dev)
{
	return 1; /* try to avoid system crash */
}
#endif /* PCI_DEV_FLAGS_ASSIGNED */
#endif /* KERNEL_VERSION(3, 10, 0)) */

#if defined(_DEFINE_PCI_NUM_VF_) || defined(__VMKLNX__)
/* Sles10sp3 and rhel5.8 doesn't have pci_num_vf() defined in kernel
 * We don't claim SRIOV support for sles10sp3 and rhel5.8 also.
 * So define pci_num_vf() and just return 0 to allow implicit PF unload.
 */
static inline int pci_num_vf(struct pci_dev *dev) { return 0; }
#endif

#if (LINUX_PRE_VERSION(2, 6, 26))
#include <linux/sched.h>
#include <linux/jiffies.h>
#include <asm/semaphore.h>
static inline int down_timeout(struct semaphore *sem, unsigned long wait)
{
	unsigned long target = jiffies + wait;
	int result = down_trylock(sem);

	while (!time_after(jiffies, target) && result != 0) {
#if (LINUX_PRE_VERSION(2, 6, 14))
		set_current_state(TASK_INTERRUPTIBLE);
		schedule_timeout(1);
#else
		schedule_timeout_interruptible(1);
#endif
		result = down_trylock(sem);
	}
	return result;
}
#endif /* KERNEL_VERSION(2, 6, 26) */

#if (LINUX_PRE_VERSION(3, 12, 0))

#if LINUX_PRE_VERSION(2, 6, 19)
enum pcie_link_width {
	PCIE_LNK_WIDTH_RESRV	= 0x00,
	PCIE_LNK_X1		= 0x01,
	PCIE_LNK_X2		= 0x02,
	PCIE_LNK_X4		= 0x04,
	PCIE_LNK_X8		= 0x08,
	PCIE_LNK_X12		= 0x0C,
	PCIE_LNK_X16		= 0x10,
	PCIE_LNK_X32		= 0x20,
	PCIE_LNK_WIDTH_UNKNOWN  = 0xFF,
};
#endif

#if LINUX_PRE_VERSION(2, 6, 34)
#if LINUX_STARTING_AT_VERSION(2, 6, 19) || XENSERVER_DISTRO
#define PCIE_SPEED_2_5GT 0x14
#define PCIE_SPEED_5_0GT 0x15
#define PCIE_SPEED_8_0GT 0x16
#elif NOT_SLES_OR_PRE_VERSION(SLES11)
enum pci_bus_speed {
	PCI_SPEED_33MHz			= 0x00,
	PCI_SPEED_66MHz			= 0x01,
	PCI_SPEED_66MHz_PCIX		= 0x02,
	PCI_SPEED_100MHz_PCIX		= 0x03,
	PCI_SPEED_133MHz_PCIX		= 0x04,
	PCI_SPEED_66MHz_PCIX_ECC	= 0x05,
	PCI_SPEED_100MHz_PCIX_ECC	= 0x06,
	PCI_SPEED_133MHz_PCIX_ECC	= 0x07,
	PCI_SPEED_66MHz_PCIX_266	= 0x09,
	PCI_SPEED_100MHz_PCIX_266	= 0x0a,
	PCI_SPEED_133MHz_PCIX_266	= 0x0b,
	AGP_UNKNOWN			= 0x0c,
	AGP_1X				= 0x0d,
	AGP_2X				= 0x0e,
	AGP_4X				= 0x0f,
	AGP_8X				= 0x10,
	PCI_SPEED_66MHz_PCIX_533	= 0x11,
	PCI_SPEED_100MHz_PCIX_533	= 0x12,
	PCI_SPEED_133MHz_PCIX_533	= 0x13,
	PCIE_SPEED_2_5GT		= 0x14,
	PCIE_SPEED_5_0GT		= 0x15,
	PCIE_SPEED_8_0GT		= 0x16,
	PCI_SPEED_UNKNOWN		= 0xff,
};
#endif
#endif

#define PCICFG_LINK_CONTROL		0xbc
#define PCICFG_LINK_WIDTH		0x1f00000
#define PCICFG_LINK_WIDTH_SHIFT		20
#define PCICFG_LINK_SPEED		0xf0000
#define PCICFG_LINK_SPEED_SHIFT		16

#if defined(_DEFINE_PCIE_GET_MIN_LINK_)
static inline int __devinit pcie_get_minimum_link(struct pci_dev *pdev,
						  enum pci_bus_speed *speed,
						  enum pcie_link_width *width)

{
	u32 link_speed, val = 0;

	pci_read_config_dword(pdev, PCICFG_LINK_CONTROL, &val);
	*width = (enum pcie_link_width)
		  ((val & PCICFG_LINK_WIDTH) >> PCICFG_LINK_WIDTH_SHIFT);

	link_speed = (val & PCICFG_LINK_SPEED) >> PCICFG_LINK_SPEED_SHIFT;

	switch (link_speed) {
	case 3:
		*speed = PCIE_SPEED_8_0GT;
		break;
	case 2:
		*speed = PCIE_SPEED_5_0GT;
		break;
	default:
		*speed = PCIE_SPEED_2_5GT;
	}

	return 0;
}
#endif
#endif

#if LINUX_PRE_VERSION(2, 6, 14) && !defined(RHEL_RELEASE_CODE)
typedef unsigned __bitwise gfp_t;
#endif

#ifdef _DEFINE_DMA_ZALLOC_COHERENT
#define gfp_t unsigned
static inline void *dma_zalloc_coherent(struct device *dev, size_t size,
					dma_addr_t *dma_handle, gfp_t flag)
{
	void *ret = dma_alloc_coherent(dev, size, dma_handle, flag);

	if(ret)
		memset(ret, 0, size);
	return ret;
}
#endif

#if LINUX_STARTING_AT_VERSION(2, 6, 27)
#define BNX2X_MAC_FMT		"%pM"
#define BNX2X_MAC_PRN_LIST(mac)	(mac)
#else
#define BNX2X_MAC_FMT		"%02x:%02x:%02x:%02x:%02x:%02x"
#define BNX2X_MAC_PRN_LIST(mac)	(mac)[0], (mac)[1], (mac)[2], (mac)[3], \
				(mac)[4], (mac)[5]
#endif

/* Defines which should be removed by flavouring script */
#define _UP_UINT2INT uint /* int on upstream flavour */
#define _UP_UINT2NONE uint /* remove on upstream flavour */
#define _UP_STATIC /* Static on upstream flavour */
#define _UP_CONST /* const on upstream flavour */

#if defined(_DEFINE_PCIE_WAIT_PEND_TRANS_)
static inline int pci_wait_for_pending_transaction(struct pci_dev *dev)
{
	int i;
	u16 status;

	/* Wait for Transaction Pending bit clean */
	for (i = 0; i < 4; i++) {
		if (i)
			msleep((1 << (i - 1)) * 100);

		pcie_capability_read_word(dev, PCI_EXP_DEVSTA, &status);
		if (!(status & PCI_EXP_DEVSTA_TRPND))
			return 1;
	}

	return 0;
}
#endif

#if LINUX_STARTING_AT_VERSION(2, 6, 27) /* BNX2X_UPSTREAM */
#define BNX2X_PM_CAP(bp)		(bp)->pdev->pm_cap
#define BNX2X_PDEV_PM_CAP(bp, pdev)	(pdev)->pm_cap
#else
#define BNX2X_PM_CAP_LEGACY
#define BNX2X_PM_CAP(bp)		(bp)->pm_cap
#define BNX2X_PDEV_PM_CAP(bp, pdev)	(bp)->pm_cap
#endif

#if LINUX_STARTING_AT_VERSION(3, 10, 0) /* BNX2X_UPSTREAM */
#define BNX2X_PDEV_MSIX_CAP(pdev, pos)	(pdev)->msix_cap
#else
#define BNX2X_MSIX_CAP_LEGACY
#define BNX2X_PDEV_MSIX_CAP(pdev, pos)	(pos)
#endif

#ifdef BNX2X_UPSTREAM /* BNX2X_UPSTREAM */
#define PRINT_ENUM_ACCESS(p_enum, state)	(state)
#define PRINT_ENUM_STRING				"%d"
#else
#define PRINT_ENUM_ACCESS(p_enum, state)	(p_enum[state])
#define PRINT_ENUM_STRING				"%s"
#endif

#ifndef _DEFINE_PHYS_PORT_ID
#define SUPPORT_PHYS_PORT_ID
#endif
#ifndef _DEFINE_PHYS_ITEM_ID /* BNX2X_UPSTREAM */
#define SUPPORT_PHYS_PORT_ID
#define SUPPORT_PHYS_ITEM_ID
#endif

#if (LINUX_STARTING_AT_VERSION(2, 6, 29) || RHEL_STARTING_AT_VERSION(5, 5))
#define SUPPORT_PCIE_ARI_CHECK
#endif

#if (defined(_HAS_HW_TSTAMP) && (defined(CONFIG_PTP_1588_CLOCK) || defined(CONFIG_PTP_1588_CLOCK_MODULE)))
#define BCM_PTP
#endif

/* cq81900 - on RH6.x eprobe defer mechanism isn't properly working although it's available */
#if defined(_DEFINE_EPROBE_DEFER) || RHEL_PRE_VERSION(6, 8)
#ifndef EPROBE_DEFER
#define EPROBE_DEFER EBUSY
#endif
#else /* BNX2X_UPSTREAM */
#define SUPPORT_EPROBE_DEFER
#endif

#ifdef _DEFINE_AER
static inline int pci_disable_pcie_error_reporting(struct pci_dev *pdev) { return -EINVAL; }
static inline int pci_enable_pcie_error_reporting(struct pci_dev *pdev) { return -EINVAL; }
static inline int pci_cleanup_aer_uncorrect_error_status(struct pci_dev *pdev) { return -EINVAL; }
#endif

#ifdef __VMKLNX__ /* ! BNX2X_UPSTREAM */
#define ESX_CHK_VF_COUNT_RTNL(bp, msg) \
	do { \
		if (bnx2x_esx_check_active_vf_count(bp, msg) > 0) { \
			rtnl_unlock();\
			return; \
		} \
	} while (0)
#define ESX_CHK_VF_COUNT(bp, msg) \
	do { \
		if (bnx2x_esx_check_active_vf_count(bp, msg) > 0) { \
			return -EINVAL; \
		} \
	} while (0)
#else
#define ESX_CHK_VF_COUNT(bp, msg)
#define ESX_CHK_VF_COUNT_RTNL(bp, msg)
#endif

#ifndef _HAS_SET_VF_LINK_STATE
enum {
	IFLA_VF_LINK_STATE_AUTO,
	IFLA_VF_LINK_STATE_DISABLE,
	IFLA_VF_LINK_STATE_ENABLE
};
#endif /* _HAS_SET_VF_LINK_STATE */

#ifndef _HAS_CLAMP
#define clamp(val, min, max) ({			\
	typeof(val) __val = (val);		\
	typeof(min) __min = (min);		\
	typeof(max) __max = (max);		\
	(void) (&__val == &__min);		\
	(void) (&__val == &__max);		\
	__val = __val < __min ? __min: __val;	\
	__val > __max ? __max: __val; })
#endif /* _HAS_CLAMP */

#if LINUX_PRE_VERSION(3, 17, 0)
/* This cannot be decided by checking header symbols from kernel includes,
 * since the change making this possible is an exported symbol in a .c file.
 */
#define is_kdump_kernel()	(reset_devices)
#endif
#ifdef __VMKLNX__ /* ! BNX2X_UPSTREAM */
#define BNX2X_EEE_DEFAULT_VAL	-1
#else
#define BNX2X_EEE_DEFAULT_VAL	0
#endif

#ifdef _DEFINE_ETHER_ADDR_EQUAL
static inline bool ether_addr_equal(const u8 *addr1, const u8 *addr2)
{
	return memcmp(addr1, addr2, ETH_ALEN) == 0;
}
#endif

#ifdef _DEFINE_SKB_SET_HASH
enum pkt_hash_types {
	PKT_HASH_TYPE_NONE,	/* Undefined type */
	PKT_HASH_TYPE_L2,	/* Input: src_MAC, dest_MAC */
	PKT_HASH_TYPE_L3,	/* Input: src_IP, dst_IP */
	PKT_HASH_TYPE_L4,	/* Input: src_IP, dst_IP, src_port, dst_port */
};

static inline void
skb_set_hash(struct sk_buff *skb, __u32 hash, enum pkt_hash_types type)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 2, 0))
	skb->l4_rxhash = (type == PKT_HASH_TYPE_L4);
#endif
#if (LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 34))
	skb->rxhash = hash;
#endif
}
#endif

#ifdef _DEFINE_SKB_MARK_NAPI_ID
#define skb_mark_napi_id(skb, napi)  do { } while (0)
#define napi_hash_add(napi)	do { } while (0)
#define napi_hash_del(napi)	do { } while (0)
#endif

#ifndef NETIF_F_GSO_IPIP
#define NETIF_F_GSO_IPIP (0)
#endif

#ifndef NETIF_F_GSO_SIT
#define NETIF_F_GSO_SIT	(0)
#endif

#ifdef _DEFINE_NETDEV_FEATURES_T
#define netdev_features_t u32
#endif

#ifdef _DEFINE_RSS_KEY_FILL
#define netdev_rss_key_fill prandom_bytes
#endif

#ifdef _DEFINE_NAPI_SCHEDULE_IRQOFF
#define napi_schedule_irqoff napi_schedule
#endif

#ifdef _DEFINE_CYCLECOUNTER_MASK
#define CYCLECOUNTER_MASK CLOCKSOURCE_MASK
#endif

#ifndef _HAS_TIMESPEC64
#define timespec64_to_ns(ts)  ((ts)->tv_sec * 10000000ULL + (ts)->tv_nsec)
#endif

#ifdef _DEFINE_SKB_VLAN_TAG
#define skb_vlan_tag_present vlan_tx_tag_present
#define skb_vlan_tag_get vlan_tx_tag_get
#endif

#ifndef NETIF_F_HW_VLAN_CTAG_FILTER
#define NETIF_F_HW_VLAN_CTAG_FILTER NETIF_F_HW_VLAN_FILTER
#endif

#ifdef _DEFINE_DATA_ACCESS_EXCEEDS_WORD_SIZE
static __always_inline void data_access_exceeds_word_size(void)
#ifdef __compiletime_warning
__compiletime_warning("data access exceeds word size and won't be atomic")
#endif
;

static __always_inline void data_access_exceeds_word_size(void)
{
}
#endif

#ifdef _DEFINE_READ_ONCE
static __always_inline void __read_once_size(volatile void *p, void *res, int size)
{
	switch (size) {
	case 1: *(__u8 *)res = *(volatile __u8 *)p; break;
	case 2: *(__u16 *)res = *(volatile __u16 *)p; break;
	case 4: *(__u32 *)res = *(volatile __u32 *)p; break;
#ifdef CONFIG_64BIT
	case 8: *(__u64 *)res = *(volatile __u64 *)p; break;
#endif
	default:
		barrier();
		memcpy((void *)res, (const void *)p, size);
		data_access_exceeds_word_size();
		barrier();
	}
}

#define READ_ONCE(x) \
	({ typeof(x) __val; __read_once_size(&x, &__val, sizeof(__val)); __val; })

#endif

#ifdef _DEFINE_WRITE_ONCE
static __always_inline void __write_once_size(volatile void *p, void *res, int size)
{
	switch (size) {
	case 1: *(volatile __u8 *)p = *(__u8 *)res; break;
	case 2: *(volatile __u16 *)p = *(__u16 *)res; break;
	case 4: *(volatile __u32 *)p = *(__u32 *)res; break;
#ifdef CONFIG_64BIT
	case 8: *(volatile __u64 *)p = *(__u64 *)res; break;
#endif
	default:
		barrier();
		memcpy((void *)p, (const void *)res, size);
		data_access_exceeds_word_size();
		barrier();
	}
}

#define WRITE_ONCE(x, val) \
	({ typeof(x) __val; __val = val; __write_once_size(&x, &__val, sizeof(__val)); __val; })

#endif

#if LINUX_PRE_VERSION(2, 6, 39) && \
    !(RHEL_STARTING_AT_VERSION(6, 6) && RHEL_PRE_VERSION(7, 0))
#define BNX2X_LEGACY_RX_CSUM
#endif

#ifndef ETH_P_8021AD
#define ETH_P_8021AD 0x88a8
#endif

#ifndef BIT
#define BIT(x)	(1 << (x))
#endif

#ifdef _DEFINE_DMA_SET_MASK_AND_COHERENT
/* A bit akward - both inner functions return 0 on success,
 * and we need this one to be `0' as well if it succeeds.
 */
#define dma_set_mask_and_coherent(dev, mask)	(!(!dma_set_mask(dev, mask) && !dma_set_coherent_mask(dev, mask)))
#endif

#ifdef _DEFINE_SKB_FREE_FRAG
#define skb_free_frag(data) put_page(virt_to_head_page(data))
#endif

#ifdef _DEFINE_GFP_ALLOW_BLOCKING
#define gfpflags_allow_blocking(mask)	((mask) & __GFP_WAIT)
#endif

#if defined(_DEFINE_KTIME_MS_DELTA) && defined(_HAS_BOOTTIME)
static inline s64 ktime_ms_delta(const ktime_t later, const ktime_t earlier)
{
	return ktime_to_ms(ktime_sub(later, earlier));
}
#endif

#endif /* __BNX2X_COMPAT_H__ */
