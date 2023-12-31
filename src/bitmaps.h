

#pragma once


// Coverter (image to cpp bitmap): http://javl.github.io/image2cpp/ (used background black, inverted)
// Icon sources: https://publicdomainvectors.org/



// '64th-20b', 20x20px
extern const unsigned char epd_bitmap_64th_20b [] PROGMEM = {
	0x01, 0xc0, 0x00, 0x00, 0x40, 0x00, 0x00, 0x40, 0x00, 0x00, 0x40, 0x00, 0x00, 0x40, 0x00, 0x00, 
	0x40, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0x80, 0x00, 0x00, 
	0x00, 0x07, 0x03, 0x00, 0x08, 0x87, 0x00, 0x10, 0x05, 0x00, 0x16, 0x09, 0x00, 0x19, 0x09, 0x00, 
	0x10, 0x91, 0x00, 0x10, 0x9f, 0x80, 0x09, 0x01, 0x00, 0x06, 0x01, 0x00
};
// 'screw-alt1-20x32', 20x32px
const unsigned char epd_bitmap_screw_alt1_20x32 [] PROGMEM = {
	0x01, 0x08, 0x00, 0x07, 0x9e, 0x00, 0x1c, 0x93, 0x80, 0x30, 0xf0, 0xc0, 0x60, 0x00, 0x60, 0xc0, 
	0x00, 0x30, 0xff, 0xff, 0xf0, 0x02, 0x04, 0x00, 0x02, 0x04, 0x00, 0x02, 0x04, 0x00, 0x02, 0x04, 
	0x00, 0x02, 0x0c, 0x00, 0x02, 0x0c, 0x00, 0x02, 0x1c, 0x00, 0x03, 0xf0, 0x00, 0x03, 0x9c, 0x00, 
	0x00, 0x70, 0x00, 0x01, 0xcc, 0x00, 0x00, 0x78, 0x00, 0x01, 0xc8, 0x00, 0x01, 0x38, 0x00, 0x00, 
	0xe0, 0x00, 0x03, 0x38, 0x00, 0x00, 0xe0, 0x00, 0x03, 0x9c, 0x00, 0x00, 0xfc, 0x00, 0x03, 0x84, 
	0x00, 0x03, 0x0c, 0x00, 0x01, 0x98, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00
};



