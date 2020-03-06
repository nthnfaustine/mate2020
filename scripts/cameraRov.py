#!/usr/bin/python

import cv2
from skimage import exposure
from cv_bridge import CvBridge, CvBridgeError
import rospy
from sensor_msgs.msg import Image, CompressedImage

def RecoverCLAHE(sceneRadiance):
    clahe = cv2.createCLAHE(clipLimit=2, tileGridSize=(4, 4))
    for i in range(3):
        sceneRadiance[:, :, i] = clahe.apply((sceneRadiance[:, :, i]))
    return sceneRadiance

rospy.init_node("cameraROV")
image_publisher = rospy.Publisher("/rov/image", Image, queue_size=8)
image_publisher_compressed = rospy.Publisher("/rov/image/compressed", CompressedImage, queue_size=8)

vid = cv2.VideoCapture(0)
bridge = CvBridge()

while not rospy.is_shutdown():
    success, img = vid.read()
    if img is None:
        break
    new_img = img.copy()
    new_img = RecoverCLAHE(new_img)

    imgmsg = bridge.cv2_to_imgmsg(new_img, "bgr8")
    # comp_imgmsg = bridge.cv2_to_compressed_imgmsg()
    image_publisher.publish(imgmsg)
