# NSST_Optimum_Focused_Image_Generate

## What is NSST ?
NSST is a discrete form of Shearlet transform, and it differs from other multi-scale transformations by avoiding up-down samplers. NSST consists of two main stages, multi-scale and multi-directional separations.

### Multi-scale
<ul>
  <li>
     The Laplacian Pyramid (NSLP) without subsampling produces low and high frequency images whose size is the same as the size of the source image.
  </li>
</ul>

### Multi-directional
<ul>
  <li>
     Versatility is achieved by using different "combinations of Shear Filters" in the so-called polar (pseude-polar) coordinate
  </li>
</ul>

## NSST Steps
The process steps performed to obtain the NSST coefficients of an image of NxN size at a fixed resolution scale are as follows:

1. Laplacian pyramid is applied to the image. Low and High pass sub-images are obtained.

2. The fourier transformations of the high pass sub-images are calculated and transformed into the Polar coordinate system.

3. Bandpass filter is applied to Polar coordinate system transformations and Fourier transforms (FFT) of Shearlet coefficients are obtained.

4. The Inverse Fourier Transform (IFT) is applied to obtain the Shearlet coefficients and the transformation is performed to the Cartesian coordinate system.

## Generally Design

![image 1](https://github.com/fbasatemur/NSST_Optimum_Focused_Image_Generate/blob/main/screenshots/NSST_optimally_focused_image.jpeg)


1. Firstly, the input image must be converted to the YCbCr channel. At this stage, only Y channel will be used for NSST. You can use <b>ConvertBMPToYCbCr()</b> for this process. General formula :

```ìni  

    I = (16 + 0.257 * Red + 0.504 * Green +  0.098 * Blue)	   // Y  => Intensity 		  
    X = (128 - 0.148 * Red - 0.291 * Green + 0.439 * Blue)	   // Cb => X 	    
    Y = (128 + 0.439 * Red - 0.368 * Green - 0.071 * Blue)	   // Cr => Y 
    
```
for more see [ITU-R_BT.601](https://en.wikipedia.org/wiki/YCbCr#ITU-R_BT.601_conversion)

2. Intensity image given to NSST function. Low (AFK) and High (YFK) Frequency coefficients are obtained at its output. You can use **NsstDec1e()** for this process.

3. **"Fusion Selection Rule 1"** is applied for only AFK coefficients. This method is the process of taking the average of the AFK coefficients of each image.

4. **"Fusion Selection Rule 2"** is applied for only YFK coefficients. This method is the process of applying the absolute maximum to the YFK coefficients of each image.

5. **"Fusion Selection Rule 2"** is applied for the Cr (Y) channel of each image.

6. **"Fusion Selection Rule 2"** is applied for the Cb (X) channel of each image. 

7. Optimum focused intensity image is obtained. You can use **NsstRec1()** for this process. 

8. In the last step, an optimally focused color image is obtained. Conversion must be done from YCbCr to RGB space. General formula :

```ini
    // I => Intensity, X => Cb, Y => Cr 

    Red   = (1.164 * (I - 16) + 1.596 * (Y - 128));
    Green = (1.164 * (I - 16) - 0.392 * (X - 128) - 0.813 * (Y - 128));
    Blue  = (1.164 * (I - 16) + 2.017 * (X - 128));
    
```

## Test

The following is my optimum focused image when tested with 30 images in the "Images" folder:

![image 2](https://github.com/fbasatemur/NSST_Optimum_Focused_Image_Generate/blob/main/screenshots/ss1.jpg)

# Thanks !
<ul>
  <li>
    <h2><a href="https://scholar.google.com/citations?hl=tr&user=Mq8UBzQAAAAJ" target="_blank">Assoc. Prof. Hülya Doğan</a></h2>
  </li>
</ul>
