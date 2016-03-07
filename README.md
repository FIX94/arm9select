# arm9select
This is a very simple A9LH binary which allows you to hold down any button on start to select the file you want to boot, files should go into /arm9select
and follow the pattern of a.bin, b.bin, start.bin etc. If you want any of these files to also have backlight, create files in the /arm9select folder in
the pattern of a_bl, b_bl, start_bl etc. This project was made with the expectation of using my arm9loaderhax fork which does not enable the backlights
by default, you can find it over on https://github.com/FIX94/arm9loaderhax.

## Credits

This Project is based on A9LH by Jason Dellaluce  
sdmmc.c & sdmmc.h originally written by Normatt

Licensed under GPLv2 or any later version, refer to the LICENSE file included.

* Smealum and contributors for libctru
* Normmatt for sdmmc.c and .h, and also for .ld files and the log from XDS by ichfly that provided us some of the information needed to get screen init
* Christophe Devine for the SHA codes
* Archshift for i2c.c and .h
* Megazig for crypto.c and .h
* Patois for original BRAHMA code
* Smealum, Derrek, Plutoo for publishing the exploit
* Yellows8 and Plutoo as ideators of it
* [3dbrew community](http://3dbrew.org/)
* bilis/b1l1s for his screen init code, and work on inegrating it into stage 2
* dark_samus for work on integrating screen init into stage 2
