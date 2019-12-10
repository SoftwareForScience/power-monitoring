from PIL import Image
img = Image.open('bram.bmp').convert('L')
img.save('gray.bmp')