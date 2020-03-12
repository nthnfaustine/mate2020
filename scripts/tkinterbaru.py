#!/usr/bin/python

import cv2
import rospy
import Tkinter
from PIL import Image, ImageTk
from cv_bridge import CvBridge, CvBridgeError
from sensor_msgs.msg import CompressedImage
import numpy as np
from random import randint

ori = np.zeros([2000,1500, 3], dtype=np.uint8) #DISINI
count = 0 #mulai dari 0

def image_callback(img):
	global ori
        ori_cv2 = np.fromstring(img.data, np.uint8)
        ori_cv2 = cv2.imdecode(ori_cv2, cv2.IMREAD_COLOR)
        ori = ori_cv2

if __name__ == '__main__':
	rospy.init_node('tkinter', anonymous=True)
	# image_subscriber = rospy.Subscriber("/rov/image", ROSImage, image_callback)
	image_subscriber_compressed = rospy.Subscriber("/rov/image/compressed", CompressedImage, image_callback)


	master = Tkinter.Tk() #ngebuat tkinter
	master.title("TKinter MATE")
	frame = Tkinter.Frame(master=master)
	master.geometry("1200x1000") 
	
	
	ori_label = Tkinter.Label(master=master, image=None)
	ori_label.place(x = 0, y =0)

	
	slider_frame1 = Tkinter.Frame(master=master)	
	Info_frame = Tkinter.Frame(master=master)


	Tkinter.Label(master=master, text="Suhu", fg='green',bg = 'white',bd = '10' ,font=("Helvetica", 25)).place(x = 650, y = 13)
	Tkinter.Label(master=master, text="Tekanan", fg='blue',bg = 'white',bd = '10' , font=("Helvetica", 25)).place(x = 650, y = 123)
	Tkinter.Label(master=master, text="Kedalaman", fg='red',bg = 'white',bd = '10' , font=("Helvetica", 25)).place(x = 650, y = 203)
	Info_frame.grid(row=1, column=1)


	while not rospy.is_shutdown():
		if ori is not None:
			b,g,r = cv2.split(ori)
            		img = cv2.merge((r,g,b)) 
            		im = Image.fromarray(img)
            		imgtk = ImageTk.PhotoImage(image=im)
            		ori_label.config(image=imgtk)
			

			count = count + 1
			if count >= 100:
				Tkinter.Label(master=master, text="25", fg='black',bg = 'green',bd = '3' ,font=("Helvetica", 25)).place(x = 890, y = 13)
				Tkinter.Label(master=master, text=str((1050,1100)), fg='black',bg = 'blue',bd = '3' , font=("Helvetica", 25)).place(x = 890, y = 123)
				Tkinter.Label(master=master, text=str((1,100)), fg='black',bg = 'red',bd = '3' , font=("Helvetica", 25)).place(x = 890, y = 203)
				count = 0
		master.update()
