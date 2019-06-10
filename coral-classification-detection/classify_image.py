# USAGE
# python classify_image.py --model inception_v4/inception_v4_299_quant_edgetpu.tflite --labels inception_v4/imagenet_labels.txt --image janie.jpg

# import the necessary packages
from edgetpu.classification.engine import ClassificationEngine
from PIL import Image
import argparse
import imutils
import time
import cv2

# construct the argument parser and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-m", "--model", required=True,
	help="path to TensorFlow Lite classification model")
ap.add_argument("-l", "--labels", required=True,
	help="path to labels file")
ap.add_argument("-i", "--image", required=True,
	help="path to input image")
args = vars(ap.parse_args())

# initialize the labels dictionary
print("[INFO] parsing class labels...")
labels = {}

# loop over the class labels file
for row in open(args["labels"]):
	# unpack the row and update the labels dictionary
	(classID, label) = row.strip().split(" ", maxsplit=1)
	labels[int(classID)] = label.strip()

# load the Google Coral classification model
print("[INFO] loading Coral model...")
model = ClassificationEngine(args["model"])

# load the input image
image = cv2.imread(args["image"])
image = imutils.resize(image, width=500)
orig = image.copy()

# prepare the image for classification by converting (1) it from BGR
# to RGB channel ordering and then (2) from a NumPy array to PIL
# image format
image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
image = Image.fromarray(image)

# make predictions on the input image
print("[INFO] making predictions...")
start = time.time()
results = model.ClassifyWithImage(image, top_k=5)
end = time.time()
print("[INFO] classification took {:.4f} seconds...".format(
	end - start))

# loop over the results
for (i, (classID, score)) in enumerate(results):
	# check to see if this is the top result, and if so, draw the
	# label on the image
	if i == 0:
		text = "Label: {}, {:.2f}%".format(labels[classID],
			score * 100)
		cv2.putText(orig, text, (10, 30), cv2.FONT_HERSHEY_SIMPLEX,
			0.8, (0, 0, 255), 2)

	# display the classification result to the terminal
	print("{}. {}: {:.2f}%".format(i + 1, labels[classID],
		score * 100))

# show the output image
cv2.imshow("Image", orig)
cv2.waitKey(0)