// 'wire_solid-20b', 20x20px
const unsigned char epd_bitmap_wire_solid_20b [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x01, 0x86, 0x00, 0x02, 0x01, 0x80, 0x04, 
	0x00, 0x80, 0x04, 0x00, 0x80, 0x0a, 0x01, 0x80, 0x09, 0xff, 0x00, 0x08, 0x01, 0x00, 0x10, 0x02, 
	0x00, 0x10, 0x02, 0x00, 0x10, 0x04, 0x00, 0x20, 0x04, 0x00, 0x20, 0x04, 0x00, 0x20, 0x08, 0x00, 
	0x40, 0x08, 0x00, 0x40, 0x10, 0x00, 0x40, 0x10, 0x00, 0x00, 0x00, 0x00
};
// 'wrench-20b', 20x20px
const unsigned char epd_bitmap_wrench_20b [] PROGMEM = {
	0x00, 0x1e, 0x00, 0x00, 0x33, 0x00, 0x00, 0x63, 0x00, 0x00, 0x46, 0x00, 0x00, 0x44, 0x60, 0x00, 
	0x4c, 0xf0, 0x00, 0x47, 0x90, 0x00, 0xc6, 0x10, 0x01, 0x80, 0x30, 0x03, 0x00, 0x60, 0x06, 0x0f, 
	0xc0, 0x0c, 0x18, 0x00, 0x18, 0x30, 0x00, 0x30, 0x60, 0x00, 0x60, 0xc0, 0x00, 0xc1, 0x80, 0x00, 
	0x83, 0x00, 0x00, 0x86, 0x00, 0x00, 0xcc, 0x00, 0x00, 0x78, 0x00, 0x00
};
// 'drill-alt1-20b', 20x20px
const unsigned char epd_bitmap_drill_alt1_20b [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xd8, 0x00, 0x40, 0x59, 0xa0, 0x7f, 
	0xdd, 0xb0, 0x7f, 0xd8, 0x00, 0x7f, 0xc0, 0x00, 0x3d, 0x00, 0x00, 0x3d, 0x00, 0x00, 0x3d, 0x00, 
	0x00, 0x7c, 0x00, 0x00, 0x78, 0x00, 0x00, 0x78, 0x00, 0x00, 0xfc, 0x00, 0x00, 0xfc, 0x00, 0x00, 
	0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'wire_stranded-20b', 20x20px
const unsigned char epd_bitmap_wire_stranded_20b [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x07, 0xcc, 0x00, 0x0c, 
	0xff, 0x00, 0x0f, 0xd8, 0x80, 0x0d, 0x9f, 0x80, 0x09, 0xf9, 0x80, 0x0f, 0x9f, 0x80, 0x09, 0xbd, 
	0x00, 0x09, 0xc9, 0x00, 0x08, 0x89, 0x00, 0x08, 0x89, 0x00, 0x0c, 0x89, 0x00, 0x0c, 0x89, 0x00, 
	0x0c, 0x85, 0x00, 0x0c, 0x45, 0x80, 0x0c, 0x44, 0x80, 0x0c, 0x44, 0x80
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 480)
const int epd_bitmap_allArray_LEN = 6;
const unsigned char* epd_bitmap_allArray[6] = {
	epd_bitmap_64th_20b,
	epd_bitmap_drill_alt1_20b,
	
	epd_bitmap_wire_solid_20b,
	epd_bitmap_wire_stranded_20b,
	epd_bitmap_wrench_20b
};












// // 'drill-alt1', 32x32px
// const unsigned char epd_bitmap_drill_alt1 [] PROGMEM = {
// 	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 	0x3f, 0xff, 0x00, 0x00, 0x7f, 0xff, 0x70, 0x00, 0x60, 0x01, 0x78, 0x00, 0x60, 0x03, 0x7c, 0xee, 
// 	0x7f, 0xff, 0x7e, 0x66, 0x7f, 0xff, 0x7e, 0x72, 0x7f, 0xff, 0x78, 0x00, 0x7f, 0xff, 0x00, 0x00, 
// 	0x1f, 0xfc, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x00, 0x0f, 0xd8, 0x00, 0x00, 0x1f, 0xd8, 0x00, 0x00, 
// 	0x1f, 0xd8, 0x00, 0x00, 0x1f, 0xc0, 0x00, 0x00, 0x3f, 0xc0, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 
// 	0x3f, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0xff, 0xc0, 0x00, 0x00, 0xff, 0xc0, 0x00, 0x00, 
// 	0xff, 0xc0, 0x00, 0x00, 0xff, 0xc0, 0x00, 0x00, 0xff, 0xc0, 0x00, 0x00, 0x7f, 0x80, 0x00, 0x00, 
// 	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
// };

// const unsigned char epd_bitmap_screw_alt1_inv [] PROGMEM = {
// 	0x00, 0x04, 0x20, 0x00, 0x00, 0x1e, 0x78, 0x00, 0x00, 0x72, 0x4e, 0x00, 0x00, 0xc3, 0xc3, 0x00, 
// 	0x01, 0x80, 0x01, 0x80, 0x03, 0x00, 0x00, 0xc0, 0x03, 0xff, 0xff, 0xc0, 0x00, 0x08, 0x10, 0x00, 
// 	0x00, 0x08, 0x10, 0x00, 0x00, 0x08, 0x10, 0x00, 0x00, 0x08, 0x10, 0x00, 0x00, 0x08, 0x30, 0x00, 
// 	0x00, 0x08, 0x30, 0x00, 0x00, 0x08, 0x70, 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x00, 0x0e, 0x70, 0x00, 
// 	0x00, 0x01, 0xc0, 0x00, 0x00, 0x07, 0x30, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x07, 0x20, 0x00, 
// 	0x00, 0x04, 0xe0, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x0c, 0xe0, 0x00, 0x00, 0x03, 0x80, 0x00, 
// 	0x00, 0x0e, 0x70, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x0e, 0x10, 0x00, 0x00, 0x0c, 0x30, 0x00, 
// 	0x00, 0x06, 0x60, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00
// };

// // 'wire-alt1', 32x32px
// const unsigned char epd_bitmap_wire_alt1 [] PROGMEM = {
// 	0x00, 0xf0, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x07, 0xfe, 0x00, 0x00, 0x07, 0xff, 0xc0, 0x00, 
// 	0x01, 0xff, 0xfc, 0x00, 0x01, 0xff, 0xff, 0x80, 0x0f, 0xff, 0x80, 0xc0, 0x01, 0xfe, 0x00, 0x60, 
// 	0x00, 0xfc, 0x00, 0x30, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x08, 
// 	0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 
// 	0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0xc0, 
// 	0x00, 0x00, 0x03, 0x80, 0x0f, 0xff, 0xfe, 0x00, 0x18, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 
// 	0x20, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 
// 	0x20, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xfc, 0x03, 0xff, 0xff, 0xfc
// };

// // 'wrench-32b', 32x32px
// const unsigned char epd_bitmap_wrench_32b [] PROGMEM = {
// 	0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x7f, 0x80, 0x00, 0x00, 0xe1, 0xc0, 0x00, 0x01, 0xc1, 0xc0, 
// 	0x00, 0x03, 0x83, 0x80, 0x00, 0x03, 0x07, 0x00, 0x00, 0x03, 0x0e, 0x0c, 0x00, 0x03, 0x0c, 0x1e, 
// 	0x00, 0x03, 0x0c, 0x3f, 0x00, 0x03, 0x0c, 0x73, 0x00, 0x03, 0x0f, 0xe3, 0x00, 0x07, 0x0f, 0xc3, 
// 	0x00, 0x0e, 0x00, 0x03, 0x00, 0x1c, 0x00, 0x07, 0x00, 0x38, 0x00, 0x0e, 0x00, 0x70, 0x00, 0x1c, 
// 	0x00, 0xe0, 0x0f, 0xf8, 0x01, 0xc0, 0x1f, 0xf0, 0x03, 0x80, 0x38, 0x00, 0x07, 0x00, 0x70, 0x00, 
// 	0x0e, 0x00, 0xe0, 0x00, 0x1c, 0x01, 0xc0, 0x00, 0x38, 0x03, 0x80, 0x00, 0x70, 0x07, 0x00, 0x00, 
// 	0xe0, 0x0e, 0x00, 0x00, 0xc0, 0x1c, 0x00, 0x00, 0xc0, 0x38, 0x00, 0x00, 0xc0, 0x70, 0x00, 0x00, 
// 	0xc0, 0xe0, 0x00, 0x00, 0xe1, 0xc0, 0x00, 0x00, 0x7f, 0x80, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00
// };

// // 'wire_stranded', 32x32px
// const unsigned char epd_bitmap_wire_stranded [] PROGMEM = {
// 	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf8, 0x00, 0x00, 0xe7, 0x04, 0x00, 
// 	0x03, 0xfc, 0x03, 0x00, 0x08, 0x0c, 0x02, 0x00, 0x08, 0x0c, 0x0f, 0xf8, 0x18, 0x0d, 0xff, 0x04, 
// 	0x18, 0x1f, 0xfc, 0x02, 0x13, 0xfc, 0x0c, 0x02, 0x1f, 0xd8, 0x0e, 0x0e, 0x38, 0x38, 0x0f, 0xf6, 
// 	0x20, 0x18, 0x0f, 0xe4, 0x20, 0x1f, 0xfc, 0x3c, 0x30, 0x33, 0xd0, 0x0c, 0x3f, 0xff, 0xf0, 0x0c, 
// 	0x27, 0x20, 0x38, 0x1c, 0x20, 0x20, 0x1f, 0xfc, 0x30, 0x30, 0x3b, 0x8c, 0x30, 0x3c, 0xe8, 0x0c, 
// 	0x30, 0x37, 0x88, 0x0c, 0x30, 0x30, 0x08, 0x0c, 0x30, 0x10, 0x0c, 0x0c, 0x30, 0x10, 0x0c, 0x0c, 
// 	0x30, 0x10, 0x0c, 0x0c, 0x30, 0x10, 0x04, 0x0c, 0x38, 0x08, 0x04, 0x04, 0x38, 0x08, 0x04, 0x04, 
// 	0x38, 0x08, 0x04, 0x04, 0x38, 0x08, 0x02, 0x04, 0x38, 0x0c, 0x02, 0x04, 0x38, 0x0c, 0x02, 0x04
// };

// const unsigned char epd_bitmap_wire_solid [] PROGMEM = {
// 	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// 	0x00, 0x03, 0xfc, 0x00, 0x00, 0x1c, 0x07, 0x00, 0x00, 0x20, 0x00, 0xc0, 0x00, 0x40, 0x00, 0x60, 
// 	0x00, 0x80, 0x00, 0x20, 0x00, 0x80, 0x00, 0x20, 0x00, 0xc0, 0x00, 0x20, 0x01, 0x40, 0x00, 0x60, 
// 	0x01, 0x30, 0x01, 0xc0, 0x01, 0x0f, 0x0f, 0x40, 0x02, 0x00, 0xf0, 0x80, 0x02, 0x00, 0x00, 0x80, 
// 	0x02, 0x00, 0x01, 0x00, 0x04, 0x00, 0x01, 0x00, 0x04, 0x00, 0x01, 0x00, 0x04, 0x00, 0x02, 0x00, 
// 	0x08, 0x00, 0x02, 0x00, 0x08, 0x00, 0x04, 0x00, 0x08, 0x00, 0x04, 0x00, 0x10, 0x00, 0x0c, 0x00, 
// 	0x10, 0x00, 0x08, 0x00, 0x10, 0x00, 0x08, 0x00, 0x20, 0x00, 0x10, 0x00, 0x20, 0x00, 0x10, 0x00, 
// 	0x60, 0x00, 0x20, 0x00, 0x40, 0x00, 0x20, 0x00, 0x40, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00
// };


// // // Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 48)
// // const int epd_bitmap_allArray_LEN = 1;
// // const unsigned char* epd_bitmap_allArray[1] = {
// // 	epd_bitmap_wrench_16b
// // };
