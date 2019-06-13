# Finding-Blobls-In-Legoland
Project developed for algorithms and data structures

"The city of LEGOLAND® is very lively! Several people walk and cycle around the central square as well as
near the hotel and the hospital! In the center of the square, the fountain gives fresh water to all the characters of this fantastic
City! Ice-cream is sold and even the Bóbi and the Tareco play merrily in the street "

However, for safety, the whole city is monitored by a set of video-surveillance cameras, which
monitor all activity in the city. The goal is that, if something goes wrong,
find out the culprit ... "

In this paper we intend to define data structures that allow searching for "BLOBS" in
images, based on color information and a certain "search tolerance" value. At the
digital image domain, a BLOB is defined as a region of the image that differs from the rest in
terms of some property (eg texture or brightness). In this work, due to
simplicity, we will simply analyze the color of each point (pixel) of the image.
As you will know, an image is represented digitally by a two-dimensional set (matrix) of
points (called pixels), each with 3 numeric values ​​(0..255) in the case of
color.

Thus, the objective of this work is to read a text file that represents a set
images, and the search by regions (BLOBs) of each of the images that correspond to a
determined by the user.

After reading the data files, the system should start by asking the user for information about
a color (R, G, and B) and a tolerance (d) should return the center positions in the image containing
connected regions close to that color.


**The text file to read has the following format:**


Image Name 1

Number of lines + Number of columns + Number of channels

Pixel (line 1, column 1, channel 1)

Pixel (line 1, column 1, channel 2)

Pixel (line 1, column 1, channel 3)

Pixel (line 1, column 2, channel 1)

...

Pixel (line 1, column 200, channel 3)

Pixel (line 2, column 1, channel 1)

...

Pixel (line 300, column 200, channel 3)

Image Name 2

...

**Example of text file:**

Test.jpg

10 10 3

150

112

135

121

...


