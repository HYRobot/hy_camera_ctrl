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

# ----------------------------------------------------------
# 依赖列表
# ----------------------------------------------------------
HY_CAMERA_CTRL_DEPENDENCIES = \
    cjson \
    jsoncpp \
    libgpiod

# ----------------------------------------------------------
# 编译标志配置 (根据 Debug 模式动态调整)
# ----------------------------------------------------------

HY_CAMERA_CTRL_DEBUG ?= y
# 1. 定义基础标志 (Release 和 Debug 通用)
# 注意：去掉强制的 -g 和 -fsanitize=address
HY_CFLAGS = $(TARGET_CFLAGS) -Wall -O2
HY_LDFLAGS = $(TARGET_LDFLAGS)

# 2. 判断 Buildroot 是否开启了 Debug 选项
ifeq ($(HY_CAMERA_CTRL_DEBUG),y)
    # --- Debug 模式 ---
    # 启用 ASan (AddressSanitizer)
    # 启用 -g 生成调试符号
    HY_CFLAGS += -fsanitize=address -g
    HY_LDFLAGS += -fsanitize=address
else
    # --- Release 模式 ---
    # 这里可以添加 Release 专用的优化参数，或者留空
    # 确保不包含 ASan
endif

# ----------------------------------------------------------
# 源文件列表
# ----------------------------------------------------------
LIBAE_SRCS = ae.c anet.c zmalloc.c
LIBVISCA_SRCS = libvisca.c libvisca_posix.c
HY_MAIN_SRCS = visca_ctrl.c gimbal_ctrl.c camera_client_async.c \
               liangyuan_lrf_905.c netlink_listener.c mavlink_listener.c main.c

# ----------------------------------------------------------
# 构建步骤
# ----------------------------------------------------------

# 编译 libae.a
define HY_CAMERA_CTRL_BUILD_LIBAE
    @echo "Building libae (Debug=$(HY_CAMERA_CTRL_DEBUG))..."
    mkdir -p $(@D)/libae
    $(TARGET_CC) $(HY_CFLAGS) -I$(HY_CAMERA_CTRL_SITE)/libae \
        -c $(addprefix $(HY_CAMERA_CTRL_SITE)/libae/, $(LIBAE_SRCS))
    mv *.o $(@D)/libae/
    ar rcs $(@D)/libae/libae.a $(@D)/libae/*.o
endef

# 编译 libvisca.a
define HY_CAMERA_CTRL_BUILD_LIBVISCA
    @echo "Building libvisca (Debug=$(HY_CAMERA_CTRL_DEBUG))..."
    mkdir -p $(@D)/libvisca
    $(TARGET_CC) $(HY_CFLAGS) -I$(HY_CAMERA_CTRL_SITE)/libvisca \
        -c $(addprefix $(HY_CAMERA_CTRL_SITE)/libvisca/, $(LIBVISCA_SRCS))
    mv *.o $(@D)/libvisca/
    ar rcs $(@D)/libvisca/libvisca.a $(@D)/libvisca/*.o
endef

# 编译主程序
define HY_CAMERA_CTRL_BUILD_CMDS
    $(call HY_CAMERA_CTRL_BUILD_LIBAE)
    $(call HY_CAMERA_CTRL_BUILD_LIBVISCA)

    @echo "Compiling hy_camera_ctrl sources..."
    $(foreach src, $(HY_MAIN_SRCS), \
        $(TARGET_CC) $(HY_CFLAGS) \
            -I$(TOPDIR)/package/hy_camera_ctrl/include/mavlink/v2.0/hy_gimbal \
            -I$(STAGING_DIR)/usr/include \
            -I$(STAGING_DIR)/usr/include/jsoncpp \
            -I$(HY_CAMERA_CTRL_SITE)/libae \
            -I$(HY_CAMERA_CTRL_SITE)/libvisca \
            -c $(HY_CAMERA_CTRL_SITE)/$(src) -o $(@D)/$(src:.c=.o); \
    )

    @echo "Linking hy_camera_ctrl..."
    # 注意：链接时使用了 HY_LDFLAGS，它会根据模式自动携带或不携带 -fsanitize=address
    $(TARGET_CXX) -o $(@D)/hy_camera_ctrl \
        $(addprefix $(@D)/, $(HY_MAIN_SRCS:.c=.o)) \
        $(HY_LDFLAGS) \
        -lgpiod -lcjson \
        $(@D)/libmultimedia_api/libmultimedia_api.a \
        $(@D)/libae/libae.a \
        $(@D)/libvisca/libvisca.a \
        -ljsoncpp
endef

# 安装命令
define HY_CAMERA_CTRL_INSTALL_TARGET_CMDS
    $(INSTALL) -D -m 0755 $(@D)/hy_camera_ctrl \
        $(TARGET_DIR)/usr/bin/hy_camera_ctrl
    $(INSTALL) -D -m 0755 $(TOPDIR)/package/hy_camera_ctrl/S82hycameractrl \
        $(TARGET_DIR)/etc/init.d/S82hycameractrl
endef

$(eval $(generic-package))