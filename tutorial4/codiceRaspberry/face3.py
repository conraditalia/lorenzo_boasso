import io
import picamera
import cv2
import numpy

import time
import Adafruit_GPIO.SPI as SPI
import Adafruit_SSD1306
import Image
import ImageDraw
import ImageFont

# Raspberry Pi pin configuration:
RST = 24
# 128x32 display with hardware I2C:
disp = Adafruit_SSD1306.SSD1306_128_32(rst=RST)
# Initialize library.
disp.begin()
# Clear display.
disp.clear()
disp.display()

# Create blank image for drawing.
# Make sure to create image with mode '1' for 1-bit color.
width = disp.width
height = disp.height
dispimage = Image.new('1', (width, height))

#Load a cascade file for detecting faces
face_cascade = cv2.CascadeClassifier('/usr/share/opencv/haarcascades/haarcascade_frontalface_alt.xml')

while True:
	#Create a memory stream so photos doesn't need to be saved in a file
	stream = io.BytesIO()

	#Get the picture (low resolution, so it should be quite fast)
	#Here you can also specify other parameters (e.g.:rotate the image)
	with picamera.PiCamera() as camera:
		camera.resolution = (320, 240)
		camera.capture(stream, format='jpeg')

	#Convert the picture into a numpy array
	buff = numpy.fromstring(stream.getvalue(), dtype=numpy.uint8)

	#Now creates an OpenCV image
	image = cv2.imdecode(buff, 1)

	

	#Convert to grayscale
	gray = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)

	#Look for faces in the image using the loaded cascade file
	faces = face_cascade.detectMultiScale(gray, 1.1, 5)

	#print "Found "+str(len(faces))+" face(s)"
	
	
	# Get drawing object to draw on image.
	draw = ImageDraw.Draw(dispimage)
	# Draw a black filled box to clear the image.
	draw.rectangle((0,0,width,height), outline=0, fill=0)
	# Load default font.
	font = ImageFont.load_default()
	# Write two lines of text.
	draw.text((5, 5),    'Enemies:',  font=font, fill=255)
	draw.text((5, 15), str(len(faces)), font=font, fill=255)
	# Display image.
	disp.image(dispimage)
	disp.display()

	#Draw a rectangle around every found face
	#for (x,y,w,h) in faces:
	#	cv2.rectangle(image,(x,y),(x+w,y+h),(255,255,0),2)

	#Save the result image
	#cv2.imwrite('result.jpg',image)
	
	#time.sleep(0.1)