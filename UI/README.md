## Image manage
For 42 students doing so_long, there's an easy way to load images and make animations..

Inside ui_images.c theres a function "images_load" that allows you to use miniibx to load up to 100 images and store them into an image array.

```mermaid
flowchart TD;
id2(copy filename);
id6{counter <= frames};
id7(Change filename using counter);
id8(Load image in array);
id11(END);

		Images_load--Reserve memory for \n filename & images-->id2
		id2--Initalize counter-->id6
		id6 -- Y --> id7 
		id7 --> id8
		id8 --Counter++--> id6
		id6 -- N --> id11
```