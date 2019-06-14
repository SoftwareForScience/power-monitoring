# USAGE
# python detect_image.py --model mobilenet_ssd_v2/mobilenet_ssd_v2_coco_quant_postprocess_edgetpu.tflite --labels mobilenet_ssd_v2/coco_labels.txt --image thanos.jpg

# import the necessary packages
from edgetpu.detection.engine import DetectionEngine
from PIL import Image
import argparse
import imutils
import time
import cv2

# construct the argument parser and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-m", "--model", required=True,
	help="path to TensorFlow Lite object detection model")
ap.add_argument("-l", "--labels", required=True,
	help="path to labels file")
ap.add_argument("-i", "--image", required=True,
	help="path to input image")
ap.add_argument("-c", "--confidence", type=float, default=0.3,
	help="minimum probability to filter weak detections")
args = vars(ap.parse_args())

# initialize the labels dictionary
print("[INFO] parsing class labels...")
labels = {}

# loop over the class labels file
for row in open(args["labels"]):
	# unpack the row and update the labels dictionary
	(classID, label) = row.strip().split(maxsplit=1)
	labels[int(classID)] = label.strip()

# load the Google Coral object detection model
print("[INFO] loading Coral model...")
model = DetectionEngine(args["model"])

# load the input image
image = cv2.imread(args["image"])
image = imutils.resize(image, width=500)
orig = image.copy()

# prepare the image for object detection by converting (1) it from
# BGR to RGB channel ordering and then (2) from a NumPy array to PIL
# image format
image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
image = Image.fromarray(image)

# make predictions on the input image
print("[INFO] making predictions...")
start = time.time()
results = model.DetectWithImage(image, threshold=args["confidence"],
	keep_aspect_ratio=True, relative_coord=False)
end = time.time()
print("[INFO] object detection took {:.4f} seconds...".format(
	end - start))

# loop over the results
for r in results:
	# extract the bounding box and box and predicted class label
	box = r.bounding_box.flatten().astype("int")
	(startX, startY, endX, endY) = box
	label = labels[r.label_id]

	# draw the bounding box and label on the image
	cv2.rectangle(orig, (startX, startY), (endX, endY),
		(0, 255, 0), 2)
	y = startY - 15 if startY - 15 > 15 else startY + 15
	text = "{}: {:.2f}%".format(label, r.score * 100)
	cv2.putText(orig, text, (startX, y),
		cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)

# show the output image
cv2.imshow("Image", orig)
cv2.waitKey(0)
