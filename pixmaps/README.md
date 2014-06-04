In order to load logos for display on this pixelboard you need to create a 16x16 raw image with pixels encoded as rgb565.

I'm using avconv (www.libav.org) to create these.

Here's a command line that works to create this file.

avconv -vcodec png -i logo-16x16.png -vcodec rawvideo -f rawvideo -pix_fmt rgb565le logo.raw
