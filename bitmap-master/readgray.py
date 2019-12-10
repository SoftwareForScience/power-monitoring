from PIL import Image
import sys

name = sys.argv[1]

img = Image.open(name).convert('L')  # convert image to 8-bit grayscale
WIDTH, HEIGHT = img.size

data = list(img.getdata()) # convert image data to a list of integers
# convert that to 2D list (list of lists of integers)
data = [data[offset:offset+WIDTH] for offset in range(0, WIDTH*HEIGHT, WIDTH)]


# At this point the image's pixels are all in memory and can be accessed
# individually using data[row][col].

height = 0
sample = 0
# For example:
for row in data:
    print(' '.join('{:3}'.format(value) for value in row))
    for value in row:
        sample = sample + 1
for col in data:
    height = height + 1

width = sample / height
print(height)
print(width)
print(sample)

with open('value.txt', 'w') as f:
    f.write("%s" % sample)

with open('graycm.txt', 'w') as f:
    for row in data:
        f.write("%s\n" % row)

# Here's another more compact representation.
#chars = '@%#*+=-:. '  # Change as desired.
#scale = (len(chars)-1)/255.
#print()
#for row in data:
#    print(' '.join(chars[int(value*scale)] for value in row))
