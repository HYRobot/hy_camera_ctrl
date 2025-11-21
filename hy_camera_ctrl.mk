################################################################################
#
# hy_camera_ctrl
#
################################################################################

HY_CAMERA_CTRL_VERSION = 1.0
HY_CAMERA_CTRL_SITE = $(TOPDIR)/package/hy_camera_ctrl/src
HY_CAMERA_CTRL_SITE_METHOD = local

HY_CAMERA_CTRL_LICENSE = MIT
HY_CAMERA_CTRL_LICENSE_FILES = LICENSE

# 依赖库
HY_CAMERA_CTRL_DEPENDENCIES = \
	cjson \
	libgpiod

# libae 源文件
LIBAE_SRCS = \
	ae.c \
	ae_epoll.c \
	ae_select.c \
	anet.c \
	zmalloc.c

# libvisca 源文件
LIBVISCA_SRCS = \
	libvisca.c \
	libvisca_posix.c


# 编译 libae.a
define HY_CAMERA_CTRL_BUILD_LIBAE
	@echo "Building libae..."
	mkdir -p $(@D)/libae
	$(TARGET_CC) $(TARGET_CFLAGS) -I$(HY_CAMERA_CTRL_SITE)/libae \
		-c $(addprefix $(HY_CAMERA_CTRL_SITE)/libae/, $(LIBAE_SRCS))
	ar rcs $(@D)/libae/libae.a *.o
endef

# 编译 libvisca.a
define HY_CAMERA_CTRL_BUILD_LIBVISCA
	@echo "Building libvisca..."
	mkdir -p $(@D)/libvisca
	$(TARGET_CC) $(TARGET_CFLAGS) -I$(HY_CAMERA_CTRL_SITE)/libvisca \
		-c $(addprefix $(HY_CAMERA_CTRL_SITE)/libvisca/, $(LIBVISCA_SRCS))
	ar rcs $(@D)/libvisca/libvisca.a *.o
endef

# 编译主程序
define HY_CAMERA_CTRL_BUILD_CMDS
	$(call HY_CAMERA_CTRL_BUILD_LIBAE)
	$(call HY_CAMERA_CTRL_BUILD_LIBVISCA)

	@echo "Building hy_camera_ctrl..."
	$(TARGET_CC) $(TARGET_CFLAGS) -Wall -O2 \
		-I$(TOPDIR)/package/hy_camera_ctrl/include/mavlink/v2.0/hy_gimbal \
		-I$(STAGING_DIR)/usr/include \
		-I$(HY_CAMERA_CTRL_SITE)/libae \
		-I$(HY_CAMERA_CTRL_SITE)/libvisca \
		-o $(@D)/hy_camera_ctrl \
		$(HY_CAMERA_CTRL_SITE)/visca_ctrl.c \
		$(HY_CAMERA_CTRL_SITE)/gimbal_ctrl.c \
		$(HY_CAMERA_CTRL_SITE)/camera_client_async.c \
		$(HY_CAMERA_CTRL_SITE)/liangyuan_lrf_905.c \
		$(HY_CAMERA_CTRL_SITE)/netlink_listener.c \
		$(HY_CAMERA_CTRL_SITE)/mavlink_listener.c \
		$(HY_CAMERA_CTRL_SITE)/main.c \
		$(TARGET_LDFLAGS) -lgpiod -lcjson \
		$(@D)/libae/libae.a \
		$(@D)/libvisca/libvisca.a
endef

# 安装到目标系统
define HY_CAMERA_CTRL_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/hy_camera_ctrl \
		$(TARGET_DIR)/usr/bin/hy_camera_ctrl
	$(INSTALL) -D -m 0755 $(TOPDIR)/package/hy_camera_ctrl/S82hycameractrl \
		$(TARGET_DIR)/etc/init.d/S82hycameractrl
endef

$(eval $(generic-package))
