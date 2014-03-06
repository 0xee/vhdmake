
#define one of the following :
#path of coco relative to this file OR
COCO_PATH_REL   = ../CocoLinux
#absolute path of coco
COCO_PATH_ABS   =

#path to coco frames files
COCO_FRAMES = $(COCO_PATH)

#installation prefix
PREFIX=/usr/bin


#do not change these!
COCO_PATH= $(COCO_PATH_ABS) ../../$(COCO_PATH_REL)
COCO        = $(COCO_PATH)/Coco
