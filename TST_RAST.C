#include <osbind.h>
#include "raster.h"
#include "TronShapes.h"

int main()
{
	void *base = Physbase();

	plot_pix(base, 111, 111);
	plot_pix(base, 112, 112);
	plot_pix(base, 113, 113);
	plot_pix(base, 114, 114);
	plot_pix(base, 115, 115);
	plot_pix(base, 116, 116);
	plot_pix(base, 117, 117);
	plot_pix(base, 118, 118);
	plot_pix(base, 119, 119);
	
	p_h_ln(base, 110, 110, 10);
	p_h_ln(base, 110, 120, 10);
	p_v_ln(base, 110, 110, 10);
	p_v_ln(base, 120, 110, 10);
	
	p_btmp_8(base, 200,100,BIKE1[0]);
	p_btmp_8(base, 220,100,BIKE1[1]);
	p_btmp_8(base, 240,100,BIKE1[2]);
	p_btmp_8(base, 260,100,BIKE1[3]);
	
	p_btmp_8(base, 200,120,BIKE2[0]);
	p_btmp_8(base, 220,120,BIKE2[1]);
	p_btmp_8(base, 240,120,BIKE2[2]);
	p_btmp_8(base, 260,120,BIKE2[3]);
	
	p_btmp_8(base, 300,200, STICKMAN);
	p_btmp_8(base, 300,208, STICKMAN);
	p_btmp_8(base, 300,216, STICKMAN);
	
	return 0;
}
