LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

#注释原始文件包含的cpp
#LOCAL_SRC_FILES := hellocpp/main.cpp \
#                   ../../Classes/AppDelegate.cpp \
#                   ../../Classes/HelloWorldScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes\
                    $(LOCAL_PATH)/../../Classes/Common\
                    $(LOCAL_PATH)/../../Classes/Common/Allocator\
                    $(LOCAL_PATH)/../../Classes/Game\
                    $(LOCAL_PATH)/../../Classes/Game/Components\
                    $(LOCAL_PATH)/../../Classes/Game/Level\
                    $(LOCAL_PATH)/../../Classes/Game/SDT4\
                    $(LOCAL_PATH)/../../Classes/Game/Weapon\
                    $(LOCAL_PATH)/../../Classes/Scenes\
                    $(LOCAL_PATH)/../../Classes/UI
                    
#cpp path
MY_CPP_SRC_PATH :=  $(LOCAL_PATH)/../../Classes\
                    $(LOCAL_PATH)/../../ThirdParty
                    
#搜索所有CPP文件 自动忽略 SNS InAppPurchase speech OpenAL文件夹
define all-cpp-files
$(patsubst ./%,%, $(shell find $(MY_CPP_SRC_PATH) -name "*.cpp" -and -not -name ".*"))
endef

#自动搜索子文件夹
define all-subdir-cpp-files
$(call all-cpp-files,.)
endef

#搜索所有.c文件 自动忽略speech Ogg freetype libjpeg openal文件夹
define all-c-files
$(patsubst ./%,%, $(shell find $(MY_CPP_SRC_PATH) -name "*.c" -and -not -name ".*"))
endef

#自动搜索子文件夹
define all-subdir-c-files
$(call all-c-files,.)
endef

#CPP_FILE_LIST 包含所有自动搜索的cpp文件 还手动添加了平台特有的cpp文件
CPP_FILE_LIST :=    $(call all-subdir-cpp-files)\
                    hellocpp/main.cpp


#C_FILE_LIST 包含所有自动搜索的c文件 还手动添加了部分c文件
C_FILE_LIST := $(call all-subdir-c-files) 

#要忽略编译的CPP文件
IGNORE_CPP_FILE := $(LOCAL_PATH)/../../Classes/HelloWorldScene.cpp

#过滤忽略文件
CPP_FILE_LIST  := $(filter-out $(IGNORE_CPP_FILE), $(CPP_FILE_LIST))
#添加需要包含的文件
LOCAL_SRC_FILES := $(CPP_FILE_LIST:$(LOCAL_PATH)/%=%)
LOCAL_SRC_FILES += $(C_FILE_LIST:$(LOCAL_PATH)/%=%)
                   
LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
