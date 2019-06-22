# TPU Object Detection

**If you run this python script from a SSH-terminal, please use the SSH -X option for the Xserver connection.**

1. Install the TPU via the [get started tutorial](https://coral.withgoogle.com/docs/accelerator/get-started/)
2. Go to the `coral-classification-detection` folder.
3. Run
```bash
python3 detect_video.py --model mobilenet_ssd_v2/mobilenet_ssd_v2_coco_quant_postprocess_edgetpu.tflite --label mobilenet_ssd_v2/coco_labels.txt
```