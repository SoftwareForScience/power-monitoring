# Copyright 2019 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""A demo to classify image."""

import argparse
import re
from edgetpu.classification.engine import ClassificationEngine
import numpy as np
import cv2
from picamera.array import PiRGBArray
from picamera import PiCamera

# Set up camera constants
IM_WIDTH = 1280
IM_HEIGHT = 720
#IM_WIDTH = 640    Use smaller resolution for
#IM_HEIGHT = 480   slightly faster framerate


# Function to read labels from text files.
def ReadLabelFile(file_path):
  """Reads labels from text file and store it in a dict.

  Each line in the file contains id and description separted by colon or space.
  Example: '0:cat' or '0 cat'.

  Args:
    file_path: String, path to the label file.

  Returns:
    Dict of (int, string) which maps label id to description.
  """
  with open(file_path, 'r', encoding='utf-8') as f:
    lines = f.readlines()
  ret = {}
  for line in lines:
    pair = re.split(r'[:\s]+', line.strip(), maxsplit=1)
    ret[int(pair[0])] = pair[1].strip()
  return ret


def main():
  parser = argparse.ArgumentParser()
  parser.add_argument(
      '--model', help='File path of Tflite model.', required=True)
  parser.add_argument(
      '--label', help='File path of label file.', required=True)
  parser.add_argument(
      '--image', help='File path of the image to be recognized.', required=True)
  args = parser.parse_args()

  # Initialize Picamera and grab reference to the raw capture
  camera = PiCamera()
  camera.resolution = (IM_WIDTH, IM_HEIGHT)
  camera.framerate = 10
  rawCapture = PiRGBArray(camera, size=(IM_WIDTH, IM_HEIGHT))
  rawCapture.truncate(0)

  # Prepare labels.
  labels = ReadLabelFile(args.label)
  # Initialize engine.
  engine = ClassificationEngine(args.model)

  for frame1 in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):

    t1 = cv2.getTickCount()

    # Acquire frame and expand frame dimensions to have shape: [1, None, None, 3]
    # i.e. a single-column array, where each item in the column has the pixel RGB value
    frame = np.copy(frame1.array)
    frame.setflags(write=1)
    frame_expanded = np.expand_dims(frame, axis=0)

    for result in engine.ClassifyWithImage(frame_expanded, top_k=3):
      print('---------------------------')
      print(labels[result[0]])
      print('Score : ', result[1])

    # Perform the actual detection by running the model with the image as input
    # (boxes, scores, classes, num) = sess.run(
    #   [detection_boxes, detection_scores, detection_classes, num_detections],
    #   feed_dict={image_tensor: frame_expanded})

    # Draw the results of the detection (aka 'visulaize the results')
    # vis_util.visualize_boxes_and_labels_on_image_array(
    #   frame,
    #   np.squeeze(boxes),
    #   np.squeeze(classes).astype(np.int32),
    #   np.squeeze(scores),
    #   category_index,
    #   use_normalized_coordinates=True,
    #   line_thickness=8,
    #   min_score_thresh=0.40)

    # cv2.putText(frame, "FPS: {0:.2f}".format(frame_rate_calc), (30, 50), font, 1, (255, 255, 0), 2, cv2.LINE_AA)

    # All the results have been drawn on the frame, so it's time to display it.
    # cv2.imshow('Object detector', frame)
    #
    # t2 = cv2.getTickCount()
    # time1 = (t2 - t1) / freq
    # frame_rate_calc = 1 / time1

    # Press 'q' to quit
    if cv2.waitKey(1) == ord('q'):
      break

    rawCapture.truncate(0)

  camera.close()



if __name__ == '__main__':
  main()
